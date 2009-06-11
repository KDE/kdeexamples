/*  This file is part of the KDE project
    Copyright (C) 2009 Harald Fernengel <harry@kdevelop.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License version 2 as published by the Free Software Foundation.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

*/

#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <kmainwindow.h>
#include <kmenubar.h>
#include <kicon.h>

#include <solid/devicenotifier.h>
#include <solid/device.h>
#include <solid/genericinterface.h>

#include <QtGui>

class SolidItem : public QTreeWidgetItem
{
public:
    enum SolidItemType { SolidType = UserType + 42 };

    SolidItem(const Solid::Device &device)
        : QTreeWidgetItem(SolidType)
    {
        setText(0, device.udi());
        QString icon = device.icon();
        if (!icon.isEmpty())
            setIcon(0, KIcon(icon));
    }
};

class SolidBrowser : public QMainWindow
{
    Q_OBJECT
public:
    SolidBrowser(QWidget *parent = 0)
        : QMainWindow(parent)
    {
        QWidget *central = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout(central);

        view = new QTreeWidget;
        view->setColumnCount(1);
        view->setHeaderLabel("Solid UDI");
        connect(view, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
                SLOT(currentItemChanged(QTreeWidgetItem*)));

        details = new QTextBrowser;

        filterCombo = new QComboBox;
        QStringList filters = QStringList()
            << "No filter"
            << "Unknown"
            << "GenericInterface"
            << "Processor"
            << "Block"
            << "StorageAccess"
            << "StorageDrive"
            << "OpticalDrive"
            << "StorageVolume"
            << "OpticalDisc"
            << "Camera"
            << "PortableMediaPlayer"
            << "NetworkInterface"
            << "AcAdapter"
            << "Battery"
            << "Button"
            << "AudioInterface"
            << "DvbInterface"
            << "Video"
            << "SerialInterface"
            << "SmartCardReader";
        filterCombo->addItems(filters);
        connect(filterCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(populate()));

        QHBoxLayout *devicesLayout = new QHBoxLayout;
        devicesLayout->addWidget(new QLabel("Devices:"));
        devicesLayout->addStretch();
        devicesLayout->addWidget(new QLabel("Filter:"));
        devicesLayout->addWidget(filterCombo);

        layout->addLayout(devicesLayout);
        layout->addWidget(view);
        layout->addWidget(new QLabel("Details:"));
        layout->addWidget(details);

        QMenu *editMenu = menuBar()->addMenu("&Edit");
        QAction *reloadAction = editMenu->addAction("&Refresh", this, SLOT(populate()));
        reloadAction->setShortcut(QKeySequence::Refresh);

        setCentralWidget(central);
    }

public slots:
    void populate();

private slots:
    void currentItemChanged(QTreeWidgetItem *current);

private:
    QTreeWidget *view;
    QTextBrowser *details;
    QComboBox *filterCombo;
};

void SolidBrowser::currentItemChanged(QTreeWidgetItem *current)
{
    details->clear();

    // 0 pointer means selection was cleared, no more current item.
    if (!current || current->type() != SolidItem::SolidType)
        return;

    SolidItem *item = static_cast<SolidItem *>(current);
    const QString udi = item->text(0);
    details->append("<h3>Details for " + udi + "</h3>");

    Solid::Device device(udi);
    if (!device.isValid()) {
        details->append("<p>Invalid Device (it might have been removed?)</p>");
        return;
    }

    if (Solid::GenericInterface *iface = device.as<Solid::GenericInterface>()) {
        QString out = "<table><tr><th>Property</th><th>Value</th></tr>\n";
        const QMap<QString, QVariant> allProperties = iface->allProperties();
        for (QMap<QString, QVariant>::const_iterator it = allProperties.constBegin();
             it != allProperties.constEnd(); ++it) {
            QString row;
            QVariant val = it.value();
            row += "<tr><td align=\"right\">";
            row += Qt::escape(it.key());
            row += ": </td><td>";
            if (val.type() == QVariant::ByteArray) {
                // byte arrays are usually only used as arrays of bytes,
                // not 8-bit strings. Output them as hex
                row += val.toByteArray().toHex();
            } else {
                row += Qt::escape(it.value().toString());
            }
            row += "</td></tr>\n";
            out += row;
        }
        out += "</table>\n";
        details->append(out);
    }
}

static SolidItem *addParentItems(const Solid::Device &device, QHash<QString, SolidItem *> &deviceHash,
        QTreeWidget *view)
{
    const QString parentUdi = device.parentUdi();

    if (deviceHash.contains(parentUdi))
        return deviceHash.value(parentUdi);

    Solid::Device parentDevice = device.parent();
    SolidItem *parentItem = new SolidItem(parentDevice);
    deviceHash[parentUdi] = parentItem;

    const QString grandParentUdi = parentDevice.parentUdi();
    if (grandParentUdi.isEmpty()) {
        view->invisibleRootItem()->addChild(parentItem);
    } else {
        // add the grandparents recursively.
        SolidItem *grandParentItem = addParentItems(parentDevice, deviceHash, view);
        grandParentItem->addChild(parentItem);
    }
    return parentItem;
}

void SolidBrowser::populate()
{
    // wipe out all data
    view->clear();

    QHash<QString, SolidItem *> deviceHash;

    // get a list of devices to show
    QList<Solid::Device> allDevices;
    if (filterCombo->currentIndex() <= 0) {
        // show all devices
        allDevices = Solid::Device::allDevices();
    } else {
        // populate with all devices of the given type
        allDevices = Solid::Device::listFromType(
            Solid::DeviceInterface::stringToType(filterCombo->currentText()));
    }

    // create on QTreeWidgetItem per device
    foreach (const Solid::Device &device, allDevices) {
        deviceHash[device.udi()] = new SolidItem(device);
    }

    // sort them
    foreach (const Solid::Device &device, allDevices) {
        SolidItem *item = deviceHash[device.udi()];
        const QString parentUdi = device.parentUdi();
        if (parentUdi.isEmpty()) {
            view->invisibleRootItem()->addChild(item);
        } else {
            SolidItem *parentItem = deviceHash.value(parentUdi);
            if (!parentItem)
                parentItem = addParentItems(device, deviceHash, view);
            parentItem->addChild(item);
        }
    }

    view->expandAll();
}

int main (int argc, char *argv[])
{
    KAboutData aboutData("solid-browser",
                         0,
                         ki18n("Solid Browser"),
                         "0.1",
                         ki18n("Displays a Solid Device Tree"),
                         KAboutData::License_GPL,
                         ki18n("(c) 2009 Harald Fernengel"),
                         ki18n("Simple and quick hack for showing a solid device tree"),
                         "http://www.kde.org/",
                         "submit@bugs.kde.org");

    KCmdLineArgs::init(argc, argv, &aboutData);
    KApplication app;

    SolidBrowser browser;
    browser.populate();
    browser.show();

    return app.exec();
}

#include "main.moc"

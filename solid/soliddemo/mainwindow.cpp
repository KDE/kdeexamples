/*
 * Copyright 2011 Jon Ander Peñalba <jonan88@gmail.com>
 * Copyright 2009 Harald Fernengel <harry@kdevelop.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"

#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

#include <KComboBox>
#include <KIcon>
#include <KListWidget>
#include <KLocale>
#include <KTextBrowser>

#include <Solid/Device>
#include <Solid/GenericInterface>

MainWindow::MainWindow(QWidget *parent)
    : KMainWindow(parent)
{
  QWidget *central = new QWidget(this);
  QVBoxLayout *layout = new QVBoxLayout(central);

  view = new KListWidget(this);
  connect(view, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
          this, SLOT(currentItemChanged(QListWidgetItem*)));

  details = new KTextBrowser;

  filterCombo = new KComboBox;
  QStringList filters;
  filters << "No filter"
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
          << "SmartCardReader"
          << "InternetGateway"
          << "NetworkShare";
  filterCombo->addItems(filters);
  connect(filterCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(populate()));
  populate();

  QHBoxLayout *devicesLayout = new QHBoxLayout(this);
  devicesLayout->addWidget(new QLabel(i18n("Devices:"),this));
  devicesLayout->addStretch();
  devicesLayout->addWidget(new QLabel(i18n("Filter:"),this));
  devicesLayout->addWidget(filterCombo);

  layout->addLayout(devicesLayout);
  layout->addWidget(view);
  layout->addWidget(new QLabel(i18n("Properties:"),this));
  layout->addWidget(details);

  view->setMinimumSize(600, 300);
  details->setMaximumHeight(250);
  setCentralWidget(central);
}

void MainWindow::currentItemChanged(QListWidgetItem *current)
{
  details->clear();

  if (!current)
    return;

  const QString udi = current->text();
  details->append("<h3>" + udi + "</h3>");

  Solid::Device device(udi);
  if (!device.isValid()) {
    details->append(i18n("Invalid Device (it might have been removed?)"));
    return;
  }

  if (Solid::GenericInterface *iface = device.as<Solid::GenericInterface>()) {
    const QMap<QString,QVariant> allProperties = iface->allProperties();
    if (allProperties.isEmpty())
      return;
    QString out = "<table><tr><th>" + i18n("Property") + "</th><th>" + i18n("Value") + "</th></tr>\n";
    QMap<QString,QVariant>::const_iterator it;
    for (it = allProperties.constBegin(); it != allProperties.constEnd(); ++it) {
      QVariant val = it.value();
      out += "<tr><td>";
      out += Qt::escape(it.key());
      out += ": </td><td>";
      if (val.type() == QVariant::ByteArray) {
        // byte arrays are usually only used as arrays of bytes,
        // not 8-bit strings. Output them as hex
        out += val.toByteArray().toHex();
      } else {
        out += Qt::escape(it.value().toString());
      }
      out += "</td></tr>\n";
    }
    out += "</table>\n";
    details->append(out);
  }
}

void MainWindow::populate()
{
  view->clear();

  QList<Solid::Device> devices;
  if (filterCombo->currentIndex() <= 0) {
    devices = Solid::Device::allDevices();
  } else {
    devices = Solid::Device::listFromType(Solid::DeviceInterface::stringToType(filterCombo->currentText()));
  }

  foreach (const Solid::Device &device, devices) {
    new QListWidgetItem(KIcon(device.icon()), device.udi(), view);
  }
}

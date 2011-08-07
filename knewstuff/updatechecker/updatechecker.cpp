/*
    Copyright (c) 2010 Frederik Gladhorn <gladhorn@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#include "updatechecker.h"

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>
#include <QtGui/QListWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

#include <kpushbutton.h>
#include <kdebug.h>

#include <KDE/KLocale>

#include <knewstuff3/downloadmanager.h>

UpdateChecker::UpdateChecker()
    : KMainWindow()
{
    setCaption(i18n("Plasma Applet Update Check Example"));
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    
    KPushButton* newestButton = new KPushButton(i18n("Show Newest Plasmoids"), this);
    connect(newestButton, SIGNAL(clicked()), this, SLOT(showNewest()));
    layout->addWidget(newestButton);
    
    m_label = new QLabel(i18n("Updates for installed applets:"), this);
    layout->addWidget(m_label);
    
    m_list = new QListWidget(this);
    layout->addWidget(m_list);
    
    KPushButton* updateButton = new KPushButton(i18n("Install"), this);
    connect(updateButton, SIGNAL(clicked()), this, SLOT(installUpdate()));
    layout->addWidget(updateButton);
    
    m_downloadManager = new KNS3::DownloadManager("plasmoids.knsrc", this);
    connect(m_downloadManager, SIGNAL(searchResult(KNS3::Entry::List)), this, SLOT(updatesFound(KNS3::Entry::List)));
    connect(m_downloadManager, SIGNAL(entryStatusChanged(KNS3::Entry)), this, SLOT(entryStatusChanged(KNS3::Entry)));
    m_downloadManager->checkForUpdates();
}

void UpdateChecker::updatesFound(const KNS3::Entry::List& updates)
{
    m_updates = updates;
    foreach (const KNS3::Entry& entry, updates) {
        new QListWidgetItem(entry.name(), m_list);
    }
}

void UpdateChecker::installUpdate()
{
    int row = m_list->currentRow();
    if (row >= 0) {
        m_downloadManager->installEntry(m_updates.at(row));
    }
}

void UpdateChecker::entryStatusChanged(const KNS3::Entry& entry)
{
    kDebug() << "Status changed: " << entry.name();
    if (entry.status() == KNS3::Entry::Installed) {
        m_label->setText(i18n("Updated/Installed: \"%1\"", entry.name()));
    }
}

void UpdateChecker::showNewest()
{
    m_list->clear();
    m_downloadManager->setSearchOrder(KNS3::DownloadManager::Newest);
    m_downloadManager->search();
    m_label->setText(i18n("Newest plasma applets:"));
}

#include "updatechecker.moc"

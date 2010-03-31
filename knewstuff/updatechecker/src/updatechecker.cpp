/*
 * updatechecker.cpp
 *
 * Copyright (C) 2008 Frederik Gladhorn <gladhorn@kde.org>
 */
#include "updatechecker.h"

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

#include <kdebug.h>

#include <KDE/KLocale>

#include <knewstuff3/downloadmanager.h>

UpdateChecker::UpdateChecker()
    : KMainWindow()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    
    m_label = new QLabel(i18n("Plasma Applet Update Check Example"), this);
    layout->addWidget(m_label);
    
    m_list = new QListWidget(this);
    layout->addWidget(m_list);

    QPushButton* updateButton = new QPushButton(i18n("Install"), this);
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
        QListWidgetItem* item = new QListWidgetItem(entry.name(), m_list);
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
        m_label->setText(i18n("Updated \"%1\"", entry.name()));
    }
}


#include "updatechecker.moc"

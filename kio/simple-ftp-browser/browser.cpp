/*
 * Copyright 2011 Jon Ander Peñalba <jonan88@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "browser.h"

#include <QVBoxLayout>

#include <KIO/Job>
#include <KListWidget>
#include <KUrl>

Browser::Browser() : QWidget(NULL)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    list_widget = new KListWidget(this);
    layout->addWidget(list_widget);
    // Create a job that lists the contents of the FTP server
    KIO::ListJob *job = KIO::listDir(KUrl("ftp://ftp.kde.org/pub/kde/"));
    connect(job, SIGNAL(entries(KIO::Job*, const KIO::UDSEntryList&)), this, SLOT(showEntries(KIO::Job*, const KIO::UDSEntryList&)));
}

void Browser::showEntries(KIO::Job *job, const KIO::UDSEntryList &list)
{
    Q_UNUSED(job);
    bool dir;
    QString name;
    foreach (const KIO::UDSEntry& entry, list) {
        // Get the info of every entry
        name = entry.stringValue(KIO::UDSEntry::UDS_NAME);
        dir = entry.isDir();
        // Add the entry to the list
        QListWidgetItem *item = new QListWidgetItem(name, list_widget);
        if (dir)
            item->setForeground(QBrush(QColor(0, 0, 255)));
        list_widget->addItem(item);
    }
}

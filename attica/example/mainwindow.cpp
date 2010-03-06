/*
    This file is part of KDE.

    Copyright (c) 2009 Frederik Gladhorn <gladhorn@kde.org>

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

#include "mainwindow.h"

#include <KDebug>
#include <QVBoxLayout>

#include <attica/providermanager.h>

#include "simplepersonrequest.h"
#include "contentdownload.h"
#include "contentcreation.h"

MainWindow::MainWindow(QWidget *parent) : KMainWindow(parent)
{
    connect(&m_manager, SIGNAL(defaultProvidersLoaded()), SLOT(providersLoaded()));
    m_manager.loadDefaultProviders();
}

void MainWindow::providersLoaded()
{
    if (!m_manager.providers().isEmpty()) {
        m_provider = m_manager.providerByUrl(QUrl("https://api.opendesktop.org/v1/"));
        if (!m_provider.isValid()) {
            kDebug() << "Could not find opendesktop.org provider.";
            return;
        }

        QTabWidget* mainWidget = new QTabWidget(this);
        setCentralWidget(mainWidget);

        SimplePersonRequest* personWidget = new SimplePersonRequest(m_provider, this);
        mainWidget->addTab(personWidget, tr("Person Search"));

        ContentDownload* contentWidget = new ContentDownload(m_provider, this);
        mainWidget->addTab(contentWidget, tr("Content"));

        ContentCreation* contentCreationWidget = new ContentCreation(m_provider, this);
        mainWidget->addTab(contentCreationWidget, tr("Add Content"));
    }
}
#include "mainwindow.moc"


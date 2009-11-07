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

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
    connect(&m_pm, SIGNAL(providersChanged()), SLOT(providersChanged()));
    m_pm.loadDefaultProviders();
 
    setupGUI();
}

void MainWindow::providersChanged()
{
    if (!m_pm.providers().isEmpty()) {
        m_provider = m_pm.providers().first();
        kDebug() << "Using provider: " << m_provider.baseUrl().toString();

        QTabWidget* mainWidget = new QTabWidget(this);
        setCentralWidget(mainWidget);

        ContentCreation* contentCreationWidget = new ContentCreation(m_provider, this);
        mainWidget->addTab(contentCreationWidget, tr("Add Content"));

        ContentDownload* contentWidget = new ContentDownload(m_provider, this);
        mainWidget->addTab(contentWidget, tr("Content"));

        SimplePersonRequest* personWidget = new SimplePersonRequest(m_provider, this);
        mainWidget->addTab(personWidget, tr("Person Search"));
    }
}


#include "mainwindow.moc"

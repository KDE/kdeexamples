/*
    This file is part of KDE.

    Copyright (c) 2009 Frederik Gladhorn <gladhorn@kde.org>
    Copyright (c) 2010 Martin Sandsmark <martin.sandsmark@kde.org>

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

#include "privatedata.h"

#include <KDebug>
#include <QtGui/QBoxLayout>
#include <QtGui/QSpacerItem>

#include <attica/privatedata.h>
#include <attica/itemjob.h>

#include "ui_privatedata.h"

PrivateDataView::PrivateDataView(Attica::ProviderManager *manager, QWidget* parent)
    : QWidget(parent), m_ui(0)
{
    m_provider = manager->providerByUrl(QUrl("http://localhost/ocs/v1.php/"));
    if (!m_provider.isValid()) {
        setLayout(new QVBoxLayout);
        layout()->addWidget(new QLabel("Please add an OCS-compliant provider for localhost in System Settings."));
        return;
    }

    m_ui = new Ui::PrivateDataWidget;
    m_ui->setupUi(this);

    QString username, password;
    if (m_provider.loadCredentials(username, password)) {
        m_ui->nick->setText(username);
        m_ui->password->setText(password);
    }

    connect(m_ui->fetchButton, SIGNAL(clicked()), SLOT(fetch()));
    connect(m_ui->submitButton, SIGNAL(clicked()), SLOT(submit()));
}

PrivateDataView::~PrivateDataView()
{
    delete m_ui;
}

void PrivateDataView::fetch()
{
    if (!m_provider.isValid()) return;

    if (!m_ui->nick->text().isEmpty() && !m_ui->nick->text().isEmpty())
        m_provider.saveCredentials(m_ui->nick->text(), m_ui->password->text());

    m_ui->keyValueView->clear();

    Attica::ItemJob<Attica::PrivateData>* job = m_provider.requestPrivateData();
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(fetchJobFinished(Attica::BaseJob*)));
    job->start();
}

void PrivateDataView::submit()
{
    if (!m_provider.isValid()) return;

    if (m_ui->key->text().isEmpty() || m_ui->value->text().isEmpty())
        return;

    Attica::PostJob *job = m_provider.setPrivateData("exampleapplication", m_ui->key->text(), m_ui->value->text());
    m_ui->key->clear();
    m_ui->value->clear();
    job->start();
}

void PrivateDataView::fetchJobFinished(Attica::BaseJob *job)
{
    kDebug() << Q_FUNC_INFO;
    Attica::ItemJob<Attica::PrivateData> *dataJob = static_cast< Attica::ItemJob<Attica::PrivateData> * >( job );
    if( dataJob->metadata().error() == Attica::Metadata::NoError ) {
        Attica::PrivateData p(dataJob->result());
        const QStringList &keys = p.keys();
        if (keys.isEmpty()) {
            m_ui->keyValueView->addItem("[empty]");
            return;
        }
        Q_FOREACH(const QString &key, keys) {
            m_ui->keyValueView->addItem(key + " : " + p.attribute(key) + " (" + p.timestamp(key).toString() + ")");
        }
    } else {
        m_ui->keyValueView->clear();
        m_ui->keyValueView->addItem("Error while fetching private data!");
        if (dataJob->metadata().error() == Attica::Metadata::OcsError) {
            m_ui->keyValueView->addItem("Server-side OCS error!");
        } else {
            m_ui->keyValueView->addItem("Network error!");
        }
        m_ui->keyValueView->addItem("Status message: " + dataJob->metadata().message());
    }
}

void PrivateDataView::submitJobFinished(Attica::BaseJob *job)
{
    kDebug() << Q_FUNC_INFO;
    Attica::PostJob *postJob = static_cast<Attica::PostJob*>(job);

    if (postJob->metadata().error() != Attica::Metadata::NoError) {
        m_ui->keyValueView->clear();
        m_ui->keyValueView->addItem("Error while setting private data!");
        if (postJob->metadata().error() == Attica::Metadata::OcsError) {
            m_ui->keyValueView->addItem("Server-side OCS error!");
        } else {
            m_ui->keyValueView->addItem("Network error!");
        }
        m_ui->keyValueView->addItem("Status message: " + postJob->metadata().message());
    }

}


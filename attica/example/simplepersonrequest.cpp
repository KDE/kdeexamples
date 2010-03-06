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

#include "simplepersonrequest.h"

#include <KDebug>
#include <QtGui/QBoxLayout>
#include <QtGui/QSpacerItem>

#include <attica/person.h>
#include <attica/itemjob.h>

SimplePersonRequest::SimplePersonRequest(Attica::Provider provider, QWidget* parent)
    : QWidget(parent)
    , m_provider(provider)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    mNickNameLineEdit = new KLineEdit();
    layout->addWidget(mNickNameLineEdit);

    mNameLabel = new QLabel(this);
    mNameLabel->setText("Name");
    layout->addWidget(mNameLabel);

    mLocationLabel = new QLabel(this);
    mLocationLabel->setText("Location");
    layout->addWidget(mLocationLabel);

    mNick = "frank";
    mNickNameLineEdit->setText(mNick);
    connect(mNickNameLineEdit, SIGNAL(returnPressed(QString)), SLOT(nickChanged(QString)));
    nickChanged(mNick);
}

void SimplePersonRequest::nickChanged(const QString& nick)
{
    mNick = nick;
    Attica::ItemJob<Attica::Person>* job = m_provider.requestPerson(mNick);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(onPersonJobFinished(Attica::BaseJob*)));
    job->start();
}

void SimplePersonRequest::onPersonJobFinished( Attica::BaseJob *job )
{
    kDebug() << "onJobFinished";
    Attica::ItemJob<Attica::Person> *personJob = static_cast< Attica::ItemJob<Attica::Person> * >( job );
    if( personJob->metadata().error() == Attica::Metadata::NoError ) {
        Attica::Person p(personJob->result());
        mNameLabel->setText(p.firstName() + ' ' + p.lastName());
        mLocationLabel->setText(p.city());
    } else {
        mNameLabel->setText("Could not fetch information.");
    }
}

#include "simplepersonrequest.moc"

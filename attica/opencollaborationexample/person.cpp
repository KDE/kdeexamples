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

#include "person.h"

#include <KDebug>
#include <QtGui/QBoxLayout>
#include <QtGui/QSpacerItem>

#include <attica/person.h>
#include <attica/itemjob.h>

#include "ui_person.h"

SimplePersonRequest::SimplePersonRequest(Attica::Provider provider, QWidget* parent)
    : QWidget(parent)
    , m_provider(provider)
{
    m_ui = new Ui::PersonWidget;
    m_ui->setupUi(this);

    mNick = "frank";
    m_ui->nick->setText(mNick);
    connect(m_ui->nick, SIGNAL(returnPressed(QString)), SLOT(nickChanged(QString)));
    nickChanged(mNick);
}

SimplePersonRequest::~SimplePersonRequest()
{
    delete m_ui;
}

void SimplePersonRequest::nickChanged(const QString& nick)
{
    mNick = nick;
    Attica::ItemJob<Attica::Person>* job = m_provider.requestPerson(mNick);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(personJobFinished(Attica::BaseJob*)));
    job->start();
}

void SimplePersonRequest::personJobFinished( Attica::BaseJob *job )
{
    kDebug() << "onJobFinished";
    Attica::ItemJob<Attica::Person> *personJob = static_cast< Attica::ItemJob<Attica::Person> * >( job );
    if( personJob->metadata().error() == Attica::Metadata::NoError ) {
        Attica::Person p(personJob->result());
        m_ui->name->setText(p.firstName() + ' ' + p.lastName());
        m_ui->city->setText(p.city());
        m_ui->country->setText(p.country());
        m_ui->messenger->setText(p.extendedAttribute("messenger1") + " (" + p.extendedAttribute("messengertype1") + ')');
        m_ui->homepage->setText(p.homepage());
        m_ui->project->setText(p.extendedAttribute("communityrole"));
        m_ui->languages->setText(p.extendedAttribute("languages"));
    } else {
        m_ui->name->setText(i18n("Could not find person."));
    }
}

#include "person.moc"


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

#ifndef PRIVATEDATA_H
#define PRIVATEDATA_H

#include <QtGui/QLabel>
#include <KLineEdit>
#include <QListWidget>
#include <attica/provider.h>
#include <attica/providermanager.h>

namespace Ui {
    class PrivateDataWidget;
}

class PrivateDataView : public QWidget
{
    Q_OBJECT

public:
    PrivateDataView(Attica::ProviderManager* manager, QWidget* parent = 0);
    ~PrivateDataView();

public Q_SLOTS:
    void fetch();
    void submit();
    void fetchJobFinished(Attica::BaseJob *job);
    void submitJobFinished(Attica::BaseJob *job);
    
private:
    Attica::Provider m_provider;
    Ui::PrivateDataWidget * m_ui;
};

#endif // PRIVATEDATA_H

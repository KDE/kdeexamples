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

#ifndef SIMPLEPERSONREQUEST_H
#define SIMPLEPERSONREQUEST_H

#include "../lib/provider.h"
#include <KLineEdit>
#include <QtGui/QLabel>

class SimplePersonRequest :public QWidget
{
    Q_OBJECT
public:
    
    SimplePersonRequest(Attica::Provider provider, QWidget* parent = 0);

public Q_SLOTS:
    void nickChanged(const QString& nick);
    void onPersonJobFinished( Attica::BaseJob *job );
    
private:
    KLineEdit* mLineEdit;
    QLabel* mNameLabel;
    QLabel* mPictureLabel;
    QString mNick;
    Attica::Provider m_provider;
};

#endif // SIMPLEPERSONREQUEST_H

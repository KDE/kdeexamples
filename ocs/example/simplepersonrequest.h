/***************************************************************************
    Copyright 2009 Frederik Gladhorn <gladhorn@kde.org>
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

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

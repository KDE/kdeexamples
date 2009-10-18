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


#ifndef CONTENTCREATION_H
#define CONTENTCREATION_H

#include "../lib/provider.h"

#include <QtGui/QLabel>

#include "ui_contentcreation.h"

class ContentCreation : public QWidget
{
    Q_OBJECT
public:
    ContentCreation(Attica::Provider provider, QWidget* parent = 0);
    
public Q_SLOTS:
    void categoriesLoaded(Attica::BaseJob *job);
    void categoryChanged();
    void contentAdded(Attica::BaseJob*);

    void submit();
    
private:    
    Attica::Provider m_provider;    
    Ui::ContentCreation ui;
    
};

#endif


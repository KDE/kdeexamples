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


#ifndef CONTENTDOWNLOAD_H
#define CONTENTDOWNLOAD_H

#include "../lib/provider.h"

#include <QtGui/QLabel>

#include "ui_contentdownload.h"

class ContentDownload : public QWidget
{
    Q_OBJECT
public:
    ContentDownload(Attica::Provider provider, QWidget* parent = 0);
    
public Q_SLOTS:
    void categoriesLoaded(Attica::BaseJob *job);
    void categorySelected(int index);
    void categoryContentsLoaded(Attica::BaseJob*);
    
private:
    Attica::Provider m_provider;    
    Ui::ContentDownload ui;
};

#endif // CONTENTDOWNLOAD_H

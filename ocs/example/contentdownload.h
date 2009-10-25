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
    void categoryChanged();
    void updateContentsList();
    void nextPage();
    void categoryContentsLoaded(Attica::BaseJob*);
    void selectedContentChanged(QTreeWidgetItem*,QTreeWidgetItem*);
    void download();
    void downloadLinkLoaded(Attica::BaseJob*);
    
    void voteGood();
    void voteBad();
    
private:
    void vote(bool positive);
    
    Attica::Provider m_provider;    
    Ui::ContentDownload ui;
    
    int m_page;
};

#endif // CONTENTDOWNLOAD_H

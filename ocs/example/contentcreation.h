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

#ifndef CONTENTCREATION_H
#define CONTENTCREATION_H

#include <attica/provider.h>

#include <QtGui/QLabel>
#include <QBuffer>

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
    void uploadFile();
    void uploadPreview1();
    void uploadPreview2();
    void uploadPreview3();

    void deleteFile();
    void deletePreview1();
    
    void fileUploadFinished(Attica::BaseJob*);

private:
    void doUpload(const QString& index, const QString& filePath);
    
    Attica::Provider m_provider;    
    Ui::ContentCreation ui;

    bool m_editMode;
    QString m_contentId;
    QByteArray m_byteArray;
};

#endif


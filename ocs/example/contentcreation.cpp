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

#include "contentcreation.h"

#include "../lib/category.h"
#include "../lib/content.h"
#include "../lib/listjob.h"
#include "../lib/content.h"
#include <QtGui/QTreeWidgetItem>
#include <KDebug>
#include <downloaditem.h>
#include <QtGui/QMessageBox>
#include <postjob.h>
#include <QFile>
#include <QtCore/QFileInfo>

using namespace Attica;

ContentCreation::ContentCreation(Attica::Provider provider, QWidget* parent)
    : QWidget(parent)
    , m_provider(provider)
    , m_editMode(false)
{
    ui.setupUi(this);
    
    connect(ui.category, SIGNAL(currentIndexChanged(int)), SLOT(categoryChanged()));
    connect(ui.submitButton, SIGNAL(clicked()), SLOT(submit()));
    
    connect(ui.upload, SIGNAL(clicked()), SLOT(uploadFile()));
    connect(ui.uploadPreview1Button, SIGNAL(clicked()), SLOT(uploadPreview1()));
    connect(ui.uploadPreview2Button, SIGNAL(clicked()), SLOT(uploadPreview2()));
    connect(ui.uploadPreview3Button, SIGNAL(clicked()), SLOT(uploadPreview3()));

    connect(ui.deleteFile, SIGNAL(clicked()), SLOT(deleteFile()));
    connect(ui.deletePreview1, SIGNAL(clicked()), SLOT(deletePreview1()));
    
    // get the available categories from the server
    ListJob<Category>* job = m_provider.requestCategories();
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(categoriesLoaded(Attica::BaseJob*)));
    job->start();
}

void ContentCreation::categoriesLoaded(Attica::BaseJob* job)
{
    ListJob<Category>* listJob = static_cast<Attica::ListJob<Attica::Category>*>(job);
    Category::List categories = listJob->itemList();
    
    Q_FOREACH(Category category, categories) {
        ui.category->addItem(category.name(), category.id());
    }
    ui.category->model()->sort(0);
}

void ContentCreation::categoryChanged()
{
}

void ContentCreation::submit()
{
    // get the currently selected category
    Category category;
    category.setId(ui.category->itemData(ui.category->currentIndex()).toString());

    // fill in the content object
    Content content;
    content.setName(ui.name->text());

    content.addAttribute("description", ui.description->text());
    content.addAttribute("changelog", ui.changelog->text());
    content.addAttribute("version", ui.version->text());
    content.addAttribute("downloadlink1", ui.link1->text());
    content.addAttribute("downloadlink2", ui.link2->text());
    content.addAttribute("homepage1", ui.homepage->text());
    content.addAttribute("blog1", ui.blog->text());

    if (!m_editMode) {
        ItemPostJob<Content>* job = m_provider.addNewContent(category, content);
        connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(contentAdded(Attica::BaseJob*)));
        job->start();
    } else {
        ItemPostJob<Content>* job = m_provider.editContent(category, m_contentId, content);
        connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(contentAdded(Attica::BaseJob*)));
        job->start();
    }
}

void ContentCreation::contentAdded(Attica::BaseJob* baseJob)
{
    ItemPostJob<Content> * job = static_cast<ItemPostJob<Content> *>(baseJob);
    QString id = job->result().id();
    QMessageBox::information(0, "Content Added", id);

    if (!id.isEmpty()) {
        ui.addFileGroup->setEnabled(true);
    }

    m_contentId = id;
    ui.contentId.setText(m_contentId);

    m_editMode = true;
}

void ContentCreation::uploadFile()
{
    doUpload(QString(), ui.uploadFile->url().toLocalFile());
}

void ContentCreation::uploadPreview1()
{
    doUpload("1", ui.uploadPreview1->url().toLocalFile());
}

void ContentCreation::uploadPreview2()
{
    doUpload("2", ui.uploadPreview2->url().toLocalFile());
}

void ContentCreation::uploadPreview3()
{
    doUpload("3", ui.uploadPreview3->url().toLocalFile());
}

void ContentCreation::doUpload(const QString& index, const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Upload", QString("File not found: %1").arg(ui.uploadFile->text()));
        return;
    }
    
    QByteArray fileContents;
    fileContents.append(file.readAll());
    file.close();

    QString fileName = QFileInfo(path).fileName();

    PostJob* job;
    if (index.isEmpty()) {
        job = m_provider.setDownloadFile(m_contentId, fileName, fileContents);
    } else {
        job = m_provider.setPreviewImage(m_contentId, index, fileName, fileContents);
    }
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(fileUploadFinished(Attica::BaseJob*)));
    job->start();

}

void ContentCreation::deleteFile()
{
    m_provider.deleteDownloadFile(m_contentId);
}

void ContentCreation::deletePreview1()
{
    m_provider.deletePreviewImage(m_contentId, "1");
}


void ContentCreation::fileUploadFinished(BaseJob* )
{
    QMessageBox::information(0, "Content Added", "File Uploaded");
}

#include "contentcreation.moc"


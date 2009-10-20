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



#include "contentcreation.h"

#include "../lib/category.h"
#include "../lib/content.h"
#include "../lib/listjob.h"
#include "../lib/content.h"
#include <QtGui/QTreeWidgetItem>
#include <KDebug>
#include <downloaditem.h>
#include <qt4/QtGui/QMessageBox>
#include <postjob.h>
#include <QFile>

using namespace Attica;

ContentCreation::ContentCreation(Attica::Provider provider, QWidget* parent)
    : QWidget(parent)
    , m_provider(provider)
{
    ui.setupUi(this);
    
    connect(ui.category, SIGNAL(currentIndexChanged(int)), SLOT(categoryChanged()));
    connect(ui.submitButton, SIGNAL(clicked()), SLOT(submit()));
    connect(ui.upload, SIGNAL(clicked()), SLOT(uploadFile()));
        
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
    
    ItemPostJob<Content>* job = m_provider.addNewContent(category, content);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(contentAdded(Attica::BaseJob*)));
    job->start();
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
}

void ContentCreation::uploadFile()
{
    /*
    m_file = new QFile("/home/frederik/testfile.txt"); //ui.uploadFile);
    if (!m_file->open(QIODevice::ReadOnly)) {
         return;
    }
    
    if (m_file->isReadable()) {
        qDebug() << "File contents: " << m_file->readAll();
        
        PostJob* job = m_provider.setDownloadFile(m_contentId, m_file);
        connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(fileUploadFinished(Attica::BaseJob*)));
        job->start();
    } else {
        qDebug() << "file not readable";
    }
    */

    //m_file = new QFile("/home/frederik/testfile.txt");
    m_byteArray.append("localfile=");
    m_byteArray.append("hello world");

    
    
    m_buffer.setData(m_byteArray);

qDebug() << m_byteArray;
    
    PostJob* job = m_provider.setDownloadFile(m_contentId, &m_buffer);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(fileUploadFinished(Attica::BaseJob*)));
    job->start();
}

void ContentCreation::fileUploadFinished(BaseJob* )
{
    QMessageBox::information(0, "Content Added", "File Uploaded");
    //m_file->close();
    //delete m_file;
}

#include "contentcreation.moc"


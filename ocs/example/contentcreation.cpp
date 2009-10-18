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

using namespace Attica;

ContentCreation::ContentCreation(Attica::Provider provider, QWidget* parent)
    : QWidget(parent)
    , m_provider(provider)
{
    ui.setupUi(this);
    
    connect(ui.category, SIGNAL(currentIndexChanged(int)), SLOT(categoryChanged()));
    connect(ui.submitButton, SIGNAL(clicked()), SLOT(submit()));
        
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
    
    PostJob* job = m_provider.addNewContent(category, content);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(contentAdded(Attica::BaseJob*)));
    job->start();
}

void ContentCreation::contentAdded(Attica::BaseJob* job)
{
    QMessageBox::information(0, "Content Added", "blah");
}


#include "contentcreation.moc"


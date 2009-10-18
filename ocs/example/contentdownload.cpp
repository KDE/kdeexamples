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



#include "contentdownload.h"

#include "../lib/category.h"
#include "../lib/content.h"
#include "../lib/listjob.h"
#include <QtGui/QStandardItemModel>

using namespace Attica;

ContentDownload::ContentDownload(Attica::Provider provider, QWidget* parent)
    : QWidget(parent)
    , m_provider(provider)
{
    ui.setupUi(this);
    
    connect(ui.category, SIGNAL(currentIndexChanged()), SLOT(updateContentsList()));
    connect(ui.search, SIGNAL(returnPressed()), SLOT(updateContentsList()));
    
    // get the available categories from the server
    ListJob<Category>* job = m_provider.requestCategories();
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(categoriesLoaded(Attica::BaseJob*)));
}

void ContentDownload::categoriesLoaded(Attica::BaseJob* job)
{
    ListJob<Category>* listJob = static_cast<Attica::ListJob<Attica::Category>*>(job);
    Category::List categories = listJob->itemList();
    
    Q_FOREACH(Category category, categories) {
        ui.category->addItem(category.name(), category.id());
    }
    ui.category->model()->sort(0);
}

void ContentDownload::updateContentsList()
{
    ui.contentList->clear();
    
    QString name = ui.category->currentText();
    QString id = ui.category->itemData(ui.category->currentIndex()).toString();
    ui.currentCategoryLabel->setText(name);
    ui.currentCategoryIdLabel->setText(id);
    
    Category cat;
    cat.setId(id);
    Category::List catList;
    catList << cat;
    
    QString searchString(ui.search->text());
    ListJob<Content>* job = m_provider.searchContents(catList, searchString);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(categoryContentsLoaded(Attica::BaseJob*)));
}

void ContentDownload::categoryContentsLoaded(BaseJob* job)
{
    ListJob<Content>* listJob = static_cast<ListJob<Content>*>(job);
    Content::List contents = listJob->itemList();
    
    Q_FOREACH(Content content, contents) {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(content.name());
        ui.contentList->addItem(item);
    }
    
    ui.countLabel->setText(tr("Total: %1").arg(listJob->metadata().totalItems));
        
}


#include "contentdownload.moc"

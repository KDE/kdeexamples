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

#include "contentdownload.h"

#include <QtGui/QTreeWidgetItem>
#include <QtGui/QMessageBox>

#include <KDebug>

#include <attica/category.h>
#include <attica/content.h>
#include <attica/downloaditem.h>
#include <attica/listjob.h>
#include <attica/postjob.h>

using namespace Attica;

ContentDownload::ContentDownload(Attica::Provider provider, QWidget* parent)
    : QWidget(parent)
    , m_provider(provider)
{
    ui.setupUi(this);
    
    connect(ui.category, SIGNAL(currentIndexChanged(int)), SLOT(categoryChanged()));
    connect(ui.search, SIGNAL(returnPressed()), SLOT(categoryChanged()));
    connect(ui.nextButton, SIGNAL(clicked()), SLOT(nextPage()));
    connect(ui.voteGood, SIGNAL(clicked()), SLOT(voteGood()));
    connect(ui.voteBad, SIGNAL(clicked()), SLOT(voteBad()));

    connect(ui.downloadButton, SIGNAL(clicked()), SLOT(download()));
    
    connect(ui.contentList, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), SLOT(selectedContentChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
    
    // get the available categories from the server
    ListJob<Category>* job = m_provider.requestCategories();
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(categoriesLoaded(Attica::BaseJob*)));
    job->start();
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

void ContentDownload::categoryChanged()
{
    m_page = 0;
    updateContentsList();
}

void ContentDownload::nextPage()
{
    ++m_page;
    updateContentsList();
}

void ContentDownload::updateContentsList()
{
    ui.contentList->clear();
    
    QString name = ui.category->currentText();
    QString id = ui.category->itemData(ui.category->currentIndex()).toString();
    ui.currentCategoryLabel->setText(name);
    ui.currentCategoryIdLabel->setText("Category Id: " + id);
    
    Category cat;
    cat.setId(id);
    Category::List catList;
    catList << cat;
    
    QString searchString(ui.search->text());
    ListJob<Content>* job = m_provider.searchContents(catList, searchString, Provider::Rating, m_page, 20);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(categoryContentsLoaded(Attica::BaseJob*)));
    job->start();
}

Q_DECLARE_METATYPE(Content)

void ContentDownload::categoryContentsLoaded(BaseJob* job)
{
    ListJob<Content>* listJob = static_cast<ListJob<Content>*>(job);
    Content::List contents = listJob->itemList();
    
    Q_FOREACH(Content content, contents) {
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, content.name());
        item->setText(1, QString("%1%").arg(content.rating()));
        item->setData(0, Qt::UserRole, qVariantFromValue(content));
        ui.contentList->addTopLevelItem(item);
    }
    ui.countLabel->setText(tr("Total items: %1").arg(listJob->metadata().totalItems));
}

void ContentDownload::selectedContentChanged(QTreeWidgetItem* , QTreeWidgetItem* selectedItem)
{
    kDebug() << "selection changed";
    if (selectedItem && qVariantCanConvert<Content>(selectedItem->data(0, Qt::UserRole))) {
        Content c = qvariant_cast<Content>(selectedItem->data(0, Qt::UserRole));
        ui.person->setText(c.attribute("personid"));
        ui.score->setText(QString::number(c.rating()));
        ui.numberDownloads->setText(QString::number(c.downloads()));
    }
}

void ContentDownload::voteGood()
{
    vote(true);
}

void ContentDownload::voteBad()
{
    vote(false);
}

void ContentDownload::vote(bool positive)
{
    QTreeWidgetItem* selectedItem = ui.contentList->currentItem();
    if (selectedItem && qVariantCanConvert<Content>(selectedItem->data(0, Qt::UserRole))) {
        Content c = qvariant_cast<Content>(selectedItem->data(0, Qt::UserRole));
        PostJob * job = m_provider.voteForContent(c.id(), positive);
        job->start();
    }
}

void ContentDownload::download()
{
    qDebug() << "download";
    QTreeWidgetItem* selectedItem = ui.contentList->currentItem();
    if (selectedItem && qVariantCanConvert<Content>(selectedItem->data(0, Qt::UserRole))) {
        Content c = qvariant_cast<Content>(selectedItem->data(0, Qt::UserRole));
        ItemJob<DownloadItem>* job = m_provider.downloadLink(c.id());
        connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(downloadLinkLoaded(Attica::BaseJob*)));
        job->start();
    }
}

void ContentDownload::downloadLinkLoaded(BaseJob* baseJob)
{
    qDebug() << "downloadLinkLoaded";
    ItemJob<DownloadItem>* job = static_cast<ItemJob<DownloadItem>*>(baseJob);
    DownloadItem item = job->result();
    QMessageBox::information(0, "Download from: ", item.url().toString());
}



#include "contentdownload.moc"

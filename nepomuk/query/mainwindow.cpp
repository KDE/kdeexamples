/*
 * Copyright 2011 Jon Ander Peñalba <jonan88@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "mainwindow.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>

#include <KLineEdit>
#include <KLocale>
#include <KPushButton>
#include <KTextBrowser>
#include <KTextEdit>

#include <Nepomuk/Query/AndTerm>
#include <Nepomuk/Query/ComparisonTerm>
#include <Nepomuk/Query/LiteralTerm>
#include <Nepomuk/Query/Query>
#include <Nepomuk/ResourceManager>

#include <Soprano/Model>
#include <Soprano/QueryResultIterator>
#include <Soprano/Vocabulary/NAO>

MainWindow::MainWindow(QWidget *parent)
    : KMainWindow(parent)
{
  QWidget *central_widget = new QWidget(this);
  QVBoxLayout *central_layout = new QVBoxLayout(this);

  QHBoxLayout *h_layout = new QHBoxLayout(this);

  QVBoxLayout *v_layout = new QVBoxLayout(this);
  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->addWidget(new QLabel(i18n("tag:"), this));
  layout->addWidget(tag = new KLineEdit(this));
  v_layout->addLayout(layout);

  layout = new QHBoxLayout(this);
  layout->addWidget(new QLabel(i18n("text:"), this));
  layout->addWidget(text = new KTextEdit(this));
  text->setMaximumHeight(100);
  v_layout->addLayout(layout);
  h_layout->addLayout(v_layout);

  KPushButton *button = new KPushButton(i18n("Search"), this);
  connect(button, SIGNAL(clicked()), this, SLOT(query()));
  h_layout->addWidget(button);

  central_layout->addLayout(h_layout);
  central_layout->addWidget(new QLabel(i18n("Result:"), this));
  central_layout->addWidget(result = new KTextBrowser(this));
  central_layout->addWidget(new QLabel(i18n("Url:"), this));
  central_layout->addWidget(url = new KTextBrowser(this));

  central_widget->setLayout(central_layout);
  setCentralWidget(central_widget);

  setMinimumSize(650,485);

  if (Nepomuk::ResourceManager::instance()->init())
    button->setEnabled(false);
}

void MainWindow::query()
{
  if (tag->text().isEmpty() && text->toPlainText().isEmpty())
    return;

  static Soprano::Model *model = Nepomuk::ResourceManager::instance()->mainModel();

  Nepomuk::Query::ComparisonTerm tag_term;
  Nepomuk::Query::LiteralTerm text_term;
  if (!tag->text().isEmpty())
    tag_term = Nepomuk::Query::ComparisonTerm(Soprano::Vocabulary::NAO::hasTag(), Nepomuk::Query::LiteralTerm(tag->text()));
  if (!text->toPlainText().isEmpty())
    text_term = Nepomuk::Query::LiteralTerm(text->toPlainText());

  Nepomuk::Query::Query query(Nepomuk::Query::AndTerm(tag_term, text_term));
  url->setText(query.toSearchUrl().url());

  Soprano::QueryResultIterator it = model->executeQuery(query.toSparqlQuery(), Soprano::Query::QueryLanguageSparql);
  QString text_result;
  while(it.next())
  {
    for (int i=0; i< it.bindingCount(); ++i)
    {
      text_result += it.binding(i).toString();
      text_result += "<br>";
    }
  }

  result->setText(text_result);
}

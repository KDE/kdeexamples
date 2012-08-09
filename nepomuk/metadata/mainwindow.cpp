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

#include <KFileDialog>
#include <KLineEdit>
#include <KLocale>
#include <KPushButton>
#include <KTextBrowser>

#include <Nepomuk2/Resource>
#include <Nepomuk2/ResourceManager>
#include <Nepomuk2/Tag>
#include <Nepomuk2/Variant>

MainWindow::MainWindow(QWidget *parent)
    : KMainWindow(parent)
{
  QWidget *central_widget = new QWidget(this);
  QVBoxLayout *central_layout = new QVBoxLayout(central_widget);

  QHBoxLayout *h_layout = new QHBoxLayout(central_widget);

  QVBoxLayout *layout = new QVBoxLayout(central_widget);
  file = new KLineEdit(central_widget);
  file->setText(i18n("No file selected"));
  file->setEnabled(false);
  tag = new KLineEdit(central_widget);
  layout->addWidget(file);
  layout->addWidget(tag);
  h_layout->addLayout(layout);

  layout = new QVBoxLayout(central_widget);
  KPushButton *button = new KPushButton(i18n("Choose File"), central_widget);
  connect(button, SIGNAL(clicked()), this, SLOT(chooseFile()));
  layout->addWidget(button);
  button = new KPushButton(i18n("Add Tag"), central_widget);
  connect(button, SIGNAL(clicked()), this, SLOT(addTag()));
  layout->addWidget(button);
  h_layout->addLayout(layout);

  central_layout->addLayout(h_layout);

  data = new KTextBrowser(central_widget);
  central_layout->addWidget(data);

  central_widget->setLayout(central_layout);
  setCentralWidget(central_widget);

  setMinimumSize(500,300);

  if (Nepomuk2::ResourceManager::instance()->init())
    button->setEnabled(false);
}

void MainWindow::chooseFile()
{
  QString file_name = KFileDialog::getOpenFileName();
  if (!file_name.isEmpty())
  {
    file->setText(file_name);
    retrieveMetadata();
  }
  else
  {
    file->setText(i18n("No file selected"));
    data->setText("");
  }
}

void MainWindow::retrieveMetadata()
{
  QString data_text;
  Nepomuk2::Resource res(file->text());
  QHash<QUrl,Nepomuk2::Variant> properties = res.properties();

  QUrl key;
  foreach (key, properties.keys())
  {
    Nepomuk2::Types::Class property_type(key);
    data_text += "<b>" + property_type.label() + ":</b> ";
    data_text += properties[key].toString() + "<br>";
  }

  data->setText(data_text);
}

void MainWindow::addTag()
{
  Nepomuk2::Tag new_tag(tag->text());
  Nepomuk2::Resource res(file->text());
  res.addTag(new_tag);
  retrieveMetadata();
}

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

#include <KActionCollection>
#include <KApplication>
#include <KLocale>
#include <KTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent)
{
  textArea = new KTextEdit;
  textArea->setReadOnly(true);
  setCentralWidget(textArea);

  textArea->setText(i18n("This is a simple example showing KXMLGUI with standard actions.\n"
                         "Notice you can edit and configure the toolbar and your changes will be saved."));

  setupActions();
}

void MainWindow::setupActions()
{
  KStandardAction::openNew(this, SLOT(openNew()), actionCollection());
  KStandardAction::open(this, SLOT(open()), actionCollection());
  KStandardAction::save(this, SLOT(save()), actionCollection());
  KStandardAction::close(this, SLOT(close()), actionCollection());

  KStandardAction::back(this, SLOT(back()), actionCollection());
  KStandardAction::forward(this, SLOT(forward()), actionCollection());

  KStandardAction::cut(this, SLOT(cut()), actionCollection());
  KStandardAction::copy(this, SLOT(copy()), actionCollection());
  KStandardAction::paste(this, SLOT(paste()), actionCollection());

  KStandardAction::quit(kapp, SLOT(quit()), actionCollection());

  setupGUI();
}

void MainWindow::openNew()
{
  textArea->setText(i18n("New signal emitted"));
}

void MainWindow::open()
{
  textArea->setText(i18n("Open signal emitted"));
}

void MainWindow::save()
{
  textArea->setText(i18n("Save signal emitted"));
}

void MainWindow::close()
{
  textArea->setText(i18n("Close signal emitted"));
}

void MainWindow::back()
{
  textArea->setText(i18n("Back signal emitted"));
}

void MainWindow::forward()
{
  textArea->setText(i18n("Forward signal emitted"));
}

void MainWindow::cut()
{
  textArea->setText(i18n("Cut signal emitted"));
}

void MainWindow::copy()
{
  textArea->setText(i18n("Copy signal emitted"));
}

void MainWindow::paste()
{
  textArea->setText(i18n("Paste signal emitted"));
}

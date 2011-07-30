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
#include <KMessageBox>
#include <KFileDialog>

#include <KService>

MainWindow::MainWindow()
    : KParts::MainWindow()
{
  setupActions();
  setMinimumSize(370,200);

  KService::Ptr service = KService::serviceByStorageId("katepart");

  if (service)
  {
    m_part = service->createInstance<KParts::ReadWritePart>(0);

    if (m_part)
    {
      setCentralWidget(m_part->widget());
      createGUI(m_part);
      setupGUI(QSize(600,475), ToolBar|Keys|StatusBar|Save);
    }
  }
  else
  {
    KMessageBox::error(this, i18n("katepart.desktop not found"));
    kapp->quit();
  }
}

void MainWindow::load(const KUrl& url)
{
  m_part->openUrl(url);
}

void MainWindow::load()
{
  load(KFileDialog::getOpenUrl());
}

void MainWindow::setupActions()
{
  KStandardAction::open(this, SLOT(load()), actionCollection());
  KStandardAction::quit(kapp, SLOT(closeAllWindows()), actionCollection());
}

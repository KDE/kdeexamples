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

#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>

#include <KStandardDirs>

#include <Kross/Action>
#include <Kross/Manager>

MainWindow::MainWindow(QWidget *parent) : KMainWindow(parent)
{
  QWidget *central = new QWidget(this);
  // Create the combobox where we display a list of
  // available interpreters.
  m_interpreters = new QComboBox(central);
  m_interpreters->addItem("Interpreters");
  // Now let's add the interpreters. Please note, that all
  // interpreters that are installed are displayed in the list.
  // Per default JavaScript will be always
  // available while Python, Ruby or other interpreters
  // may need to be installed.
  foreach(QString s, Kross::Manager::self().interpreters())
    m_interpreters->addItem(s);

  // Connect the combobox signal with our slot to be able to
  // do something if the active item in the combobox changed.
  connect(m_interpreters, SIGNAL(activated(const QString &)),
          this, SLOT(interpreterActivated(const QString &)));

  // The label we want to manipulate from within scripting code.
  m_text = new QLabel("Select an interpreter", this);

  // Put everything into a layout to have it shown in a nice way.
  QVBoxLayout *layout = new QVBoxLayout(central);
  layout->addWidget(m_interpreters);
  layout->addWidget(m_text);
  central->setLayout(layout);
  setCentralWidget(central);

  // Now let's create a Kross::Action instance which will act
  // as container for our script.
  script = new Kross::Action(this, "MyScript");
}

// This slot is called when the active item of the combobox changes
void MainWindow::interpreterActivated(const QString &selected_interpreter)
{
  // Now let's set the scripts that should be executed
  // depending on the choosen interpreter.
  if(selected_interpreter == "python") {
      script->setFile(KStandardDirs::locate("data", "kdeexamples/kross/krosshello/hello.py"));
  } else if(selected_interpreter == "ruby") {
      script->setFile(KStandardDirs::locate("data", "kdeexamples/kross/krosshello/hello.rb"));
  } else if(selected_interpreter == "javascript") {
    script->setFile(KStandardDirs::locate("data", "kdeexamples/kross/krosshello/hello.js"));
  } else {
    m_text->setText("No script");
    return;
  }

  // Now let's add the QLabel instance to let the scripting code access it.
  script->addObject(m_text, "MyLabel");

  // Finally execute the scripting code.
  script->trigger();
}

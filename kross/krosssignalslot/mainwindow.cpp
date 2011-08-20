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

#include <QLabel>
#include <QVBoxLayout>

#include <KStandardDirs>
#include <KPushButton>

#include <Kross/Action>

MainWindow::MainWindow(QWidget *parent) : KMainWindow(parent)
{
  QWidget *central = new QWidget(this);

  // Create the widgets
  KPushButton *button1 = new KPushButton("Change text on click", this);
  KPushButton *button2 = new KPushButton("Emit signal", this);
  QLabel *text = new QLabel("Press a button", this);

  // Put everything into a layout to have it shown in a nice way.
  QHBoxLayout *h_layout = new QHBoxLayout(this);
  QVBoxLayout *v_layout = new QVBoxLayout(this);
  h_layout->addWidget(button1);
  h_layout->addWidget(button2);
  v_layout->addLayout(h_layout);
  v_layout->addWidget(text);
  central->setLayout(v_layout);
  setCentralWidget(central);

  // Now let's load and execute the scripts
  Kross::Action *script = new Kross::Action(this, "OnClick");
  script->addObject(button1, "Button");
  script->addObject(text, "Label");
  script->setFile(KStandardDirs::locate("data", "kdeexamples/kross/krosssignalslot/onclick.js"));
  script->trigger();
  script = new Kross::Action(this, "EmitSignal");
  script->addObject(button1, "Button1");
  script->addObject(button2, "Button2");
  script->setFile(KStandardDirs::locate("data", "kdeexamples/kross/krosssignalslot/emitsignal.js"));
  script->trigger();
}

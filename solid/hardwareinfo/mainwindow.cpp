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

#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

#include <KLocale>

#include <Solid/Processor>

MainWindow::MainWindow(QWidget *parent)
    : KMainWindow(parent)
{
  processors = Solid::Device::listFromType(Solid::DeviceInterface::Processor);

  QGroupBox *groupBox = new QGroupBox(i18n("Processors"), this);
  QVBoxLayout *layout = new QVBoxLayout(groupBox);

  QLabel *text = new QLabel("<b>" + i18n("Processor: ") + "</b>", groupBox);
  QComboBox *comboBox = new QComboBox(groupBox);
  for (int i = 0; i < processors.count(); ++i)
    comboBox->addItem(QString::number(i));
  QHBoxLayout *hLayout = new QHBoxLayout(groupBox);
  hLayout->addWidget(text);
  hLayout->addWidget(comboBox);
  layout->addLayout(hLayout);

  hLayout = new QHBoxLayout(groupBox);
  hLayout->addWidget(new QLabel(i18n("Maximum speed: "), groupBox));
  hLayout->addWidget(proccessor_speed = new QLabel(groupBox));
  layout->addLayout(hLayout);

  hLayout = new QHBoxLayout(groupBox);
  hLayout->addWidget(new QLabel(i18n("Frequency change: "), groupBox));
  hLayout->addWidget(freq_change = new QLabel(groupBox));
  layout->addLayout(hLayout);

  hLayout = new QHBoxLayout(groupBox);
  hLayout->addWidget(new QLabel(i18n("Intel MMX: "), groupBox));
  hLayout->addWidget(mmx = new QLabel(groupBox));
  layout->addLayout(hLayout);

  hLayout = new QHBoxLayout(groupBox);
  hLayout->addWidget(new QLabel(i18n("Intel SSE: "), groupBox));
  hLayout->addWidget(see = new QLabel(groupBox));
  layout->addLayout(hLayout);

  hLayout = new QHBoxLayout(groupBox);
  hLayout->addWidget(new QLabel(i18n("Intel SSE2: "), groupBox));
  hLayout->addWidget(see2 = new QLabel(groupBox));
  layout->addLayout(hLayout);

  hLayout = new QHBoxLayout(groupBox);
  hLayout->addWidget(new QLabel(i18n("Intel SSE3: "), groupBox));
  hLayout->addWidget(see3 = new QLabel(groupBox));
  layout->addLayout(hLayout);

  hLayout = new QHBoxLayout(groupBox);
  hLayout->addWidget(new QLabel(i18n("Intel SSE4: "), groupBox));
  hLayout->addWidget(see4 = new QLabel(groupBox));
  layout->addLayout(hLayout);

  hLayout = new QHBoxLayout(groupBox);
  hLayout->addWidget(new QLabel(i18n("AMD 3DNOW: "), groupBox));
  hLayout->addWidget(amd = new QLabel(groupBox));
  layout->addLayout(hLayout);

  hLayout = new QHBoxLayout(groupBox);
  hLayout->addWidget(new QLabel(i18n("PPC AltiVec: "), groupBox));
  hLayout->addWidget(ppc = new QLabel(groupBox));
  layout->addLayout(hLayout);

  connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(processorChanged(int)));
  processorChanged(0);

  groupBox->setLayout(layout);
  setCentralWidget(groupBox);
}

void MainWindow::processorChanged(int num)
{
  static QString yes = i18n("yes");
  static QString no = i18n("no");

  Solid::Processor *processor = processors[num].as<Solid::Processor>();

  proccessor_speed->setText(QString::number(processor->maxSpeed()));

  freq_change->setText(QString(processor->canChangeFrequency() ? yes:no));

  Solid::Processor::InstructionSets extensions = processor->instructionSets();
  mmx->setText(QString(extensions & Solid::Processor::IntelMmx ? yes:no));
  see->setText(QString(extensions & Solid::Processor::IntelSse ? yes:no));
  see2->setText(QString(extensions & Solid::Processor::IntelSse2 ? yes:no));
  see3->setText(QString(extensions & Solid::Processor::IntelSse3 ? yes:no));
  see4->setText(QString(extensions & Solid::Processor::IntelSse4 ? yes:no));
  amd->setText(QString(extensions & Solid::Processor::Amd3DNow ? yes:no));
  ppc->setText(QString(extensions & Solid::Processor::AltiVec ? yes:no));
}

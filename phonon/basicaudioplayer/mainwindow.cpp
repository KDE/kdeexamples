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

#include <KApplication>
#include <KFileDialog>
#include <KLineEdit>
#include <KPushButton>

#include <Phonon/AudioOutput>
#include <Phonon/MediaObject>
#include <Phonon/SeekSlider>
#include <Phonon/VolumeSlider>

MainWindow::MainWindow(QWidget *parent)
    : KMainWindow(parent)
{
  // Create the widgets

  // File selector
  file_name = new KLineEdit("Open an audio file", this);
  file_button = new KPushButton("Open", this);
  file_name->setEnabled(false);
  connect(file_button, SIGNAL(clicked()), this, SLOT(openFile()));

  // Audio control
  Phonon::SeekSlider *seek = new Phonon::SeekSlider(this);
  KPushButton *play_button = new KPushButton("Play", this);
  KPushButton *stop_button = new KPushButton("Stop", this);
  Phonon::VolumeSlider *volume = new Phonon::VolumeSlider(this);
  volume->setOrientation(Qt::Vertical);

  // Define the layout
  QHBoxLayout *file_layout = new QHBoxLayout(this);
  file_layout->addWidget(file_name);
  file_layout->addWidget(file_button);
  QHBoxLayout *button_layout = new QHBoxLayout(this);
  button_layout->addWidget(play_button);
  button_layout->addWidget(stop_button);
  QVBoxLayout *left_layout = new QVBoxLayout(this);
  left_layout->addWidget(seek);
  left_layout->addLayout(button_layout);
  QHBoxLayout *audio_layout = new QHBoxLayout(this);
  audio_layout->addLayout(left_layout);
  audio_layout->addWidget(volume);

  QWidget *central_widget = new QWidget(this);
  QVBoxLayout *central_layout = new QVBoxLayout(this);
  central_layout->addLayout(file_layout);
  central_layout->addLayout(audio_layout);
  central_widget->setLayout(central_layout);
  setCentralWidget(central_widget);

  // Create the media and define the output
  media = new Phonon::MediaObject(this);
  Phonon::AudioOutput *output = new Phonon::AudioOutput(Phonon::MusicCategory, this);
  Phonon::createPath(media, output);

  // Connect the widgets to the audio
  seek->setMediaObject(media);
  volume->setAudioOutput(output);
  connect(play_button, SIGNAL(clicked()), media, SLOT(play()));
  connect(stop_button, SIGNAL(clicked()), media, SLOT(stop()));
}

void MainWindow::openFile()
{
  QString file = KFileDialog::getOpenFileName();
  file_name->setText(file);
  media->setCurrentSource(file);
  media->play();
}

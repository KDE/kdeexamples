/*  This file is part of the KDE project
    Copyright (C) 2007 Matthias Kretz <kretz@kde.org>

    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appear in all
    copies and that both that the copyright notice and this
    permission notice and warranty disclaimer appear in supporting
    documentation, and that the name of the author not be used in
    advertising or publicity pertaining to distribution of the
    software without specific, written prior permission.

    The author disclaim all warranties with regard to this
    software, including all implied warranties of merchantability
    and fitness.  In no event shall the author be liable for any
    special, indirect or consequential damages or any damages
    whatsoever resulting from loss of use, data or profits, whether
    in an action of contract, negligence or other tortious action,
    arising out of or in connection with the use or performance of
    this software.

*/

#include <Phonon/AudioOutput>
#include <Phonon/Global>
#include <Phonon/MediaObject>
#include <Phonon/Path>
#include <Phonon/SeekSlider>
#include <Phonon/VolumeSlider>

#include <QtGui/QApplication>
#include <QtGui/QColumnView>
#include <QtGui/QDirModel>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class PlayerWidget : public QWidget
{
    Q_OBJECT
    public:
        PlayerWidget();

        void play(const QDirModel *model, const QModelIndex &index);

    private:
        void delayedInit();

        Phonon::MediaObject *m_media;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow();

    private slots:
        void providePlayer(const QModelIndex &index);

    private:
        QColumnView m_fileView;
        QDirModel m_model;
        PlayerWidget m_player;
};

PlayerWidget::PlayerWidget()
    : m_media(0)
{
}

void PlayerWidget::delayedInit()
{
    if (!m_media) {
        m_media = new Phonon::MediaObject(this);
        Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
        createPath(m_media, audioOutput);

        QHBoxLayout *topLayout = new QHBoxLayout(this);
        QVBoxLayout *leftLayout = new QVBoxLayout(this);
        QHBoxLayout *buttonLayout = new QHBoxLayout(this);

        Phonon::VolumeSlider *vs = new Phonon::VolumeSlider(audioOutput, this);
        vs->setOrientation(Qt::Vertical);

        QPushButton *playButton = new QPushButton(QLatin1String("play"), this);
        connect(playButton, SIGNAL(clicked()), m_media, SLOT(play()));

        QPushButton *stopButton = new QPushButton(QLatin1String("stop"), this);
        connect(stopButton, SIGNAL(clicked()), m_media, SLOT(stop()));

        topLayout->addLayout(leftLayout);
        topLayout->addWidget(vs);

        leftLayout->addLayout(buttonLayout);
        leftLayout->addWidget(new Phonon::SeekSlider(m_media, this));
        leftLayout->addStretch();

        buttonLayout->addWidget(playButton);
        buttonLayout->addWidget(stopButton);
    }
}

void PlayerWidget::play(const QDirModel *model, const QModelIndex &index)
{
    delayedInit();
    m_media->clearQueue();
    m_media->setCurrentSource(model->filePath(index));
    m_media->play();
    QModelIndex nextIndex = index.sibling(index.row() + 1, index.column());
    while (nextIndex.isValid()) {
        m_media->enqueue(model->filePath(nextIndex));
        nextIndex = index.sibling(nextIndex.row() + 1, nextIndex.column());
    }
}

MainWindow::MainWindow()
    : m_fileView(this)
{
    setCentralWidget(&m_fileView);
    m_fileView.setModel(&m_model);
    m_fileView.setPreviewWidget(&m_player);
    m_fileView.setFrameStyle(QFrame::NoFrame);

    connect(&m_fileView, SIGNAL(updatePreviewWidget(const QModelIndex &)), SLOT(providePlayer(const QModelIndex &)));
}

void MainWindow::providePlayer(const QModelIndex &index)
{
    m_player.play(&m_model, index);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Phonon Tutorial 4");
    MainWindow mw;
    mw.show();
    return app.exec();
}

#include "tutorial4.moc"

/*
*   Copyright (C) 2008 Nicola Gigante <nicola.gigante@gmail.com>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU Lesser General Public License as published by
*   the Free Software Foundation; either version 2.1 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU Lesser General Public License
*   along with this program; if not, write to the
*   Free Software Foundation, Inc.,
*   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .
*/

//krazy:excludeall=qclasses

#include "mainwindow.h"

#include <QFile>
#include <QTextStream>

#include <KAction>
#include <KAuth/Action>
#include <KAuth/ActionWatcher>
#include <KDebug>
#include <KLocale>
#include <KFileDialog>
#include <KMessageBox>
#include <KPushButton>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    progressBar = new QProgressBar();
    pushButton = new QPushButton();
    pushButton->setText("Stop");
    connect(pushButton, SIGNAL(clicked()), this, SLOT(stopLongAction()));
    progressBar->setRange(0, 100);
    statusBar()->addPermanentWidget(progressBar);
    statusBar()->addPermanentWidget(pushButton);
    pushButton->hide();
    progressBar->hide();
    KAction *action = new KAction(this);
    ui->menuFile->addAction(action);
    action->setIcon(KIcon("dialog-ok-apply"));
    action->setText(i18n("KAction Integration"));
    action->setAuthAction("org.kde.auth.example.kactionaction");
    connect(action, SIGNAL(authorized(KAuth::Action*)), this, SLOT(kactionTriggered()));
    ui->openButton->setAuthAction("org.kde.auth.example.read");
    connect(ui->openButton, SIGNAL(authorized(KAuth::Action*)), this, SLOT(on_actionOpen_triggered()));
    ui->saveButton->setAuthAction("org.kde.auth.example.write");
    connect(ui->saveButton, SIGNAL(authorized(KAuth::Action*)), this, SLOT(on_actionSave_triggered()));
    ui->longButton->setAuthAction("org.kde.auth.example.longaction");
    connect(ui->longButton, SIGNAL(authorized(KAuth::Action*)), this, SLOT(on_longAction_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = KFileDialog::getOpenFileName(KUrl("/"), i18n("All (*.*)"), this);

    QFile file(filename);
    QTextStream stream(&file);
    QString contents;

    if (!file.open(QIODevice::ReadOnly)) {
        if (file.error() & QFile::PermissionsError) {
            Action readAction("org.kde.auth.example.read");
            readAction.addArgument("filename", filename);

            ActionReply reply = readAction.execute("org.kde.auth.example");
            if (reply.failed()) {
                KMessageBox::information(this, "Error", i18n("KAuth returned an error code: %1", reply.errorCode()));
            } else {
                contents = reply.data()["contents"].toString();
            }
        } else {
            KMessageBox::information(this, "Error", i18n("Unable to open file: %1", file.error()));
        }
    } else {
        contents = stream.readAll();
    }

    ui->plainTextEdit->setPlainText(contents);

    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = KFileDialog::getSaveFileName(KUrl("/"), i18n("All (*.*)"), this);
    QFile file(filename);
    QTextStream stream(&file);

    if (!file.open(QIODevice::WriteOnly)) {
        if (file.error() & QFile::PermissionsError) {
            Action writeAction("org.kde.auth.example.write");
            writeAction.addArgument("filename", filename);
            writeAction.addArgument("contents", ui->plainTextEdit->toPlainText());

            ActionReply reply = writeAction.execute("org.kde.auth.example");
            if (reply.failed())
                KMessageBox::information(this, i18n("Error"), i18n("KAuth returned an error code: %1", reply.errorCode()));
        } else {
            KMessageBox::information(this, i18n("Error"), i18n("Unable to open file: %1", file.error()));
        }
    } else {
        stream << ui->plainTextEdit->toPlainText();
    }

    file.close();
}

void MainWindow::on_longAction_triggered()
{
    Action longAction("org.kde.auth.example.longaction");
    longAction.setExecutesAsync(true);
    connect(longAction.watcher(), SIGNAL(progressStep(int)), progressBar, SLOT(setValue(int)));
    connect(longAction.watcher(), SIGNAL(actionPerformed(ActionReply)), this, SLOT(longActionPerformed(ActionReply)));

    if (longAction.execute("org.kde.auth.example") != ActionReply::SuccessReply) {
        this->statusBar()->showMessage("Could not execute the long action");
    } else {
        pushButton->show();
        progressBar->show();
    }
}

void MainWindow::stopLongAction()
{
    Action("org.kde.auth.example.longaction").stop();
}

void MainWindow::longActionPerformed(ActionReply reply)
{
    progressBar->hide();
    pushButton->hide();
    progressBar->setValue(0);

    if (reply.succeeded()) {
        statusBar()->showMessage("Action succeeded", 10000);
    } else {
        statusBar()->showMessage(QString("Could not execute the long action: %1").arg(reply.errorCode()), 10000);
    }
}

void MainWindow::kactionTriggered()
{
    kDebug() << "Action triggered!";
    KMessageBox::information(this, "Error", i18n("Action triggered!"));
}


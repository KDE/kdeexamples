/*
*   Copyright (C) 2008 Nicola Gigante <nicola.gigante@gmail.com>
*                                                               
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or   
*   (at your option) any later version.                                 
*                                                                       
*   This program is distributed in the hope that it will be useful,     
*   but WITHOUT ANY WARRANTY; without even the implied warranty of      
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the       
*   GNU General Public License for more details.                        
*                                                                       
*   You should have received a copy of the GNU General Public License   
*   along with this program; if not, write to the                       
*   Free Software Foundation, Inc.,                                     
*   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .      
*/

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Action.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("All (*.*)"));

    QFile file(filename);
    QTextStream stream(&file);

    if(!file.open(QIODevice::ReadOnly))
    {
        Action::setHelperID("org.kde.auth.example");
        
        Action readAction = "org.kde.auth.example.read";
        ActionReply reply;
        if(readAction.authorize())
        {
            readAction.arguments()["path"] = filename;
            reply = readAction.execute();
            
            QMap<QString, QVariant>::const_iterator i = reply.data().constBegin();
            while (i != reply.data().constEnd()) {
                qDebug() << "Argument key:" << i.key() << "- value:" << i.value().toString();
                ++i;
            }
            
            // Asynchronous alternative:
            // readAction.execute(SLOT(readActionFinished(ActionReply)));
            // return;
        }

        if(reply.failed())
            QMessageBox::information(this, "Errore", QString("KAuth returned an error code: %1").arg(reply.errorCode()));
        else
            ui->plainTextEdit->setPlainText(reply.data().value("text").toString());

        return;
    }

    ui->plainTextEdit->setPlainText(stream.readAll());

    file.close();
}

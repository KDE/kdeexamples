/*
    This file is part of KDE.

    Copyright (c) 2009 Frederik Gladhorn <gladhorn@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>
 
#include "mainwindow.h"

// There is really nothing new in this file, you should look at more basic tutorial if you don't understand this.


int main (int argc, char *argv[])
{
    KAboutData aboutData( "opencollaborationexample", 0,
    ki18n("Open Collaboration Services Demo"), "1.0",
    ki18n("Show how to use libattica to access the Open Collaboration Services"),
    KAboutData::License_GPL,
    ki18n("Copyright (c) 2009 Frederik Gladhorn") );
    KCmdLineArgs::init( argc, argv, &aboutData );

    KApplication app;
     
    MainWindow* window = new MainWindow();
    window->show();
     
    return app.exec();
}


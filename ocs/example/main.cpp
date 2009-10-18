#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>
 
#include "mainwindow.h"
 
int main (int argc, char *argv[])
{
    KAboutData aboutData( "libatticademo", 0,
    ki18n("Attica Demo"), "1.0",
    ki18n("Show how to use libattica to access the Open Collaboration Services"),
    KAboutData::License_GPL,
    ki18n("Copyright (c) 2009 Frederik Gladhorn") );
    KCmdLineArgs::init( argc, argv, &aboutData );
     
    KApplication app;
     
    MainWindow* window = new MainWindow();
    window->show();
     
    return app.exec();
}


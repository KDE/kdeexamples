#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
 
#include "mainwindow.h"
 
int main (int argc, char *argv[])
{
  KAboutData aboutData( "tutorial-kicon", "tutorial-kicon",
      ki18n("Tutorial KIcon"), "1.0",
      ki18n("A simple text area using KIcons, KAction etc."),
      KAboutData::License_GPL,
      ki18n("Copyright (c) 2011 Developer") );
  KCmdLineArgs::init( argc, argv, &aboutData );
  KApplication app;
 
  MainWindow* window = new MainWindow();
  window->show();
  return app.exec();
}

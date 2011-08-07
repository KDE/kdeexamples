/*
 * Copyright 2011 Jon Ander Peñalba <jonan88@gmail.com>
 * Copyright 2009 Harald Fernengel <harry@kdevelop.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <KAboutData>
#include <KApplication>
#include <KCmdLineArgs>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
  KAboutData aboutData("soliddemo", 0,
                       ki18n("Solid Demo"), "1.0",
                       ki18n("Basic Solid (KDE's hardware abstraction layer) demo."),
                       KAboutData::License_GPL,
                       ki18n("Copyright (c) 2011 Jon Ander Peñalba <jonan88@gmail.com>"));
  KCmdLineArgs::init(argc, argv, &aboutData);
  KApplication app;

  MainWindow *window = new MainWindow();
  window->show();

  return app.exec();
}


/*
*  kcontrolmodule_example.h
*
*  Copyright (C) 2010 David Hubner <hubnerd@ntlworld.com>
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*
*/

#ifndef KCONTROLMODULEEXAMPLE
#define KCONTROLMODULEEXAMPLE

// Include to register and export your KCM plugin
#include <KPluginFactory>
#include <KPluginLoader>

// Include KCModule, the class your need to inherit from
#include <KCModule>

// Include to set about data
#include <KAboutData>
#include <kdeversion.h>

// Widgets and labels used for display
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

/* 
Create the class, the KCM has to inherit KCModule
Check http://api.kde.org/4.x-api/kdelibs/kdeui/classKCModule.html
for reference. 
*/

class KControlModuleExample : public KCModule
{
  Q_OBJECT
  
  public:
    KControlModuleExample(QWidget *, const QVariantList &);
    
  private:
    void createDisplay(QWidget *);
    void exportInformation();
    
    QLabel *m_exampleLabel;
};
  
#endif //KCONTROLMODULEEXAMPLE


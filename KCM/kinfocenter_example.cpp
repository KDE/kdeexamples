
/*
*  kinfocenter_example.cpp
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

#include "kinfocenter_example.h"

/*
Register and Export the plugin
*/
K_PLUGIN_FACTORY(KInfoCenterExampleFactory, registerPlugin<KInfoCenterExample>();)
K_EXPORT_PLUGIN(KInfoCenterExampleFactory("kinfocenterexample"))

KInfoCenterExample::KInfoCenterExample(QWidget *parent, const QVariantList &args) :
  KCModule(KInfoCenterExampleFactory::componentData(),parent)
{
  
  // We do not use args in this example, so set unused so compiler does not display warning.
  Q_UNUSED(args);
  
  // Set KInfoCenter About Data
  const KAboutData *about =
  new KAboutData(I18N_NOOP("KInfoCenterExample"), 0, ki18n("KInfoCenter Example"),"0.01", 
    KLocalizedString(), KAboutData::License_GPL, ki18n("(c) 2010 David Hubner"));

  setAboutData(about);
  
  // Create display
  createDisplay(this);
  
  // Set Buttons
  // There are NoAdditionalButton, Help, Default, Apply and Export
  //
  // NoAdditionalButton - No buttons
  // Help - Display Help Button
  // Default - Help and Apply are displayed
  // Apply - Display Apply button, Not used in KInfoCenter
  // Export - Display Export button
  setButtons(Help);
}

/*
Create a label at the top the KCM
*/
void KInfoCenterExample::createDisplay(QWidget *parent)
{
  QWidget *maindisplay = new QWidget(parent);
  QVBoxLayout *layout = new QVBoxLayout(maindisplay);
 
  m_exampleLabel = new QLabel(i18nc("Example Label","Here is the Label"));
  layout->addWidget(m_exampleLabel);
}

/*
Set the export of information, this sets the information returned
when the export button is pressed. Needs KDE 4.5
*/
void KInfoCenterExample::exportInformation()
{
  setExportText(m_exampleLabel->text());
}
  
  
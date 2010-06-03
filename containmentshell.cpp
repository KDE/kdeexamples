/*
*   Copyright 2010 Ryan Rix <ry@n.rix.si>
*   Copyright 2010 Siddharth Sharma <siddharth.kde@gmail.com>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU Library General Public License version 2 as
*   published by the Free Software Foundation
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details
*
*   You should have received a copy of the GNU Library General Public
*   License along with this program; if not, write to the
*   Free Software Foundation, Inc.,
*   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "containmentshell.h"

#include <KService>
#include <KMessageBox>
#include <KDebug>
#include <KStandardAction>
#include <KActionCollection>


#include <Plasma/Containment>

#include <QApplication>

ContainmentShell::ContainmentShell()
	: KParts::MainWindow( ),
	  m_dialog(0)
{
    setXMLFile("plasma-kpart-shellui.rc");
    
    KAction* action = KStandardAction::quit(qApp, SLOT(quit()), actionCollection());
    
    action = new KAction("&Configure", actionCollection());
    connect(action, SIGNAL(triggered()), this, SLOT(optionsPreferences()));
    actionCollection()->addAction("options_configure", action);
    
    
	// this routine will find and load our Part.  it finds the Part by
	// name which is a bad idea usually.. but it's alright in this
	// case since our Part is made for this Shell
	KService::Ptr service = KService::serviceByDesktopPath( "plasma-kpart.desktop" );
	
	if (service)
	{
		QVariantList args = QVariantList() << "Online Services"; 

		// now that the Part is loaded, we cast it to a Part to get
		// our hands on it
		m_part = service->createInstance<KParts::ReadOnlyPart>(0, args);
		
		if (m_part)
		{
			// tell the KParts::MainWindow that this is indeed the main widget
			setCentralWidget(m_part->widget());

			// and integrate the part's GUI with the shell's
			createGUI(m_part);

        }
		else
		{
			// For whatever reason the part didn't load
			KMessageBox::error(this, i18n("Could not instantiate our Part!"));
			qApp->quit();
		}
	}
	else
	{
		// if we couldn't find our Part, we exit since the Shell by
		// itself can't do anything useful
		KMessageBox::error(this, i18n("Could not find our Part!"));
		qApp->quit();
		// we return here, cause qApp->quit() only means "exit the
		// next time we enter the event loop...
		return;
	}

	// apply the saved mainwindow settings, if any, and ask the mainwindow
	// to automatically save settings if changed: window size, toolbar
	// position, icon size, etc.
	setAutoSaveSettings();
}

ContainmentShell::~ContainmentShell()
{
}

void ContainmentShell::optionsPreferences()
{
    if( !m_dialog )
    {
        QWidget* widget = 0;
        m_dialog = new KDialog(this);
        widget = new QWidget(m_dialog);
        
        
        m_dialog->setMainWidget( widget );
        createConfigurationInterface(widget);
        
        m_dialog->setButtons( KDialog::Ok | KDialog::Cancel | KDialog::Default );
        m_dialog->show();
    }
    else
    {
        m_dialog->show();
    }
}

QWidget* ContainmentShell::createConfigurationInterface(QWidget* parent)
{
    connect(this,SIGNAL(sigCreateConfigurationInterface(QWidget*)), m_part, SLOT(createConfigurationInterface(QWidget*)));
    
    emit sigCreateConfigurationInterface(parent);
}

#include "containmentshell.moc"
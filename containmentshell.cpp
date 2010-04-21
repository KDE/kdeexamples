/*
 * containmentshell.cpp
 *
 * Copyright (C) 2010 Ryan Rix <ry@n.rix.si>
 */
#include "containmentshell.h"
#include "containmentshell.moc"

#include <KService>
#include <KMessageBox>
#include <KStandardAction>
#include <KStandardDirs>
#include <KLocale>
#include <KDebug>

#include <Plasma/Containment>
#include <plasma/containmentactionspluginsconfig.h>

#include <QApplication>

ContainmentShell::ContainmentShell()
    : KParts::MainWindow( )
{
    // set the shell's ui resource file
    setXMLFile("plasma-kpart-shell.rc");

    // this routine will find and load our Part.  it finds the Part by
    // name which is a bad idea usually.. but it's alright in this
    // case since our Part is made for this Shell
    KService::Ptr service = KService::serviceByDesktopPath( "plasma-kpart.desktop" );

    if (service)
    {
        // Pass an config name to the KPart. If this argument is omitted from the factory creation,
        // the Corona's initializeLayout function will guess the appletsrc name based on the name
        // of the component that called it. Thus, this argument is really only necessary if you plan
        // on having more than one dashboard in different parts of your application.
        QVariantList args = QVariantList() << "plasma-kpart-shell-appletsrc"; 

        // now that the Part is loaded, we cast it to a Part to get
        // our hands on it
        m_part = service->createInstance<KParts::Part>(0, args);

        if (m_part)
        {
            // tell the KParts::MainWindow that this is indeed the main widget
            setCentralWidget(m_part->widget());

            // and integrate the part's GUI with the shell's
            setupGUI();
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

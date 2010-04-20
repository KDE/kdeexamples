/*
 * containmentshell.cpp
 *
 * Copyright (C) 2010 Ryan Rix <ry@n.rix.si>
 */
#include "containmentshell.h"
#include "containmentshell.moc"

#include <KPluginLoader>
#include <KPluginFactory>
#include <KMessageBox>
#include <KStandardAction>
#include <KStandardDirs>
#include <KLocale>
#include <KDebug>

#include "../kpartcorona.h"
#include <Plasma/Containment>

#include <QApplication>

ContainmentShell::ContainmentShell()
    : KParts::MainWindow( )
{
    // set the shell's ui resource file
    setXMLFile("plasma-kpart-shell.rc");

    // this routine will find and load our Part.  it finds the Part by
    // name which is a bad idea usually.. but it's alright in this
    // case since our Part is made for this Shell
    KPluginFactory *factory = (new KPluginLoader("plasma-kpart.so"))->factory();
    if (factory)
    {
	// These are the default theme arguments to pass to the KPart; Config Group, 
	// default theme color, and default system font.
	QStringList args = QStringList() << "Theme-plasma-desktop" << "air" << "Sans" << "plasma-kpart-shell-appletsrc"; // << "containmentshell-appletsrc";
        // now that the Part is loaded, we cast it to a Part to get
        // our hands on it
        m_part = static_cast<PlasmaKPart*>(factory->create(this,"PlasmaKPart", args ));

        if (m_part)
        {
	    // connect to some signals
	    QObject::connect(m_part->corona(), SIGNAL(parentLoadDefaultLayout()), this, SLOT(loadDefaultLayout()) );
	    
            // tell the KParts::MainWindow that this is indeed the main widget
            setCentralWidget(m_part->widget());

            // and integrate the part's GUI with the shell's
            setupGUI();
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


void ContainmentShell::loadDefaultLayout()
{
    /*KPartCorona* corona = m_part->corona();
    
    QString defaultConfig = KStandardDirs::locate("appdata", "plasma-default-layoutrc");
    if (!defaultConfig.isEmpty()) {
	kDebug() << "attempting to load the default layout from:" << defaultConfig;
	corona->loadLayout(defaultConfig);
	
	// used to force a save into the config file
	KConfigGroup invalidConfig;

	Plasma::Containment* c = m_part->addContainment("newspaper");

	if (!c) {
	    return;
	}

	c->init();

	c->setWallpaper("image", "SingleImage");
	c->setFormFactor(Plasma::Planar);
	c->updateConstraints(Plasma::StartupCompletedConstraint);
	c->flushPendingConstraintsEvents();
	c->save(invalidConfig);

	corona->requestConfigSync();
    }*/
}
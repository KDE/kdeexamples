#include "containmentshell.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
	I18N_NOOP("A KDE KPart Application");

static const char version[] = "0.1";

int main(int argc, char** argv)
{
	KAboutData about("plasma-kpart-shell", 0, ki18n("Plasma KPart Shell"), version, ki18n(description), KAboutData::License_GPL, ki18n("(C) 2010 Ryan Rix"), KLocalizedString(), 0, "ry@n.rix.si");
	about.addAuthor( ki18n("Ryan Rix"), KLocalizedString(), "ry@n.rix.si" );
	KCmdLineArgs::init(argc, argv, &about);

	KApplication app;

	// see if we are starting with session management
	if (app.isSessionRestored())
		RESTORE(ContainmentShell)
	else
	{
		ContainmentShell* widget = new ContainmentShell;
		widget->show();
	}

	return app.exec();
}

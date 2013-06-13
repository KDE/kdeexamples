/***************************************************************************
 *                                                                         *
 *   Copyright 2011 Sebastian Kügler <sebas@kde.org>                       *
 *   Copyright 2011 Marco Martin <mart@kde.org>                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

// KDE
#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KDebug>
#include <KDE/KLocale>
#include <KToolBar>
#include <KConfigGroup>

// Own
#include "exampleapp.h"

static const char description[] = I18N_NOOP("Example QML App");
static const char version[] = "1.0";

int main(int argc, char **argv)
{
    KAboutData about("example-qmlapp", 0, ki18n("Example QML App"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("Copyright 2011 Marco Martin"), KLocalizedString(), 0, "mart@kde.org");
                     about.addAuthor( ki18n("Marco Martin"), KLocalizedString(), "mart@kde.org" );
    about.setProgramIconName("plasma");
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;

    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    ExampleApp *mainWindow = new ExampleApp();
    mainWindow->show();
    args->clear();
    return app.exec();
}

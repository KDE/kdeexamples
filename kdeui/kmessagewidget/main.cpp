/* This file is part of the KDE libraries
 *
 * Copyright (c) 2011 Aurélien Gâteau <agateau@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */
#include "window.h"

#include <KAboutData>
#include <KApplication>
#include <KCmdLineArgs>

static KAboutData about(
    "KMessageWidgetDemoApplication",
    "",
    ki18n("KMessageWidgetDemoApplication"),
    "1.0",
    ki18n("Demonstrates basic KMessageWidget usage."),
    KAboutData::License_LGPL,
    ki18n("(C) 2011 Aurélien Gâteau")
    );

int main(int argc, char *argv[])
{
    KCmdLineArgs::init(argc, argv, &about);
    KApplication app;

    Window* window = new Window;
    window->show();
    return app.exec();
}


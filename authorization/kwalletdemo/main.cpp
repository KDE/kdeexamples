// This code is released into the public domain by the author Martin T. Sandsmark

#include "dialog.h"

#include <KAboutData>
#include <KApplication>
#include <KCmdLineArgs>

static KAboutData about(
    "KWalletDemoApplication",
    "",
    ki18n("KWalletDemoApplication"),
    "1.0",
    ki18n("Demonstrates basic KWallet usage."),
    KAboutData::License_LGPL,
    ki18n("(C) 2010 Martin Sandsmark"),
    KLocalizedString(),
    "http://www.mts.ms/");

int main(int argc, char *argv[])
{
    about.addAuthor(ki18n("Martin Sandsmark"), ki18n("Maintainer"), "martin.sandsmark@kde.org", "http://iskrembilen.com/");

    KCmdLineArgs::init(argc, argv, &about);
    KApplication app;

    Dialog dialog;
    dialog.show();
    return app.exec();
}

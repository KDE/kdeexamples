/**
 *
 *   Copyright 2011 Sebastian Kügler <sebas@kde.org>
 *   Copyright 2011 Marco Martin <mart@kde.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef KDECLARATIVEVIEW_H
#define KDECLARATIVEVIEW_H

#include <QDeclarativeView>

namespace Plasma
{
    class Package;
}

class QScriptEngine;
class KDeclarativeViewPrivate;

class KDeclarativeView : public QDeclarativeView
{
    Q_OBJECT

public:
    KDeclarativeView(QWidget *parent = 0);
    ~KDeclarativeView();

    /**
     * Sets the package from where load the application QML UI
     * The package must be of the type "Generic package"
     * it must provide a qml file as "mainscript"
     * @arg QString packageName the plugin name of the package
     */
    void setPackageName(const QString &packageName);
    /**
     * @returns the plugin name of the package
     */
    QString packageName() const;

    /**
     * @returns the plugin name of the package that holds the application QML UI
     */
    Plasma::Package *package() const;

    QSize sizeHint() const;

    QScriptEngine *scriptEngine() const;

private:
    KDeclarativeViewPrivate *const d;
};

#endif //KDECLARATIVEVIEW_H

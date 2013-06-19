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

#include "kdeclarativeview.h"

#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeItem>
#include <QGLWidget>

#include <KDebug>

#include  <kdeclarative.h>

#include <Plasma/Package>

class KDeclarativeViewPrivate
{
public:
    KDeclarativeViewPrivate()
    {}

    KDeclarative kdeclarative;
    Plasma::PackageStructure::Ptr structure;
    Plasma::Package *package;
    QString packageName;
};

KDeclarativeView::KDeclarativeView(QWidget *parent)
    : QDeclarativeView(parent),
      d(new KDeclarativeViewPrivate)
{
    // avoid flicker on show
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);

    setResizeMode(QDeclarativeView::SizeRootObjectToView);

    d->kdeclarative.setDeclarativeEngine(engine());
    d->kdeclarative.initialize();
    //binds things like kconfig and icons
    d->kdeclarative.setupBindings();

    d->structure = Plasma::PackageStructure::load("Plasma/Generic");

    show();
}

KDeclarativeView::~KDeclarativeView()
{
}


void KDeclarativeView::setPackageName(const QString &packageName)
{
    d->package = new Plasma::Package(QString(), packageName, d->structure);
    d->packageName = packageName;
    setSource(QUrl(d->package->filePath("mainscript")));
}

QString KDeclarativeView::packageName() const
{
    return d->packageName;
}

Plasma::Package *KDeclarativeView::package() const
{
    return d->package;
}

QSize KDeclarativeView::sizeHint() const
{
    return QSize(800, 600);
}

QScriptEngine *KDeclarativeView::scriptEngine() const
{
    return d->kdeclarative.scriptEngine();
}

#include "kdeclarativeview.moc"

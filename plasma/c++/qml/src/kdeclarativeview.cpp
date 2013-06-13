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

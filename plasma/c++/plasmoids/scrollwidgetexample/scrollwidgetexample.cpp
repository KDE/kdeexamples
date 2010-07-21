/*
 *   Copyright 2010 Ryan Rix <ry@n.rix.si>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2,
 *   or (at your option) any later version.
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

#include "scrollwidgetexample.h"

#include <Plasma/ScrollWidget>
#include <Plasma/Frame>
#include <Plasma/Label>

#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>
#include <QGraphicsItem>
#include <QString>
#include <QVariant>

K_EXPORT_PLASMA_APPLET(scrollareaexample, ScrollWidgetExample)

ScrollWidgetExample::ScrollWidgetExample( QObject* parent, const QVariantList& args )
    : Plasma::Applet( parent, args ),
      m_scrollWidget(0),
      m_scroller(0),
      m_scrollerLayout(0)
{
    init();
}

void ScrollWidgetExample::init()
{
    // Start by setting up the main widget
    setPreferredSize(100,400);
    QGraphicsLinearLayout* lay = new QGraphicsLinearLayout( Qt::Vertical);
    setLayout( lay );

    // Put the scroller inside of the QGW
    m_scrollWidget = new Plasma::ScrollWidget( );
    m_scrollWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_scroller = new QGraphicsWidget( );
    m_scrollerLayout = new QGraphicsLinearLayout( Qt::Vertical, m_scroller );
    m_scrollWidget->setWidget( m_scroller );
    lay->addItem( m_scrollWidget );

    // add some items
    for ( int i = 0; i < 10; i++ ) {
        addScrollerItem(QString(i));
    }
}

void ScrollWidgetExample::addScrollerItem( QString text )
{
    // Objects in scrollers can be any type of widget you
    // want, but Plasma::Frames look the best, imo.

    Plasma::Frame* item = new Plasma::Frame();
    QGraphicsLinearLayout* lay = new QGraphicsLinearLayout( Qt::Horizontal );
    Plasma::Label* label = new Plasma::Label();
    label->setText(text);
    lay->addItem(label);
    item->setLayout(lay);

    // Add the widget you've created to the scroller and force it to recalculate its sizes
    m_scrollerLayout->addItem(item);
    setPreferredSize(-1,-1);
    m_scrollerLayout->invalidate();

    emit sizeHintChanged(Qt::PreferredSize);
}

#include "scrollwidgetexample.moc"

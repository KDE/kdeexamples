/**
 * Copyright 2010 Ryan Rix <ry@n.rix.si>
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
 **/

#include "scrollwidgetexample.h"

#include <Plasma/ScrollWidget>
#include <Plasma/Frame>
#include <Plasma/Label>

#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>
#include <QGraphicsItem>
#include <QString>
#include <QVariant>

K_EXPORT_PLASMA_APPLET(scrollwidgetexample, ScrollWidgetExample)

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

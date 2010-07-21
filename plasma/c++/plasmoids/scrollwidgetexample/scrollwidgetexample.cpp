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
    setPreferredSize(100,400);
}

void ScrollWidgetExample::init()
{
    // Start by setting up the Applet with a layout
    QGraphicsLinearLayout* lay = new QGraphicsLinearLayout(Qt::Vertical);
    setLayout(lay);

    // Create the scroll widget and set the desired size policy if different than the default
    // this ScrollWidget will handle the scrollbars as well actual scrolling, including
    // kinetic and gesture-based (e.g. flicking) scrolling for us!
    m_scrollWidget = new Plasma::ScrollWidget(this);
    m_scrollWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Create the QGraphicsWidget we will be scrolling across
    m_scroller = new QGraphicsWidget(m_scroller);
    m_scrollerLayout = new QGraphicsLinearLayout(Qt::Vertical, m_scroller);

    // Put that widget inside the ScrollWidget
    m_scrollWidget->setWidget(m_scroller);

    // add the scrollwidget to the top level layout of the Applet
    lay->addItem(m_scrollWidget);

    // now we add some items to the scrolling widget
    for (int i = 0; i < 10; i++) {
        addScrollerItem(QString::number(i));
    }
}

void ScrollWidgetExample::addScrollerItem(const QString &text)
{
    // Objects in scrollers can be any type of widget you
    // want, but Plasma::Frames look rather good.
    Plasma::Frame* item = new Plasma::Frame(m_scroller);
    QGraphicsLinearLayout* lay = new QGraphicsLinearLayout(Qt::Horizontal);
    Plasma::Label* label = new Plasma::Label(item);
    label->setText(text);
    lay->addItem(label);
    item->setLayout(lay);

    // Add the widget we've just created to the scroller
    m_scrollerLayout->addItem(item);
}

#include "scrollwidgetexample.moc"

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

#ifndef SCROLLWIDGETEXAMPLE_H
#define SCROLLWIDGETEXAMPLE_H

#include <Plasma/Applet>

namespace Plasma
{
    class ScrollWidget;
    class Frame;
} // namespace Plasma

class QGraphicsLinearLayout;
class QGraphicsWidget;

class ScrollWidgetExample : public Plasma::Applet
{
Q_OBJECT
public:
    ScrollWidgetExample( QObject* parent, const QVariantList& args );

    void init();
    void addScrollerItem( QString text );

private:
    Plasma::ScrollWidget* m_scrollWidget;
    QGraphicsWidget* m_scroller;
    QGraphicsLinearLayout* m_scrollerLayout;
};

#endif

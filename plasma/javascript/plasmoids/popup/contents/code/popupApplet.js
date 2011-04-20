// -*- coding: iso-8859-1 -*-
/*
 *   Author: Diego Casella <polentino911@gmail.com>
 *   Date: Sat Apr 16 2011, 17:10:39
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 or
 *   (at your option) any later version.
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

mainLayout = new LinearLayout(plasmoid);
label = new Label();
label.text = '<font color=\'red\'>Hey I\'m a Popup Label :)</font>';
mainLayout.addItem(label);

// When the applet is smaller than this minimum size, the popupIcon will be displayed.
plasmoid.setMinimumSize(100,100);
// When the popupIcon gets a click event, the associated popupWidget will be shown.
plasmoid.popupWidget = label;
// The famous popupIcon :)
plasmoid.popupIcon = "plasma";


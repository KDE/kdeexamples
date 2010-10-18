// -*- coding: iso-8859-1 -*-
/*
 *   Author: rich <rich@kde.org>
 *   Date: Sat Feb 20 2010, 15:03:07
 *
 *   (c) Copyright 2010 Richard Moore, rich@kde.org
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

engine = dataEngine('geolocation');

// Create and set a simple label; then add it
label = new Label();
label.text = 'Where am I?';
mainLayout.addItem(label);

plasmoid.dataUpdated = function(name, data)
{
   label.text = 'You are in ' +  data['city'] + ' in the country ' + data['country'];
}

engine.connectSource(engine.sources[0], plasmoid, 10*1000);



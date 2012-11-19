/*
*   Copyright 2012 by Sebastian Kügler <sebas@kde.org>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU Library General Public License as
*   published by the Free Software Foundation; either version 2, or
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

import QtQuick 1.1
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.extras 0.1 as PlasmaExtras


PlasmaComponents.Page {
    implicitWidth: childrenRect.width
    implicitHeight: childrenRect.height
    tools: Row {
        spacing: 5
        PlasmaComponents.ToolButton {
            visible: pageStack.depth > 1
            iconSource: "go-previous"
            onClicked: pageStack.pop()
        }
        PlasmaComponents.Button {
            text: "Button"
        }
    }

    PlasmaExtras.ScrollArea {
        anchors.fill: parent
        Flickable {
            id: flickable
            //contentWidth: column.width
            contentHeight: column.height
            clip: true
            anchors.fill: parent

            Column {
                id: column
                width: parent.width
                anchors {
                    //fill: parent
                    margins: 12
                }
                spacing: 12

                PlasmaExtras.Title {
                    text: "Typography in Plasma Quick"
                }
                PlasmaExtras.Heading {
                    level: 1
                    text: "Examples of Text"
                }
                PlasmaExtras.Heading {
                    level: 3
                    text: "Email from Thomas"
                }
                PlasmaExtras.Paragraph {
                    text: "Andrew Lake has written up some ideas for a typography guideline for Plasma Active. I'm still working on creating an HIG based on it, but as Aaron suggested, you may be interested in the raw input from Andrew as well, so you'll find it attached. Andrew Lake has written up some ideas for a typography guideline for Plasma Active. I'm still working on creating an HIG based on it, but as Aaron suggested, you may be interested in the raw input from Andrew as well, so you'll find it attached. Andrew Lake has written up some ideas for a typography guideline for Plasma Active. I'm still working on creating an HIG based on it, but as Aaron suggested, you may be interested in the raw input from Andrew as well, so you'll find it attached."
                }
                PlasmaExtras.Heading {
                    level: 3
                    text: "Email from Andrew"
                }
                PlasmaExtras.Paragraph {
                    text: "For clarity, I'm no typography expert so nothing I've written is meant to be sacred. I'm just a hardcore UI design hobbyist that has spent a great deal of time immersed in lots of UI and graphic design literature and wanted to provide some constructive feedback based on what I've learned over the years."
                }
                Item {
                    height: 40
                    width: parent.width
                }
                PlasmaExtras.Heading {
                    level: 1
                    text: "Heading at level " + level
                }
                PlasmaExtras.Heading {
                    level: 2
                    text: "Heading at level " + level
                }
                PlasmaExtras.Heading {
                    level: 3
                    text: "Heading at level " + level
                }
                PlasmaExtras.Heading {
                    level: 4
                    text: "Heading at level " + level
                }
                PlasmaExtras.Heading {
                    level: 5
                    text: "Heading at level " + level
                }
            }
        }
    }
}


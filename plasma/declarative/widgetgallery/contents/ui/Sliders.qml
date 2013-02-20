/*
*   Copyright (C) 2011 by Daker Fernandes Pinheiro <dakerfp@gmail.com>
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

import QtQuick 2.0
import org.kde.plasma.components 0.1 as PlasmaComponents

PlasmaComponents.Page {
    height: childrenRect.height
    property int implicitHeight: childrenRect.height

    tools: PlasmaComponents.ToolBarLayout {
        spacing: 5
        PlasmaComponents.ToolButton {
            visible: pageStack.depth > 1
            iconSource: "go-previous"
            onClicked: pageStack.pop()
        }
        PlasmaComponents.Slider {
            width: 140
            enabled: true
        }
        PlasmaComponents.TextField {
            clearButtonShown: true
            text: "hello"
        }
    }

    Flickable {
        id: flickable
        contentWidth: column.width
        contentHeight: column.height
        clip: true
        anchors.fill: parent

        Item {
            width: Math.max(flickable.width, column.width)
            height: column.height
            Column {
                id: column
                spacing: 20
                anchors.horizontalCenter: parent.horizontalCenter

                PlasmaComponents.Label {
                    font.pixelSize: 20
                    text: "Slider"
                }


                Column {
                    spacing: 10

                    PlasmaComponents.Label { text: "Color Selector"; font.pixelSize: 20 }

                    PlasmaComponents.Label { text: "Red" }

                    PlasmaComponents.Slider {
                        id: redSlider
                        height: 20
                        width: 255
                        orientation: Qt.Horizontal
                        minimumValue: 0
                        maximumValue: 255
                        stepSize: 10
                        Keys.onTabPressed: greenSlider.forceActiveFocus()
                    }

                    PlasmaComponents.Label { text: "Green" }

                    PlasmaComponents.Slider {
                        id: greenSlider
                        height: 20
                        width: 255
                        orientation: Qt.Horizontal
                        minimumValue: 0
                        maximumValue: 255
                        stepSize: 10
                        Keys.onTabPressed: blueSlider.forceActiveFocus()
                    }

                    PlasmaComponents.Label { text: "Blue" }

                    PlasmaComponents.Slider {
                        id: blueSlider
                        height: 20
                        width: 255
                        orientation: Qt.Horizontal
                        minimumValue: 0
                        maximumValue: 255
                        stepSize: 10
                        Keys.onTabPressed: redSlider.forceActiveFocus()
                    }

                    Rectangle {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width / 2
                        height: width
                        color: Qt.rgba(redSlider.value / 255, greenSlider.value / 255, blueSlider.value / 255, 1)
                    }
                }

                PlasmaComponents.Label { text: "Disabled Horizontal Slider" }

                PlasmaComponents.Slider {
                    id: horizontalSlider
                    width: 140
                    height: 20
                    enabled: false
                }

                PlasmaComponents.Label { text: "Inverted Horizontal Slider" }

                PlasmaComponents.Slider {
                    id: invHorizontalSlider
                    width: 140
                    height: 20
                    inverted: true
                    enabled: true
                }

                PlasmaComponents.Label { text: "Vertical Slider" }

                Row {
                    spacing: 30
                    PlasmaComponents.Slider {
                        id: verticalSlider
                        width: 20
                        height: 140
                        orientation: Qt.Vertical
                        minimumValue: 10
                        maximumValue: 1000
                        stepSize: 50
                        inverted: true
                    }
                    PlasmaComponents.Label { text: verticalSlider.value }
                }

            }
        }
    }

    PlasmaComponents.ScrollBar {
        id: horizontalScrollBar

        flickableItem: flickable
        orientation: Qt.Horizontal
        anchors {
            left: parent.left
            right: verticalScrollBar.left
            bottom: parent.bottom
        }
    }

    PlasmaComponents.ScrollBar {
        id: verticalScrollBar

        orientation: Qt.Vertical
        flickableItem: flickable
        anchors {
            top: parent.top
            right: parent.right
            bottom: horizontalScrollBar.top
        }
    }
}

#   -*- coding: utf-8 -*-
#
#   Copyright (C) 2009 Petri Damstén <damu@iki.fi>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU Library General Public License as
#   published by the Free Software Foundation; either version 2, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details
#
#   You should have received a copy of the GNU Library General Public
#   License along with this program; if not, write to the
#   Free Software Foundation, Inc.,
#   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

import os, sys
from PyQt4.QtCore import *
from PyQt4.QtGui  import *
from PyQt4 import uic
from PyKDE4.plasma import Plasma
from PyKDE4.plasmascript import Applet
from PyKDE4.kdecore import *
from PyKDE4.kdeui import *

class Hello(Applet):
    def __init__(self, parent, args = None):
        Applet.__init__(self, parent)
        self.frame = None

    def init(self):
        print '~~~ init'
        self.setPopupIcon('text-x-python')
        if not self.extender().hasItem('pyhello'):
            self.extenderItem = Plasma.ExtenderItem(self.extender())
            self.initExtenderItem(self.extenderItem)
        self.engine = self.dataEngine('pyhello')
        self.engine.connectSource('hello_index', self, 500)
        self.controller = self.engine.serviceForSource('hello_index')

    def initExtenderItem(self, item):
        print '~~~ initExtenderItem'
        self.layout = QGraphicsLinearLayout(Qt.Vertical)

        self.frame = Plasma.Frame(item)
        f = self.frame.font()
        f.setPointSizeF(36.0)
        self.frame.setFont(f)
        self.layout.addItem(self.frame)

        self.edit = Plasma.LineEdit(item)
        self.edit.setText('10')
        self.layout.addItem(self.edit)

        self.button = Plasma.PushButton(item)
        self.button.setText('Change')
        self.connect(self.button, SIGNAL('clicked()'), self.clicked)
        self.layout.addItem(self.button)

        self.widget = QGraphicsWidget(item)
        self.widget.setLayout(self.layout)
        #self.widget.setMinimumSize(QSizeF(250, 45));
        #self.widget.setPreferredSize(QSizeF(250, 45));

        item.setWidget(self.widget)
        item.setName('pyhello')
        item.setTitle(i18n('Python Hello'))
        item.showCloseButton()

    def createConfigurationInterface(self, dlg):
        print '~~~ createConfigurationInterface'
        w = QWidget(dlg)
        uic.loadUi(self.package().filePath('ui', 'config.ui'), w)
        dlg.addPage(w, i18n('Python Hello'), 'text-x-python')

    def clicked(self):
        print '~~~ clicked'
        operation = self.controller.operationDescription('value')
        operation.writeEntry('set', QVariant(int(self.edit.text())))
        self.controller.startOperationCall(operation)

    @pyqtSignature('dataUpdated(const QString&, const Plasma::DataEngine::Data&)')
    def dataUpdated(self, sourceName, data):
        print '~~~ dataUpdated', data[QString('index')]
        if self.frame:
            self.frame.setText(str(data[QString('index')]))


def CreateApplet(parent):
    return Hello(parent)


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

from PyQt4.QtCore import *
from PyKDE4.plasma import Plasma
from PyKDE4.plasmascript import DataEngine
from PyKDE4.kdecore import *

class HelloJob(Plasma.ServiceJob):
    def __init__(self, source, operation, parameters, parent = None):
        print '######### HelloJob'
        Plasma.ServiceJob.__init__(self, source.objectName(), operation, parameters, parent)
        self.source = source

    def start(self):
        print '######### HelloJob start', self.operationName(), self.parameters()
        if self.operationName() == 'value':
            if QString('set') in self.parameters():
                self.source.setData('index', self.parameters()[QString('set')].toInt()[0])
                self.setResult(True)
                return
        self.setResult(False)


class HelloService(Plasma.Service):
    def __init__(self, parent):
        print '####### HelloService'
        Plasma.Service.__init__(self, parent)
        self.setName('hello')

    def createJob(self, operation, parameters):
        print '####### HelloService createJob'
        return HelloJob(self.parent(), operation, parameters, self)

    def registerOperationsScheme(self):
        print '####### HelloService registerOperationsScheme'
        engine = self.parent().parent()
        path = engine.package().filePath('data', 'hello.operations')
        if path.isEmpty():
            print '####### Cannot find operations'
            return
        f = QFile(path)
        self.setOperationsScheme(f)


class HelloSource(Plasma.DataContainer):
    def __init__(self, parent):
        print '##### HelloSource'
        Plasma.DataContainer.__init__(self, parent)
        self.setObjectName('hello_index')
        self.setData('index', 0)

    def createService(self):
        print '##### HelloSource createService'
        return HelloService(self)


class Hello(DataEngine):
    def __init__(self, parent, args = None):
        DataEngine.__init__(self, parent)

    def init(self):
        print '### init'
        self.setMinimumPollingInterval(500)
        self.source = HelloSource(self)
        self.addSource(self.source)

    def updateSourceEvent(self, name):
        print '### updateSourceEvent:', name
        if name == 'hello':
            self.setData(name, 'message', 'Hello World!')
            return True
        return False

    def sourceRequestEvent(self, name):
        print '### sourceRequestedEvent:', name
        return self.updateSourceEvent(name)

    def sources(self):
        print '### sources'
        return ['hello', 'hello_index']

    def serviceForSource(self, source):
        print '### serviceForSource:', source
        container = self.containerForSource(source)
        if container:
            return container.createService()
        else:
            return DataEngine.serviceForSource(source)


def CreateDataEngine(parent):
    return Hello(parent)

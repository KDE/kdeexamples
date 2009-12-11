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
from PyQt4 import uic
from PyKDE4.kdecore import *
from PyKDE4.kdeui import *
from PyKDE4.plasma import *
from PyKDE4.plasmascript import Runner

class Hello(Runner):
    def __init__(self, parent, args = None):
        Runner.__init__(self, parent)
        self.actions = []

    def init(self):
        print '### init'
        self.reloadConfiguration()
        ign = Plasma.RunnerContext.Types(Plasma.RunnerContext.Directory |
                                         Plasma.RunnerContext.File | \
                                         Plasma.RunnerContext.NetworkLocation)
        self.setIgnoredTypes(ign)
        description = i18n("Python Test Runner. Responds Hello World! to hello (= :q:)");
        self.addSyntax(Plasma.RunnerSyntax(":q:", description))
        self.setSpeed(Plasma.AbstractRunner.NormalSpeed)
        self.setPriority(Plasma.AbstractRunner.LowestPriority)
        self.setHasRunOptions(True)

    def match(self, search):
        print '### match:',
        term = search.query()
        print term
        if term.toLower() == 'hello':
            match = Plasma.QueryMatch(self.runner)
            match.setType(Plasma.QueryMatch.ExactMatch)
            match.setIcon(KIcon('text-x-python'))
            match.setText(i18n('Hello World!'))
            match.setData(self.url)
            search.addMatch(term, match)

    def run(self, search, action):
        print '### run:',
        data = action.data().toString()
        print data
        KToolInvocation.invokeBrowser(data)

    def prepare(self):
        print '### prepare',
        lock = QMutexLocker(self.bigLock())
        print 'in BIG lock'

    def teardown(self):
        print '### teardown'

    def createRunOptions(self, parent):
        print '### createRunOptions', parent
        uic.loadUi(self.package().filePath('ui', 'config.ui'), parent)

    def reloadConfiguration(self):
        print '### reloadConfiguration: ',
        self.url = unicode(self.config().readEntry('url', 'http://www.kde.org').toString())
        print self.url


def CreateRunner(parent):
    return Hello(parent)


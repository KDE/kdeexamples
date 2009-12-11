#   -*- coding: utf-8 -*-
#
#   Copyright (c) 2009 by Petri Damstén <damu@iki.fi>
#   Copyright (c) 2007 by Paolo Capriotti <p.capriotti@gmail.com>
#   Copyright (c) 2007 by Aaron Seigo <aseigo@kde.org>
#   Copyright (c) 2008 by Alexis Ménard <darktears31@gmail.com>
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

# Some parts of the code are converted to python from C++ Image wallpaper plugin (GPLv2+)

import os, sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PyQt4.phonon import *
from PyQt4 import uic
from PyKDE4.plasma import Plasma
from PyKDE4.plasmascript import Wallpaper
from PyKDE4.kdecore import *
from PyKDE4.kdeui import *

class Test(Wallpaper):
    def __init__(self, parent, args = None):
        Wallpaper.__init__(self, parent)
        self.pixmap = None

    def init(self, config):
        print '### init',
        self.method = Plasma.Wallpaper.ResizeMethod(config.readEntry('method', \
                Plasma.Wallpaper.ScaledResize).toInt()[0])
        self.color = QColor(config.readEntry("wallpapercolor", QColor(56, 111, 150)))
        self.size = self.boundingRect().size().toSize()
        self.image = self.package().filePath('images', 'wallpaper.png')
        print self.size, self.image
        self.render(self.image, self.size, self.method, self.color)
        self.test = QAction(i18n('Test'), self)
        self.setContextualActions([self.test])
        self.connect(self.test, SIGNAL('triggered(bool)'), self.play)

    def paint(self, painter, exposedRect):
        print '### paint'
        painter.fillRect(exposedRect, self.color)

        if self.pixmap:
            if painter.worldMatrix() == QMatrix():
                # draw the background untransformed when possible; (saves lots of per-pixel-math)
                painter.resetTransform()

            # blit the background (saves all the per-pixel-products that blending does)
            painter.setCompositionMode(QPainter.CompositionMode_Source)

            # for pixmaps we draw only the exposed part (untransformed since the
            # bitmapBackground already has the size of the viewport)
            painter.drawPixmap(exposedRect, self.pixmap,
                               exposedRect.translated(-self.boundingRect().topLeft()))

    def createConfigurationInterface(self, parent):
        print '### createConfigurationInterface '
        self.currentColor = self.color
        widget = QWidget(parent)
        ui = uic.loadUi(self.package().filePath('ui', 'config.ui'), widget)
        ui.resizeCombo.setCurrentIndex(self.method)
        self.connect(ui.resizeCombo, SIGNAL('currentIndexChanged(int)'), self.resizeChanged)
        return widget

    def resizeChanged(self, index):
        print '### resizeChanged'
        self.method = index
        self.settingsChanged(True)
        self.render(self.image, self.size, self.method, self.color)

    def save(self, config):
        print '### save'
        config.writeEntry('method', self.method)

    def mouseMoveEvent(self, event):
        print '### mouseMoveEvent', event.scenePos()

    def mousePressEvent(self, event):
        print '### mousePressEvent', event.scenePos()

    def mouseReleaseEvent(self, event):
        print '### mouseReleaseEvent', event.scenePos()

    def wheelEvent(self, event):
        print '### wheelEvent', event.scenePos()

    def renderCompleted(self, image):
        print '### renderCompleted', image.size()
        self.pixmap = QPixmap(image)
        self.update(self.boundingRect())

    def urlDropped(self, url):
        print '### urlDropped', url

    def play(self):
        print '### play'
        media = Phonon.MediaObject(self)
        output = Phonon.AudioOutput(self);
        Phonon.createPath(media, output)
        media.setCurrentSource(Phonon.MediaSource(\
                KStandardDirs.locate('sound', 'KDE-Sys-Log-In.ogg')))
        media.play()


def CreateWallpaper(parent):
    return Test(parent)


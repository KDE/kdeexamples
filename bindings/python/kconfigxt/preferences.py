#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright 2010 Luca Beltrame <einar@heavensinferno.net>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

"""
This module implements an example configuration using KConfigXT. If you have
read the C++ tutorial (URL) you will notice that there is no way to generate
Python code from .kcfg files (yet). The solution is to implement the
configuration skeleton itself in code, as this example shows.

This example creates a KConfigSkeleton subclass which stores two values, a
server name and a port number (inspired by the original tutorial on KDE's
Techbase).It will also create a proper KConfigDialog.
"""

from PyQt4 import QtGui, QtCore
from PyKDE4 import kdecore, kdeui

from ui_generalpage import Ui_GeneralPage


class Preferences(kdeui.KConfigSkeleton):

    "Example implementation of a KConfigSkeleton subclass."

    def __init__(self, *args):

        """Initialize the instance. Once it has been created, you need to set a
        current group (with setCurrentGroup) and add items with the various
        addItem* functions (addItemString and addItemInt are shown here - check
        the API docs for more information.

        The C++ addItem* functions want a pointer to the type of the object
        you're storing. As Python does not have pointer, you need to pass a
        reference to the object type. They MUST be bound to the class (i.e.,
        instance attributes) or they will be garbage collected, causing
        unexpected behaviors (even crashes). To prevent access, make the
        items hidden (self._*) or mangled (self.__*).

        Once you have set everything, call readConfig()."""

        kdeui.KConfigSkeleton.__init__(self, *args)

        self.setCurrentGroup("General")

        # Using "" here won't work, we need an actual instance of QString or we
        # may get unexpected behavior (like values not being written)
        self._url_data = QtCore.QString()
        predefined_url = QtCore.QString("http://www.kde.org")
        self._url = self.addItemString("serverName", self._url_data,
                                       predefined_url)
        self._port_number = self.addItemInt("portNumber", 0, 80)
        self.readConfig()

    # A Pythonic approach to access values stored in a KConfigSkeleton instance
    # is to use properties by appropriately decorating functions, as the
    # examples below show.

    @property
    def url(self):
        return self._url.value()

    @property
    def port(self):
        return self._port_number.value()


class ConfigDialog(kdeui.KConfigDialog):

    "Example implementation of a KConfigDialog subclass."

    def __init__(self, parent=None, name=None, preferences=None):

        """Initialize the dialog. First of all, we set the buttons, using
        KDialog.ButtonCode. Then we add a GeneralPage instance, subsequently
        added with the addPage and we connect the settingsChanged signal to a
        slot which will pop up a message box every time the settings change."""

        super(ConfigDialog, self).__init__(parent, name, preferences)
        self.setButtons(kdeui.KDialog.ButtonCode(
            kdeui.KDialog.Ok|kdeui.KDialog.Apply|kdeui.KDialog.Cancel)
        )

        self.general_page = GeneralPage(self, preferences)
        self.preferences = preferences
        self.general_page_item = self.addPage(self.general_page,
                                              kdecore.i18n("General"))

        # The following adds a nice icon to the configuration page
        self.general_page_item.setIcon(kdeui.KIcon("network-server"))
        # Show the results every time the settings change
        self.settingsChanged.connect(self.show_values)

    def show_values(self):

        "Shows a dialog with the settings."

        server_name = kdecore.i18n("Server name: %1",
                                   self.preferences.url)
        port_number = kdecore.i18n("Port number: %1",
                                   self.preferences.port)

        text = server_name + "\n" + port_number
        kdeui.KMessageBox.information(self, text,
                                      kdecore.i18n("Settings changed"))


class GeneralPage(QtGui.QWidget, Ui_GeneralPage):

    "Example widget to be embedded in the KConfigDialog."

    def __init__(self, parent=None, preferences=None):

        super(GeneralPage, self).__init__(parent)
        self.setupUi(self)

        self.kcfg_serverName.setText(preferences.url)
        self.kcfg_portNumber.setValue(preferences.port)

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

"Module that calls the KConfigXT objects and displays them."

import sys

from PyQt4 import QtCore
from PyKDE4 import kdecore, kdeui

import preferences


app_name = "kconfigxtexample"
program_name = kdecore.ki18n("Example KConfigXT application (PyKDE4)")
about_data = kdecore.KAboutData(QtCore.QByteArray(app_name), "",
                                program_name, QtCore.QByteArray("0.1"))
kdecore.KCmdLineArgs.init(sys.argv, about_data)
app = kdeui.KApplication()

def main():

    settings = preferences.Preferences()
    print "Generated prefs"
    print "URL", settings.url

    dialog = preferences.ConfigDialog(None, "settings", settings)
    print "Creating dialog"

    dialog.show()
    app.exec_()

if __name__ == '__main__':
    main()

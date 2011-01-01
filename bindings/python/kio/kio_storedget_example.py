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

"""Module that shows how to download data using KIO.storedGet.

storedGet, like the name says, allows KIO to get a single URL into a QByteArray,
which than can be accessed through the data() function. Unlike KIO.get, the data
is kept entirely in memory.

This module shows an example by downloading HTML from www.kde.org and displaying
it in a text edit widget. The operation is done asynchronously, without blocking
the GUI.

"""

import sys

import PyQt4.QtCore as QtCore
import PyQt4.QtGui as QtGui
import PyKDE4.kdecore as kdecore
import PyKDE4.kdeui as kdeui
from PyKDE4.kio import KIO

# This is the compiled file from textbrowser.ui, using pykdeuic4.

from ui_textbrowser import Ui_Form

class TextArea(QtGui.QWidget, Ui_Form):

    """Example class used to show how KIO works."""

    def __init__(self, parent=None):

        super(TextArea, self).__init__(parent)
        self.setupUi(self)

        # Basic signal/slot connections
        # The first connects the clicked signal from the download button to the
        # start of the download, the second is used to clear the textedit

        self.downloadButton.clicked.connect(self.start_download)
        self.clearButton.clicked.connect(self.textWidget.clear)

    def start_download(self):

        """Slot invoked from clicking on downloadButton.

        It first shows a messagebox informing what will be done, then downloads
        the data using KIO, connecting the result signal to the handle_download
        slot."""

        kdeui.KMessageBox.information(self.parent(),
                                      "Now data will be retrieved from "
                                      "www.kde.org using KIO")

        # KIO wants KUrls
        data_url = kdecore.KUrl("http://www.kde.org")

        # Here we set some basic job properties. In particular the call is made
        # by indicating the url, then the LoadType (usually NoReload), then the
        # JobFlags. In case we use a single flag, we can specify directly the
        # flag, like we did here by suppressing the progress information.
        # Otherwise, we have to use a binary OR (|) to put also the other types
        # in.
        # KIO.storedGet returns the job handling the operation.

        retrieve_job = KIO.storedGet(data_url, KIO.NoReload, KIO.HideProgressInfo)

        # To actually obtain the data, we connect the result signal, which is
        # emitted at the end of the operation. Notice that KIO.storedGet keeps
        # the result in memory.

        retrieve_job.result.connect(self.handle_download)

    def handle_download(self, job):

        """Slot called from the retrieval job.

        It sets the data of the job (text) in the textwidget of the UI."""

        # Bail out in case of errors
        if job.error():
            return

        print "This slot has been called. The job has finished its operation."

        # The job's data, stored as a QByteArray, is kept in the data()
        # function.

        data = job.data()

        # To set the data, we convert it to a QString and we set it as plain
        # text in the text widget.

        self.textWidget.setPlainText(QtCore.QString(data))


class ExampleWindow(kdeui.KMainWindow):

    """Example main window used to showcase KIO."""

    def __init__(self, *args):

        super(ExampleWindow, self).__init__(*args)

        self.textbrowser = TextArea(self)
        self.setCentralWidget(self.textbrowser)


def main():

    app_name = "kio_storedget_example"
    program_name = kdecore.ki18n("Example KIO usage (PyKDE4)")
    about_data = kdecore.KAboutData(QtCore.QByteArray(app_name), "",
                                program_name, QtCore.QByteArray("0.1"))
    kdecore.KCmdLineArgs.init(sys.argv, about_data)
    app = kdeui.KApplication()

    mainwindow = ExampleWindow()
    mainwindow.show()
    app.exec_()

if __name__ == '__main__':
    main()

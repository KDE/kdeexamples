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

"Module that shows how to tag files."

import sys

from PyQt4 import QtCore
from PyKDE4 import kdecore
from PyKDE4 import kdeui
from PyKDE4.nepomuk import Nepomuk

def nepomuk_examples():

    # Create a fake file to be tagged

    dummy_file = open("dummy.txt", "w")
    dummy_file.write("Some text\n")
    dummy_file.close()

    # Initialize Nepomuk

    result = Nepomuk.ResourceManager.instance().init()

    # 0 means that we have access to Nepomuk - bail out otherwise

    if result != 0:
        print "Nepomuk not running. Bailing out."
        return

    # Next, we create a Nepomuk.Resource for our file. This is required for all
    # Nepomuk related operations. To construct it, we need an absolute path:
    # relative paths or file names won't work.

    file_info = QtCore.QFileInfo("dummy.txt")
    absolute_path = file_info.absoluteFilePath()

    print "Creating Nepomuk resource..."
    resource = Nepomuk.Resource(kdecore.KUrl(absolute_path))

    print "Nepomuk resource created.\n"
    # To tag a file, we create an instance of Nepomuk.Tag. We define it with an
    # identifier that is the name of our tag. If the tag already exists, it is
    # transparently re-used.

    print "Creating tag 'test_example'..."

    tag = Nepomuk.Tag("test_example")

    # A tag needs a label too, to be displayed. So we add the label using
    # setLabel()

    tag.setLabel("test_example")

    # Then we tag the file with the addTag method of the resource.
    # All tags in the resource can be accessed with the tags() method, which
    # returns a list of Tag instances.

    print "Adding tag..."
    resource.addTag(tag)

    print "We now have this tag:'%s'\n" % unicode(resource.tags()[0].label())

    # We can add  comments directly to the resource using setDescription().

    print "Adding description..."
    resource.setDescription("This is an example comment.")
    print "The file has the description: '%s'\n" % unicode(resource.description())


    # To strip a resource of everything, we use the remove() method.
    # resource.remove()
    # To remove specific properties, you can access the URI of the property,
    # such as descriptionUri() or tagUri() and remove them using
    # removeProperty():

    # resource.removeProperty(resource.descriptionUri()) # remove comment
    # resource.removeProperty(resource.tagUri()) # remove tags

    # Changes should be immediately visible in file managers such as Dolphin.

    print "Press a key to display the results in Dolphin."
    print "Check the 'dummy.txt' file.\n"
    raw_input()

    res = kdecore.KUrl(file_info.absolutePath()).prettyUrl()
    kdecore.KToolInvocation.startServiceByDesktopName("dolphin",
                                                      res)

def main():

    app_name = "nepomuk_tag_example"
    program_name = kdecore.ki18n("Example Nepomuk application (PyKDE4)")
    about_data = kdecore.KAboutData(QtCore.QByteArray(app_name), "",
                                program_name, QtCore.QByteArray("0.1"))
    kdecore.KCmdLineArgs.init(sys.argv, about_data)
    app = kdeui.KApplication()

    nepomuk_examples()
    QtCore.QTimer.singleShot(3000, app.quit)
    app.exec_()

if __name__ == '__main__':
    main()

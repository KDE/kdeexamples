#!/usr/bin/env python

# Copyright 2011 Luca Beltrame <einar@heavensinferno.net>         
#                                                                  
# Redistribution and use in source and binary forms, with or without 
# modification, are permitted provided that the following conditions
# are met
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

import sys

import PyQt4.QtCore as QtCore

import PyKDE4.kdecore as kdecore
import PyKDE4.kdeui as kdeui
from PyKDE4.kio import KIO
from PyKDE4.nepomuk import Nepomuk
from PyKDE4.soprano import Soprano


class NepomukTagQueryExample(QtCore.QObject):

    def __init__(self, parent=None):

        super(NepomukTagQueryExample, self).__init__(parent)

    def query_tag(self, tag):

        """Query for a specific tag."""

        # Generate a Nepomuk-understandable tag from our string representation
        tag = Nepomuk.Tag(tag)

        # We need now to get an URI to a resource which will be fed into
        # the query. Since we're using tags, we're using 
        # Soprano.Vocabulary.NAO.hasTag(). 

        soprano_term_uri = Soprano.Vocabulary.NAO.hasTag()

        # The API documentation on api.kde.org uses the URI directly, but 
        # under PyKDE4 generates an error, hence we wrap it in 
        # Nepomuk.Types.Property

        nepomuk_property = Nepomuk.Types.Property(soprano_term_uri)

        # The actual term for the query, in this case a ComparisonTerm,
        # because we compare our hasTag() with the actual tag
        # The tag is wrapped in a ResourceTerm

        comparison_term = Nepomuk.Query.ComparisonTerm(nepomuk_property,
                Nepomuk.Query.ResourceTerm(tag))

        # Now we make a query. We use a FileQuery since we're interested in
        # files, but if we want more generic results we can use 
        # Nepomuk.Query.Query.

        query = Nepomuk.Query.FileQuery(comparison_term)

        # We want to get results using KIO, so we get the search URL of
        # the result.

        search_url = query.toSearchUrl()

        # Finally we make a job to list those files
        # We connect entries, which is emitted with each result,
        # to our slot which will do the actual handling
        # Once the job is finished, we close the signal

        search_job = KIO.listDir(kdecore.KUrl(search_url))
        search_job.entries.connect(self.search_slot)
        search_job.result.connect(search_job.entries.disconnect)

    def search_slot(self, job, data):

        # We may get invalid entries, so skip those
        if not data:
            return

        for item in data:
            # Print the result (an UDSEntry) as string with proper
            # formatting
            print item.stringValue(KIO.UDSEntry.UDS_DISPLAY_NAME)

def main():

    app_name = "nepomuk_tag_query_example"
    program_name = kdecore.ki18n("Example Nepomuk tag query"
            " application (PyKDE4)")
    about_data = kdecore.KAboutData(QtCore.QByteArray(app_name), "",
                                program_name, QtCore.QByteArray("0.1"))
    kdecore.KCmdLineArgs.init(sys.argv, about_data)
    app = kdeui.KApplication()

    test = NepomukTagQueryExample()
    # Change this to a tag you have on your system
    test.query_tag("test")

    QtCore.QTimer.singleShot(5000, app.quit)
    app.exec_()

if __name__ == '__main__':
    main()

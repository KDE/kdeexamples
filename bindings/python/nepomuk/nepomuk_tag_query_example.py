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
        self.results = list()
        self.service_client = Nepomuk.Query.QueryServiceClient()

        # Gather results as they are found
        self.service_client.newEntries.connect(self.query_client_slot)

        # Ensure we disconnect after we're done
        #self.service_client.finishedListing.connect(
            #self.service_client.newEntries.disconnect)

        # Once the query is over, we'll display the results
        self.service_client.finishedListing.connect(self.display_results)

    def display_results(self):

        # get rid of duplicate items
        results = set(self.results)

        print "Displaying search results"
        print

        for item in results:
            print item

        print
        print "End results"

    def query_client_slot(self, data):

        # Instead of displaying results, we add them to an
        # internal list, because this slot is called for both
        # the initial search and when results are added.

        if not data:
            return

        for item in data:
            # Get the file name
            result = item.resource().genericLabel()
            self.results.append(result)

    def query_tag(self, tag):

        tag = Nepomuk.Tag(tag)

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

        # We call now the Nepomuk Query Service to execute our query
        # asynchronously
        self.service_client.query(query)

    def query_desktop_query(self, tag):

        # A simple query using Desktop Query instead of building a query
        # For tags it's very acceptable

        query = "hasTag:%s" % tag

        self.service_client.desktopQuery(query)

def main():

    app_name = "nepomuk_tag_query_example"
    program_name = kdecore.ki18n("Example Nepomuk tag query"
            " application (PyKDE4)")
    about_data = kdecore.KAboutData(QtCore.QByteArray(app_name), "",
                                program_name, QtCore.QByteArray("0.1"))
    kdecore.KCmdLineArgs.init(sys.argv, about_data)
    app = kdeui.KApplication()

    first_test = NepomukTagQueryExample()
    first_test.query_tag("test_query")

    second_test = NepomukTagQueryExample()
    second_test.query_desktop_query("test_query")

    QtCore.QTimer.singleShot(5000, app.quit)
    app.exec_()

if __name__ == '__main__':
    main()

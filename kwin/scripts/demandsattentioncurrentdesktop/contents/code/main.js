/********************************************************************
 KWin - the KDE window manager
 This file is part of the KDE project.

Copyright (C) 2012 Martin Gräßlin <mgraesslin@kde.org>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

var demandsAttention = new Array();

var containsClient = function(client) {
    for (var i=0; i<demandsAttention.length; i++) {
        if (demandsAttention[i] == client) {
            return true;
        }
    }
    return false;
};

var removeClient = function(client) {
    for (var i=0; i<demandsAttention.length; i++) {
        if (demandsAttention[i] == client) {
            demandsAttention.splice(i, 1);
            return;
        }
    }
};

var checkDemandsAttention = function(client) {
    if (!client.demandsAttention) {
        // client does not demand attention
        if (client.desktop == workspace.currentDesktop) {
            // client is on the current desktop, this means it either lost demands attention by
            // itself or we switched back to the desktop and need to restore it
            if (containsClient(client)) {
                // have to restore demands attention
                removeClient(client);
                client.demandsAttention = true;
            }
        }
        return;
    }
    // client received demands attention
    if (client.desktop != workspace.currentDesktop) {
        // client is not on the current desktop, so we have to remove demands attention and remember
        // that we removed it
        if (!containsClient(client)) {
            demandsAttention[demandsAttention.length] = client;
        }
        client.demandsAttention = false;
    }
};

var testAllClients = function() {
    var clients = workspace.clientList();
    for (var i=0; i<clients.length; i++) {
        checkDemandsAttention(clients[i]);
    }
};

workspace.clientDemandsAttentionChanged.connect(checkDemandsAttention);
workspace.clientAdded.connect(checkDemandsAttention);
workspace.clientRemoved.connect(removeClient);
workspace.currentDesktopChanged.connect(testAllClients);

// and the init test
testAllClients();

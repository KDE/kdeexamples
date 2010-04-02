/*
    Copyright (c) 2010 Frederik Gladhorn <gladhorn@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include <kmainwindow.h>
#include <knewstuff3/entry.h>

class QLabel;
class QListWidget;

namespace KNS3 {
    class DownloadManager;
}

/**
 * This class serves as the main window for UpdateChecker.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Frederik Gladhorn <gladhorn@kde.org>
 * @version 0.1
 */
class UpdateChecker : public KMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    UpdateChecker();

private slots:

    void updatesFound(const KNS3::Entry::List& updates);
    void entryStatusChanged(const KNS3::Entry& entry);
    void installUpdate();
    void showNewest();
    
private:
    QListWidget* m_list;
    QLabel* m_label;
    KNS3::DownloadManager* m_downloadManager;
    KNS3::Entry::List m_updates;
};

#endif

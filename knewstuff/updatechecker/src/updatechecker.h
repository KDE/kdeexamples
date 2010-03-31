/*
 * updatechecker.h
 *
 * Copyright (C) 2008 Frederik Gladhorn <gladhorn@kde.org>
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
    void installUpdate();
    void entryStatusChanged(const KNS3::Entry& entry);
    
private:
    QListWidget* m_list;
    QLabel* m_label;
    KNS3::DownloadManager* m_downloadManager;
    KNS3::Entry::List m_updates;
};

#endif

#ifndef CONTAINMENTSHELL_H
#define CONTAINMENTSHELL_H

#include "../plasmakpart.h"

#include <kparts/mainwindow.h>

/**
 * This is the application "Shell".  It has a menubar, toolbar, and
 * statusbar but relies on the "Part" to do all the real work.
 *
 * @short Application Shell
 * @author Ryan Rix <ry@n.rix.si>
 * @version 0.01
 */
class ContainmentShell : public KParts::MainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    ContainmentShell();

    /**
     * Default Destructor
     */
    virtual ~ContainmentShell();
    
    void loadDefaultLayout();

private:
    PlasmaKPart *m_part;
};

#endif // CONTAINMENTSHELL_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <KXmlGuiWindow>
#include <KLineEdit>
#include <QLabel>


#include "../lib/provider.h"

namespace Attica {
    class BaseJob;
}

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=0);

private:
    Attica::Provider m_provider;
};
 
#endif


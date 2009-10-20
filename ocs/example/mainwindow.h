#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <KXmlGuiWindow>
#include <KLineEdit>
#include <QLabel>


#include "../lib/providermanager.h"
#include "../lib/provider.h"

namespace Attica {
    class BaseJob;
}

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=0);

public Q_SLOTS:
    void providersChanged();

private:
    Attica::Provider m_provider;
    Attica::ProviderManager m_pm;
};
 
#endif


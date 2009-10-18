#include "mainwindow.h"


#include <KDebug>
#include <QVBoxLayout>
#include "simplepersonrequest.h"

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
    m_provider = Attica::Provider::createProvider("opendesktop");
    
    QTabWidget* mainWidget = new QTabWidget(this);
    setCentralWidget(mainWidget);
    
    SimplePersonRequest* personWidget = new SimplePersonRequest(m_provider, this);
    mainWidget->addTab(personWidget, tr("Person Search"));
        
    setupGUI();
}


#include "mainwindow.moc"

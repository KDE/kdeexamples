#include "mainwindow.h"


#include <KDebug>
#include <QVBoxLayout>
#include "simplepersonrequest.h"
#include "contentdownload.h"
#include "contentcreation.h"
#include "providermanager.h"

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
    Attica::ProviderManager pm;
    m_provider = pm.providerById("opendesktop");
    //m_provider = Attica::Provider::createProvider("opendesktop");
    
    QTabWidget* mainWidget = new QTabWidget(this);
    setCentralWidget(mainWidget);
 
    ContentCreation* contentCreationWidget = new ContentCreation(m_provider, this);
    mainWidget->addTab(contentCreationWidget, tr("Add Content"));
       
    ContentDownload* contentWidget = new ContentDownload(m_provider, this);
    mainWidget->addTab(contentWidget, tr("Content"));
    
    SimplePersonRequest* personWidget = new SimplePersonRequest(m_provider, this);
    mainWidget->addTab(personWidget, tr("Person Search"));

    setupGUI();
}


#include "mainwindow.moc"

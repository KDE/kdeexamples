#include "mainwindow.h"


#include <KDebug>
#include <QVBoxLayout>
#include "simplepersonrequest.h"
#include "contentdownload.h"
#include "contentcreation.h"
#include "providermanager.h"

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
    connect(&m_pm, SIGNAL(providersChanged()), SLOT(providersChanged()));
    m_pm.initialize();
 
    setupGUI();
}

void MainWindow::providersChanged()
{
    if (m_pm.contains("opendesktop")) {
        m_provider = m_pm.providerById("opendesktop");

        QTabWidget* mainWidget = new QTabWidget(this);
        setCentralWidget(mainWidget);

        ContentCreation* contentCreationWidget = new ContentCreation(m_provider, this);
        mainWidget->addTab(contentCreationWidget, tr("Add Content"));

        ContentDownload* contentWidget = new ContentDownload(m_provider, this);
        mainWidget->addTab(contentWidget, tr("Content"));

        SimplePersonRequest* personWidget = new SimplePersonRequest(m_provider, this);
        mainWidget->addTab(personWidget, tr("Person Search"));
    }
}


#include "mainwindow.moc"

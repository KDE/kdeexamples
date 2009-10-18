#include "mainwindow.h"

#include "../lib/person.h"
#include "../lib/personjob.h"

#include <KDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    
    QVBoxLayout* layout = new QVBoxLayout(mainWidget);
    
    mLineEdit = new KLineEdit();
    layout->addWidget(mLineEdit);
    mNick = "fregl";
    mLineEdit->setText(mNick);
    connect(mLineEdit, SIGNAL(returnPressed(QString)), SLOT(nickChanged(QString)));
    
    QHBoxLayout* hLayout = new QHBoxLayout;
    layout->addLayout(hLayout);
    
    mPictureLabel = new QLabel(mainWidget);
    mPictureLabel->setText("Picture");
    hLayout->addWidget(mPictureLabel);
    
    mNameLabel = new QLabel(mainWidget);
    mNameLabel->setText("Name");
    hLayout->addWidget(mNameLabel);
    
    setupGUI();
    initOcs();
}

void MainWindow::nickChanged(const QString& nick)
{
    mNick = nick;
    initOcs();
}

void MainWindow::initOcs()
{
    m_provider = Attica::Provider::createProvider("opendesktop");
    kDebug() << "base" << m_provider.baseUrl();
    
    kDebug() << "init OCS";

    Attica::PersonJob* job = m_provider.requestPerson(mNick);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(onPersonJobFinished(Attica::BaseJob*)));
}

void MainWindow::onPersonJobFinished( Attica::BaseJob *job )
{
    kDebug() << "onJobFinished";
    Attica::PersonJob *personJob = static_cast< Attica::PersonJob * >( job );
    if( personJob->error() == 0 )
    {
        Attica::Person p(personJob->result());
        mNameLabel->setText(p.firstName() + ' ' + p.lastName() + '\n' +
            p.city() + "; " + p.country());
        mPictureLabel->setPixmap(p.avatar());
    } else {
        mNameLabel->setText("Could not fetch information.");
    }
}

#include "mainwindow.moc"

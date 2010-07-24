// This code is released into the public domain by the author Martin T. Sandsmark

#include "dialog.h"

#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QMap>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    setLayout(new QVBoxLayout);
    m_wallet = Wallet::openWallet(Wallet::NetworkWallet(),
                                  winId(),
                                  Wallet::Asynchronous);

    QLabel *explanation = new QLabel("<b>HELLO!</b><br/>"
                                     "Please type in something to save in the wallet!<br/>"
                                     "It will be saved in the form data folder, under <br/>"
                                     "the entry <i>http://test.com/#form</i>.");
    m_statusLabel = new QLabel("Opening wallet...", this);
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_keyInput = new QLineEdit(this);
    m_valueInput = new QLineEdit(this);
    m_launchButton = new QPushButton("Save!", this);
    m_launchButton->setDisabled(true);

    layout()->addWidget(explanation);
    qobject_cast<QVBoxLayout*>(layout())->addStretch();
    layout()->addWidget(m_statusLabel);
    layout()->addWidget(new QLabel("Key:", this));
    layout()->addWidget(m_keyInput);
    layout()->addWidget(new QLabel("Value:", this));
    layout()->addWidget(m_valueInput);
    layout()->addWidget(m_launchButton);

    connect(m_launchButton, SIGNAL(clicked()), SLOT(doSave()));
    connect(m_wallet, SIGNAL(walletOpened(bool)), SLOT(walletOpened(bool)));
    setMinimumSize(500, 200);
}

void Dialog::walletOpened(bool ok)
{

    if (ok &&
        (m_wallet->hasFolder(KWallet::Wallet::FormDataFolder()) ||
        m_wallet->createFolder(KWallet::Wallet::FormDataFolder())) &&
        m_wallet->setFolder(KWallet::Wallet::FormDataFolder())) {
        m_launchButton->setDisabled(false);
        m_statusLabel->setText("Idle.");
    } else
        m_statusLabel->setText("Error opening wallet!");

}

void Dialog::doSave()
{
    if (m_keyInput->text().isEmpty() || m_valueInput->text().isEmpty()) {
        m_statusLabel->setText("Empty field!");
        return;
    }

    m_launchButton->setDisabled(true);

    m_statusLabel->setText("Saving ...");

    QMap<QString, QString> map;
    map[m_keyInput->text()] = m_valueInput->text();
    if (m_wallet->writeMap("http://test.com/#form", map)) m_statusLabel->setText("Something went wrong!");
    else {
        m_statusLabel->setText("Saved!");
        m_keyInput->clear();
        m_valueInput->clear();
    }
    m_launchButton->setDisabled(false);
}


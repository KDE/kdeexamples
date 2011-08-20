// This code is released into the public domain by the author Martin T. Sandsmark

#include "dialog.h"

#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>

#include <KLocale>
#include <KWallet/Wallet>

using KWallet::Wallet;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    m_wallet = Wallet::openWallet(Wallet::LocalWallet(),
                                  winId(),
                                  Wallet::Asynchronous);
    connect(m_wallet, SIGNAL(walletOpened(bool)), SLOT(walletOpened(bool)));

    QLabel *explanation = new QLabel(i18n("<b>HELLO!</b><br/>"
                                     "Please type in something to save in the wallet.<br/>"
                                     "It will be saved in the form data folder, under <br/>"
                                     "the entry <i>http://test.com/#form</i>."), this);
    m_statusLabel = new QLabel(i18n("Opening wallet..."), this);
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_keyInput = new QLineEdit(this);
    m_keyOutput = new QLineEdit(this);
    m_keyOutput->setDisabled(true);
    m_valueInput = new QLineEdit(this);
    m_valueOutput = new QLineEdit(this);
    m_valueOutput->setDisabled(true);
    m_launchButton = new QPushButton(i18n("Save"), this);
    m_launchButton->setDisabled(true);
    m_retrieveButton = new QPushButton(i18n("Retrieve"), this);
    m_retrieveButton->setDisabled(true);

    setLayout(new QVBoxLayout(this));
    layout()->addWidget(explanation);
    qobject_cast<QVBoxLayout*>(layout())->addStretch();
    layout()->addWidget(m_statusLabel);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QVBoxLayout *vLayout;

    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(new QLabel(i18n("Key:"), this));
    vLayout->addWidget(m_keyInput);
    vLayout->addWidget(new QLabel(i18n("Value:"), this));
    vLayout->addWidget(m_valueInput);
    vLayout->addWidget(m_launchButton);
    hLayout->addLayout(vLayout);

    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(new QLabel(i18n("Key:"), this));
    vLayout->addWidget(m_keyOutput);
    vLayout->addWidget(new QLabel(i18n("Value:"), this));
    vLayout->addWidget(m_valueOutput);
    vLayout->addWidget(m_retrieveButton);
    hLayout->addLayout(vLayout);

    layout()->addItem(hLayout);

    connect(m_launchButton, SIGNAL(clicked()), SLOT(doSave()));
    connect(m_retrieveButton, SIGNAL(clicked()), SLOT(doRetrieve()));

    setMinimumSize(500, 200);
}

void Dialog::walletOpened(bool ok)
{

    if (ok) {
        if (!m_wallet->hasFolder(KWallet::Wallet::FormDataFolder()))
            m_wallet->createFolder(KWallet::Wallet::FormDataFolder());

        m_wallet->setFolder(KWallet::Wallet::FormDataFolder());
        m_statusLabel->setText(i18n("Wallet opened."));
        m_launchButton->setDisabled(false);
        m_retrieveButton->setDisabled(false);
    } else {
        m_statusLabel->setText(i18n("Error opening wallet!"));
    }
}

void Dialog::doSave()
{
    if (m_keyInput->text().isEmpty() || m_valueInput->text().isEmpty()) {
        m_statusLabel->setText(i18n("Empty field!"));
        return;
    }

    m_launchButton->setDisabled(true);
    m_retrieveButton->setDisabled(true);

    m_statusLabel->setText(i18n("Saving ..."));

    QMap<QString, QString> map;
    map[m_keyInput->text()] = m_valueInput->text();
    if (m_wallet->writeMap("http://test.com/#form", map)) {
        m_statusLabel->setText(i18n("Something went wrong!"));
    } else {
        m_statusLabel->setText(i18n("Saved!"));
        m_keyInput->clear();
        m_valueInput->clear();
    }

    m_launchButton->setDisabled(false);
    m_retrieveButton->setDisabled(false);
}

void Dialog::doRetrieve()
{
    m_launchButton->setDisabled(true);
    m_retrieveButton->setDisabled(true);

    m_statusLabel->setText(i18n("Retrieving ..."));

    QMap<QString, QString> map;
    if (m_wallet->readMap("http://test.com/#form", map)) {
        m_statusLabel->setText(i18n("Something went wrong!"));
    } else {
        m_statusLabel->setText(i18n("Retrieved!"));
        QMapIterator<QString, QString> i(map);
        if (i.hasNext())
        {
            i.next();
            m_keyOutput->setText(i.key());
            m_valueOutput->setText(i.value());
        }
    }

    m_launchButton->setDisabled(false);
    m_retrieveButton->setDisabled(false);
}

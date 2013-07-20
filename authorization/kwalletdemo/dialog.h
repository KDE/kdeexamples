// This code is released into the public domain by the author Martin T. Sandsmark

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;

namespace KWallet {
class Wallet;
}

class Dialog : public QDialog
{
Q_OBJECT

public:
    Dialog(QWidget *parent = 0);

private Q_SLOTS:
    void doSave();
    void doRetrieve();

    void walletOpened(bool ok);

private:
    KWallet::Wallet *m_wallet;

    QLabel *m_statusLabel;
    QLineEdit *m_keyInput, *m_keyOutput;
    QLineEdit *m_valueInput, *m_valueOutput;
    QPushButton *m_launchButton, *m_retrieveButton;
};

#endif // DIALOG_H

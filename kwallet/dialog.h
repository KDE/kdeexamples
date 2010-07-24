// This code is released into the public domain by the author Martin T. Sandsmark

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <KWallet/Wallet>

using KWallet::Wallet;

class Dialog : public QDialog
{
Q_OBJECT
public:
    Dialog(QWidget *parent = 0);

private slots:
    void doSave();
    void walletOpened(bool ok);

private:
    Wallet *m_wallet;
    QLineEdit *m_keyInput;
    QLineEdit *m_valueInput;
    QLabel *m_statusLabel;
    QPushButton *m_launchButton;
};

#endif // DIALOG_H

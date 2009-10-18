#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <KXmlGuiWindow>
#include <KLineEdit>
#include <QLabel>

namespace Attica {
    class BaseJob;
}

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=0);

    void initOcs();

public Q_SLOTS:
    void nickChanged(const QString& nick);
    void onPersonJobFinished( Attica::BaseJob *job );


private:
    KLineEdit* mLineEdit;
    QLabel* mNameLabel;
    QLabel* mPictureLabel;
    QString mNick;
};
 
#endif


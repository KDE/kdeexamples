#ifndef PLTEST_H
#define PLTEST_H

#include <KIcon>

#include <Plasma/Applet>
#include <Plasma/Svg>

class PlasmaAnimationExample : public Plasma::Applet
{
    Q_OBJECT

public:
    PlasmaAnimationExample(QObject *parent, const QVariantList &args);

    void init();

private slots:

    void startAll();
    void revertDirection();

private:
    QSequentialAnimationGroup *m_seqGroup;
};

#endif

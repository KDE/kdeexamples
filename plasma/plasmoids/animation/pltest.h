#ifndef PLTEST_H
#define PLTEST_H

#include <KIcon>

#include <Plasma/Applet>
#include <Plasma/Svg>


class PlasmaAnimTest : public Plasma::Applet
{
    Q_OBJECT
    public:
        PlasmaAnimTest(QObject *parent, const QVariantList &args);
        ~PlasmaAnimTest();

    void init();

};
 
#endif

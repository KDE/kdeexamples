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
};
 
#endif

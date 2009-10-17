#include "PlasmaAnimationExample.h"

#include <QPainter>
#include <QPushButton>
#include <QFontMetrics>
#include <QSizeF>

#include <plasma/svg.h>
#include <plasma/theme.h>
#include <plasma/widgets/pushbutton.h>

#include <plasma/animations/animationgroup.h>
#include <plasma/animations/grow.h>
#include <plasma/animations/slide.h>
#include <plasma/animations/expand.h>
#include <plasma/animations/fade.h>
#include <plasma/animations/rotation.h>
#include <plasma/animations/pulser.h>

using namespace Plasma;

K_EXPORT_PLASMA_APPLET(plasma-applet-pltest, PlasmaAnimationExample)

PlasmaAnimationExample::PlasmaAnimationExample(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args)
{
    // set a default size
    resize(300, 400);
}

void PlasmaAnimationExample::init()
{

    PushButton* button1 = new PushButton(this);
    button1->setText("button1!");
    button1->setGeometry(QRectF(100, 100, 100, 25));

    PushButton* button2 = new PushButton(this);
    button2->setText("button2!");
    button2->setGeometry(QRectF(100, 200, 100, 25));

    PushButton* button3 = new PushButton(this);
    button3->setText("button3!");
    button3->setGeometry(QRectF(100, 300, 100, 25));

    //animation
    RotationAnimation *rotAnim = new RotationAnimation;
    rotAnim->setAxis(Qt::ZAxis);
    rotAnim->setReference(RotationAnimation::Center);
    rotAnim->setAngle(180);
    rotAnim->setWidget(button1);
    FadeAnimation *fadeAnim = new FadeAnimation(0.40);
    fadeAnim->setWidget(button1);

    PulseAnimation *pulseAnim = new PulseAnimation;
    pulseAnim->setWidget(button2);

    GrowAnimation *growAnim = new GrowAnimation(2.0);
    growAnim->setWidget(button3);
    SlideAnimation *slideAnim = new SlideAnimation(MoveDown, 30);
    slideAnim->setWidget(button3);

    //group 'em up!
    AnimationGroup *inner_g = new AnimationGroup();
    inner_g->setParallel(true);
    inner_g->add(rotAnim);
    inner_g->add(pulseAnim);
    inner_g->add(growAnim);

    AnimationGroup *outer_g = new AnimationGroup(this);
    outer_g->add(inner_g);
    outer_g->add(slideAnim);
    outer_g->add(fadeAnim);

    QObject::connect(button1, SIGNAL(clicked()), outer_g, SLOT(start()));

}

#include "PlasmaAnimationExample.moc"

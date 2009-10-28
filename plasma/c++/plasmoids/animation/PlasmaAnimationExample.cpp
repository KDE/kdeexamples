#include "PlasmaAnimationExample.h"

#include <QPainter>
#include <QPushButton>
#include <QFontMetrics>
#include <QSizeF>

#include <plasma/svg.h>
#include <plasma/theme.h>
#include <plasma/widgets/pushbutton.h>

#include <plasma/animations/animationgroup.h>
#include <plasma/animations/animation.h>

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
    AbstractAnimation *rotAnim =
      Plasma::Animator::create(Plasma::Animator::RotationAnimation);
    rotAnim->setProperty("axis", Qt::ZAxis);
    rotAnim->setProperty("reference", AbstractAnimation::Center);
    rotAnim->setProperty("angle", 180);
    rotAnim->setWidgetToAnimate(button1);

    AbstractAnimation *fadeAnim =
      Plasma::Animator::create(Plasma::Animator::FadeAnimation);
    fadeAnim->setProperty("startOpacity", 0.8);
    fadeAnim->setProperty("targetOpacity", 0.2);
    fadeAnim->setWidgetToAnimate(button1);

    AbstractAnimation *pulseAnim =
      Plasma::Animator::create(Plasma::Animator::PulseAnimation);
    pulseAnim->setWidgetToAnimate(button2);

    AbstractAnimation *growAnim =
      Plasma::Animator::create(Plasma::Animator::GrowAnimation);
    growAnim->setProperty("factor", 2.0);
    growAnim->setWidgetToAnimate(button3);

    AbstractAnimation *slideAnim =
      Plasma::Animator::create(Plasma::Animator::SlideAnimation);
    slideAnim->setProperty("direction", Plasma::MoveDown);
    slideAnim->setProperty("distance", 30);
    slideAnim->setWidgetToAnimate(button3);

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

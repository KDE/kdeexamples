#include "PlasmaAnimationExample.h"

#include <QPainter>
#include <QPushButton>
#include <QFontMetrics>
#include <QSizeF>

#include <plasma/svg.h>
#include <plasma/theme.h>
#include <plasma/widgets/pushbutton.h>

#include <plasma/animations/animation.h>

#include <QGraphicsLinearLayout>
#include <QGraphicsLayoutItem>
#include <QSequentialAnimationGroup>

using namespace Plasma;

Q_DECLARE_METATYPE(QGraphicsWidget*)
Q_DECLARE_METATYPE(QGraphicsLayoutItem*)

K_EXPORT_PLASMA_APPLET(plasma-applet-pltest, PlasmaAnimationExample)

PlasmaAnimationExample::PlasmaAnimationExample(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args)
{
    // set a default size
    resize(300, 400);
}

void PlasmaAnimationExample::init()
{
    QGraphicsLinearLayout *mLayout = new QGraphicsLinearLayout(this);
    QGraphicsWidget *frontWidget = new QGraphicsWidget(this);
    QGraphicsLinearLayout *frontLayout = new QGraphicsLinearLayout(Qt::Vertical, frontWidget);

    PushButton* button1 = new PushButton(frontWidget);
    button1->setText("Press me!");

    PushButton *button2 = new PushButton(frontWidget);
    button2->setText("Pulse Animation!");

    PushButton* button3 = new PushButton(frontWidget);
    button3->setText("Grow Animation!");

    PushButton *button4 = new PushButton(frontWidget);
    button4->setText("Fade Animation!");
    
    PushButton *button5 = new PushButton(frontWidget);
    button5->setText("Slide Animation!");
    
    PushButton *button6 = new PushButton(frontWidget);
    button6->setText("Rotation stacked!");
    
    PushButton *button7 = new PushButton(frontWidget);
    button7->setText("Rotation!");

    PushButton *button8 = new PushButton(frontWidget);
    button8->setText("Zoom");


    frontLayout->addItem(button1);
    frontLayout->addItem(button2);
    frontLayout->addItem(button3);
    frontLayout->addItem(button4);
    frontLayout->addItem(button8);
    frontLayout->addItem(button5);
    frontLayout->addItem(button6);
    frontLayout->addItem(button7);


    qRegisterMetaType<QGraphicsLayoutItem *>("QGraphicsLayoutItem *");

    Animation* rotStackedAnim =
        Plasma::Animator::create(Plasma::Animator::RotationStackedAnimation);
    rotStackedAnim->setTargetWidget(frontWidget);
    QVariant var;
    var.setValue(static_cast<QGraphicsWidget*>(button6));
    rotStackedAnim->setProperty("backWidget", var);
    rotStackedAnim->setProperty("reference", Animation::Center);
    rotStackedAnim->setProperty("movementDirection", Plasma::MoveRight);
    //rotStackedAnim->setProperty("duration", 1000);
    QVariant varLayout = rotStackedAnim->property("layout");
    mLayout->addItem(varLayout.value<QGraphicsLayoutItem*>());

    //animation
    Animation *rotAnim =
      Plasma::Animator::create(Plasma::Animator::RotationAnimation);
    rotAnim->setProperty("axis", Qt::ZAxis);
    rotAnim->setProperty("reference", Animation::Center);
    rotAnim->setProperty("angle", 180);
    rotAnim->setTargetWidget(button7);

    Animation *fadeAnim =
      Plasma::Animator::create(Plasma::Animator::FadeAnimation);
    fadeAnim->setProperty("startOpacity", 0.8);
    fadeAnim->setProperty("targetOpacity", 0.2);
    fadeAnim->setTargetWidget(button4);

    Animation *pulseAnim =
      Plasma::Animator::create(Plasma::Animator::PulseAnimation);
    pulseAnim->setTargetWidget(button2);

    Animation *growAnim =
      Plasma::Animator::create(Plasma::Animator::GrowAnimation);
    growAnim->setProperty("factor", 2.0);
    growAnim->setTargetWidget(button3);

    Animation *slideAnim =
      Plasma::Animator::create(Plasma::Animator::SlideAnimation);
    slideAnim->setProperty("movementDirection", Plasma::MoveDown);
    slideAnim->setProperty("distance", 30);
    slideAnim->setTargetWidget(button5);

    Animation *zoomAnim =
      Plasma::Animator::create(Plasma::Animator::ZoomAnimation);
    zoomAnim->setProperty("zoom", 2.0);
    zoomAnim->setTargetWidget(button8);

    //group 'em up!
    m_seqGroup = new QSequentialAnimationGroup(this);
    m_seqGroup->addAnimation(rotAnim);
    m_seqGroup->addAnimation(zoomAnim);
    m_seqGroup->addAnimation(fadeAnim);
    m_seqGroup->addAnimation(pulseAnim);
    m_seqGroup->addAnimation(growAnim);
    m_seqGroup->addAnimation(slideAnim);
    m_seqGroup->addAnimation(rotStackedAnim);

    QObject::connect(button1, SIGNAL(clicked()), this, SLOT(startAll()));
    QObject::connect(button6, SIGNAL(clicked()), this, SLOT(revertDirection()));
}

void PlasmaAnimationExample::revertDirection()
{
    if (m_seqGroup->property("direction") == QAbstractAnimation::Forward)
        m_seqGroup->setProperty("direction", QAbstractAnimation::Backward);
    m_seqGroup->start();

}
void PlasmaAnimationExample::startAll()
{
    if (m_seqGroup->property("direction") == QAbstractAnimation::Backward)
        m_seqGroup->setProperty("direction", QAbstractAnimation::Forward);
    m_seqGroup->start();
}


#include "PlasmaAnimationExample.moc"

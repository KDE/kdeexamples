#include "pltest.h"
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


using namespace Plasma;

K_EXPORT_PLASMA_APPLET(plasma-applet-pltest, PlasmaAnimTest)

PlasmaAnimTest::PlasmaAnimTest(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args)
{
    setBackgroundHints(DefaultBackground);
    resize(300, 400);
}


PlasmaAnimTest::~PlasmaAnimTest()
{
}

void PlasmaAnimTest::init()
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
    //GrowAnimation *a = new GrowAnimation(2.0);
    RotationAnimation *a = new RotationAnimation;
    a->setAxis(Qt::ZAxis);
    a->setReference(RotationAnimation::Center);
    a->setAngle(180);
    a->setWidget(button1);

    GrowAnimation *b = new GrowAnimation(2.0);
    b->setWidget(button2);

    SlideAnimation *c = new SlideAnimation(MoveDown, 30);
    c->setWidget(button3);

    FadeAnimation *d = new FadeAnimation(0.40);
    d->setWidget(button1);

    //group 'em up!
    AnimationGroup *inner_g = new AnimationGroup();
    inner_g->setParallel(true);
    inner_g->add(a);
    inner_g->add(b);

    AnimationGroup *outer_g = new AnimationGroup(this);
    outer_g->add(inner_g);
    outer_g->add(c);
    outer_g->add(d);

    QObject::connect(button1, SIGNAL(clicked()), outer_g, SLOT(start()));

}

#include "pltest.moc"

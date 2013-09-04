/**
 * Copyright 2011 Aaron Seigo <aseigo@kde.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **/

#include "tooltips.h"

#include <QGraphicsLinearLayout>

#include <KIcon>

#include <Plasma/IconWidget>
#include <Plasma/ToolTipManager>

ToolTipExample::ToolTipExample(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
      m_count(0)
{
    // setup a simple user interface: a single icon
    Plasma::IconWidget *icon = new Plasma::IconWidget(this);
    icon->setIcon(KIcon("plasma"));

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(this);
    layout->addStretch();
    layout->addItem(icon);

    // now we will create a static tooltip for the icon
    Plasma::ToolTipContent content(i18n("This is an icon!"), i18n("Here is more text"), KIcon("plasma"));
    Plasma::ToolTipManager::self()->setContent(icon, content);

    // now we will register the applet itself for a tooltip as well, but this time it will be
    // a dynamic one: we will set the content in toolTipAboutToShow and clear it in toolTipHidden
    Plasma::ToolTipManager::self()->registerWidget(this);
}

void ToolTipExample::toolTipAboutToShow()
{
    // the ToolTip is about to show! Set up some content.
    Plasma::ToolTipContent content;
    content.setMainText(i18np("This tooltip has been shown once.",
                              "This tooltip has been shown %1 times",
                              ++m_count));
    Plasma::ToolTipManager::self()->setContent(this, content);

    // we could also start updating the ToolTip, e.g. with a timer, and stop the 
    // updating in toolTipHidden
}

void ToolTipExample::toolTipHidden()
{
    // our ToolTip has been hidden; we can, if we wish, do something in response to that
    // such as stop any ToolTip updating code or even just clear the data from memory
    Plasma::ToolTipManager::self()->clearContent(this);
}

K_EXPORT_PLASMA_APPLET(org.kde.exampletooltips, ToolTipExample)
#include "tooltips.moc"


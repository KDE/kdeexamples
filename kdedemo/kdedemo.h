/*
 * Copyright 2011 Jon Ander Peñalba <jonan88@gmail.com>
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
 */

#ifndef KDEDEMO_H
#define KDEDEMO_H

#include <QtCore/QList>
#include <Plasma/Applet>

class QGraphicsGridLayout;

namespace Plasma {
class Label;
class PushButton;
}

struct Category;

class KdeDemo : public Plasma::Applet
{
    Q_OBJECT

    public:
        KdeDemo(QObject *parent, const QVariantList &args);
        ~KdeDemo();

        void init();

    signals:
        void hideCategories();
        void showCategories();

    private slots:
        void loadExamples();
        void backToCategories();

    private:
        void loadButtons(QList<Plasma::PushButton*> list, QString m_text);
        void loadConfig();
        void loadTextFromFile(QString tittle, QString file_name);

        QList<Category> m_categories;
        QList<Plasma::PushButton*> m_category_buttons, m_current_buttons;
        QList< QList<Plasma::PushButton*> > m_example_buttons;
        Plasma::PushButton *m_back_button, *m_quit_launch_button;
        Plasma::Label *m_text, *m_tittle;
        QGraphicsGridLayout *m_layout;
};

#endif // KDEDEMO_H

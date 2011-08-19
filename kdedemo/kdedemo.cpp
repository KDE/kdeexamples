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

#include "kdedemo.h"

#include <QtCore/QProcess>
#include <QtGui/QGraphicsGridLayout>
#include <QtGui/QGraphicsLinearLayout>

#include <KStandardDirs>

#include <Plasma/Animator>
#include <Plasma/Label>
#include <Plasma/PushButton>

#include "xmlhandler.h"

// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(kdedemo, KdeDemo)

KdeDemo::KdeDemo(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args)
    , m_back_button(new Plasma::PushButton)
    , m_quit_launch_button(new Plasma::PushButton)
    , m_show_source_button(new Plasma::PushButton)
    , m_text(new Plasma::Label)
    , m_tittle(new Plasma::Label)
    , m_layout(new QGraphicsGridLayout)
    , m_current_category(new Category)
    , m_current_example(new Example)
{
    setBackgroundHints(DefaultBackground);
}

KdeDemo::~KdeDemo()
{
}

void KdeDemo::init()
{
    m_layout->setColumnFixedWidth(0, 200);
    m_layout->setColumnMinimumWidth(1, 300);
    m_layout->setRowMaximumHeight(1, 30);
    m_layout->setHorizontalSpacing(15);
    m_layout->setVerticalSpacing(30);

    m_tittle->setAlignment(Qt::AlignCenter);

    m_text->setAlignment(Qt::AlignJustify);
    loadTextFromFile("KDE Examples and Demos", KStandardDirs::locate("data", "kdeexamples/README"));
    m_layout->addItem(m_text, 0, 1, Qt::AlignCenter);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
    m_back_button->setText("Back");
    m_back_button->hide();
    connect(m_back_button, SIGNAL(clicked()), this, SLOT(backToCategories()));
    layout->addItem(m_back_button);
    m_layout->addItem(layout, 1, 0);

    layout = new QGraphicsLinearLayout(Qt::Horizontal);
    layout->addStretch();
    m_show_source_button->setText("Show Source Code");
    m_show_source_button->hide();
    connect(m_show_source_button, SIGNAL(clicked()), this, SLOT(openSourceCode()));
    layout->addItem(m_show_source_button);
    m_quit_launch_button->setText("Quit");
    connect(m_quit_launch_button, SIGNAL(clicked()), this, SLOT(destroy()));
    layout->addItem(m_quit_launch_button);
    m_layout->addItem(layout, 1, 1);

    setLayout(m_layout);

    loadConfig();
    if (hasFailedToLaunch())
        return;

    foreach (Category c, m_categories) {
        Plasma::PushButton *button = new Plasma::PushButton;
        button->setText(c.name);
        connect(button, SIGNAL(clicked()), this, SLOT(loadExampleList()));
        m_category_buttons.push_back(button);

        QList<Plasma::PushButton*> x;
        m_example_buttons.push_back(x);

        foreach (Example e, c.examples) {
            Plasma::PushButton *button = new Plasma::PushButton;
            button->setText(e.name);
            connect(button, SIGNAL(clicked()), this, SLOT(loadExample()));
            m_example_buttons.back().push_back(button);
        }
    }
    loadButtons(m_category_buttons, "Categories");
}

void KdeDemo::loadExampleList()
{
    Plasma::PushButton *button = qobject_cast<Plasma::PushButton*>(sender());
    if (!button)
        return;

    foreach (Plasma::PushButton *b, m_category_buttons)
        b->hide();
    m_back_button->show();

    int index = m_category_buttons.indexOf(button);
    *m_current_category = m_categories.at(index);
    QString file("kdeexamples/" + m_current_category->dirName + "/README");
    loadTextFromFile(m_current_category->name, KStandardDirs::locate("data", file));
    loadButtons(m_example_buttons.at(index), button->text());
}

void KdeDemo::loadExample()
{
    Plasma::PushButton *button = qobject_cast<Plasma::PushButton*>(sender());
    if (!button)
        return;

    m_show_source_button->show();
    m_quit_launch_button->disconnect();
    m_quit_launch_button->setText("Launch");
    connect(m_quit_launch_button, SIGNAL(clicked()), this, SLOT(launchExample()));

    int i = m_categories.indexOf(*m_current_category);
    int j = m_example_buttons.at(i).indexOf(button);

    *m_current_example = m_current_category->examples.at(j);
    QString file("kdeexamples/" + m_current_category->dirName + "/" + m_current_example->fileName + "/README");
    loadTextFromFile(m_current_example->name, KStandardDirs::locate("data", file));
}

void KdeDemo::backToCategories()
{
    foreach (Plasma::PushButton *b, m_current_buttons)
        b->hide();
    m_back_button->hide();
    m_show_source_button->hide();
    loadButtons(m_category_buttons, "Categories");
    loadTextFromFile("KDE Examples and Demos", KStandardDirs::locate("data", "kdeexamples/README"));
    m_quit_launch_button->disconnect();
    m_quit_launch_button->setText("Quit");
    connect(m_quit_launch_button, SIGNAL(clicked()), this, SLOT(destroy()));
}

void KdeDemo::openSourceCode()
{
    QString dir(KStandardDirs::locate("data", "kdeexamples/" + m_current_category->dirName + "/" + m_current_example->fileName + "/"));
    if (dir.isEmpty())
        return;

    QProcess *process = new QProcess(this);
    process->setWorkingDirectory(dir);
    process->start("ls");
    process->waitForFinished(-1);
    QString files = process->readAll();

    process = new QProcess(this);
    process->setWorkingDirectory(dir);
    process->start(KStandardDirs::locate("exe", "kate"), QStringList() << "-n" << files.split("\n", QString::SkipEmptyParts));
}

void KdeDemo::launchExample()
{
    QProcess *myProcess = new QProcess(this);
    myProcess->start(KStandardDirs::locate("exe", m_current_example->fileName));
}

void KdeDemo::loadButtons(QList<Plasma::PushButton*> list, QString text)
{
    m_current_buttons = list;
    foreach (Plasma::PushButton *b, m_current_buttons)
        b->show();
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
    m_tittle->setText("<h2>"+text+"</h2>");
    layout->addItem(m_tittle);
    foreach (Plasma::PushButton *b, list)
        layout->addItem(b);
    layout->addStretch();

    m_layout->addItem(layout, 0, 0);
}

void KdeDemo::loadConfig()
{
    QString file_name = KStandardDirs::locate("data", "kdeexamples/kdedemo/");
    if (file_name.isEmpty()) {
        setFailedToLaunch(true, "No config file");
        return;
    }

    QXmlSimpleReader xmlReader;
    XmlHandler handler;
    xmlReader.setContentHandler(&handler);
    QXmlInputSource *source = new QXmlInputSource(new QFile(file_name + "examples.xml"));
    if (xmlReader.parse(source))
        m_categories = handler.getCategories();
}

void KdeDemo::loadTextFromFile(QString tittle, QString file_name)
{
    QString text_string("<h1>" + tittle + "</h1>");
    QFile file(file_name);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        text_string += "<p>";
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.isEmpty())
                text_string += "</p><p>";
            else
                text_string += line;
        }
        text_string += "</p>";
    } else {
        text_string += "<p>No description available</p>";
    }
    m_text->setText(text_string);
}

/* This file is part of the KDE libraries
 *
 * Copyright (c) 2011 Aurélien Gâteau <agateau@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */
#include <window.h>

// KDE
#include <KAction>
#include <KLocale>
#include <KMessageWidget>
#include <KStandardAction>

// Qt
#include <QCheckBox>
#include <QCoreApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

Window::Window(QWidget *parent)
: KMainWindow(parent)
{
    QWidget* widget = new QWidget;
    setCentralWidget(widget);
    resize(500, 400);

    m_layout = new QVBoxLayout(widget);

    m_messageWidget = new KMessageWidget(this);
    m_messageWidget->hide();
    m_layout->addWidget(m_messageWidget);

    m_layout->addStretch();
    createButton(i18n("Error"), SLOT(showErrorMessage()));
    createButton(i18n("Warning"), SLOT(showWarningMessage()));
    createButton(i18n("Information"), SLOT(showInformationMessage()));
    createButton(i18n("Positive"), SLOT(showPositiveMessage()));
    m_layout->addStretch();

    m_actions
        << new QAction(i18n("Action 1"), this)
        << new QAction(i18n("Action 2"), this)
        ;

    QCheckBox* wordwrapCheckBox = new QCheckBox(i18n("Word wrap"));
    m_layout->addWidget(wordwrapCheckBox);
    connect(wordwrapCheckBox, SIGNAL(toggled(bool)), m_messageWidget, SLOT(setWordWrap(bool)));

    QCheckBox* showActionsCheckBox = new QCheckBox(i18n("Show action buttons"));
    m_layout->addWidget(showActionsCheckBox);
    connect(showActionsCheckBox, SIGNAL(toggled(bool)), SLOT(showActions(bool)));

    QCheckBox* showCloseButtonCheckBox = new QCheckBox(i18n("Show close button"));
    showCloseButtonCheckBox->setChecked(true);
    m_layout->addWidget(showCloseButtonCheckBox);
    connect(showCloseButtonCheckBox, SIGNAL(toggled(bool)),m_messageWidget, SLOT(setCloseButtonVisible(bool)));

    m_animatedShowCheckBox = new QCheckBox(i18n("Animated"));
    m_animatedShowCheckBox->setChecked(true);
    m_layout->addWidget(m_animatedShowCheckBox);

    addAction(KStandardAction::quit(qApp, SLOT(quit()), this));
}

void Window::createButton(const QString& label, const char* slot)
{
    QPushButton* button = new QPushButton(label, this);
    connect(button, SIGNAL(clicked(bool)), slot);
    m_layout->addWidget(button);
}

void Window::showErrorMessage()
{
    m_messageWidget->setText(i18n("Sorry, wrong password"));
    m_messageWidget->setMessageType(KMessageWidget::ErrorMessageType);
    showMessage();
}

void Window::showWarningMessage()
{
    m_messageWidget->setText(i18n("You have some unsaved changes"));
    m_messageWidget->setMessageType(KMessageWidget::WarningMessageType);
    showMessage();
}

void Window::showInformationMessage()
{
    m_messageWidget->setText(i18n("The weather is great!"));
    m_messageWidget->setMessageType(KMessageWidget::InformationMessageType);
    showMessage();
}

void Window::showPositiveMessage()
{
    m_messageWidget->setText(i18n("All your files have been backed up"));
    m_messageWidget->setMessageType(KMessageWidget::PositiveMessageType);
    showMessage();
}

void Window::showMessage()
{
    if (m_animatedShowCheckBox->isChecked()) {
        m_messageWidget->animatedShow();
    } else {
        m_messageWidget->show();
    }
}

void Window::showActions(bool show)
{
    if (show) {
        Q_FOREACH(QAction* action, m_actions) {
            m_messageWidget->addAction(action);
        }
    } else {
        Q_FOREACH(QAction* action, m_actions) {
            m_messageWidget->removeAction(action);
        }
    }
}

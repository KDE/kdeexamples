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
#include <KTextEdit>
#include <kdeversion.h>

// Qt
#include <QCheckBox>
#include <QCoreApplication>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

Window::Window(QWidget *parent)
    : KMainWindow(parent)
{
    QWidget* widget = new QWidget;
    setCentralWidget(widget);
    resize(500, 400);

    m_actions
        << new QAction(KIcon("document-save"), i18n("Save"), this)
        << new QAction(i18n("Discard"), this)
        ;

    QVBoxLayout* mainLayout = new QVBoxLayout(widget);

    // KMessageWidget
    m_messageWidget = new KMessageWidget(this);
    m_messageWidget->hide();
    mainLayout->addWidget(m_messageWidget);

    // Message buttons
    {
        QGroupBox* groupBox = new QGroupBox();
        groupBox->setTitle(i18n("Show/hide message widget"));
        mainLayout->addWidget(groupBox);
        QVBoxLayout* layout = new QVBoxLayout(groupBox);

        createMessageButton(layout, i18n("Error"), SLOT(showErrorMessage()));
        createMessageButton(layout, i18n("Warning"), SLOT(showWarningMessage()));
        createMessageButton(layout, i18n("Information"), SLOT(showInformationMessage()));
        createMessageButton(layout, i18n("Positive"), SLOT(showPositiveMessage()));
    }

    // Text
    {
        QGroupBox* groupBox = new QGroupBox();
        groupBox->setTitle(i18n("Text"));
        mainLayout->addWidget(groupBox);
        QVBoxLayout* layout = new QVBoxLayout(groupBox);

        m_edit = new KTextEdit;
        m_edit->setClickMessage(i18n("Use default text"));
        layout->addWidget(m_edit);
    }

    // Options
    {
        QGroupBox* groupBox = new QGroupBox();
        groupBox->setTitle(i18n("Options"));
        mainLayout->addWidget(groupBox);
        QVBoxLayout* layout = new QVBoxLayout(groupBox);

        QCheckBox* wordwrapCheckBox = new QCheckBox(i18n("Word wrap"));
        layout->addWidget(wordwrapCheckBox);
        connect(wordwrapCheckBox, SIGNAL(toggled(bool)), m_messageWidget, SLOT(setWordWrap(bool)));

        QCheckBox* showActionsCheckBox = new QCheckBox(i18n("Show action buttons"));
        layout->addWidget(showActionsCheckBox);
        connect(showActionsCheckBox, SIGNAL(toggled(bool)), SLOT(showActions(bool)));

        QCheckBox* showCloseButtonCheckBox = new QCheckBox(i18n("Show close button"));
        showCloseButtonCheckBox->setChecked(true);
        layout->addWidget(showCloseButtonCheckBox);
        connect(showCloseButtonCheckBox, SIGNAL(toggled(bool)),m_messageWidget, SLOT(setCloseButtonVisible(bool)));

        m_animatedShowCheckBox = new QCheckBox(i18n("Animated"));
        m_animatedShowCheckBox->setChecked(true);
        layout->addWidget(m_animatedShowCheckBox);

        QLabel* iconLabel = new QLabel("Icon:");
        layout->addWidget(iconLabel);

        m_iconComboBox = new QComboBox;
        iconLabel->setBuddy(m_iconComboBox);
        QStringList names = QStringList() << QString() << "preferences-system-network" << "document-save" << "system-users";
        Q_FOREACH(const QString &name, names) {
            QIcon icon = QIcon::fromTheme(name);
            m_iconComboBox->addItem(icon, name.isEmpty() ? "none" : name);
        }
        connect(m_iconComboBox, SIGNAL(activated(int)), SLOT(setIconFromComboBox(int)));
        layout->addWidget(m_iconComboBox);
    }

    addAction(KStandardAction::quit(qApp, SLOT(quit()), this));
}

void Window::createMessageButton(QLayout* layout, const QString& label, const char* slot)
{
    QPushButton* button = new QPushButton(label);
    connect(button, SIGNAL(clicked(bool)), slot);
    layout->addWidget(button);
}

void Window::showErrorMessage()
{
    if (m_messageWidget->isVisible() && m_messageWidget->messageType() == KMessageWidget::Error) {
        hideMessage();
    } else {
        m_messageWidget->setText(messageText(i18n("Sorry, wrong password")));
        m_messageWidget->setMessageType(KMessageWidget::Error);
        showMessage();
    }
}

void Window::showWarningMessage()
{
    if (m_messageWidget->isVisible() && m_messageWidget->messageType() == KMessageWidget::Warning) {
        hideMessage();
    } else {
        m_messageWidget->setText(messageText(i18n("You have some unsaved changes")));
        m_messageWidget->setMessageType(KMessageWidget::Warning);
        showMessage();
    }
}

void Window::showInformationMessage()
{
    if (m_messageWidget->isVisible() && m_messageWidget->messageType() == KMessageWidget::Information) {
        hideMessage();
    } else {
        m_messageWidget->setText(messageText(i18n("The weather is great!")));
        m_messageWidget->setMessageType(KMessageWidget::Information);
        showMessage();
    }
}

void Window::showPositiveMessage()
{
    if (m_messageWidget->isVisible() && m_messageWidget->messageType() == KMessageWidget::Positive) {
        hideMessage();
    } else {
        m_messageWidget->setText(messageText(i18n("All your files have been backed up")));
        m_messageWidget->setMessageType(KMessageWidget::Positive);
        showMessage();
    }
}

QString Window::messageText(const QString& defaultText) const
{
    QString text = m_edit->toPlainText().trimmed();
    return text.isEmpty() ? defaultText : text;
}

void Window::showMessage()
{
    if (m_animatedShowCheckBox->isChecked()) {
        m_messageWidget->animatedShow();
    } else {
        m_messageWidget->show();
    }
}

void Window::hideMessage()
{
    if (m_animatedShowCheckBox->isChecked()) {
        m_messageWidget->animatedHide();
    } else {
        m_messageWidget->hide();
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

void Window::setIconFromComboBox(int index)
{
    // KMessageWidget::setIcon() requires KDE >= 4.11
#if KDE_VERSION >= KDE_MAKE_VERSION(4,10,60)
    QIcon icon = m_iconComboBox->itemIcon(index);
    m_messageWidget->setIcon(icon);
#endif
}

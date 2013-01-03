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
#ifndef WINDOW_H
#define WINDOW_H

// KDE
#include <KMainWindow>

class QCheckBox;
class QGroupBox;
class QVBoxLayout;

class KMessageWidget;

class Window : public KMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget* parent = 0);

private Q_SLOTS:
    void showErrorMessage();
    void showWarningMessage();
    void showInformationMessage();
    void showPositiveMessage();

    void showActions(bool show);

private:
    QVBoxLayout* m_layout;
    KMessageWidget* m_messageWidget;
    QList<QAction*> m_actions;
    QCheckBox* m_animatedShowCheckBox;
    QGroupBox* m_groupBox;

    void createButton(const QString& label, const char* slot);
    void showMessage();
    void hideMessage();
};

#endif // WINDOW_H

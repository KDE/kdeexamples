/*
 * Copyright 2011 Jon Ander Peñalba <jonan88@gmail.com>
 * Copyright 2009 Harald Fernengel <harry@kdevelop.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KMainWindow>

class QListWidgetItem;

class KComboBox;
class KListWidget;
class KTextBrowser;

class MainWindow : public KMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

  private Q_SLOTS:
    void populate();
    void currentItemChanged(QListWidgetItem *current);

  private:
    KListWidget *view;
    KTextBrowser *details;
    KComboBox *filterCombo;
};

#endif // MAINWINDOW_H

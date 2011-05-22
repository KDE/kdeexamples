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

#include "mainwindow.h"

#include <QGroupBox>
#include <QVBoxLayout>

#include <KDateComboBox>
#include <KDatePicker>
#include <KDateTable>
#include <KDateTimeEdit>
#include <KDateTimeWidget>
#include <KDateWidget>
#include <KCharSelect>
#include <KColorButton>
#include <KColorCombo>
#include <KColorPatch>
#include <KEditListWidget>
#include <KFontChooser>
#include <KFontComboBox>
#include <KGradientSelector>
#include <KHueSaturationSelector>
#include <KIntNumInput>
#include <KKeySequenceWidget>
#include <KLocale>
#include <KLineEdit>
#include <KPlotWidget>
#include <kratingwidget.h>
#include <kshortcutwidget.h>
#include <KTabWidget>
#include <KTimeComboBox>
#include <KTimeZoneWidget>
#include <KVBox>

MainWindow::MainWindow(QWidget *parent)
    : KMainWindow(parent)
{
    tabWidget = new KTabWidget(this);

    createInputTab();
    createDateTimeTab();
    createFontTab();
    createColorTab();

    setCentralWidget(tabWidget);
}

void MainWindow::createWidget(QString name, QWidget *widget, KVBox *parent)
{
  QGroupBox *groupBox = new QGroupBox(name, parent);
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(widget);
  groupBox->setLayout(layout);
}

void MainWindow::createInputTab()
{
  KHBox *tab = new KHBox(this);
  KVBox *column;

  // *** Column 1 ***
  column = new KVBox(tab);
  createWidget("KLineEdit", new KLineEdit(this), column);
  createWidget("KIntNumInput", new KIntNumInput(this), column);
  createWidget("KDoubleNumInput", new KDoubleNumInput(this), column);
  createWidget("KRatingWidget", new KRatingWidget(this), column);
  createWidget("KKeySequenceWidget", new KKeySequenceWidget(this), column);
  createWidget("KShortcutWidget", new KShortcutWidget(this), column);

  // *** Column 2 ***
  column = new KVBox(tab);
  createWidget("KEditListWidget", new KEditListWidget(this), column);
  createWidget("KPlotWidget", new KPlotWidget(this), column);

  tabWidget->addTab(tab, i18n("Input"));
}

void MainWindow::createDateTimeTab()
{
  KHBox *tab = new KHBox(this);
  KVBox *column;

  // *** Column 1 ***
  column = new KVBox(tab);
  createWidget("KDateComboBox", new KDateComboBox(this), column);
  createWidget("KTimeComboBox", new KTimeComboBox(this), column);
  createWidget("KDateTable", new KDateTable(this), column);
  createWidget("KDatePicker", new KDatePicker(this), column);
  createWidget("KDateWidget", new KDateWidget(this), column);
  createWidget("KDateTimeWidget", new KDateTimeWidget(this), column);

  // *** Column 2 ***
  column = new KVBox(tab);
  createWidget("KDateTimeEdit", new KDateTimeEdit(this), column);
  createWidget("KTimeZoneWidget", new KTimeZoneWidget(this), column);

  tabWidget->addTab(tab, i18n("Date && Time"));
}

void MainWindow::createFontTab()
{
  KHBox *tab = new KHBox(this);
  KVBox *column;

  // *** Column 1 ***
  column = new KVBox(tab);
  createWidget("KFontComboBox", new KFontComboBox(this), column);
  createWidget("KFontChooser", new KFontChooser(this), column);

  // *** Column 2 ***
  column = new KVBox(tab);
  createWidget("KCharSelect", new KCharSelect(this,NULL), column);

  tabWidget->addTab(tab, i18n("Font"));
}

void MainWindow::createColorTab()
{
  KHBox *tab = new KHBox(this);
  KVBox *column;

  // *** Column 1 ***
  column = new KVBox(tab);
  createWidget("KColorButton", new KColorButton(this), column);
  createWidget("KColorCombo", new KColorCombo(this), column);
  createWidget("KColorPatch", new KColorPatch(this), column);

  // *** Column 2 ***
  column = new KVBox(tab);
  createWidget("KGradientSelector", new KGradientSelector(this), column);
  createWidget("KHueSaturationSelector", new KHueSaturationSelector(this), column);

  tabWidget->addTab(tab, i18n("Color"));
}

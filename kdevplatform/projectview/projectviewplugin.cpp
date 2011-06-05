/*  This file is part of KDevelop
    Copyright 2010 Aleix Pol <aleixpol@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "projectviewplugin.h"
#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/iproject.h>
#include <KPluginFactory>
#include <KLocalizedString>
#include <KAboutData>
#include <QTreeView>

K_PLUGIN_FACTORY(ProjectViewFactory, registerPlugin<ProjectViewPlugin>(); )
K_EXPORT_PLUGIN(ProjectViewFactory(
    KAboutData("kdevprojectview","kdevprojectview",
               ki18n("Project View"), "0.1", ki18n("KDevPlatform example plugin with toolview"), KAboutData::License_GPL)))

using namespace KDevelop;

class KDevProjectViewFactory: public KDevelop::IToolViewFactory
{
    public:
        KDevProjectViewFactory( QAbstractItemModel *model ): model(model) {}
        
        virtual QWidget* create( QWidget *parent = 0 )
        {
            QTreeView* view=new QTreeView(parent);
            view->setHeaderHidden(true);
            view->setModel(model);
            return view;
        }
        
        virtual Qt::DockWidgetArea defaultPosition() { return Qt::LeftDockWidgetArea; }
        
        virtual QString id() const { return "org.kdevelop.ProjectViewPlugin"; }
        
    private:
        QAbstractItemModel *model;
};

ProjectViewPlugin::ProjectViewPlugin(QObject* parent, const QVariantList&)
    : KDevelop::IPlugin(ProjectViewFactory::componentData(), parent)
{
    m_model=new QStandardItemModel(this);
    
    core()->uiController()->addToolView(i18n("ProjectView"), new KDevProjectViewFactory(m_model));
    connect(core()->projectController(), SIGNAL(projectOpened(KDevelop::IProject*)), this, SLOT(projectOpened(KDevelop::IProject*)));
    connect(core()->projectController(), SIGNAL(projectClosed(KDevelop::IProject*)), this, SLOT(projectClosed(KDevelop::IProject*)));
}

void ProjectViewPlugin::projectOpened(IProject* p)
{
    m_model->appendRow(new QStandardItem(p->name()));
}

void ProjectViewPlugin::projectClosed(IProject* p)
{
    QList< QStandardItem* > items=m_model->findItems(p->name());
    if(!items.isEmpty()) {
        QStandardItem* it=items.takeFirst();
        m_model->removeRow(it->row());
    }
}


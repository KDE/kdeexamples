/*
This is a test case for KDE's iCalendar functionality.
(c) 2008 by Thorsten Staerk
*/

#include <QString>
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <KMainWindow>
#include <kcal/resourcecalendar.h>
#include <kcal/resourcecached.h>
#include <kcal/resourcelocal.h>

int main (int argc, char *argv[])
{
  const QByteArray& ba=QByteArray("test");
  const KLocalizedString name=ki18n("myName");
  KAboutData aboutData( ba, ba, name, ba, name);
  KCmdLineArgs::init( argc, argv, &aboutData );
  KApplication khello;
  KCal::ResourceCalendar* cal;
  KCal::ResourceCached* resource;
  resource=new KCal::ResourceLocal("/tmp/test.ics");
  cal=resource;
  cal->load();
  KCal::Todo* todo1 = new KCal::Todo();
  todo1->setSummary("test todo");
  cal->addTodo(todo1);
  KCal::Event* event1 = new KCal::Event();
  event1->setRelatedTo(todo1);
  cal->addEvent(event1);
  KABC::Lock *lock = cal->lock();
  cal->save();
  lock->unlock();
}

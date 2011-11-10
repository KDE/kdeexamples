#include <QtSql>

int main(int argc, char *argv[])
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sqlite.dat");

    if (db.open()) 
        qDebug() << "success";
    else 
        qDebug() << "failed";
    QSqlQuery query;
    query.exec("create table stocks(id int primary key, name varchar(20))");
    db.commit();
    db.close();
}

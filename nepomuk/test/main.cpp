#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
#include <QtCore/QTimer>

#include <Soprano/Statement>
#include <Soprano/Node>
#include <Soprano/Model>
#include <Soprano/QueryResultIterator>
#include <Soprano/StatementIterator>
#include <Soprano/NodeIterator>
#include <Soprano/PluginManager>

// Vocabularies
#include <Soprano/Vocabulary/RDF>
#include <Soprano/Vocabulary/RDFS>
#include <Soprano/Vocabulary/NRL>
#include <Soprano/Vocabulary/NAO>

#include <Nepomuk2/Vocabulary/NIE>
#include <Nepomuk2/Vocabulary/NFO>
#include <Nepomuk2/Vocabulary/NMM>
#include <Nepomuk2/Vocabulary/NCO>
#include <Nepomuk2/Vocabulary/PIMO>
#include <Nepomuk2/Vocabulary/NCAL>

#include <KUrl>
#include <KJob>
#include <KDebug>

#include <Nepomuk2/Resource>
#include <Nepomuk2/ResourceManager>
#include <Nepomuk2/Tag>
#include <Nepomuk2/Variant>
#include <Nepomuk2/Query/QueryServiceClient>
#include <Nepomuk2/Query/ResourceTypeTerm>
#include <Nepomuk2/Query/LiteralTerm>

#include <Nepomuk2/DataManagement>
#include <Nepomuk2/SimpleResource>
#include <Nepomuk2/SimpleResourceGraph>
#include <Nepomuk2/StoreResourcesJob>


using namespace Soprano::Vocabulary;
using namespace Nepomuk2::Vocabulary;

class TestObject : public QObject {
    Q_OBJECT

public slots:
    void main();
public:
    TestObject() {
        QTimer::singleShot( 0, this, SLOT(main()) );
        //QTimer::singleShot( 5000, QCoreApplication::instance(), SLOT(quit()) );
    }

    virtual ~TestObject() {
    }
};

int main( int argc, char ** argv ) {
    KComponentData component( QByteArray("nepomuk-test") );
    QCoreApplication app( argc, argv );

    TestObject a;
    app.exec();
}

void TestObject::main()
{
    // Code goes here
}


#include "main.moc"

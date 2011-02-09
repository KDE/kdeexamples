#include <QtCore>

#include <Soprano/Statement>
#include <Soprano/Node>
#include <Soprano/Model>
#include <Soprano/QueryResultIterator>
#include <Soprano/StatementIterator>
#include <Soprano/NodeIterator>
#include <Soprano/PluginManager>

#include <Nepomuk/Resource>
#include <Nepomuk/ResourceManager>
#include <Nepomuk/Variant>
#include <Nepomuk/File>
#include <Nepomuk/Tag>

#include <Nepomuk/Types/Property>
#include <Nepomuk/Types/Class>

#include <Nepomuk/Query/Query>
#include <Nepomuk/Query/ComparisonTerm>
#include <Nepomuk/Query/LiteralTerm>
#include <Nepomuk/Query/ResourceTerm>
#include <Nepomuk/Query/QueryServiceClient>
#include <Nepomuk/Query/QueryParser>

#include <KDebug>
#include <QDebug>

// Vocabularies
#include <Soprano/Vocabulary/RDF>
#include <Soprano/Vocabulary/RDFS>
#include <Soprano/Vocabulary/NRL>
#include <Soprano/Vocabulary/NAO>

#include <Nepomuk/Vocabulary/NIE>
#include <Nepomuk/Vocabulary/NFO>
#include <Nepomuk/Vocabulary/NMM>
#include <Nepomuk/Vocabulary/NCO>

#include <KUrl>

int main() {
    if( Nepomuk::ResourceManager::instance()->init() ) {
        qDebug() << "Nepomuk isn't running";
        return 0;
    }
    
    // --- CODE
    
    
    // ----
    return 0;
}

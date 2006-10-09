
#include "pcmoutput.h"

#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <kapplication.h>
#include <QByteArray>
#include <QDataStream>
#include <QSlider>
#include <QHBoxLayout>
#include <phonon/audiooutput.h>
#include <phonon/audiopath.h>
#include <phonon/bytestream.h>
#include <QTimer>
#include <QFile>
#include <QLabel>

static const int SAMPLE_RATE = 48000;

PcmPlayer::PcmPlayer( QWidget *parent )
	: QWidget( parent ),
	m_frequency( 440 )
{
	Phonon::AudioOutput* m_output = new Phonon::AudioOutput( Phonon::MusicCategory, this );
	Phonon::AudioPath* m_path = new Phonon::AudioPath( this );
	m_path->addOutput( m_output );
	m_stream = new Phonon::ByteStream( this );
	m_stream->addAudioPath( m_path );
	m_stream->setStreamSeekable( false );
	m_stream->setStreamSize( 0x7FFFFFFF );

	QTimer* m_timer = new QTimer( this );
	m_timer->setInterval( 0 );
	connect( m_timer, SIGNAL( timeout() ), SLOT( sendData() ) );

	connect( m_stream, SIGNAL( needData() ), m_timer, SLOT( start() ) );
	connect( m_stream, SIGNAL( enoughData() ), m_timer, SLOT( stop() ) );

	m_stream->writeData( wavHeader() );

	setLayout( new QHBoxLayout );
	QSlider* slider = new QSlider( this );
	layout()->addWidget( slider );
	slider->setRange( 200, 4000 );
	slider->setValue( m_frequency );
	connect( slider, SIGNAL( valueChanged( int ) ), SLOT( setFrequency( int ) ) );

	QTimer::singleShot( 0, m_timer, SLOT( start() ) );
	QTimer::singleShot( 0, m_stream, SLOT( play() ) );

	m_fLabel = new QLabel( this );
	layout()->addWidget( m_fLabel );
	m_fLabel->setText( QString::number( m_frequency ) );
}

void PcmPlayer::setFrequency( int f )
{
	m_frequency = f;
	m_fLabel->setText( QString::number( m_frequency ) );
}

void PcmPlayer::sendData()
{
	m_stream->writeData( pcmBlock( m_frequency ) );
}

QByteArray PcmPlayer::wavHeader() const
{
	QByteArray data;
	QDataStream stream( &data, QIODevice::WriteOnly );
	stream.setByteOrder( QDataStream::LittleEndian );
	stream
		<< 0x46464952 //"RIFF"
		<< static_cast<quint32>( 0x7FFFFFFF )
		<< 0x45564157 //"WAVE"
		<< 0x20746D66 //"fmt "           //Subchunk1ID
		<< static_cast<quint32>( 16 )    //Subchunk1Size
		<< static_cast<quint16>( 1 )     //AudioFormat
		<< static_cast<quint16>( 2 )     //NumChannels
		<< static_cast<quint32>( SAMPLE_RATE ) //SampleRate
		<< static_cast<quint32>( 2*2*SAMPLE_RATE )//ByteRate
		<< static_cast<quint16>( 2*2 )   //BlockAlign
		<< static_cast<quint16>( 16 )    //BitsPerSample
		<< 0x61746164 //"data"                   //Subchunk2ID
		<< static_cast<quint32>( 0x7FFFFFFF-36 )//Subchunk2Size
		;
	return data;
}

QByteArray PcmPlayer::pcmBlock( int freq ) const
{
	QByteArray data;
	QDataStream stream( &data, QIODevice::WriteOnly );
	stream.setByteOrder( QDataStream::LittleEndian );

	const int samplesPerHalfWave = SAMPLE_RATE / ( 2*freq );
	const int sampleDiff = ( 1 << 16 ) / samplesPerHalfWave;
	const int samplesPerQuarterWave = samplesPerHalfWave / 2;

	for( int i = 0; i < samplesPerQuarterWave; ++i )
		stream << static_cast<quint16>( i * sampleDiff )
			<< static_cast<quint16>( -i * sampleDiff );
	for( int i = 0; i < samplesPerHalfWave; ++i )
		stream << static_cast<quint16>( 32767 - i * sampleDiff )
			<< static_cast<quint16>( -32768 + i * sampleDiff );
	for( int i = 0; i < samplesPerQuarterWave; ++i )
		stream << static_cast<quint16>( -32768 + i * sampleDiff )
			<< static_cast<quint16>( 32767 - i * sampleDiff );

	return data;
}

int main( int argc, char** argv )
{
	KAboutData about( "videoplayandforget", "Phonon VideoPlayer Example",
			"1.0", "",
			KAboutData::License_LGPL, 0 );
	about.addAuthor( "Matthias Kretz", 0, "kretz@kde.org" );
	KCmdLineArgs::init( argc, argv, &about );
	KApplication app;
	PcmPlayer player;
	player.show();
	app.exec();
}

#include "pcmoutput.moc"

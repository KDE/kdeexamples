/*  This file is part of the KDE project
    Copyright (C) 2006 Matthias Kretz <kretz@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License version 2 as published by the Free Software Foundation.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

*/

#include "crossfade.h"
#include <phonon/mediaobject.h>
#include <phonon/audiopath.h>
#include <phonon/audiooutput.h>
#include <phonon/volumefadereffect.h>
#include <kurl.h>
#include <QTimer>

static const long CROSSFADE_TIME = 3000; // 3 seconds

Crossfader::Crossfader( QObject* parent )
	: QObject( parent )
{
	m1 = new MediaObject( this ); m2 = new MediaObject( this );
	a1 = new AudioPath( this );   a2 = new AudioPath( this );
	f1 = new VolumeFaderEffect( this ); f2 = new VolumeFaderEffect( this );
	output = new AudioOutput( this );

	m1->addAudioPath( a1 );  m2->addAudioPath( a2 );
	a1->insertEffect( f1 );  a2->insertEffect( f2 );
	a1->addOutput( output ); a2->addOutput( output );
	m1->setAboutToFinishTime( CROSSFADE_TIME ); m2->setAboutToFinishTime( CROSSFADE_TIME );
	connect( m1, SIGNAL( aboutToFinish( long ) ), SLOT( crossfade( long ) ) );
	connect( m2, SIGNAL( aboutToFinish( long ) ), SLOT( crossfade( long ) ) );
	connect( m1, SIGNAL( finished() ), SLOT( setupNext() ) );
	connect( m2, SIGNAL( finished() ), SLOT( setupNext() ) );
}

void Crossfader::crossfade( long fadeTime )
{
	f1->fadeOut( fadeTime );
	f2->fadeIn( fadeTime );
	m2->play();
}

void Crossfader::setupNext()
{
	qSwap( m1, m2 ); qSwap( a1, a2 ); qSwap( f1, f2 );
	KUrl nextUrl;
	emit needNextUrl( nextUrl );
	m2->setUrl( nextUrl );
}

void Crossfader::start( const KUrl& firstUrl )
{
	m1->setUrl( firstUrl );
	m1->play();
}

void Crossfader::stop()
{
	f1->fadeOut( CROSSFADE_TIME );
	QTimer::singleShot( CROSSFADE_TIME, m1, SLOT( stop() ) );
}

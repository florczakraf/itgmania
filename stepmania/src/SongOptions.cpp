#include "global.h"
#include "SongOptions.h"
#include "RageUtil.h"

void SongOptions::Init() 
{
	m_LifeType = LIFE_BAR;
	m_DrainType = DRAIN_NORMAL;
	m_iBatteryLives = 4;
	m_FailType = FAIL_IMMEDIATE;
	m_bAssistTick = false;
	m_fMusicRate = 1.0f;
	m_bAutoSync = false;
	m_bSaveScore = true;
}

CString SongOptions::GetString() const
{
	CString sReturn;

	switch( m_LifeType )
	{
	case LIFE_BAR:		
		switch( m_DrainType )
		{
		case DRAIN_NORMAL:										break;
		case DRAIN_NO_RECOVER:		sReturn	+= "NoRecover, ";	break;
		case DRAIN_SUDDEN_DEATH:	sReturn	+= "SuddenDeath, ";	break;
		}
		break;
	case LIFE_BATTERY:
		sReturn	+= ssprintf( "%dLives, ", m_iBatteryLives );
		break;
	}


	switch( m_FailType )
	{
	case FAIL_IMMEDIATE:										break;
	case FAIL_END_OF_SONG:		sReturn	+= "FailEndOfSong, ";	break;
	case FAIL_OFF:				sReturn	+= "FailOff, ";			break;
	}

	if( m_fMusicRate != 1 )
	{
		CString s = ssprintf( "%2.2f", m_fMusicRate );
		if( s[s.GetLength()-1] == '0' )
			s.erase(s.GetLength()-1);
		sReturn += s + "xMusic, ";
	}

	if( m_bAutoSync )
		sReturn += "AutoSync, ";

	if( sReturn.GetLength() > 2 )
		sReturn.erase( sReturn.GetLength()-2 );	// delete the trailing ", "
	return sReturn;
}

/* Options are added to the current settings; call Init() beforehand if
 * you don't want this. */
void SongOptions::FromString( CString sOptions )
{
//	Init();
	sOptions.MakeLower();
	CStringArray asBits;
	split( sOptions, ",", asBits, true );

	for( unsigned i=0; i<asBits.size(); i++ )
	{
		CString& sBit = asBits[i];
		TrimLeft(sBit);
		TrimRight(sBit);
		
		Regex mult("^([0-9]+(\\.[0-9]+)?)xmusic$");
		vector<CString> matches;
		if( mult.Compare(sBit, matches) )
		{
			int ret = sscanf( matches[0], "%f", &m_fMusicRate );
			ASSERT( ret == 1 );
		}

		matches.clear();
		Regex lives("^([0-9]+) ?(lives|life)$");
		if( lives.Compare(sBit, matches) )
		{
			int ret = sscanf( matches[0], "%i", &m_iBatteryLives );
			ASSERT( ret == 1 );
		}

		CStringArray asParts;
		split( sBit, " ", asParts, true );
		bool on = true;
		if( asParts.size() > 1 )
		{
			sBit = asParts[1];

			if( asParts[0] == "no" )
				on = false;
		}

		if(	     sBit == "norecover" )		m_DrainType = DRAIN_NO_RECOVER;
		else if( sBit == "suddendeath" )	m_DrainType = DRAIN_SUDDEN_DEATH;
		else if( sBit == "power-drop" )		m_DrainType = DRAIN_NO_RECOVER;
		else if( sBit == "death" )			m_DrainType = DRAIN_SUDDEN_DEATH;
		else if( sBit == "normal-drain" )	m_DrainType = DRAIN_NORMAL;
		else if( sBit == "failarcade" || 
				 sBit == "failimmediate" )	m_FailType = FAIL_IMMEDIATE;
		else if( sBit == "failendofsong" )	m_FailType = FAIL_END_OF_SONG;
		else if( sBit == "failoff" )		m_FailType = FAIL_OFF;
		else if( sBit == "assisttick" )		m_bAssistTick = on;
		else if( sBit == "autosync" )		m_bAutoSync = on;
		else if( sBit == "savescore" )		m_bSaveScore = on;
		else if( sBit == "bar" )			m_LifeType = LIFE_BAR;
		else if( sBit == "battery" )		m_LifeType = LIFE_BATTERY;
	}
}

bool SongOptions::operator==( const SongOptions &other ) const
{
#define COMPARE(x) { if( x != other.x ) return false; }
	COMPARE( m_LifeType );
	COMPARE( m_DrainType );
	COMPARE( m_iBatteryLives );
	COMPARE( m_FailType );
	COMPARE( m_fMusicRate );
	COMPARE( m_bAssistTick );
	COMPARE( m_bAutoSync );
	COMPARE( m_bSaveScore );
#undef COMPARE
	return true;
}

/*
 * (c) 2001-2004 Chris Danford, Glenn Maynard
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

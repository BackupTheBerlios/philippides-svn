//******************************************************************************
/**
 * @file Athlet.cpp
 * This file contains the implementation of the CAthlet class.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 13.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************


//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes
#include <qtextstream.h>


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "Exceptions.h"
#include "AthletDtd.h"
#include "Athlet.h"


//******************************************************************************
// implementation
//******************************************************************************
namespace Phil
{

//------------------------------------------------------------------------------
// structors
//------------------------------------------------------------------------------
CAthlet::CAthlet(const QString& sFirstName, const QString& sLastName, const QDate& birthday):
    m_sFirstName( sFirstName ),
    m_sLastName( sLastName ),
    m_birthday( birthday ),
    m_fAvgDistance( 0.0 ),
    m_fWeight( 0.0 ),
    m_nAvgPulse( 0 ),
    m_nBiggestDistance( 0 ),
    m_nHeight( 0 ),
    m_nRunningFreq( 0 ),
    m_nMorningPulse( 0 )
{
    // check for valid minimal parameters
    if( m_sFirstName.isEmpty() )
	throw Except::EmptyParamException( "CAthlet::CAthlet", "sFirstName" );

    if( m_sLastName.isEmpty() )
	throw Except::EmptyParamException( "CAthlet::CAthlet", "sLastName" );

    if( !m_birthday.isValid() )
	throw Except::InvalidDataException( "CAthlet::CAthlet", "Birthday");
}

CAthlet::~CAthlet()
{
    /* EMPTY */
}

//------------------------------------------------------------------------------
// accessors
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// operator
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// methods
//------------------------------------------------------------------------------

QString CAthlet::ToXml() const
{
    QString sXml;
    QTextStream stream(&sXml, IO_WriteOnly);
   
    // ok, ok, this looks really ugly but it is a compact way of interleaving
    // variables into xml strings. 
    // (I should participate in the obfuscated code contest)
    stream  << "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n"
	    <<  DTD::szAthletDtd
	    <<  "<athlet>\n"
	    << (m_sFirstName.isEmpty() ? "" : 
		"\t<firstname>" + m_sFirstName + "</firstname>\n")
	    << (m_sLastName.isEmpty() ? "" : 
		"\t<lastname>" + m_sLastName + "</lastname>\n")
	    << (!m_birthday.isValid() ? "" : 
		"\t<birthday>" + m_birthday.toString( Qt::ISODate ) + "</birthday>\n")
	    << (!(m_fWeight > 0.0) ? "" : 
		"\t<weight>" + QString::number(m_fWeight) + "</weight>\n")
	    << (!(m_nHeight > 0) ? "" : 
		"\t<height>" + QString::number(m_nHeight) + "</height>\n")
	    << (!(m_nRunningFreq > 0) ? "" : 
		"\t<runningfreq>" + QString::number(m_nRunningFreq) + "</runningfreq>\n")
	    << (!(m_fAvgDistance > 0.0) ? "" : 
		"\t<avgdist>" + QString::number(m_fAvgDistance) + "</avgdist>\n") 
	    << (m_kmTime5.isNull() ? "" : 
		"\t<kmtime5>" + m_kmTime5.toString(Qt::ISODate) + "</kmtime5>\n")
	    << (!(m_nBiggestDistance > 0) ? "" : 
		"\t<biggestdist>" + QString::number(m_nBiggestDistance) + "</biggestdist>\n")
	    << (!(m_nAvgPulse > 0) ? "" : 
		"\t<morningpulse>" + QString::number(m_nMorningPulse) + "</morningpulse>\n")
	    << "</athlet>\n";
return sXml;
}

};//namespace


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
#include <qfile.h>
#include <qxml.h>

// kde includes
#include <kapplication.h>
#include <kstandarddirs.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "Exceptions.h"
#include "AthletDtd.h"
#include "Athlet.h"
#include "AthletParser.h"


//******************************************************************************
// implementation
//******************************************************************************
namespace Phil
{

//------------------------------------------------------------------------------
// structors
//------------------------------------------------------------------------------
CAthlet::CAthlet()
{
    // here we use "standard" parameters, we always want minimal values for our 
    // object. TODO: perhaps implement a empty-object constructor, think about it.
    CAthlet("Mickey", "Mouse", CAthlet::MALE, QDate(1928, 11, 18));
}
    
    
CAthlet::CAthlet(const QString& sFirstName, const QString& sLastName, 
		 EnGender gender, const QDate& birthday):
    m_sFirstName( sFirstName ),
    m_sLastName( sLastName ),
    m_EnGender( gender ),
    m_birthday( birthday ),
    m_nAvgDistance( 0 ),
    m_nWeight( 0 ),
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
	    <<  "<athlet version=\"" << DTD::szAthletVERSION << "\">\n"
	    << (m_sFirstName.isEmpty() ? "" : 
		"\t<firstname>" + m_sFirstName + "</firstname>\n")
	    << (m_sLastName.isEmpty() ? "" : 
		"\t<lastname>" + m_sLastName + "</lastname>\n")
	    << ( (m_EnGender == FEMALE) ? "\t<gender value=\"female\"/>\n":
		"\t<gender value=\"male\"/>\n" )
	    << (!m_birthday.isValid() ? "" : 
		"\t<birthday>" + m_birthday.toString( Qt::ISODate ) + "</birthday>\n")
	    << (!(m_nWeight > 0.0) ? "" : 
		"\t<weight>" + QString::number(m_nWeight) + "</weight>\n")
	    << (!(m_nHeight > 0) ? "" : 
		"\t<height>" + QString::number(m_nHeight) + "</height>\n")
	    << (!(m_nRunningFreq > 0) ? "" : 
		"\t<runningfreq>" + QString::number(m_nRunningFreq) + "</runningfreq>\n")
	    << (!(m_nAvgPulse > 0.0) ? "" : 
		"\t<avgpulse>" + QString::number(m_nAvgPulse) + "</avgpulse>\n") 
	    << (!(m_nAvgDistance > 0.0) ? "" : 
		"\t<avgdist>" + QString::number(m_nAvgDistance) + "</avgdist>\n") 
	    << (m_kmTime5.isNull() ? "" : 
		"\t<kmtime5>" + m_kmTime5.toString(Qt::ISODate) + "</kmtime5>\n")
	    << (m_kmTime10.isNull() ? "" : 
		"\t<kmtime10>" + m_kmTime10.toString(Qt::ISODate) + "</kmtime10>\n")
	    << (!(m_nBiggestDistance > 0) ? "" : 
		"\t<biggestdist>" + QString::number(m_nBiggestDistance) + "</biggestdist>\n")
	    << (!(m_nAvgPulse > 0) ? "" : 
		"\t<morningpulse>" + QString::number(m_nMorningPulse) + "</morningpulse>\n")
	    << "</athlet>\n";
return sXml;
}


void CAthlet::ToDisk() const
{
    QString sPath = kapp->dirs()->saveLocation("data", "philippides/");

    ToDisk(sPath, DTD::szAthletFile);
}


void CAthlet::ToDisk(const QString& sPath, const QString& sFileName) const
{
    QFile file(sPath + '/' + sFileName);
    if( file.open(IO_WriteOnly) ){
	QTextStream stream(&file);
	stream << ToXml();
	file.flush();
	file.close();
    }
    else{
	throw Except::IOException("CAthlet::ToDisk(const QString&, const QString&)", file.name());
    }
}


CAthlet* CAthlet::FromDisk()
{
    if(!FileExists())
	throw Except::GenericException("CAthlet::FromDisk()", 
			"Athlet file does not exist in the user's home directory");

    QString sPath = kapp->dirs()->saveLocation("data", "philippides/");

    return FromDisk(sPath, DTD::szAthletFile);
}

CAthlet* CAthlet::FromDisk(const QString& sPath, const QString& sFileName)
{
    QFile file(sPath + '/' + sFileName);
    if(!file.open(IO_ReadOnly))
	throw Except::IOException("CAthlet::FromDisk(const QString&, const QString&)",
				  file.name());

    //------------------------------------------------------------------------------ 
    // here I create the new CAthlet object, a pointer to it is given to the parser
    // to fill it with values, this class keeps the ownership ob the object and 
    // discards it later when returning from this method.
    //------------------------------------------------------------------------------ 

    CAthlet* pAthlet = new CAthlet();
    
    QXmlInputSource source(&file);
    QXmlSimpleReader reader;

    //TODO: what about the parser's memory, who cares for it?
    CAthletParser* parser = new CAthletParser(pAthlet);
    reader.setContentHandler(parser);
    reader.parse(source);

return pAthlet;
}


bool CAthlet::FileExists()
{
    return !locate("data", QString("philippides/") + DTD::szAthletFile).isEmpty();
}

//------------------------------------------------------------------------------
// operator
//------------------------------------------------------------------------------
bool operator==(const CAthlet& a, const CAthlet& b)
{
return (a.m_sFirstName == b.m_sFirstName)   &&
       (a.m_sLastName == b.m_sLastName)	    &&
       (a.m_EnGender == b.m_EnGender)	    &&
       (a.m_birthday == b.m_birthday)	    &&
       (a.m_kmTime5 == b.m_kmTime5)	    &&
       (a.m_kmTime10 == b.m_kmTime10)	    &&
       (a.m_nAvgDistance == b.m_nAvgDistance) &&
       (a.m_nWeight == b.m_nWeight)	    &&
       (a.m_nAvgPulse == b.m_nAvgPulse)	    &&
       (a.m_nBiggestDistance == b.m_nBiggestDistance) &&
       (a.m_nHeight == b.m_nHeight)	    &&
       (a.m_nRunningFreq == b.m_nRunningFreq) &&
       (a.m_nMorningPulse == b.m_nMorningPulse);
}

bool operator!=(const CAthlet& a, const CAthlet& b)
{
    return !(a == b);
}

};//namespace


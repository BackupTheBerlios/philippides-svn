//******************************************************************************
/**
 * @file AthletParser.cpp
 * This file contains the implementation of the class CAthletParser
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/26/2004
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
// qt headers
#include <qdatetime.h>

// kde headers
#include <kdebug.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "Athlet.h"
#include "AthletParser.h"
#include "Exceptions.h"

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------


//******************************************************************************
// implementation
//******************************************************************************
namespace Phil
{

//------------------------------------------------------------------------------
// structors
//------------------------------------------------------------------------------
CAthletParser::CAthletParser(CAthlet* pAthlet):
    m_pAthlet(pAthlet)
{
    /* EMPTY */ 
}

CAthletParser::~CAthletParser()
{
    /* EMPTY because the athlet object is not ours */ 
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
bool CAthletParser::startElement(const QString& /* EMPTY */,
				 const QString& /* EMPTY */, 
	                         const QString& sElementName, 
				 const QXmlAttributes& attrib)
{
    if(sElementName == "athlet")
	    m_sVersion = attrib.value("version");

    if(sElementName == "gender"){
	if(attrib.value("value") == "male"){
	    m_pAthlet->m_EnGender = CAthlet::MALE;
	}
	else if(attrib.value("value") == "female"){
	    m_pAthlet->m_EnGender = CAthlet::FEMALE;
	}
	else{
	    throw Except::InvalidDataException("CAthletParser::startElement", "m_EnGender");
	}
    }

return true;
}

bool CAthletParser::characters(const QString& sText)
{
    m_sParsedText += sText; 

return true;
}


bool CAthletParser::endElement(const QString& /* EMPTY */, 
			       const QString& /* EMPTY */, 
			       const QString& sElementName)
{   
    //TODO: Do some error handling here, look if minimal requirements are present. 
    
    // we habe to strip the whitespaces in front and back of the string to allow
    // functions like fromString() to work correctly, watch out for problems on 
    // other tags with tis setting, perhaps use it exclusively on the affected
    // tags.
    m_sParsedText = m_sParsedText.stripWhiteSpace();
    if(sElementName == "firstname"){
	m_pAthlet->m_sFirstName = m_sParsedText; 
    }
    else if(sElementName == "lastname"){
	m_pAthlet->m_sLastName = m_sParsedText;
    }
    else if(sElementName == "birthday"){
	m_pAthlet->m_birthday = QDate::fromString( m_sParsedText, Qt::ISODate);
    }
    else if(sElementName == "weight"){
	m_pAthlet->m_nWeight = m_sParsedText.toUShort();
    }
    else if(sElementName == "height"){
	m_pAthlet->m_nHeight = m_sParsedText.toUShort();
    }
    else if(sElementName == "runningfreq"){
	m_pAthlet->m_nRunningFreq = m_sParsedText.toUShort();
    }
    else if(sElementName == "avgdist"){
	m_pAthlet->m_nAvgDistance = m_sParsedText.toUShort();
    }
    else if(sElementName == "kmtime5"){
	m_pAthlet->m_kmTime5 = QTime::fromString(m_sParsedText, Qt::ISODate);
    }
    else if(sElementName == "kmtime10"){
	m_pAthlet->m_kmTime10 = QTime::fromString(m_sParsedText, Qt::ISODate);
    }
    else if(sElementName == "biggestdist"){
	m_pAthlet->m_nBiggestDistance = m_sParsedText.toUShort();
    }
    else if(sElementName == "avgpulse"){
	m_pAthlet->m_nAvgPulse = m_sParsedText.toUShort();
    }
    else if(sElementName == "morningpulse"){
	m_pAthlet->m_nMorningPulse = m_sParsedText.toUShort();
    }
    
    m_sParsedText = "";

return true;
}

};//namespace



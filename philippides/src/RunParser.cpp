//******************************************************************************
/**
 * @file RunParser.cpp
 * This file contains the implementation of the class CRunParser.
 * brief description.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/28/2004
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
// headers for each lib should have own section


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "RunParser.h"
#include "Run.h"
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
CRunParser::CRunParser(QPtrList<CRun>* pRunList):
    m_pRun(0),
    m_pRunList(pRunList)
{
    m_pRunList->clear();
}

CRunParser::~CRunParser()
{
    /* EMPTY because the run object is not ours */ 
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
bool CRunParser::startElement(const QString& /* EMPTY */,
			      const QString& /* EMPTY */,
			      const QString& sElementName,
			      const QXmlAttributes& attrib)
{
    if(sElementName == "rundb")
	m_sVersion = attrib.value("version");

    if(sElementName == "run"){
	// if m_pRun is not null, a error occured
	if(m_pRun){
	    delete m_pRun;
	    throw Except::InvalidDataException("CRunParser::startElement()",
					       "m_pRun");
	}
	m_pRun = new CRun();
    }

    if(sElementName == "weather"){
	QString sValue = attrib.value("value");
	if(sValue == "clear")
	    m_pRun->m_EnWeather = CRun::CLEAR;
	else if(sValue == "cloudy")
	    m_pRun->m_EnWeather = CRun::CLOUDY;
	else if(sValue == "stormy")
	    m_pRun->m_EnWeather = CRun::STORMY;
	else if(sValue == "snowy")
	    m_pRun->m_EnWeather = CRun::SNOWY;
	else
	    m_pRun->m_EnWeather = CRun::NOWEATHER;
    }

    if(sElementName == "impression"){
	QString sValue = attrib.value("value");
	if(sValue == "good")
	    m_pRun->m_EnImpression = CRun::GOOD;
	else if(sValue == "fair")
	    m_pRun->m_EnImpression = CRun::FAIR;
	else if(sValue == "bad")
	    m_pRun->m_EnImpression = CRun::BAD;
	else if(sValue == "aborted")
	    m_pRun->m_EnImpression = CRun::ABORTED;
	else
	    m_pRun->m_EnImpression = CRun::NOIMPRESSION;
    }
return true;
}
 
bool CRunParser::characters(const QString& sText)
{
    m_sParsedText += sText;

return true;
}

bool CRunParser::endElement(const QString& /* EMPTY */,
			    const QString& /* EMPTY */,
			    const QString& sElementName)
{
    /// @todo Do some error handling here, look if minimal requirements are present. 
    
    // we habe to strip the whitespaces in front and back of the string to allow
    // functions like fromString() to work correctly, watch out for problems on 
    // other tags with tis setting, perhaps use it exclusively on the affected
    // tags.

    m_sParsedText = m_sParsedText.stripWhiteSpace();
    
    if(sElementName == "date")
	m_pRun->m_Date = QDate::fromString(m_sParsedText, Qt::ISODate);
    else if(sElementName == "time")
	m_pRun->m_Time = QTime::fromString(m_sParsedText, Qt::ISODate);
    else if(sElementName == "length")
	m_pRun->m_nLength = m_sParsedText.toUShort();
    else if(sElementName == "pulse")
	m_pRun->m_nPulse = m_sParsedText.toUShort();
    else if(sElementName == "comment")
	m_pRun->m_sComment = m_sParsedText;
    else if(sElementName == "run"){
        m_pRunList->append(m_pRun);
	m_pRun = 0;
    }
    m_sParsedText = "";

return true;
}


};//namespace


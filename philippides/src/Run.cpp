//******************************************************************************
/**
 * @file Run.cpp
 * short description.
 * brief description.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 16.3.2004
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
#include "RunDtd.h"
#include "Run.h"


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
CRun::CRun(const QDate& date, const QTime& time):
    m_Date( date ),
    m_Time( time ),
    m_nPulse( 0 ),
    m_EnWeather( NOWEATHER ),
    m_EnImpression( NOIMPRESSION )
{
    if( !m_Date.isValid() )
	throw Except::InvalidDataException( "CRun::CRun", "date" );
    if( !m_Time.isValid() )
	throw Except::InvalidDataException( "CRun::CRun", "time" );
};

CRun::~CRun()
{

};

//------------------------------------------------------------------------------
// accessors
//------------------------------------------------------------------------------
QString CRun::XmlHeader() const
{
    QString sXml;
    QTextStream stream( &sXml, IO_WriteOnly );

    stream  << "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n"
	    << DTD::szRunDtd
	    << "<rundb version=\"" << DTD::szRundbVERSION << "\">\n";

return sXml;
}

QString CRun::XmlFooter() const
{
    return QString( "</rundb>\n" );
}

QString CRun::ToXml() const
{
    QString sXml;
    QTextStream stream(&sXml, IO_WriteOnly);

    // check for minimal values which must be existant to generate a run entry
    if(!m_Date.isValid() || m_Date.isNull())
	throw Except::InvalidDataException("CRun::ToXml", "m_Date");

    if(!m_Time.isValid() || m_Date.isNull())
	throw Except::InvalidDataException("CRun::ToXml", "m_Time");
	    
    stream  << "<run>\n"
	    << "\t<date>" << m_Date.toString(Qt::ISODate) << "</date>\n"
	    << "\t<time>" << m_Time.toString(Qt::ISODate) << "</time>\n"
	    << ((m_nLength > 0) ? "\t<length>" + QString::number(m_nLength) + "</length>\n" : "")
	    << ((m_nPulse > 0) ? "\t<pulse>" + QString::number(m_nPulse) + "</pulse>\n" : "")
	    << ((m_EnWeather != NOWEATHER) ? "\t<weather>" + QString::number(m_EnWeather) +
		"</weather>\n" : "")
	    << ((m_EnImpression != NOIMPRESSION) ? "\t<impression>" + 
		    QString::number(m_EnImpression) + "</impression>\n" : "")
	    << ((!m_sComment.isEmpty()) ? "\t<comment>" + m_sComment + "</comment>\n" : "")
	    << "</run>\n";

return sXml;
}

//------------------------------------------------------------------------------
// operator
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// methods
//------------------------------------------------------------------------------

};//namespace


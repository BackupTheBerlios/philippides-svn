//******************************************************************************
/**
 * @file Run.cpp
 * CRun implementation.
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
#include <qfile.h>
#include <qxml.h>
#include <qdatetime.h>
#include <qptrlist.h>

// kde includes
#include <kapplication.h>
#include <kstandarddirs.h>


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "Exceptions.h"
#include "RunDtd.h"
#include "Run.h"
#include "RunParser.h"
#include "Athlet.h"

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
CRun::CRun():
    m_Date( QDate::currentDate() ),
    m_Time( QTime::currentTime() ),
    m_nLength( 0 ),
    m_nPulse( 0 ),
    m_EnWeather( NOWEATHER ),
    m_EnImpression( NOIMPRESSION )
{
    /* EMPTY */ 
}
    
    
CRun::CRun(const QDate& date, const QTime& time):
    m_Date( date ),
    m_Time( time ),
    m_nLength( 0 ),
    m_nPulse( 0 ),
    m_EnWeather( NOWEATHER ),
    m_EnImpression( NOIMPRESSION )
{
    if( !m_Date.isValid() )
	throw Except::InvalidDataException( "CRun::CRun", "date" );
    if( !m_Time.isValid() )
	throw Except::InvalidDataException( "CRun::CRun", "time" );
}

CRun::~CRun()
{
    /* EMPTY */ 
}

//------------------------------------------------------------------------------
// accessors
//------------------------------------------------------------------------------
QString CRun::XmlHeader()
{
    QString sXml;
    QTextStream stream( &sXml, IO_WriteOnly );

    stream  << "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n"
	    << DTD::szRunDtd
	    << "<rundb version=\"" << DTD::szRundbVERSION << "\">\n";

return sXml;
}

QString CRun::XmlFooter()
{
    return QString( "</rundb>\n" );
}

QString CRun::ToXml() const
{
    QString sXml;
    QTextStream stream(&sXml, IO_WriteOnly);

    // check for minimal values which must exist to generate a run entry
    if(!m_Date.isValid() || m_Date.isNull())
	throw Except::InvalidDataException("CRun::ToXml", "m_Date");

    if(!m_Time.isValid() || m_Date.isNull())
	throw Except::InvalidDataException("CRun::ToXml", "m_Time");
	    

    // create attributes
    QString sWeather = "\t<weather value=\"";
    if(m_EnWeather != NOWEATHER){
	if(m_EnWeather == CLEAR)
	    sWeather += "clear\"/>\n";
	else if(m_EnWeather == CLOUDY)
	    sWeather += "cloudy\"/>\n";
	else if(m_EnWeather == STORMY)
	    sWeather += "stormy\"/>\n";
	else if(m_EnWeather == SNOWY)
	    sWeather += "snowy\"/>\n";
    }
    else{
	sWeather = "";
    }

    QString sImpression = "\t<impression value=\"";
    if(m_EnImpression != NOIMPRESSION){
	if(m_EnImpression == GOOD)
	    sImpression += "good\"/>\n";
	else if(m_EnImpression == FAIR)
	    sImpression += "fair\"/>\n";
	else if(m_EnImpression == BAD)
	    sImpression += "bad\"/>\n";
	else if(m_EnImpression == ABORTED)
	    sImpression += "aborted\"/>\n";
    }
    else{
	sImpression = "";
    }
    
    stream  << "<run>\n"
	    << "\t<date>" << m_Date.toString(Qt::ISODate) << "</date>\n"
	    << "\t<time>" << m_Time.toString(Qt::ISODate) << "</time>\n"
	    << ((m_nLength > 0) ? "\t<length>" + QString::number(m_nLength) + "</length>\n" : "")
	    << ((m_nPulse > 0) ? "\t<pulse>" + QString::number(m_nPulse) + "</pulse>\n" : "")
	    << sWeather 
	    << sImpression
	    << ((!m_sComment.isEmpty()) ? "\t<comment>" + m_sComment + "</comment>\n" : "")
	    << "</run>\n";

return sXml;
}

bool CRun::FileExists()
{
    return !locate("data", QString("philippides/") + DTD::szRunFile).isEmpty();
}


void CRun::ToDisk(QPtrList<CRun>& runList)
{
    QString sPath = kapp->dirs()->saveLocation("data", "philippides/");

    ToDisk(sPath, DTD::szRunFile, runList);
}

void CRun::ToDisk(const QString& sPath, const QString& sFileName, QPtrList<CRun>& runList)
{
    QFile file(sPath + '/' + sFileName);
    if( !file.open(IO_WriteOnly))
	throw Except::IOException("CRun::ToDisk(const QString&, const QString&, const QPtrList)",
				  file.name());

    QTextStream stream(&file);
    stream << XmlHeader();

    const CRun* pRun;
    for(pRun = runList.first(); pRun; pRun = runList.next())
	stream << pRun->ToXml();

    stream << XmlFooter();

    file.flush();
    file.close();
}

QPtrList<CRun>* CRun::FromDisk()
{
    if(!FileExists())
	throw Except::GenericException("CRun::FromDisk()",
				    "Run database does not exist in the user's home directory");
    
    QString sPath = kapp->dirs()->saveLocation("data", "philippides/");

return FromDisk(sPath, DTD::szRunFile);
}

QPtrList<CRun>* CRun::FromDisk(const QString& sPath, const QString& sFileName)
{
    QFile file(sPath + '/' + sFileName);
    if(!file.open(IO_ReadOnly))
	throw Except::IOException("CRun::FromDisk(const QString&, const QString&)",
				    file.name());
    
    //------------------------------------------------------------------------------ 
    // here I create the new QPtrList object, a reference to it is given to the parser
    // to fill it with values, this class keeps the ownership of the object and 
    // discards it later when returning from this method.
    //------------------------------------------------------------------------------ 
    QPtrList<CRun>* pList = new QPtrList<CRun>();

    QXmlInputSource source(&file);
    QXmlSimpleReader reader;

    /// @todo What about the parser's memory?
    CRunParser* parser = new CRunParser(pList);
    reader.setContentHandler(parser);
    reader.parse(source);

return pList;
}

//------------------------------------------------------------------------------
// operator
//------------------------------------------------------------------------------
bool operator==(const CRun& a, const CRun& b)
{
    return  a.m_Date==b.m_Date			&&
	    a.m_Time==b.m_Time			&&
	    a.m_nLength==b.m_nLength		&&
	    a.m_nPulse==b.m_nPulse		&&
	    a.m_EnWeather==b.m_EnWeather	&&
	    a.m_EnImpression==b.m_EnImpression	&&
	    a.m_sComment==b.m_sComment;
}

bool operator!=(const CRun& a, const CRun& b)
{
    return !(a==b);
}

//------------------------------------------------------------------------------
// methods
//------------------------------------------------------------------------------

};//namespace


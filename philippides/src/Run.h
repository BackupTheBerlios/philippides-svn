//******************************************************************************
/** @file Run.h
 * This file contains the definition of the class CRun
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 16.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_RUN_H__
#define __PHIL_RUN_H__

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes
#include <qstring.h>
#include <qdatetime.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

//******************************************************************************
// declarations
//******************************************************************************

namespace Phil
{

/** @class CRun
 *
 * An object of this class represents a \b run entity.
 * A CRun object contains typical data which describe a run entity.
 * There is a method to get a string with an XML header including 
 * the CRun DTD ( look at: RunDtd.h ). And another method to get the
 * objects's data as XML string. and a method to get a XML closing
 * string.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 16.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de> 
 **/
class CRun
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef CRun TSelf;

    /** weather conditions */
    enum EnWeather{ CLEAR, CLOUDY, STORMY, SNOWY, NOWEATHER };

    /** the athlet's personal impression of the run */
    enum EnImpression{ GOOD, FAIR, BAD, ABORTED, NOIMPRESSION };
    
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* default constructor
	*
	* @exception Except::InvalidDataException
	*
	* @param date the run's date
	* @param time time the run took
	* **/
	CRun(const QDate& date, const QTime& time);

	/** default destructor */
	virtual ~CRun();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------
	QString XmlHeader() const;
	QString XmlFooter() const;

	QString ToXml() const;

    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	QDate m_Date;                 ///< the run's date
	QTime m_Time;                 ///< time the run took
	unsigned int  m_nLength;      ///< the run's length in m
	unsigned char m_nPulse;       ///< the athlet's average pulse
	EnWeather m_EnWeather;        ///< the run's weather conditions;
	EnImpression m_EnImpression;  ///< the athlet's feeling while running
	QString m_sComment;           ///< space for personal notes
};

}; //namespace

#endif//__PHIL_RUN_H__


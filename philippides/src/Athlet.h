//******************************************************************************
/** @file Athlet.h
 * This file contains the definition of the CAthlet class
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 13.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_ATHLET_H__
#define __PHIL_ATHLET_H__

//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes
#include <qdatetime.h>
#include <qstring.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------


//******************************************************************************
// declarations
//******************************************************************************


namespace Phil
{

/** @class CAthlet 
 * This class represent Phil's Athlet entity.
 * Objects of CAthlet contain data, representing athlet entities. There are 
 * methods for getting an XML string with the object's data.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 13.3.2004
 **/
class CAthlet
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
	typedef CAthlet TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* default constuctor
	* @exception Except::EmptyParamException
	* @exception Except::InvalidDataException
	*
	* @param name desc
	**/
	CAthlet( const QString& sFirstName, const QString& sLastName, const QDate& birthday );

	/** default destructor */
	virtual ~CAthlet();


    //------------------------------------------------------------------------------ 
    // accessors
    //------------------------------------------------------------------------------ 
	/**
	 * Convert the object's data to a XML string with header and DTD.
	 * It can be written to file and will produce a valid xml document.
	 *
	 * @note Empty or standard values/unmodified values will not be included
	 * in the string.
	 *
	 * @return The XML sting containing the object's data. 
	 **/
	QString ToXml() const;
	
	
    //--------------------------------------------------------------------------
    // members
    //--------------------------------------------------------------------------
	QString m_sFirstName;			///< the first name
	QString m_sLastName;			///< the last name
	QDate m_birthday;			///< the birthday
	QTime m_kmTime5;			///< time the athlet needs to run 5 km
	float m_fAvgDistance;			///< the average distence the athlet normally runs
	float m_fWeight;			///< the athlet's weight in kg
	unsigned short m_nAvgPulse;		///< the athlet's average pulse
	unsigned short m_nBiggestDistance;	///< the biggest distance the athlet had ever run
	unsigned short m_nHeight;		///< the athlet's height in cm
	unsigned short m_nRunningFreq;		///< how many training units does the athlet do
	unsigned short m_nMorningPulse;		///< the athlet's moning pulse (pulse @b before getting up)
};

}; //namespace

#endif//__PHIL_ATHLET_H__


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
 * This class represent Phil's \b athlet entity.
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
	/** genders */
	enum EnGender{ MALE, FEMALE };
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* default constuctor
	*
	* @exception Except::EmptyParamException
	* @exception Except::InvalidDataException
	*
	* @param sFirstName the athlet's first name
	* @param sLastName the athlet's last name
	* @param gender the athlet's gender \see EnGender
	* @param birthday the athlet's birthday
	**/
	CAthlet( const QString& sFirstName, 
		 const QString& sLastName, 
		 EnGender gender,
		 const QDate& birthday);

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
	 *	 in the string.
	 *
	 * @return The XML sting containing the object's data. 
	 **/
	QString ToXml() const;
	
	
    //--------------------------------------------------------------------------
    // members
    //--------------------------------------------------------------------------
	QString m_sFirstName;			///< the first name
	QString m_sLastName;			///< the last name
	EnGender m_EnGender;                    ///< the gender
	QDate m_birthday;			///< the birthday
	QTime m_kmTime5;			///< time the athlet needs to run 5000m
	QTime m_kmTime10;			///< time the athlet needs to run 10.000m
	unsigned short m_nAvgDistance;		///< the average distance the athlet normally runs
	unsigned short m_nWeight;		///< the athlet's weight in kg
	unsigned short m_nAvgPulse;		///< the athlet's average pulse
	unsigned short m_nBiggestDistance;	///< the biggest distance the athlet had ever run
	unsigned short m_nHeight;		///< the athlet's height in cm
	unsigned short m_nRunningFreq;		///< how many training units does the athlet do
	unsigned short m_nMorningPulse;		///< the athlet's moning pulse (pulse @b before getting up)
};

}; //namespace

#endif//__PHIL_ATHLET_H__


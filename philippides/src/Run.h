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
#include <qdatetime.h>
#include <qptrlist.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------
// qt forwarding
class CRun;

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
	/** weather conditions */
	enum EnWeather{ NOWEATHER = -1, CLEAR, CLOUDY, STORMY, SNOWY };

	/** the athlet's personal impression of the run */
	enum EnImpression{ NOIMPRESSION = -1, GOOD, FAIR, BAD, ABORTED };
    
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/**
	 * Default constructor
	 */
	CRun();
	
	
	/** 
	* Constructor
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
	/**
	 * Return a rundb XML header with version number.
	 * 
	 * @see DTD::szRundbVERSION
	 * 
	 * @return the headerstring
	 */
	static QString XmlHeader();

	/**
	 * Return a rundb XML footer string
	 *
	 * @return the footerstring
	 */
	static QString XmlFooter();

	/**
	 * Serialize a QPtrList<CRun> to disk.
	 * The database is written to KDE's default location for writing XML data.
	 * The file will have the name in DTD::szRunFile with the DTD in DTD::szAthletDtd.
	 * 
	 * @param runList [IN] - The database to be serialized
	 */
	static void ToDisk(QPtrList<CRun>& runList);

	/**
	 * The database is serialized to the given path with the given filename.
	 *
	 * @overload
	 * @exception Except::IOException
	 * @param sPath [IN] - the path to store the xml file in.
	 * @param sFileName [IN] - the filename the database gets.
	 * @param runList [IN] - the database to store.
	 */
	static void ToDisk(const QString& sPath, 
			   const QString& sFileName,
		           QPtrList<CRun>& runList);

	/**
	 * Loads and creates a QPtrList<CRun> from disk.
	 * The database is loaded from KDE's default location. KDE searches for a file
	 * with the name stored in DTD::szRunFile.
	 *
	 * @return the new rundatabase
	 */
	static QPtrList<CRun>* FromDisk();

	/**
	 * The database is loaded from the given path with the given filename.
	 *
	 * @overload
	 * @exception Except::IOException
	 * @param sPath [IN] - the path to load the xml file from
	 * @param sFileName [IN] - the databases' filename
	 * @return the new rundatabase
	 */
	static QPtrList<CRun>* FromDisk(const QString& sPath, const QString& sFileName);
	
	/**
	 * Convert the object to an XML string.
	 * 
	 * @note No XML header and footer will be included, you must call the static 
	 *	 methods XmlHeader() and XmlFooter() to get these.
	 *
	 * @exception Except::InvalidDataException
	 * @return the objects XML string representation
	 */
	QString ToXml() const;
	
    //------------------------------------------------------------------------------ 
    // methods
    //------------------------------------------------------------------------------ 
	/**
	 * Check if the XML file exists in the user's home directory.
	 * This method uses KDE's default path and filename
	 *
	 * @return does the file exist?
	 */
	static bool FileExists();
	
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

/**
 * equality operator
 */
bool operator==(const CRun& a, const CRun& b);

/**
 * inequality operator
 */
bool operator!=(const CRun& a, const CRun& b);

}; //namespace

#endif//__PHIL_RUN_H__


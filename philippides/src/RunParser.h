//******************************************************************************
/** @file RunParser.h
 *  This file contains the definition of the class CRunParser
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/28/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_RUN_PARSER_H__
#define __PHIL_RUN_PARSER_H__

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes
#include <qxml.h>


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------
// local forwarding
namespace Phil
{
    class CRun;
}
    

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

//******************************************************************************
// declarations
//******************************************************************************

namespace Phil
{

/** @class CRunParser
 * This class can parse serialized CRun objects.
 * The class parses a XML file which must be compilant to the DTD defined
 * in DTD::szRunDtd. It does \b NOT create a QPtrList<CRun> object, it fills
 * the list given in the constructor. But the CRun objects pushed into the list
 * are created by this class.
 * 
 * \note This class is not responsible for the QPtrList<CRun> object it fills,
 *	 the calling class must care about it's memory.
 *
 * \note This class discards the possession of the created CRun objects
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/28/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CRunParser: public QXmlDefaultHandler
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
	typedef CRunParser TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* Constructor.
	* The given parameter list is filled with the parsed values
	*
	* @param pRunList [IN/OUT] - the list to be filled with CRun objects
	**/
	CRunParser(QPtrList<CRun>* pRunList);

	/** default destructor */
	virtual ~CRunParser();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // methods
    //------------------------------------------------------------------------------
	/**
	 * This method is called when a new tag starts while parsing.
	 *
	 * @exception Except::InvalidDataException
	 * @param sElementName [IN] - the name of the starting tag
	 * @param attributes [IN] - the tag's attributes
	 * @return successful?
	 */
	bool startElement(const QString& /* EMPTY */, 
			  const QString& /* EMPTY */,
			  const QString& sElementName,
			  const QXmlAttributes& attributes);

	/**
	 * This method is called when a end tag is parsed.
	 *
	 * @param sElementName [IN] - the name of the starting tag
	 * @return successful?
	 */
	bool endElement(const QString& /* EMPTY */, 
			const QString& /* EMPTY */, 
			const QString& sElementName);

	/**
	 * This method reads strings between tags.
	 * The strings are evaluated in endElement().
	 *
	 * @param sText [IN] - the read string
	 * @return successful?
	 */
	bool characters(const QString& sText);


    private:
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	CRun* m_pRun;		    ///< The new CRun onject (possession discarded)
	QPtrList<CRun>* m_pRunList; ///< The runlist to be filled with objects (not owned)
	QString m_sVersion;	    ///< The DTD version (for use in later versions)
	QString m_sParsedText;	    ///< The parsed text between start and end tag
    
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CRunParser( const TSelf& other );
};

}; //namespace

#endif//__PHIL_RUN_PARSER_H__


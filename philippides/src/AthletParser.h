//******************************************************************************
/** @file AthletParser.h
 *  This file contains the definition of the class CAthletParser 
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/26/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_ATHLET_PARSER_H__
#define __PHIL_ATHLET_PARSER_H__

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt headers
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
    class CAthlet;
}


//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

//******************************************************************************
// declarations
//******************************************************************************

namespace Phil
{

/** @class CAthletParser
 *  This class can parse serialized CAthlet objects.
 *  The class parses a XML file which must be compilant to the DTD defined
 *  in DTD::szAthletDtd. It does \b NOT create a CAthlet object, it fills
 *  the object given in the constructor,
 *  
 *  \note This class is not responsible for the CAthlet object it fills,
 *	  the calling class must care about it's memory.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/26/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CAthletParser: public QXmlDefaultHandler
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef CAthletParser TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* Constructor.
	* The given parameter object is filled with the parsed values.
	*
	* @param pAthlet [IN/OUT] - the object to be filled
	**/
	CAthletParser(CAthlet* pAthlet);

	/** default destructor */
	virtual ~CAthletParser();

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
	 * @param attributies [IN] - the tag's attributes
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
    CAthlet* m_pAthlet;		///< The handled CAthlet object (not owned)
    QString m_sVersion;		///< The DTD version (for use in later versions)
    QString m_sParsedText;	///< this stores the parsed text between the tags

    
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CAthletParser( const TSelf& other );
};

}; //namespace

#endif//__PHIL_ATHLET_PARSER_H__


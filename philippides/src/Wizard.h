//******************************************************************************
/** @file Wizard.h
 * This file contains the class CWizard definition.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 23.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_WIZARD_H__
#define __PHIL_WIZARD_H__

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes
#include <qobject.h>


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "WizardBase.h"

//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------
// qt forwarding
class QWidget;

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

/** @class CWizard
 * This class implements a CAthlet setup-wizard.
 * The Wizard is shown on first Phil-startup, which usually means there is no 
 * athlet.xml file in the user's home directory, and that is exactly what the 
 * mainapp checks on startup.<br>
 * The Wizard let the user accept Phil's licensing issues and then creates a 
 * CAthlet object by letting the user fill out some forms. The CAthlet object
 * is then serialized to his home directory.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 23.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CWizard: public CWizardBase
{
	
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
	typedef CWizard TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* Constructor.
	* Standard constructor
	*
	* @param pParent [IN] - the parent widget
	* @param szName [IN] - qt's internal name representation for this widget
	**/
	CWizard(QWidget* pParent, const char* szName);

	/** default destructor */
	virtual ~CWizard();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------
	/**
	 * Return the newly created CAthlet object.
	 * Throws an exception if called before a CAthlet object was created.
	 *
	 * @exception Except::GenericException
	 *
	 * @return the new CAthlet object
	 */
	CAthlet* GetAthlet() const;

    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // methods
    //------------------------------------------------------------------------------
    private slots:
	/**
	 * Checks all values on the second page for validity.
	 * If all values are ok, the next btn is enabled.
	 *
	 * @param sText [IN] - the text of the calling edit widget.
	 */
	void SlotCheckPage2(const QString& sText);

	/**
	 * Sets a boolean value to true to show that the user changed the date.
	 *
	 * @note Can't set a valid/invalid date, so we have to check for a change.
	 */
	void SlotDateChanged();

	/**
	 * Creates the CAthlet object.
	 * The object is created from the values in the editfields.
	 *
	 * @note Exceptions when creating a new CAthlet onject are caught here.
	 */
	void SlotCreateAthlet();
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	bool m_bDateChanged;	///< did the user change the dateedit widget?
	CAthlet* m_pAthlet;	///< the created CAthlet object.
    
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CWizard( const TSelf& other );
};

}; //namespace

#endif//__PHIL_WIZARD_H__


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
	* short method description.
	* brief method description.
	*
	* @param name desc
	**/
	CWizard(QWidget* pParent, const char* szName);

	/** default destructor */
	virtual ~CWizard();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------
    CAthlet* GetAthlet() const;

    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // methods
    //------------------------------------------------------------------------------

    protected:


    private slots:
	void SlotCheckPage2(const QString& sText);
	void SlotDateChanged();
	void SlotCreateAthlet();
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	bool m_bDateChanged;
	CAthlet* m_pAthlet;
    
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CWizard( const TSelf& other );
};

}; //namespace

#endif//__PHIL_WIZARD_H__


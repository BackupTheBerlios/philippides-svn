//******************************************************************************
/** @file RunDialog.h
 * This file contains the definition of the class CRunDialog
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/32/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_RUN_DIALOG_H__
#define __PHIL_RUN_DIALOG_H__

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// headers for each lib should have own section


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "RunDialogBase.h"

//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------
//local forwarding
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

/** @class CRunDialog
 * This dialog can create and edit CRun objects.
 * The object discards the newly created object's ownership.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/32/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CRunDialog: public CRunDialogBase
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef CRunDialog TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* Constructor.
	* Creates the dialog and set's all widgets to a default state.
	*
	* @param pParent    [IN] - The widget's parent widget
	* @param szName	    [IN] - Qt's internal string representation
	**/
	CRunDialog(QWidget* pParent, const char* szName);
	
	/**
	 * Constructor.
	 * Sets the widget's initial values it gets from the given CRun object.
	 *
	 * @overload
	 * @exception Except::InvalidDataException
	 * @param pRun	    [IN] - The dialog's widgets are set to the values from 
	 *			    this object.
	 * @param pParent   [IN] - The widget's parent widget
	 * @param szName    [IN] - Qt's internal string representation
	 */
	CRunDialog(const CRun* pRun, QWidget* pParent, const char* szName);

	/** default destructor */
	virtual ~CRunDialog();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------
	/**
	 * Returns the created object.
	 * \note Ownership is discarded.
	 *
	 * @exception Except::GenericException
	 * @return the new object
	 */
	CRun* GetRun();

    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // methods
    //------------------------------------------------------------------------------

    protected:


    private slots:
	/**
	 * This slot creates the new CRun object.
	 */
	void SlotCreateRun();

    private:
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	CRun* m_pRun;	    ///< The created CRun object.
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CRunDialog( const TSelf& other );
};

}; //namespace

#endif//__PHIL_RUN_DIALOG_H__


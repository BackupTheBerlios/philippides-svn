//******************************************************************************
/** @file DbWidget.h
 *  This file contains the definition of the class CDbWidget
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 23.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_DB_WIDGET_H__
#define __PHIL_DB_WIDGET_H__

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
#include "DbWidgetBase.h"

//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------
// qt forwarding
class QWidget;

// local forwarding
namespace Phil
{
    class CAthlet;
    class CRun;
    class CRunPtrList;
}

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

//******************************************************************************
// declarations
//******************************************************************************

namespace Phil
{

/** @class CDbWidget
 * This class is phil's basewidget.
 * It contains different Labels that display the CAthlet and current CRun values.
 * It also contains a QListView with the different runs. In the ListView, there are
 * CRunListViewItem objects, which are normal QListViewItems plus one CRun*, so
 * we have to keep track of only one databaslocations. I decided for this solution
 * because it's hard to keep two database representations (e.g. the QListView and a 
 * QPtrList) in sync. For database exchange between objects, the CRun*s are stored in
 * a non-destructive QPtrList but the main database is the QListView / it's items.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 23.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CDbWidget: public CDbWidgetBase
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef CDbWidget TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* Constructor.
	* This constructor creates a normal qt widget and initializes his CAthlet
	* related labels with the given object.
	* \note We always have one CAthlet object, because if no athlet xml file exists
	*	the wizard gets called a CAthlet object is created. So we don't need 
	*	another constructor.
	*
	* @param pParent    [IN] - Qt's parent widget
	* @param szName	    [IN] - Qt's internal widget name.
	* @param pAthlet    [IN] - The user's CAthlet object.
	**/
	CDbWidget(QWidget* pParent, const char* szName, const CAthlet* pAthlet);

	/** default destructor */
	virtual ~CDbWidget();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------
	/**
	 * Set's a new CAthlet object.
	 * The old one get's deleted.
	 *
	 * @param pAthlet [IN] - The new CAthlet object
	 */
	void SetAthlet(const CAthlet* pAthlet);

	/**
	 * Had the database been changed since the last save?
	 *
	 * @return Had the database been changed?
	 */
	bool IsChanged() const {return m_bChanged;}

	/**
	 * Set the "changed" state of the database.
	 * This method is necessary because at startup the databse is read and
	 * SlotNewRun get's called, which sets the "changed" state to true,
	 * this is false at startup, so we have to set the state to "not changed"
	 * after startup.
	 *
	 * @param bChanged [IN] - set the database status to changed/not changed.
	 */
	void SetChanged(bool bChanged) {m_bChanged = bChanged;}


	CRunPtrList* GetRunList() const;
	
    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // methods
    //------------------------------------------------------------------------------
    public slots:
	/**
	 * Adds a CRun Object to the databse.
	 * 
	 * @param pRun [IN] - The Run object to add
	 */
	void SlotNewRun(CRun* pRun);

	/**
	 * Opens a dialog to create the CRun object.
	 *
	 * @overload
	 */
	void SlotNewRun();

	/**
	 * Deletes the selected item from the database.
	 * If no item is selected, a errorbox pops up.
	 */
	void SlotDelRun();

	/**
	 * Opens a CRunDialog with the initial values of the selected item.
	 * If data is changed, the old object gets deleted and the new one is 
	 * added. If no Item is selected a errorbox pops up.
	 */
	void SlotEditRun();

	/**
	 * Called when a CRunListViewItem is selected.
	 * This method updates the CRun related labels with the values of the 
	 * selected item.
	 *
	 * \note The parameter item is a CRunListViewItem, we have to cast it to
	 *	 get the CRun*.
	 *
	 * @param pItem [IN] - The selected item.
	 */
	void SlotSelected(QListViewItem* pItem);

	/**
	 * Save the databse to disk.
	 * Calles Philippise's save slot and sets the "changed" state to false.
	 */
	void SlotSaveDatabase();
	
    protected:


    private:
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	const CAthlet* m_pAthlet;	///< The user's CAthlet representation
	bool m_bChanged;		///< Flag which marks if the database had been 
					///< changed since last save.
					
    private:
	/**
	 * Updates all CAthlet related labels with m_pAthlet's values.
	 */
	void UpdateAthletLabel();
	
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CDbWidget( const TSelf& other );
};

}; //namespace

#endif//__PHIL_DB_WIDGET_H__


//******************************************************************************
/** @file RunListViewItem.h
 * This file contains the definition of the class CRunListViewItem.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/32/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_RUN_LIST_VIEW_ITEM_H__
#define __PHIL_RUN_LIST_VIEW_ITEM_H__

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes
#include <qlistview.h>

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

/** @class RunListViewItem
 * Adapted version of a ListView Item.
 * This class provides an extended functionality to a QListViewItem by storung a 
 * pointer to a CRun object.
 *
 * \note This object owns the pointer and deletes the CRun object at destruction.  
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/32/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CRunListViewItem: public QListViewItem
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef CRunListViewItem TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* Constructor
	* This is the only constructor to make sure that every object of this class
	* has one CRun*.
	*
	* @param pParent    [IN] - The item's QListView to add the object to.
	* @param pRun	    [IN] - The owned CRun pointer.
	**/
	CRunListViewItem(QListView* pParent, const CRun* pRun);

	/** default destructor */
	virtual ~CRunListViewItem();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------
	/**
	 * Returns the owned CRun*
	 *
	 * @return The CRun*.
	 */
	const CRun* GetRun() const  {return m_pRun;}
    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // methods
    //------------------------------------------------------------------------------

    protected:


    private:
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	const CRun* m_pRun;	///< The owned CRun*
	    
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CRunListViewItem( const TSelf& other );
};

}; //namespace

#endif//__PHIL_RUN_LIST_VIEW_ITEM_H__


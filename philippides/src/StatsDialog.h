//******************************************************************************
/** @file StatsDialog.h
 * This file contains the definition of the class CStatsDialog
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Apr/18/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_STATS_DIALOG_H__
#define __PHIL_STATS_DIALOG_H__

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------
#include <vector>

//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "StatsDialogBase.h"

//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------
namespace Phil
{
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

/** @class CStatsDialog
 * Thic class provides a dialog which can show different kindas of statistics.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Apr/18/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CStatsDialog: public CStatsDialogBase
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef CStatsDialog TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* Standard constructor.
	*
	* @param pRunList   [IN] - The list with the CRun objects to create the stats
	*			    from.
	* @param pParent    [IN] - the dialog's parent widget.
	* @param szName	    [IN] - Qt's internal name representation of the object/class.
	**/
	CStatsDialog(CRunPtrList* pRunList, QWidget* pParent, const char* szName);

	/** default destructor */
	virtual ~CStatsDialog();


    private slots:
	/**
	 * Creates all the statistics.
	 * The data is stored in the vector m_pData.
	 */
	void SlotCreateStats();

    private:
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	CRunPtrList* m_pRunList;		///< The list with all the CRun objects.
						///< This is owned here and will be deleted 
						///< here!!
						
	std::vector<unsigned int>* m_pData;	///< The created statistics are stored here.
						///< Owned and deleted here!!

    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CStatsDialog( const TSelf& other );
};

}; //namespace

#endif//__PHIL_STATS_DIALOG_H__


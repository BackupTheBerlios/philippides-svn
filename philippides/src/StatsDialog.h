//******************************************************************************
/** @file StatsDialog.h
 *
 * short description.
 * brief description.
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
 *
 * short description.
 * brief description.
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
	* short method description.
	* brief method description.
	*
	* @param name desc
	**/
	CStatsDialog(CRunPtrList* pRunList, QWidget* pParent, const char* szName);

	/** default destructor */
	virtual ~CStatsDialog();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // methods
    //------------------------------------------------------------------------------
		
    protected:

    private slots:
	void SlotCreateStats();

    private:
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	CRunPtrList* m_pRunList;
	std::vector<unsigned int>* m_pData;

    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CStatsDialog( const TSelf& other );
};

}; //namespace

#endif//__PHIL_STATS_DIALOG_H__

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
 *
 * short description.
 * brief description.
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
	* short method description.
	* brief method description.
	*
	* @param name desc
	**/
	CDbWidget(QWidget* pParent, const char* szName, const CAthlet* pAthlet);

	/** default destructor */
	virtual ~CDbWidget();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------
	void SetAthlet(const CAthlet* pAthlet);

    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // methods
    //------------------------------------------------------------------------------
    public slots:
	void SlotNewRun();
	void SlotNewRun(CRun* pRun);
	void SlotSelected(QListViewItem* pItem);
	void SlotSaveDatabase();
	
    protected:


    private:
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	const CAthlet* m_pAthlet;
    private:
	void UpdateAthletLabel();
	
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CDbWidget( const TSelf& other );
};

}; //namespace

#endif//__PHIL_DB_WIDGET_H__


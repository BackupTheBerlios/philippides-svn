//******************************************************************************
/** @file DbWidget.h
 *
 * short description.
 * brief description.
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
	CDbWidget(QWidget* pParent, const char* szName);

	/** default destructor */
	virtual ~CDbWidget();

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


    private:
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	    
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CDbWidget( const TSelf& other );
};

}; //namespace

#endif//__PHIL_DB_WIDGET_H__


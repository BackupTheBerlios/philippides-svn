//******************************************************************************
/** @file MapWidget.h
 *
 * short description.
 * brief description.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Jun/3/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_MAP_WIDGET_H__
#define __PHIL_MAP_WIDGET_H__

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes
#include <qlabel.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------
// qt forwarding
class QPaintEvent;

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

//******************************************************************************
// declarations
//******************************************************************************

namespace Phil
{

/** @class CMapWidget
 *
 * short description.
 * brief description.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Jun/3/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CMapWidget: public QLabel
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef CMapWidget TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* short method description.
	* brief method description.
	*
	* @param name desc
	**/
	CMapWidget(QWidget* pParent, const char* szName);

	/** default destructor */
	virtual ~CMapWidget();

    protected:
//	void paintEvent(QPaintEvent* e);
	
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CMapWidget( const TSelf& other );
};

}; //namespace

#endif//__PHIL_MAP_WIDGET_H__


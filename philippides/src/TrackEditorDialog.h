//******************************************************************************
/** @file TrackEditorDialog.h
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

#ifndef __PHIL_TRACK_EDITOR_DIALOG_H__
#define __PHIL_TRACK_EDITOR_DIALOG_H__


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt headers
#include <qimage.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "TrackEditorDialogBase.h"

//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------
// qt forwarding
class QLabel;

namespace Phil{
    class CMapWidget;
}
//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

//******************************************************************************
// declarations
//******************************************************************************

namespace Phil
{

/** @class CTrackEditorDialog
 *
 * short description.
 * brief description.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Jun/3/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CTrackEditorDialog: public CTrackEditorDialogBase
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef CTrackEditorDialog TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* short method description.
	* brief method description.
	*
	* @param name desc
	**/
	CTrackEditorDialog(QWidget* pParent, const char* szName);

	/** default destructor */
	virtual ~CTrackEditorDialog();


    private:
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	void SlotOkBtn();
	void SlotOpenBtn();
	void SlotMagBtn();
	void SlotMinBtn();

	QImage m_mapImage;
	CMapWidget* m_pMapLabel;
	
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CTrackEditorDialog( const TSelf& other );
};

}; //namespace

#endif//__PHIL_TRACK_EDITOR_DIALOG_H__


//******************************************************************************
/** @file StatsWidget.h
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

#ifndef __PHIL_STATS_WIDGET_H__
#define __PHIL_STATS_WIDGET_H__

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------
#include <vector>

//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt headers
#include <qframe.h>  // baseclass
#include <qstringlist.h>


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

//******************************************************************************
// declarations
//******************************************************************************

namespace Phil
{

/** @class CStatsWidget
 *
 * short description.
 * brief description.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Apr/18/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CStatsWidget: public QFrame
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef CStatsWidget TSelf;
    
    enum EnDrawMode{
	    WEEK_MODE,
	    MONTH_MODE,
	    YEAR_MODE,
	    FREE_MODE};

   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* short method description.
	* brief method description.
	*
	* @param name desc
	**/
	CStatsWidget(QWidget* pParent, const char* szName);

	/** default destructor */
	virtual ~CStatsWidget();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------
	void SetData(const std::vector<unsigned int>* pData, EnDrawMode mode) {
			m_pData = pData;
			m_EnDrawMode = mode;
			repaint();}
			
	

    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // methods
    //------------------------------------------------------------------------------

    protected:


    private:
	void paintEvent(QPaintEvent* p);
	void DrawGrid(const QStringList& labelList);
	void DrawBars();
	void DrawData();
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	EnDrawMode m_EnDrawMode;	    
	const std::vector<unsigned int>* m_pData;

	unsigned int m_nLeftBorder;
	unsigned int m_nBottomBorder;
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CStatsWidget( const TSelf& other );
};

}; //namespace

#endif//__PHIL_STATS_WIDGET_H__


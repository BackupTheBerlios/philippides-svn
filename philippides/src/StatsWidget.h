//******************************************************************************
/** @file StatsWidget.h
 * This file contains the definition of the class CStatsWidget
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
 * This class provides a widget with can display bar graphs of given values.
 * The drawn values are gained from the vector given in SetData. The bars 
 * are labeled with the appropriate day/week/month name/number which is 
 * specified with the EnDrawMode parameter in SetData.
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
	    YEAR_WEEK_MODE,
	    YEAR_MODE,
	    FREE_MODE};

   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* standard constructor
	*
	* @param pParent    [IN] - The widget's parent widget.
	* @param szName	    [IN] - Qt's internal name representation.
	**/
	CStatsWidget(QWidget* pParent, const char* szName);

	/** default destructor */
	virtual ~CStatsWidget();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------
	/**
	 * Set the data to display  and the draw mode.
	 *
	 * @param pData [IN] - The data to display.
	 * @param mode	[IN] - The draw mode (day, week, monthe, year)
	 */
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
	/** Inherited from baseclass, see there for details */ 
	void paintEvent(QPaintEvent* p);

	/** helper function to draw the grid. Called by paintEvent */
	void DrawGrid(const QStringList& labelList);

	/** helper function to draw the bars. Called by paintEvent */
	void DrawBars();

	/** helper function to draw the data. Called by paintEvent */
	void DrawData();
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	EnDrawMode m_EnDrawMode;		    ///< The draw mode \see EnDrawMode.
	const std::vector<unsigned int>* m_pData;   ///< The data to display. Not Owned.
	unsigned int m_nLeftBorder;		    ///< The left border of the draw area.
	unsigned int m_nBottomBorder;		    ///< The bottom border of the draw area.
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CStatsWidget( const TSelf& other );
};

}; //namespace

#endif//__PHIL_STATS_WIDGET_H__


//******************************************************************************
/**
 * @file StatsWidget.cpp
 * short description.
 * brief description.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Apr/18/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************


//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes
#include <qapplication.h>
#include <qpainter.h>
#include <qpen.h>
#include <qdatetime.h>
#include <qstring.h>

// kde includes
#include <klocale.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "Exceptions.h"
#include "StatsWidget.h"


//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------


//******************************************************************************
// implementation
//******************************************************************************
namespace Phil
{

//------------------------------------------------------------------------------
// structors
//------------------------------------------------------------------------------
CStatsWidget::CStatsWidget(QWidget* pParent, const char* szName):
    QFrame(pParent, szName),
    m_EnDrawMode(WEEK_MODE)
{
    setEraseColor(Qt::black);
}

CStatsWidget::~CStatsWidget()
{

}

//------------------------------------------------------------------------------
// accessors
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// operator
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// methods
//------------------------------------------------------------------------------
void CStatsWidget::paintEvent(QPaintEvent* p)
{
    DrawData();
}

void CStatsWidget::DrawData()
{
    switch(m_EnDrawMode){
	case WEEK_MODE:
	    {
		QStringList dayList;
		for(int i=1; i<=7; i++){
		    dayList += QDate::longDayName(i);
		}
		DrawGrid(dayList);
		break;
	    }
	case MONTH_MODE:
	    {
		QStringList monthList;
		for(int i=1; i<=31; i++){
		    monthList += QString::number(i);
		}
		DrawGrid(monthList);
	        break;
	    }
	case YEAR_MODE:
	    {
		QStringList yearList;
		for(int i=1; i<=12; i++){
		    yearList += QDate::longMonthName(i);
		}
		DrawGrid(yearList);
	    break;
	    }
	case FREE_MODE:
	    throw Except::GenericException(__PRETTY_FUNCTION__, "Free mode not yet implemented");
	    break;

	default:
	    throw Except::InvalidDataException(__PRETTY_FUNCTION__, "m_EnDrawMode");
    }
}

void CStatsWidget::DrawGrid(const QStringList& labelList)
{
    unsigned int nCols = labelList.size();
    unsigned int nLeftBorder = 40;
    unsigned int nBottomBorder = 20;
    unsigned int nWidth = width() - nLeftBorder;
    unsigned int nHeight = height() - nBottomBorder;
    QPainter p(this);
    QPen GridPen(Qt::gray);
    QPen TextPen(Qt::lightGray);
    p.setPen(GridPen);

    // draw horizontal line
    p.drawLine(nLeftBorder, nHeight, width(), nHeight);
    
    unsigned int nColWidth = nWidth / nCols;
	    
    // draw vertical lines
    for(unsigned int i=0; i<nCols; i++){
	unsigned int nX = i*nColWidth + nLeftBorder;
	p.drawLine(nX, 0, nX, nHeight);
    }
    
    p.setPen(TextPen);
    
    // draw weekday names
    for(unsigned int i=0; i<labelList.size(); i++){
	unsigned int nX = i*nColWidth + nLeftBorder + 5;
	p.drawText(nX, height()-5, labelList[i]);
    }
}

};//namespace


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
#include <algorithm>

//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes
#include <qapplication.h>
#include <qpainter.h>
#include <qpen.h>
#include <qbrush.h>
#include <qdatetime.h>
#include <qstring.h>

// kde includes
#include <klocale.h>
#include <kdebug.h>

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
    DrawBars();
}

void CStatsWidget::DrawData()
{
    m_nLeftBorder = 40;
    m_nBottomBorder = 20;
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
		for(unsigned int i=1; i<=m_pData->size(); i++){
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
    unsigned int nWidth = width() - m_nLeftBorder;
    unsigned int nHeight = height() - m_nBottomBorder;
    QPainter p(this);
    QPen GridPen(Qt::gray);
    QPen TextPen(Qt::lightGray);
    p.setPen(GridPen);

    // draw horizontal line
    p.drawLine(m_nLeftBorder, nHeight, width(), nHeight);
    
    unsigned int nColWidth = nWidth / nCols;
	    
    // draw vertical lines
    for(unsigned int i=0; i<nCols; i++){
	unsigned int nX = i*nColWidth + m_nLeftBorder;
	p.drawLine(nX, 0, nX, nHeight);
    }
    
    p.setPen(TextPen);
    
    // draw weekday names
    for(unsigned int i=0; i<labelList.size(); i++){
	unsigned int nX = i*nColWidth + m_nLeftBorder + 5;
	p.drawText(nX, height()-5, labelList[i]);
    }
}

void CStatsWidget::DrawBars()
{
    for(int i=0; i<m_pData->size(); i++)
	kdDebug() << "Value: " << m_pData->at(i) << endl;
    unsigned int nCols = m_pData->size();
    unsigned int nDrawWidth = width() - m_nLeftBorder;
    unsigned int nDrawHeight = height() - m_nBottomBorder;
    unsigned int nColWidth = nDrawWidth / nCols;
    unsigned int nMaxVal = *(std::max_element(m_pData->begin(), m_pData->end())); 
   
    float fScale = ((float)nDrawHeight) / nMaxVal;

    // scale to 90% of draw area
    fScale *= 0.9;
    
    QPainter p(this);
    QPen BarFramePen(Qt::white);
    QBrush BarFillBrush(Qt::red, Qt::Dense3Pattern);
    p.setPen(BarFramePen);
    p.setBrush(BarFillBrush);

    for(unsigned int i=0; i<m_pData->size(); i++){
	if(m_pData->at(i) == 0)
	    continue;
	unsigned int nX = i*nColWidth + m_nLeftBorder;
	unsigned int nY = nDrawHeight-(unsigned int)(m_pData->at(i)*fScale);
	p.drawRect(nX, nY, nColWidth, nDrawHeight-nY);
    }
}

};//namespace


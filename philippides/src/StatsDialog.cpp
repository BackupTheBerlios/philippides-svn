//******************************************************************************
/**
 * @file StatsDialog.cpp
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
#include <qdatetime.h>
#include <qptrlist.h>
#include <qradiobutton.h>

// kde includes
#include <kdebug.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "Run.h"
#include "StatsDialog.h"
#include "RunPtrList.h"
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
CStatsDialog::CStatsDialog(CRunPtrList* pRunList, QWidget* pParent, 
			   const char* szName):
    CStatsDialogBase(pParent, szName),
    m_pRunList(pRunList),
    m_pData(0)
{
    connect((QObject*)periodButtonGroup, SIGNAL(clicked(int)), SLOT(SlotCreateStats()));
    SlotCreateStats();
}

CStatsDialog::~CStatsDialog()
{
    delete m_pRunList;
    delete m_pData;
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
void CStatsDialog::SlotCreateStats()
{
    delete m_pData;
    m_pData = 0;
    CRun* pRun=0;

    m_pRunList->sort();
    
    if(weekBtn->isOn()){
	m_pData = new std::vector<unsigned int>(7, 0);
	for(pRun = m_pRunList->first(); pRun; pRun = m_pRunList->next()){
	    kdDebug() << "Days to: " << pRun->m_Date.daysTo( QDate::currentDate()) << endl;
	    int nDaysTo = pRun->m_Date.daysTo(QDate::currentDate());
	    if(nDaysTo > 7)
		continue;
	    if(nDaysTo < 0)
		break;
	    if(nDaysTo < QDate::currentDate().dayOfWeek())
		m_pData->at(pRun->m_Date.dayOfWeek()-1) = pRun->m_nLength;
	}
	statsWidget->SetData(m_pData, CStatsWidget::WEEK_MODE);
    }
    else if(monthBtn->isOn()){
	m_pData = new std::vector<unsigned int>(QDate::currentDate().daysInMonth(), 0);
	for(pRun = m_pRunList->first(); pRun; pRun = m_pRunList->next()){
	    kdDebug() << "Days to: " << pRun->m_Date.daysTo( QDate::currentDate()) << endl;
	    int nDaysTo = pRun->m_Date.daysTo(QDate::currentDate());
	    if(nDaysTo > QDate::currentDate().daysInMonth())
		continue;
	    if(nDaysTo < 0)
		break;
	    if(nDaysTo < QDate::currentDate().day())
		m_pData->at(pRun->m_Date.day()-1) = pRun->m_nLength;
	}
	statsWidget->SetData(m_pData, CStatsWidget::MONTH_MODE);
    }
    else if(yearBtn->isOn()){
	m_pData = new std::vector<unsigned int>(12, 0);
	for(pRun = m_pRunList->first(); pRun; pRun = m_pRunList->next()){
	    int nDaysTo = pRun->m_Date.daysTo(QDate::currentDate());
	    if(nDaysTo > QDate::currentDate().daysInYear())
		continue;
	    if(nDaysTo < 0)
		break;
	    if(nDaysTo < QDate::currentDate().dayOfYear())
		m_pData->at(pRun->m_Date.month()) += pRun->m_nLength;
	}
	statsWidget->SetData(m_pData, CStatsWidget::YEAR_MODE);
    }
    else{

    }
}

};//namespace

//******************************************************************************
/**
 * @file RunListViewItem.cpp
 * short description.
 * brief description.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/32/2004
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
#include <qstring.h>


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "Run.h"
#include "RunListViewItem.h"


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
CRunListViewItem::CRunListViewItem(QListView* pParent, const CRun* pRun):
    QListViewItem(pParent, 
		  pRun->m_Date.toString(Qt::ISODate), 
		  QString::number(pRun->m_nLength),
		  pRun->m_Time.toString()),
    m_pRun(pRun)
{

}

CRunListViewItem::~CRunListViewItem()
{
    delete m_pRun;
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

};//namespace


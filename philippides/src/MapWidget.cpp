//******************************************************************************
/**
 * @file MapWidget.cpp
 * short description.
 * brief description.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Jun/3/2004
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


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "MapWidget.h"


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
CMapWidget::CMapWidget(QWidget* pParent, const char* szName):
    QLabel(pParent, szName)
{

}

CMapWidget::~CMapWidget()
{
    /* EMPTY */ 
}
/*
void CMapWidget::paintEvent(QPaintEvent* e)
{
    

}
*/

};//namespace

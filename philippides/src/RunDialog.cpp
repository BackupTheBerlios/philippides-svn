//******************************************************************************
/**
 * @file RunDialog.cpp
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
// qt headers
#include <qdatetimeedit.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <qtextedit.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "Run.h"
#include "Exceptions.h"
#include "RunDialog.h"


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
CRunDialog::CRunDialog(QWidget* pParent, const char* szName):
    CRunDialogBase(pParent, szName),
    m_pRun(0)
{
    DateEdit->setDate(QDate::currentDate());
    connect((QWidget*)OkBtn, SIGNAL(clicked()), SLOT(SlotCreateRun()));
}

CRunDialog::~CRunDialog()
{

}

//------------------------------------------------------------------------------
// accessors
//------------------------------------------------------------------------------
inline CRun* CRunDialog::GetRun()
{
    if(!m_pRun)
	throw Except::GenericException("CRunDialog::GetRun()",
		"Trying to get a pointer to a non existent object (null-ptr)!");

    return m_pRun;
}

//------------------------------------------------------------------------------
// operator
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// methods
//------------------------------------------------------------------------------
void CRunDialog::SlotCreateRun()
{
    delete m_pRun;

    m_pRun = new CRun(DateEdit->date(), TimeEdit->time());
    if(LengthBox->value() > 0)
	m_pRun->m_nLength = LengthBox->value();
    if(PulseBox->value() > 0)
	m_pRun->m_nPulse = PulseBox->value();
    if(WeatherBox->currentItem() > 0)
	m_pRun->m_EnWeather = static_cast<CRun::EnWeather>(WeatherBox->currentItem()-1);
    if(ImpressionBox->currentItem() > 0)
	m_pRun->m_EnImpression = static_cast<CRun::EnImpression>(ImpressionBox->currentItem()-1);
    if(!CommentEdit->text().isEmpty())
	m_pRun->m_sComment = CommentEdit->text();

    accept();
}


};//namespace

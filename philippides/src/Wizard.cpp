//******************************************************************************
/**
 * @file Wizard.cpp
 * short description.
 * brief description.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 23.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************


//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------
#include <iostream>

//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt headers
#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qtextbrowser.h>
#include <qpushbutton.h>
#include <qdatetime.h>
#include <qlineedit.h>
#include <qcombobox.h>

// kde headers
#include <kstandarddirs.h>
#include <kdatewidget.h>
#include <knuminput.h>
#include <ktimewidget.h>


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "Wizard.h"
#include "Exceptions.h"
#include "Athlet.h"

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
CWizard::CWizard(QWidget* pParent, const char* szName):
    CWizardBase( pParent, szName ),
    m_bDateChanged( false ),
    m_pAthlet( 0 )
{
    // disable next button until user accepts disclaimer
    setNextEnabled( page_1, false );
    // disable next button until user enters valid data for name and birthday
    setNextEnabled( page_2, false );
    setFinishEnabled( page_3, true );
    
    QString sLicensePath = locate( "data", "LICENSES/GPL_V2" );
    
    if ( sLicensePath.isEmpty() ){
	LicenseTextBrowser->setText( "License file not found!" );
    }
    else{
	QFile file( sLicensePath );
	
	if ( file.open( IO_ReadOnly ) ){
	    QTextStream stream( &file );
	    LicenseTextBrowser->setText( stream.read() );
	}
	else{
	    LicenseTextBrowser->setText( "Can't open license file!" );
	}
	
	file.close();
    }

    QButton* pNextBtn = nextButton();
    QButton* pFinishBtn = finishButton();
    connect( ( QObject* )AcceptBtn, SIGNAL( toggled( bool ) ), 
			 pNextBtn, SLOT( setEnabled( bool ) ) );

    connect( ( QObject* )pFinishBtn, SIGNAL( clicked() ),
			    this, SLOT( SlotCreateAthlet() ) );

    connect( ( QObject* ) FNameEdit, SIGNAL( textChanged( const QString&) ),
			    this, SLOT( SlotCheckPage2( const QString& ) ) );
    connect( ( QObject* ) LNameEdit, SIGNAL( textChanged( const QString& ) ),
			    this, SLOT( SlotCheckPage2( const QString& ) ) );
    connect( ( QObject* ) DateWidget, SIGNAL( changed( QDate ) ),
			    this, SLOT( SlotDateChanged() ) );
}

CWizard::~CWizard()
{
    /* EMPTY */
}


//------------------------------------------------------------------------------
// accessors
//------------------------------------------------------------------------------
CAthlet* CWizard::GetAthlet() const
{
    if ( !m_pAthlet )
	throw Except::GenericException( "CWizard::GetAthlet", 
					"Trying to get a athlet object* while none was created" );
return m_pAthlet;
}

//------------------------------------------------------------------------------
// operator
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// methods
//------------------------------------------------------------------------------
void CWizard::SlotCheckPage2(const QString& )
{
    if ( !FNameEdit->text().isEmpty() &&
	 !LNameEdit->text().isEmpty() &&
	 m_bDateChanged){
	nextButton()->setEnabled( true );
    }
}

void CWizard::SlotDateChanged()
{
    m_bDateChanged = true;
    SlotCheckPage2("");
}

void CWizard::SlotCreateAthlet()
{
    try{
	CAthlet::EnGender gender;
	if ( GenderBox->currentItem( ) == 0 )
	    gender = CAthlet::FEMALE;
	else
	    gender = CAthlet::MALE;
	
	m_pAthlet = new CAthlet( FNameEdit->text(), 
				 LNameEdit->text(), 
				 gender,
				 DateWidget->date() );

	if ( WeightInput->value() > 0 ) m_pAthlet->m_nWeight = WeightInput->value();
	if ( HeightInput->value() > 0 ) m_pAthlet->m_nHeight = HeightInput->value();
	if ( RunFreqInput->value() > 0 ) m_pAthlet->m_nRunningFreq = RunFreqInput->value();
	if ( AvgDistInput->value() > 0 ) m_pAthlet->m_nAvgDistance = AvgDistInput->value();
	if ( !Km5TimeWidget->time().isNull() ) m_pAthlet->m_kmTime5 = Km5TimeWidget->time();
	if ( !Km10TimeWidget->time().isNull() ) m_pAthlet->m_kmTime10 = Km10TimeWidget->time();
	if ( BigDistInput->value() > 0 ) m_pAthlet->m_nBiggestDistance = BigDistInput->value();
	if ( AvgPulseInput->value() > 0 ) m_pAthlet->m_nAvgPulse = AvgPulseInput->value();
	if ( MorningPulseInput->value() > 0 ) m_pAthlet->m_nMorningPulse = MorningPulseInput->value();
    }
    catch( Except::PhilException& e )
    {
	std::cerr << e.what() << std::endl;
    }
}

};//namespace


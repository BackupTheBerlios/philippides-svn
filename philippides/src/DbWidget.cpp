//******************************************************************************
/**
 * @file DbWidget.cpp
 * This file contains the implementation of the class CDbWidget
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


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// stl includes
#include <iostream>

// qt includes
#include <qlabel.h>
#include <qtextedit.h>
#include <qptrlist.h>
#include <qwidgetstack.h>
#include <qlayout.h>

// kde includes
#include <klocale.h>
#include <kdebug.h>
#include <klistview.h>
#include <kmessagebox.h>
#include <khtml_part.h>
#include <khtmlview.h>

// libxml includes
#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlIO.h>
#include <libxml/DOCBparser.h>
#include <libxml/xinclude.h>
#include <libxml/catalog.h>

// libxslt includes
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "Exceptions.h"
#include "RunListViewItem.h"
#include "RunDialog.h"
#include "Athlet.h"
#include "DbWidget.h"
#include "RunPtrList.h"


//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------
extern int xmlLoadExtDtdDefaultValue;

//******************************************************************************
// implementation
//******************************************************************************
namespace Phil
{

//------------------------------------------------------------------------------
// structors
//------------------------------------------------------------------------------
CDbWidget::CDbWidget(QWidget* pParent, const char* szName, const CAthlet* pAthlet):
    CDbWidgetBase( pParent, szName ),
    m_pAthlet(pAthlet),
    m_bChanged(false)
{
    QHBoxLayout* pLayout = new QHBoxLayout(m_pHtmlFrame);
    m_pHtmlPart = new KHTMLPart(m_pHtmlFrame, "htmlpart", this, "htmlpart");
    m_pHtmlPart->view()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    kdDebug() << m_pHtmlPart->name() << endl; 
    pLayout->addWidget(m_pHtmlPart->view());
    
    connect((QObject*)AddBtn, SIGNAL(clicked()), SLOT(SlotNewRun()));
    connect((QObject*)DelBtn, SIGNAL(clicked()), SLOT(SlotDelRun()));
    connect((QObject*)EditBtn, SIGNAL(clicked()), SLOT(SlotEditRun()));
    connect((QObject*)RunListView, SIGNAL(selectionChanged(QListViewItem*)), 
				   SLOT(SlotSelected(QListViewItem*)));
    
    if(m_pAthlet)
	UpdateAthletLabel();
}

CDbWidget::~CDbWidget()
{

}

//------------------------------------------------------------------------------
// accessors
//------------------------------------------------------------------------------
void CDbWidget::SetAthlet(const CAthlet* pAthlet)
{
    delete m_pAthlet;
    m_pAthlet = pAthlet;
    UpdateAthletLabel();
}

//------------------------------------------------------------------------------
// operator
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// methods
//------------------------------------------------------------------------------
void CDbWidget::SlotNewRun()
{
    CRunDialog runDlg(this, "rundialog");
   
    try{
	if(runDlg.exec() == QDialog::Rejected)
	    return;
	
	SlotNewRun(runDlg.GetRun());
    }
    catch(Except::PhilException& e)
    {
	kdDebug() << e.what() << endl;
    }
}

void CDbWidget::SlotNewRun(CRun* pRun)
{
    QListViewItem* pItem = new CRunListViewItem((QListView*)RunListView, pRun);
    RunListView->setSelected(pItem, true);
    m_bChanged = true;
}

void CDbWidget::SlotDelRun()
{
    CRunListViewItem* pItem = static_cast<CRunListViewItem*>(RunListView->selectedItem());
    if(!pItem){
	KMessageBox::sorry(this,i18n("No item selected"), i18n( "Sorry..."));
	return;
    }
    RunListView->takeItem(pItem);
    m_bChanged = true;
}

void CDbWidget::SlotEditRun()
{
    CRunListViewItem* pItem = static_cast<CRunListViewItem*>(RunListView->selectedItem());
    if(!pItem){
	KMessageBox::sorry(this,i18n("No item selected"), i18n( "Sorry..."));
	return;
    }
    
    try{
	CRunDialog runDlg( pItem->GetRun(), this, "rundialog");

	if(runDlg.exec() == QDialog::Rejected)
	    return;

	RunListView->takeItem(pItem);
	SlotNewRun(runDlg.GetRun());
    }
    catch(Except::PhilException& e)
    {
	kdDebug() << e.what() << endl;
    }
}

void CDbWidget::SlotSelected(QListViewItem* pItem)
{
    const CRun* pRun = static_cast<CRunListViewItem*>(pItem)->GetRun();

    DateLabel->setText(pRun->m_Date.toString(Qt::ISODate));
    LengthLabel->setText(QString::number(pRun->m_nLength) + "m");
    TimeLabel->setText(pRun->m_Time.toString(Qt::ISODate));
    PulseLabel->setText(QString::number(pRun->m_nPulse) + "/s");
    CommentEdit->setText(pRun->m_sComment);

    /// @todo change the sequence of images in the stack that 0 is the no-image
    // widget, so we can do a pRun->m_EnWeather - 1 to show the right one and we don't have
    // to use 4 as magic number
    if(pRun->m_EnWeather >= 0)
	WeatherStack->raiseWidget(pRun->m_EnWeather);
    else
	WeatherStack->raiseWidget(4);

    if(pRun->m_EnImpression >= 0)
	ImpressionStack->raiseWidget(pRun->m_EnImpression);
    else
	ImpressionStack->raiseWidget(4);

}

void CDbWidget::SlotSaveDatabase()
{
    if(!m_bChanged) return;
	
    QPtrList<Phil::CRun> list;
    CRunListViewItem* pItem = static_cast<CRunListViewItem*>(RunListView->firstChild());
    
    while(pItem){
	list.append(pItem->GetRun());
    	pItem = static_cast<CRunListViewItem*>(pItem->itemBelow());
    }

    try{
	CRun::ToDisk(list);
	m_bChanged = false;
    }
    catch(Except::PhilException& e){
	std::cerr << e.what()  << std::endl;
    }
}

void CDbWidget::UpdateAthletLabel()
{
    FNameLabel->setText(m_pAthlet->m_sFirstName);
    LNameLabel->setText(m_pAthlet->m_sLastName);

    if(m_pAthlet->m_EnGender == CAthlet::MALE)
	GenderLabel->setText("male");
    else
	GenderLabel->setText("female");

    BirthdayLabel->setText(m_pAthlet->m_birthday.toString(Qt::TextDate));
    HeightLabel->setText(QString::number(m_pAthlet->m_nHeight)+"cm");
    WeightLabel->setText(QString::number(m_pAthlet->m_nWeight)+"kg");
    Km5Label->setText(m_pAthlet->m_kmTime5.toString(Qt::TextDate));
    Km10Label->setText(m_pAthlet->m_kmTime10.toString(Qt::TextDate));
    AvgDistLabel->setText(QString::number(m_pAthlet->m_nAvgDistance)+"m");
    BigDistLabel->setText(QString::number(m_pAthlet->m_nBiggestDistance)+"m");
    RunFreqLabel->setText(QString::number(m_pAthlet->m_nRunningFreq)+"x");
    AvgPulseLabel->setText(QString::number(m_pAthlet->m_nAvgPulse)+"/s");
    MorningPulseLabel->setText(QString::number(m_pAthlet->m_nMorningPulse)+"/s");


    // XSLT stuff
    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;
    xsltStylesheetPtr pStylesheet = xsltParseStylesheetFile((const xmlChar*)"xslt/athlet2html.xsl");
    kdDebug() << "*" << endl;
    xmlDocPtr pXml = xmlParseFile("xslt/athlet.xml");
    xmlDocPtr pHtml = xsltApplyStylesheet(pStylesheet, pXml, 0);
    
    xmlChar* pString;
    int nSize;
    xmlDocDumpMemory(pHtml, &pString, &nSize);    
    kdDebug() << "+" << endl;
    m_pHtmlPart->begin();
    m_pHtmlPart->write(QString((char*)pString));
    m_pHtmlPart->end();
    
    xsltFreeStylesheet(pStylesheet);
    xmlFreeDoc(pXml);
    xmlFreeDoc(pHtml);
    xsltCleanupGlobals();
    xmlCleanupParser();
}

CRunPtrList* CDbWidget::GetRunList() const
{
    CRunPtrList* pRunList = new CRunPtrList();
    
    CRunListViewItem* pItem = static_cast<CRunListViewItem*>(RunListView->firstChild());

    while(pItem){
	pRunList->append(pItem->GetRun());
	pItem = static_cast<CRunListViewItem*>(pItem->itemBelow());
    }

return pRunList;
}

};//namespace


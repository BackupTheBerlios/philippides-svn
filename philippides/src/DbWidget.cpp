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
#include <kstandarddirs.h>

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
#include "AthletDtd.h"
#include "Run.h"
#include "RunDtd.h"
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
    QHBoxLayout* pAthletLayout = new QHBoxLayout(m_pAthletHtmlFrame);
    m_pAthletHtmlPart = new KHTMLPart(m_pAthletHtmlFrame, "athlethtmlpart", this, "athlethtmlpart");
    m_pAthletHtmlPart->view()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pAthletLayout->addWidget(m_pAthletHtmlPart->view());
   
    QHBoxLayout* pRunLayout = new QHBoxLayout(m_pRunHtmlFrame);
    m_pRunHtmlPart = new KHTMLPart(m_pRunHtmlFrame, "runhtmlpart", this, "runhtmlpart");
    m_pRunHtmlPart->view()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pRunLayout->addWidget(m_pRunHtmlPart->view());
    
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

    // XSLT stuff
    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;
    QString sXsltFile = locate("data", QString("philippides/") + DTD::szRunToHtmlFile);
    xsltStylesheetPtr pStylesheet = xsltParseStylesheetFile((const xmlChar*)sXsltFile.ascii());
    QString sXml = pRun->ToXml();
    xmlDocPtr pXml = xmlParseMemory(sXml.ascii(), sXml.length());
    xmlDocPtr pHtml = xsltApplyStylesheet(pStylesheet, pXml, 0);
    
    xmlChar* pString;
    int nSize;
    xmlDocDumpMemory(pHtml, &pString, &nSize);    
    m_pRunHtmlPart->begin();
    m_pRunHtmlPart->write(QString((char*)pString));
    m_pRunHtmlPart->end();
    
    xsltFreeStylesheet(pStylesheet);
    xmlFreeDoc(pXml);
    xmlFreeDoc(pHtml);
    xsltCleanupGlobals();
    xmlCleanupParser();
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
    // XSLT stuff
    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;
    QString sXsltFile = locate("data", QString("philippides/") + 
							    DTD::szAthletToHtmlFile);
    xsltStylesheetPtr pStylesheet = xsltParseStylesheetFile((const xmlChar*)sXsltFile.ascii());
    xmlDocPtr pXml = xmlParseFile(locate("data", QString("philippides/") + DTD::szAthletFile));
    xmlDocPtr pHtml = xsltApplyStylesheet(pStylesheet, pXml, 0);
    
    xmlChar* pString;
    int nSize;
    xmlDocDumpMemory(pHtml, &pString, &nSize);    
    m_pAthletHtmlPart->begin();
    m_pAthletHtmlPart->write(QString((char*)pString));
    m_pAthletHtmlPart->end();
    
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


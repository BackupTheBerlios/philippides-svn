//******************************************************************************
/**
 * @file TrackEditorDialog.cpp
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
// xyzlib headers
//------------------------------------------------------------------------------
// qt headers
#include <qlabel.h>

// kde headers
#include <kfiledialog.h>
#include <kmessagebox.h>
#include <klocale.h>

//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "MapWidget.h"
#include "TrackEditorDialog.h"


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
CTrackEditorDialog::CTrackEditorDialog(QWidget* pParent, const char* szName):
    CTrackEditorDialogBase(pParent, szName),
    m_pMapLabel(0)
{

}

CTrackEditorDialog::~CTrackEditorDialog()
{

}

void CTrackEditorDialog::SlotOkBtn()
{
}
void CTrackEditorDialog::SlotOpenBtn()
{
    delete m_pMapLabel;
    m_pMapLabel = 0;
    
    QString sFileName = KFileDialog::getOpenFileName(".", "*.jpg", this, 
						     i18n("Choose a map image"));
    if(!m_mapImage.load(sFileName)){
	KMessageBox::error(this, i18n("Invalid file or filename"), i18n("Error..."));
	return;
    }

    m_pMapLabel = new CMapWidget(mapWidget->viewport(), "mapwidget");
    m_pMapLabel->setScaledContents(true);
    m_pMapLabel->setPixmap(QPixmap(m_mapImage));
    m_pMapLabel->show();
	
    mapWidget->addChild(m_pMapLabel);
    mapWidget->center((int)(m_pMapLabel->width()/2.0), (int)(m_pMapLabel->height()/2.0));
}

void CTrackEditorDialog::SlotMagBtn()
{
    if(!m_pMapLabel) return;
    
    m_pMapLabel->resize(m_pMapLabel->size() *= 1.1);
    mapWidget->center((int)(m_pMapLabel->width()/2.0), (int)(m_pMapLabel->height()/2.0));
}

void CTrackEditorDialog::SlotMinBtn()
{
    if(!m_pMapLabel) return;

    // if the image gets too small, a magnification is impossible/distortet, so we prevent
    // minification smaller then the viewport of the dialog.
    if(m_pMapLabel->width() < mapWidget->width() || m_pMapLabel->height() < mapWidget->height())
	return;

    m_pMapLabel->resize(m_pMapLabel->size() *= 0.9);
    mapWidget->center((int)(m_pMapLabel->width()/2.0), (int)(m_pMapLabel->height()/2.0));
}

};//namespace


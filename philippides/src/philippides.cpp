/*!
 * @file philippides.cpp
 * This file contains the Philippides class implementation.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date   Sun Mar 14 18:14:02 CET 2004
*/

// the class' header file
#include "philippides.h"

// stl includes
#include <iostream>

// qt includes
#include <qlabel.h>
#include <qstring.h>
#include <qfileinfo.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qptrlist.h>

// kde includes
#include <kapplication.h>
#include <kmainwindow.h>
#include <klocale.h>
#include <kconfig.h>
#include <kaction.h>
#include <kstdaction.h>
#include <kkeydialog.h>
#include <kedittoolbar.h>
#include <kstatusbar.h>
#include <kstandarddirs.h>
#include <ksavefile.h>
#include <kdebug.h>
#include <kmessagebox.h>
#include <kshortcut.h>

// local includes
#include "Exceptions.h"
#include "DbWidget.h"
#include "AthletDtd.h"
#include "Wizard.h"
#include "Athlet.h"
#include "Run.h"
#include "StatsDialog.h"

/*******************************************************************************
 * implementation
 ******************************************************************************/  
namespace Phil
{


//------------------------------------------------------------------------------
// structors
//------------------------------------------------------------------------------
Philippides::Philippides():
    KMainWindow( 0, "Philippides" ),
    m_pAthlet( 0 ),
    m_pStatsDialog(0),
    m_pTrackEditorDialog(0)
{

    setupActions();

    statusBar()->show();
    statusBar()->message( "...ready" );

    checkForAthlet();

    m_pBaseWidget = new CDbWidget( this, "dbwidget", m_pAthlet );
    setCentralWidget( m_pBaseWidget );


    // apply the saved mainwindow settings, if any, and ask the mainwindow
    // to automatically save settings if changed: window size, toolbar
    // position, icon size, etc.
    setAutoSaveSettings();
    
    
    //read XML .rc file and create menu and toolbar
    createGUI("philippidesui.rc");
    
    checkForRunDb();
}

Philippides::~Philippides()
{
}

//------------------------------------------------------------------------------
// methods
//------------------------------------------------------------------------------ 
void Philippides::checkForAthlet()
{
    // check for the existance of the athlet.xml file and open the 
    // wizard if it doesn't exist.
    if ( !CAthlet::FileExists() ){
	kdDebug() << "Athlet file not found!" <<  endl;
	CWizard* pWizard = new CWizard( this, "athletwizard" );
	
	/// @todo add error handling here
	if ( pWizard->exec() == QDialog::Rejected )
	    kapp->quit();
	
	m_pAthlet = pWizard->GetAthlet();

	try{
	    m_pAthlet->ToDisk();
	}
	catch(Except::PhilException& e)
	{
	    kdDebug() << e.what() << endl;
	}
    }
    else{
	/// @todo create CAthlet object from file.
	kdDebug() << "Athlet file found!" << endl;
	try{
	    m_pAthlet = CAthlet::FromDisk();
	}
	catch(Except::PhilException& e)
	{
	    kdDebug() << e.what() << endl;
	}
    }

}

void Philippides::checkForRunDb()
{
    if(!CRun::FileExists()){
	kdDebug() << "database file does not exist." << endl;
	return;
    }

    try{
	QPtrList<CRun>* pList = CRun::FromDisk();
	CRun* pRun;

	for(pRun = pList->first(); pRun; pRun = pList->next()){
	    m_pBaseWidget->SlotNewRun( pRun );
	}
	
	// set not changed because we read the database and no data has been changed
	// the method SlotNewRun sets changed to true, so we have to set it to false
	m_pBaseWidget->SetChanged(false);
    }
    catch(Except::PhilException& e){
	std::cerr << e.what() << std::endl;
    }
}


bool Philippides::queryClose()
{
    if(m_pBaseWidget->IsChanged() &&
       KMessageBox::questionYesNo(this, 
	   i18n("Your database is unsaved, do you wanna save it?"),
	   i18n("Unsaved data...")) == KMessageBox::Yes){
	SlotSave();
    }
    
    return true;
}

void Philippides::saveProperties( KConfig* )
{
    /* EMPTY */ 
}

void Philippides::readProperties( KConfig* )
{
    /* EMPTY */ 
}

void Philippides::setupActions()
{
    KStdAction::quit( kapp, SLOT( quit() ), actionCollection() );
    KStdAction::save( this, SLOT( SlotSave()), actionCollection());

    m_toolbarAction = KStdAction::showToolbar( this, SLOT( optionsShowToolbar() ), 
						actionCollection() );
    m_statusbarAction = KStdAction::showStatusbar( this, SLOT( optionsShowStatusbar() ),
						actionCollection() );

    KStdAction::keyBindings( this, SLOT( optionsConfigureKeys() ), actionCollection() );
    KStdAction::configureToolbars( this, SLOT( optionsConfigureToolbars() ), actionCollection() );

    m_pStatsAction = new KToggleAction( i18n("View statsdialog"), "catagory", KShortcut("Shift+S"), 
					this, SLOT( SlotShowStatsDialog()), 
					actionCollection(), "view_stats");

    m_pTrackEditorAction = new KToggleAction( i18n("View Track Editor"), "signature", 
					KShortcut("Shift+T"), this, SLOT( SlotShowTrackEditor()),
					actionCollection(), "view_trackeditor");
}

void Philippides::optionsConfigureKeys()
{
    KKeyDialog::configure( actionCollection());
}

void Philippides::SlotSave()
{   
    m_pBaseWidget->SlotSaveDatabase();
}

void Philippides::optionsConfigureToolbars()
{
#if defined(KDE_MAKE_VERSION)
# if KDE_VERSION >= KDE_MAKE_VERSION(3,1,0)
    saveMainWindowSettings(KGlobal::config(), autoSaveGroup());
# else
    saveMainWindowSettings(KGlobal::config() );
# endif
#else
    saveMainWindowSettings(KGlobal::config() );
#endif

    // use the standard toolbar editor
    KEditToolbar dlg(factory());
    connect(&dlg, SIGNAL(newToolbarConfig()),
            this, SLOT(applyNewToolbarConfig()));
    dlg.exec();
}

void Philippides::applyNewToolbarConfig()
{
#if defined(KDE_MAKE_VERSION)
# if KDE_VERSION >= KDE_MAKE_VERSION(3,1,0)
    applyMainWindowSettings(KGlobal::config(), autoSaveGroup());
# else
    applyMainWindowSettings(KGlobal::config());
# endif
#else
    applyMainWindowSettings(KGlobal::config());
#endif
}

void Philippides::optionsShowToolbar()
{
    if ( m_toolbarAction->isChecked() )
	toolBar()->show();
    else
	toolBar()->hide();
}

void Philippides::optionsShowStatusbar()
{
    if ( m_statusbarAction->isChecked() )
	statusBar()->show();
    else
	statusBar()->hide();
}


void Philippides::SlotShowStatsDialog()
{
    // is the dialog already open?
    if( m_pStatsAction->isChecked() && m_pStatsDialog ){
	m_pStatsDialog->close();
    }
    else{
	if(!m_pStatsDialog) m_pStatsDialog = new CStatsDialog(m_pBaseWidget->GetRunList(), 
							      this, "statsdialog");
	// we use a non-modal dialog.
	m_pStatsDialog->show();
    }
}

void Philippides::SlotShowTrackEditor()
{

    if(m_pTrackEditorAction->isChecked() && m_pTrackEditorDialog){
	m_pTrackEditorDialog->close();
    }
    else{
	if(!m_pTrackEditorDialog) m_pTrackEditorDialog = new CTrackEditorDialog(this,
								"trackeditordialog");
	m_pTrackEditorDialog->show();
    }
}

}; // namespace

#include "philippides.moc"



/*!
 * @file philippides.cpp
 *
 * @brief
 *
 *
 * $Id$
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date   Sun Mar 14 18:14:02 CET 2004
*/


#include "philippides.h"

#include <iostream>

#include <qlabel.h>
#include <qstring.h>
#include <qfileinfo.h>
#include <qfile.h>
#include <qtextstream.h>

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

#include "Exceptions.h"
#include "DbWidget.h"
#include "AthletDtd.h"
#include "Wizard.h"
#include "Athlet.h"

namespace Phil
{

Philippides::Philippides():
    KMainWindow( 0, "Philippides" ),
    m_pAthlet( 0 )
{

    setupActions();

    statusBar()->show();
    statusBar()->message( "...ready" );

    m_pBaseWidget = new CDbWidget( this, "dbwidget" );
    setCentralWidget( m_pBaseWidget );


    // apply the saved mainwindow settings, if any, and ask the mainwindow
    // to automatically save settings if changed: window size, toolbar
    // position, icon size, etc.
    setAutoSaveSettings();
    
    
    //read XML .rc file and create menu and toolbar
    createGUI("philippidesui.rc");
    
    checkForAthlet();
}

Philippides::~Philippides()
{
}

void Philippides::checkForAthlet()
{
    // check for the existance of the athlet.xml file and open the 
    // wizard if it doesn't exist.
    QString sPath = locate( "data", QString( "philippides/%1" ).arg( DTD::szAthletFile ) );

    if ( sPath.isEmpty() ){
	std::clog << "Athlet file not found!" << std::endl;
	QString sPath = kapp->dirs()->saveLocation( "data", "philippides/" );
	sPath += DTD::szAthletFile;
	std::clog << "Path to save athlet file to: " << sPath << std::endl;
	CWizard* pWizard = new CWizard( this, "athletwizard" );
	
	//TODO: add error handling here
	if ( pWizard->exec() == QDialog::Rejected )
	    exit( -1 );
	
	m_pAthlet = pWizard->GetAthlet();

	QFile file( sPath );
	if ( file.open( IO_WriteOnly ) ){
	    QTextStream stream( &file );
	    stream << m_pAthlet->ToXml();
	    file.flush();
	    file.close();
	}
	else{
	    throw Except::GenericException( "Philippides::checkForAthlet",
				QString( "Can't write athlet databasefile to %1" ).arg( sPath ) );
	}
    }
    else{
	std::clog << "Athlet file found!" << std::endl;
    }

}

void Philippides::saveProperties( KConfig* config )
{

}

void Philippides::readProperties( KConfig* config )
{
}

void Philippides::setupActions()
{
    KStdAction::quit( kapp, SLOT( quit() ), actionCollection() );

    m_toolbarAction = KStdAction::showToolbar( this, SLOT( optionsShowToolbar() ), 
						actionCollection() );
    m_statusbarAction = KStdAction::showStatusbar( this, SLOT( optionsShowStatusbar() ),
						actionCollection() );

    KStdAction::keyBindings( this, SLOT( optionsConfigureKeys() ), actionCollection() );
    KStdAction::configureToolbars( this, SLOT( optionsConfigureToolbars() ), actionCollection() );
}

void Philippides::optionsConfigureKeys()
{
    KKeyDialog::configure( actionCollection());
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

}; // namespace

#include "philippides.moc"



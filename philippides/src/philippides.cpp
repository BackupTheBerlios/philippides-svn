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

#include <qlabel.h>

#include <kapplication.h>
#include <kmainwindow.h>
#include <klocale.h>
#include <kconfig.h>
#include <kaction.h>
#include <kstdaction.h>
#include <kkeydialog.h>
#include <kedittoolbar.h>
#include <kstatusbar.h>

#include "DbWidgetBase.h"

namespace Phil
{

Philippides::Philippides()
    : KMainWindow( 0, "Philippides" )
{
    //read XML .rc file and create menu and toolbar
    createGUI();

    setupActions();

    statusBar()->show();
    statusBar()->message( "...ready" );

    m_pBaseWidget = new CDbWidgetBase( this, "dbwidget" );
    setCentralWidget( m_pBaseWidget );

    // apply the saved mainwindow settings, if any, and ask the mainwindow
    // to automatically save settings if changed: window size, toolbar
    // position, icon size, etc.
    setAutoSaveSettings();
}

Philippides::~Philippides()
{
}

void Philippides::saveProperties( KConfig* /*config*/ )
{

}

void Philippides::readProperties( KConfig* /*config*/ )
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



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

#include <kmainwindow.h>
#include <klocale.h>




Philippides::Philippides()
    : KMainWindow( 0, "Philippides" )
{
    // set the shell's ui resource file
    setXMLFile("philippidesui.rc");

//    setupActions();

//    statusBar()->show();

    new QLabel( "Hello World", this, "hello label" );
}

Philippides::~Philippides()
{
}

#include "philippides.moc"

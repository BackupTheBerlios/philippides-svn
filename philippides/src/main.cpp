//******************************************************************************
/** @file main.cpp
 *  This file includes the Phil's main function and some KDE specific 
 *  environment data.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 13.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

/** @mainpage This is the API documentation of Philippides
 *
 * @section Section
 * @todo insert text here
 */

#include "philippides.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
    I18N_NOOP("A runner's diary");

static const char version[] = "0.1";

static KCmdLineOptions options[] =
{
//    { "+[URL]", I18N_NOOP( "Document to open." ), 0 },
    KCmdLineLastOption
};

int main(int argc, char **argv)
{
    KAboutData about("philippides", I18N_NOOP("Philippides"), version, description,
                     KAboutData::License_GPL, "(C) 2004 Falco Hirschenberger", 0, 0, 
		     "hirsch@bigfoot.de");
    about.addAuthor( "Falco Hirschenberger", 0, "hirsch@bigfoot.de" );
    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineArgs::addCmdLineOptions( options );
    KApplication app;
    Phil::Philippides *mainWin = 0;

    if (app.isRestored())
    {
        RESTORE(Phil::Philippides);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

        /// @todo do something with the command line args here

        mainWin = new Phil::Philippides();
        app.setMainWidget( mainWin );
        mainWin->show();

        args->clear();
    }

    // mainWin has WDestructiveClose flag by default, so it will delete itself.
    return app.exec();
}


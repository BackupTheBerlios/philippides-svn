/**
 * @file philippides.h
 * This is the
 *
 *
 * $Id$
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date   Sun Mar 14 18:17:04 CET 2004
*/
#ifndef _PHILIPPIDES_H_
#define _PHILIPPIDES_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kmainwindow.h>

// forward declarations
class KToggleAction;

namespace Phil
{
    class CDbWidget;
    class CAthlet;
}

namespace Phil
{

/**
 * @short Application Main Window
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @version 0.1
 */
class Philippides : public KMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    Philippides();

    /**
     * Default Destructor
     */
    virtual ~Philippides();

protected:

     /**
     * This method is called when it is time for the app to save its
     * properties for session management purposes.
     */
    void saveProperties(KConfig *);

    /**
     * This method is called when this app is restored.  The KConfig
     * object points to the session management config file that was saved
     * with @ref saveProperties
     */
    void readProperties(KConfig *);

//    TODO:: implement these!
//    bool queryClose();
//
//    bool queryExit();
//
//
private:
    void setupActions();
    void checkForAthlet();
    CDbWidget* m_pBaseWidget;
    CAthlet* m_pAthlet;
    
private slots:
    void optionsShowToolbar();
    void optionsShowStatusbar();
    void optionsConfigureKeys();
    void optionsConfigureToolbars();
    void applyNewToolbarConfig();
    
    KToggleAction* m_toolbarAction;
    KToggleAction* m_statusbarAction;
};


};     // namepspace
#endif // _PHILIPPIDES_H_

/**
 * @file philippides.h
 * This file contains the class \b Philippides
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date   Sun Mar 14 18:17:04 CET 2004
*/
#ifndef _PHILIPPIDES_H_
#define _PHILIPPIDES_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

//------------------------------------------------------------------------------ 
// xyzlib headers
//------------------------------------------------------------------------------ 
// kde includes
#include <kmainwindow.h>


//------------------------------------------------------------------------------ 
// forwarding
//------------------------------------------------------------------------------ 
class KToggleAction;


namespace Phil
{
    class CDbWidget;
    class CAthlet;
}


/******************************************************************************* 
 * declarations
 ******************************************************************************/  


/** @namespace Phil This is Philippides' main namespace.
 * All application specific data are inside this namespace.
 */
namespace Phil
{

/** @class Philippides
 * This id Philippides' main class.
 * All other dialogs/widgets are created from here. This class is responsible 
 * for the session management and the menu and toolbar. The menu and toolbar 
 * are configured by a XML file, which contains the menuentries and the 
 * corresponding actions to be called.
 * 
 * @see KMainWindow::createGUI() KXMLGUIFactory and KAction 
 * 
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date   Sun Mar 14 18:17:04 CET 2004
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

///    @todo implement these!
//    bool queryClose();
//
//    bool queryExit();
//
//
private:
    /**
     * Binds the entries and actions configured in the KXMLGUIFactory XML file
     * to the corresponding methods.
     */
    void setupActions();

    /**
     * Checks whether a athlet XML file exists in the user's home directory.
     * If not, this meand that the user starts Philippides for the first time
     * and a athlet configuration file must be created, so this method calls
     * the CWizard, which creates such a file and an object.
     * If the file exists, it is used to create a CAthlet object for further
     * use.
     */
    void checkForAthlet();


    /**
     * Checks whether a rundb XML file existes in the user's home directory,
     * if it exists, the file is parsed and the deserialized CRun objects are
     * created and given to the DbWidget which will care for them.
     * 
     * \note This method discards ownership of the created objects!
     */
    void checkForRunDb();
    
    CDbWidget* m_pBaseWidget;		///< The database display widget
    CAthlet* m_pAthlet;			///< The CAthlet object used for statistics
    KToggleAction* m_toolbarAction;	///< toggles if the toolbar is shown or not
    KToggleAction* m_statusbarAction;	///< toggles if the statusbar is shown or not
    
    
private slots:
    /**
     * shows/hides the toolbar depending on the state of m_toolbarAction
     */
    void optionsShowToolbar();

    /**
     * shows/hides the statusbar depending on the state of m_statusbarAction
     */
    void optionsShowStatusbar();

    /**
     * shows a KKeyDialog to configure key shortcuts
     */
    void optionsConfigureKeys();

    /**
     * saves and changes the toolbar configuration
     */
    void optionsConfigureToolbars();

    /**
     * applies the new toolbar configuration and saves the state
     */
    void applyNewToolbarConfig();

    /**
     * called when the "save" menu entry or toolbar button is pressed
     */
    void SlotSave();
};


};     // namepspace
#endif // _PHILIPPIDES_H_

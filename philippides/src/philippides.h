/**
 * @file philippides.h
 *
 * @brief
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
};

#endif // _PHILIPPIDES_H_

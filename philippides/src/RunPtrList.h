//******************************************************************************
/** @file RunPtrList.h
 * This file contains the definition of the class CRunPtrList.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Apr/19/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef __PHIL_RUN_PTR_LIST_H__
#define __PHIL_RUN_PTR_LIST_H__

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// qt includes
#include <qptrlist.h>
#include <qptrcollection.h>


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include <Run.h>

//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

//******************************************************************************
// declarations
//******************************************************************************

namespace Phil
{

/** @class CRunPtrList
 * This class implements a pointer list of CRun objects.
 * The method compareItems is overwritten to make the sorting of the list
 * possible.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Apr/19/2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
class CRunPtrList: public QPtrList<CRun>
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef CRunPtrList TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/** 
	* default constructor
	**/
	CRunPtrList();

	/** default destructor */
	virtual ~CRunPtrList();


    protected:
	/** Inherited from baseclass, see there for details */ 
	inline int compareItems(CRunPtrList::Item item1, CRunPtrList::Item item2);

    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	CRunPtrList( const TSelf& other );
};

}; //namespace

#endif//__PHIL_RUN_PTR_LIST_H__


//******************************************************************************
/** @file Exceptions.h
 *  This file contains some own exception classes.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date 13.3.2004
 *
 * (c) Falco Hirschenberger <hirsch@bigfoot.de>
 **/
//******************************************************************************

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

// stl includes
#include <exception>

// qt includes
#include <qstring.h>

//******************************************************************************
// declarations
//******************************************************************************


/** @namespace Except
 * This namespace contains all C++ exception related stuff.
 */
namespace Except
{

//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
/** @class PhilException
 * This is the baseclass for all own exceptions.
 * @note This class is pure virtual.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/23/2004 
 */
class PhilException: public std::exception
{
    public:
	/** 
	 * default constructor 
	 */
	PhilException()
	{ /* EMPTY */ }
	
	/** 
	 * default destructor 
	 */
	virtual ~PhilException() throw()
	{ /* EMPTY */ }

	/**
	 * return a string describing the kind of error that occured
	 * 
	 * @return string with error description
	 */
	virtual const char* what() const throw() =0;
};

//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
/** @class GenericException
 * This class is a generic exception class usefull for cases where no other
 * exception class matches.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date Mar/23/2004 
 */
class GenericException: public PhilException
{
    public:
	/**
	 * Constructor.
	 *
	 * @param sMethod [IN] - name of the method the error occured
	 * @param sDescription [IN] - description of the error
	 */
	GenericException(const QString& sMethod, const QString& sDescription):
		m_sMethod(sMethod),
		m_sDescription(sDescription) 
		{ /* EMPTY */ }
	
	/** 
	 * default destructor 
	 */
	virtual ~GenericException() throw()
		{ /* EMPTY */ }

	/** Inherited from baseclass, see there for details */ 
	const char* what() const throw(){
	    return QString( "\nEXCEPTION:\n\t%1\n\tin Method: %2\n" )
			    .arg(m_sDescription).arg(m_sMethod).ascii();
	}
	
	QString m_sMethod, m_sDescription;
};

//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
/** @class EmptyParamException
 * This exception class is useful when ckecking function/method parameters.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de> 
 * @date Mar/23/2004 
 */
class EmptyParamException: public PhilException
{
    public:
	/**
	 * Constructor.
	 *
	 * @param sMethod [IN] - name of the method the error occured
	 * @param sParam [IN] - parameter that is erroneous
	 */
	EmptyParamException(const QString& sMethod, const QString& sParam):
		m_sMethod(sMethod),
		m_sParam(sParam)
		{ /* EMPTY*/ }

	/**
	 * default destructor
	 */
	virtual ~EmptyParamException() throw()
		{ /* EMPTY */ }
	
	/** Inherited from baseclass, see there for details */ 
	const char* what() const throw(){
	    return QString( "\nEXCEPTION:\n\tEmpty parameter: %1\n\tin Method: %2\n" )
				.arg( m_sParam ).arg( m_sMethod ).ascii();
	}

	QString m_sMethod, m_sParam;
};

//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
/** @class InvalidDataException
 * Thic exception can be thrown if some kind of wrong/invalid data occur.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de> 
 * @date Mar/23/2004 
 */
class InvalidDataException: public PhilException
{
    public:
	/**
	 * Constructor.
	 *
	 * @param sMethod [IN] - name of the method the error occured
	 * @param sVariable [IN] - description of the error
	 */
	InvalidDataException( const QString& sMethod, const QString& sVariable ):
	    m_sVariable( sVariable ),
	    m_sMethod( sMethod )
	    { /* EMPTY */ }

	/**
	 * default destructor
	 */
	virtual ~InvalidDataException() throw()
	    { /* EMPTY */ } 

	/** Inherited from baseclass, see there for details */ 
	const char* what() const throw(){
	    return QString( "\nEXCEPTION:\n\tInvalid data: %1\n\tin Method: %2\n" )
				.arg( m_sVariable ).arg( m_sMethod ).ascii();
	}

	QString m_sVariable, m_sMethod;
};

} //namespace
#endif //include guard

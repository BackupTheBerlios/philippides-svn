//******************************************************************************
/** @file Exceptions.h
 *
 * short description.
 * brief description.
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


class PhilException: public std::exception
{
    public:
	PhilException()
	{ /* EMPTY */ }
	
	virtual ~PhilException() throw()
	{ /* EMPTY */ }

	virtual const char* what() const throw() =0;
};
    
class GenericException: public PhilException
{
    public:
	GenericException(const QString& sMethod, const QString& sDescription):
		m_sMethod(sMethod),
		m_sDescription(sDescription) 
		{ /* EMPTY */ }
		
	virtual ~GenericException() throw()
		{ /* EMPTY */ }

		const char* what() const throw(){
			return QString( "\nEXCEPTION:\n\t%1\n\tin Method: %2\n" )
					.arg(m_sDescription).arg(m_sMethod).ascii();
		}
	QString m_sMethod, m_sDescription;
};

class EmptyParamException: public PhilException
{
    public:
	EmptyParamException(const QString& sMethod, const QString& sParam):
		m_sMethod(sMethod),
		m_sParam(sParam)
		{ /* EMPTY*/ }

	virtual ~EmptyParamException() throw()
		{ /* EMPTY */ }
		
	const char* what() const throw(){
	    return QString( "\nEXCEPTION:\n\tEmpty parameter: %1\n\tin Method: %2\n" )
				.arg( m_sParam ).arg( m_sMethod ).ascii();
	}

	QString m_sMethod, m_sParam;
};


class InvalidDataException: public PhilException
{
    public:
	InvalidDataException( const QString& sMethod, const QString& sVariable ):
	    m_sVariable( sVariable ),
	    m_sMethod( sMethod )
	    { /* EMPTY */ }

	virtual ~InvalidDataException() throw()
	    { /* EMPTY */ } 

	const char* what() const throw(){
	    return QString( "\nEXCEPTION:\n\tInvalid data: %1\n\tin Method: %2\n" )
				.arg( m_sVariable ).arg( m_sMethod ).ascii();
	}

	QString m_sVariable, m_sMethod;
};

} //namespace
#endif //include guard

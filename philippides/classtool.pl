#!/usr/bin/perl

use warnings;

################################################################################
#   Classtool for generating c++ class skeletons                               #
#                                                                              #
#   Author:  Falco Hirschenberger <hirsch@bigfoot.de>                          #
#   Usage:   ./classtool <CLASSNAME> <NAMESPACENAME>                           #
#   Changelog:                                                                 #
#              March 2004: bugfix filename tag in Cpp files                    #
#              September 2003: Added ITWM coding and style rules               #
################################################################################

$author = "Falco Hirschenberger <hirsch\@bigfoot.de>";

$classname = shift @ARGV;
$namespace = shift @ARGV;

$classname or die "FEHLER: kein Klassenname angegeben. Nutzung:\n$0 <classname> [ <namespace> ]";

if(not $namespace){
    $namespace = "ITWM"; 
    print "\nUsing standard namespace ITWM\n";
}

$date = ((gmtime)[3]+1) . '.' . ((gmtime)[4]+1) . '.' . ((gmtime)[5]+1900);

$headfilename = $classname.".h";
$headfilename =~ s/^C//;
$filename = $classname.".cpp";
$filename =~ s/^C//;

if(-e $headfilename) {
    printRed("Warning:");
    print " File:\"" . $headfilename . "\" already exists, a backup-copy will be created.\n";
    `mv $headfilename $headfilename."old"`;
}

if(-e $filename) { 
    printRed("Warning:");
    print " File:\"" . $filename . "\" already exists, a backup-copy will be created.\n";
    `mv $filename $filename."old"`;
}

$uppercaseclassname = '';
$tmp = $classname;

$tmp =~/^C?([A-Z][a-z0-9]*)/;
$uppercaseclassname .= uc $1;

$tmp = $';

while($tmp)
{
    $tmp =~/^([A-Z][a-z0-9]*)/;
    
    if($1){
      $uppercaseclassname .= '_' . uc $1;
      $tmp = $';
    }
    # Every not alphanumeric char will be substituted by a '_' char.
    else{
     $uppercaseclassname .= '_';
     $tmp = substr($', 2);
    };
};

$DEFheader = uc "__".$namespace."_".$uppercaseclassname."_H__";



#Use DOXYGEN comments only in header files
$isHeader = '*';
&readHeader;

$HEAD =<<EOF;
$HEADER
#ifndef $DEFheader
#define $DEFheader

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// headers for each lib should have own section


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// forwarding
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

//******************************************************************************
// declarations
//******************************************************************************

namespace $namespace
{

/** \@class $classname
 *
 * short description.
 * brief description.
 *
 * \@author $author
 * \@date $date
 *
 * (c) $author
 **/
class $classname
{
    public:
    //--------------------------------------------------------------------------
    // types
    //--------------------------------------------------------------------------
    typedef $classname TSelf;
   
    //--------------------------------------------------------------------------
    // structors
    //--------------------------------------------------------------------------
	/*$isHeader 
	* short method description.
	* brief method description.
	*
	* \@param name desc
	**/
	$classname();

	/*$isHeader default destructor */
	virtual ~$classname();

    //--------------------------------------------------------------------------
    // accessors
    //--------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // operator
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    // methods
    //------------------------------------------------------------------------------

    protected:


    private:
    //------------------------------------------------------------------------------
    // members
    //------------------------------------------------------------------------------
	    
    private:
    //------------------------------------------------------------------------------
    // implementation protection
    //------------------------------------------------------------------------------
	TSelf& operator=( const TSelf& other );
	$classname( const TSelf& other );
};

}; //namespace

#endif//$DEFheader

EOF



# turn off DOXYGEN comments
$isHeader = '';
&readHeader;

$CPPFILE =<<EOF;
$HEADER

//------------------------------------------------------------------------------
// STL headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// xyzlib headers
//------------------------------------------------------------------------------
// headers for each lib should have own section


//------------------------------------------------------------------------------
// local headers
//------------------------------------------------------------------------------
#include "$headfilename"


//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------


//******************************************************************************
// implementation
//******************************************************************************
namespace $namespace
{

//------------------------------------------------------------------------------
// structors
//------------------------------------------------------------------------------
$classname\:\:$classname()
{

}

$classname\:\:~$classname()
{

}

//------------------------------------------------------------------------------
// accessors
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// operator
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// methods
//------------------------------------------------------------------------------

};//namespace

EOF

open $FH ,">$headfilename" or die "FEHLER: Kann Datei nicht öffnen!";
print $FH $HEAD;
print "\n$headfilename \tgenerated";
close $FH;

open $FH ,">$filename" or die "FEHLER: Kann Datei nicht öffnen!";
print $FH $CPPFILE;
print "\n$filename \tgenerated\n\n";
close $FH;



sub readHeader{
if($isHeader eq '*'){
$HEADER =<<EOF;
//******************************************************************************
/** \@file $headfilename
 *
 * short description.
 * brief description.
 *
 * \@author $author
 * \@date $date
 *
 * (c) $author
 **/
//******************************************************************************
EOF
}
else{
$HEADER=<<EOF;
//******************************************************************************
/**
 * \@file $filename
 * short description.
 * brief description.
 *
 * \@author $author
 * \@date $date
 *
 * (c) $author
 **/
//******************************************************************************
EOF
}
}

sub printRed{
    print chr(27)."[31m" . $_[0] . chr(27)."[0m";
}

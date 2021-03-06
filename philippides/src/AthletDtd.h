/**
 * @file AthletDtd.h
 * The CAthlet DTD and version.
 * This file contains the DTD for the CAthlet entity as a constant string
 * and a string for the version number of this DTD to ease updates.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date   Sun Mar 21 21:22:30 CET 2004
 **/
#ifndef __ATHLET_DTD_H__
#define __ATHLET_DTD_H__

/** @namespace DTD DTD/XML related stuff.
 * This namespace contains all DTD/XML related stuff like DTD strings which
 * can be included in XML files, version numbers to handle updated XML formats
 * and filenames for the XML database files.
 */
namespace DTD
{

/**
 * filename of the athlet configuration file
 */
const char* const szAthletFile = "athlet.xml";

/**
 * filename of the athlet to html xslt transformation
 */
const char* const szAthletToHtmlFile = "xslt/athlet2html.xsl";

/**
 * image filenames which are diplayes in the XSLT transformed HTML page
 */
const char* const pszAthletImages[2] = {"pics/runner.png", "pics/runner-light.png"};

/**
 * the athlet DTD's version number
 */
const char* const szAthletVERSION = "1.0";

/**
 * the athlet DTD
 */
const char* const szAthletDtd = 
    "\n<!-- the dtd describing an athlet entity -->\n\
    <!DOCTYPE athlet [\n\
    	<!ELEMENT athlet (firstname,\n\
    			  lastname,\n\
    			  gender,\n\
    			  birthday,\n\
    			  weight?,\n\
    			  height?,\n\
    			  runningfreq?,\n\
    			  avgdist?,\n\
    			  kmtime5?,\n\
    			  kmtime10?,\n\
    			  biggestdist?,\n\
    			  avgpulse?,\n\
    			  morningpulse?\n\
    	)>\n\
    	<!ATTLIST athlet version CDATA #REQUIRED>\n\
    		<!ELEMENT firstname (#PCDATA)>\n\
    		<!ELEMENT lastname (#PCDATA)>\n\
	        <!ELEMENT gender EMPTY>\n\
                <!ATTLIST gender value (female | male) #REQUIRED>\n\
    		<!ELEMENT birthday (#PCDATA)>\n\
    		<!ELEMENT weight (#PCDATA)>\n\
    		<!ELEMENT height (#PCDATA)>\n\
    		<!ELEMENT runningfreq (#PCDATA)>\n\
    		<!ELEMENT avgdist (#PCDATA)>\n\
    		<!ELEMENT kmtime5 (#PCDATA)>\n\
    		<!ELEMENT kmtime10 (#PCDATA)>\n\
    		<!ELEMENT biggestdist (#PCDATA)>\n\
    		<!ELEMENT avgpulse (#PCDATA)>\n\
    		<!ELEMENT morningpulse (#PCDATA)>\n\
    ]>\n";

};     // namespace
#endif //include guard

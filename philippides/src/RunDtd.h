/**
 * @file RunDtd.h
 * The RunDB DTD and version.
 * This file contains the DTD for the RunBD XML representation and a string which 
 * contains the version number of this DTD to ease updates.
 *
 * @author Falco Hirschenberger <hirsch@bigfoot.de>
 * @date   Sun Mar 21 21:24:16 CET 2004
 **/
#ifndef __RUN_DTD_H__
#define __RUN_DTD_H__

namespace DTD
{

/**
 * the filename the rundb will be stored in
 */
const char* const szRunFile = "rundb.xml";
    
/**
 * the rundb DTD version number
 */
const char* const szRundbVERSION = "1.0";

/**
 * the run DTD
 */
const char* const szRunDtd = 
    "<!-- the dtd describing an run database consisting of run entities -->\n \
    <!DOCTYPE rundb[\n\
    	<!ELEMENT rundb (run)*>\n\
    	<!ATTLIST rundb version CDATA #REQUIRED>\n\
    		<!ELEMENT run (date,\n\
    			       time,\n\
    		               length?,\n\
    			       pulse?,\n\
    			       weather?,\n\
    			       impression?,\n\
    			       comment?\n\
    		)>\n\
    		<!ATTLIST run key CDATA #REQUIRED> <!-- primary key -->\n\
    			<!ELEMENT date (#PCDATA)>\n\
    			<!ELEMENT time (#PCDATA)>\n\
    			<!ELEMENT pulse (#PCDATA)>\n\
    			<!ELEMENT weather EMPTY>\n\
    			<!ATTLIST weather value (clear | cloudy | stormy | snowy) #REQUIRED>\n\
    			<!ELEMENT impression EMPTY>\n\
    			<!ATTLIST impression value (good | fair | bad | aborted) #REQUIRED>\n\
    			<!ELEMENT comment (#PCDATA)>\n\
    ]>\n";

};     // namespace
#endif // include guard

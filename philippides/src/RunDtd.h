#ifndef __RUN_DTD_H__
#define __RUN_DTD_H__

namespace DTD
{


const char* const szRunDtd = 
    "<!-- the dtd describing an run database consisting of run entities -->\n"
    "<!DOCTYPE rundb[\n"
    "	<!ELEMENT rundb(run)*>\n"
    "		<!ELEMENT run(date,\n"
    "			      time,\n"
    "		              length?,\n"
    "			      pulse?,\n"
    "			      weather?,\n"
    "			      impression?,\n"
    "			      comment?\n"
    "		)>\n"
    "			<!ATTLIST run key CDATA #REQUIRED> <!-- primary key -->\n"
    "			<!ELEMENT date (#PCDATA)>\n"
    "			<!ELEMENT time (#PCDATA)>\n"
    "			<!ELEMENT pulse (#PCDATA)>\n"
    "			<!ELEMENT weather (#PCDATA) EMPTY>\n"
    "				<!ATTLIST weather value (clear, cloudy, stormy, snowy) #REQUIRED>\n"
    "			<!ELEMENT impression (#PCDATA) EMPTY>\n"
    "				<!ATTLIST impression value (good, fair, bad, aborted) #REQUIRED>\n"
    "			<!ELEMENT comment (#PCDATA)>\n"
    "]>\n";

};     // namespace
#endif // include guard

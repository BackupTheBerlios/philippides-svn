#ifndef __ATHLET_DTD_H__
#define __ATHLET_DTD_H__

namespace DTD
{

const char* const szAthletDtd = 
    "\n<!-- the dtd describing an athlet entity -->\n"
    "<!DOCTYPE athlet [\n"
    "	<!ELEMENT athlet (firstname,\n"
    "			  lastname,\n"
    "			  gender,\n,"
    "			  birthday,\n"
    "			  weight?,\n"
    "			  height?,\n"
    "			  runningfreq?,\n"
    "			  avgdist?,\n"
    "			  kmtime5?,\n"
    "			  kmtime10?,\n"
    "			  biggestdist?,\n"
    "			  avgpulse?,\n"
    "			  morningpulse?\n"
    "	)>\n"
    "		<!ELEMENT firstname (#PCDATA)>\n"
    "		<!ELEMENT lastname (#PCDATA)>\n"
    "           <!ELEMENT gender (#PCDATA) EMPTY>\n"
    "               <!ATTLIST gender value (female, male) #REQUIRED>\n"
    "		<!ELEMENT birthday (#PCDATA)>\n"
    "		<!ELEMENT weight (#PCDATA)>\n"
    "		<!ELEMENT height (#PCDATA)>\n"
    "		<!ELEMENT runningfreq (#PCDATA)>\n"
    "		<!ELEMENT avgdist (#PCDATA)>\n"
    "		<!ELEMENT kmtime5 (#PCDATA)>\n"
    "		<!ELEMENT kmtime10 (#PCDATA)>\n"
    "		<!ELEMENT biggestdist (#PCDATA)>\n"
    "		<!ELEMENT avgpulse (#PCDATA)>\n"
    "		<!ELEMENT morningpulse (#PCDATA)>\n"
    "]>\n";

};     // namespace
#endif //include guard

#include <iostream>

#include <qstring.h>
#include <qdatetime.h>

#include "Exceptions.h"
#include "Athlet.h"

int main(int argc, char** argv)
{
    try{
	Phil::CAthlet* pAthlet = new Phil::CAthlet("Falco", "Hirschenberger", 
						    Phil::CAthlet::MALE, QDate(1978, 7, 6));
	pAthlet->m_nAvgDistance = 5000;
	pAthlet->m_kmTime5 = QTime(0, 30, 0);
	pAthlet->m_kmTime10 = QTime(0, 53, 0);
	pAthlet->m_nWeight = 75;
	pAthlet->m_nAvgPulse = 160;
	pAthlet->m_nBiggestDistance = 22000;
	pAthlet->m_nHeight = 178;
	pAthlet->m_nRunningFreq = 4;
	pAthlet->m_nMorningPulse = 55;
	
	pAthlet->ToDisk(".", "athlet.xml");

	Phil::CAthlet* pAthletNew= Phil::CAthlet::FromDisk(".", "athlet.xml");
	
	std::cout << "The classes are: " 
		  << (!(*pAthletNew != *pAthlet) ? "EQUAL" : "NOT EQUAL") 
		  << std::endl;
    }
    catch(Except::PhilException& e)
    {
	std::cout << e.what() << std::endl;
    }
    catch(std::exception& e)
    {
	std::cout << e.what() << std::endl;
    }
    catch(...)
    {
	std::cout << "UNCAUGHT EXCEPTION!" << std::endl;
    }


exit(0);
}

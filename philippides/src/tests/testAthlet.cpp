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
	pAthlet->m_nAvgDistance = 500;
	std::cout << pAthlet->ToXml() << std::endl;
    }
    catch(std::exception& e)
    {
	std::cout << e.what() << std::endl;
    }

exit(0);
}

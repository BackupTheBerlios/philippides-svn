#include <iostream>

#include <qstring.h>
#include <qdatetime.h>

#include "Exceptions.h"
#include "Athlet.h"

int main(int argc, char** argv)
{
    try{
	Phil::CAthlet* pAthlet = new Phil::CAthlet("", "Hirschenberger", QDate(1978, 7, 6));
	pAthlet->m_fAvgDistance = .5;
	std::cout << pAthlet->ToXml() << std::endl;
    }
    catch(std::exception& e)
    {
	std::cout << e.what() << std::endl;
    }

exit(0);
}

#include <iostream>

#include <qstring.h>
#include <qdatetime.h>

#include "Exceptions.h"
#include "Run.h"

int main(int argc, char** argv)
{
    try{
	Phil::CRun* pRun = new Phil::CRun(QDate(2004, 3, 30), QTime(1, 13, 34));
	pRun->m_nLength = 10000;
	pRun->m_nPulse = 170;
	pRun->m_EnWeather = Phil::CRun::SNOWY;
	pRun->m_EnImpression = Phil::CRun::NOIMPRESSION;
	pRun->m_sComment = "Ein guter lauf mit allem drum und dran.";
	std::cout << pRun->XmlHeader() << pRun->ToXml() << pRun->XmlFooter() << std::endl;
    }
    catch(std::exception& e)
    {
	std::cout << e.what() << std::endl;
    }

exit(0);
}

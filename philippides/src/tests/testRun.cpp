#include <iostream>

#include <qstring.h>
#include <qdatetime.h>
#include <qptrlist.h>

#include "Exceptions.h"
#include "Run.h"

int main(int argc, char** argv)
{
    try{
	Phil::CRun* pRun = new Phil::CRun(QDate(2004, 3, 30), QTime(1, 13, 34));
	pRun->m_nLength = 10000;
	pRun->m_nPulse = 170;
	pRun->m_EnWeather = Phil::CRun::SNOWY;
	pRun->m_EnImpression = Phil::CRun::GOOD;
	pRun->m_sComment = "Ein guter lauf mit allem drum und dran.";
	//std::cout << pRun->XmlHeader() << pRun->ToXml() << pRun->XmlFooter() << std::endl;

	QPtrList<Phil::CRun> list;
	list.append(pRun);
	list.append(new Phil::CRun(QDate(2002, 5, 2), QTime(2, 3, 3)));
	
	pRun->ToDisk(".", "run.xml", list);

	QPtrList<Phil::CRun>* pListNew = Phil::CRun::FromDisk(".", "run.xml");

	std::cout << pListNew->at(0)->ToXml()
		  << pListNew->at(1)->ToXml()
		  << std::endl;
    }
    catch(std::exception& e)
    {
	std::cout << e.what() << std::endl;
    }

exit(0);
}

#include <unit++/unit++.h>
#include <iostream>
#include <qstring.h>
#include <qdatetime.h>

#include "Athlet.h"
#include "Exceptions.h"

using namespace unitpp;

namespace
{

class Test: public suite
{

public:
    
    Test():
	suite("AthletTest")
    {	
	pMe = new Phil::CAthlet("Falco", "Hirschenberger", 
				Phil::CAthlet::MALE, QDate(1978, 7, 6));

	pMe->m_nAvgDistance = 5000;
	pMe->m_kmTime5 = QTime(0, 30, 0);
	pMe->m_kmTime10 = QTime(0, 53, 0);
	pMe->m_nWeight = 75;
	pMe->m_nAvgPulse = 160;
	pMe->m_nBiggestDistance = 22000;
	pMe->m_nHeight = 178;
	pMe->m_nRunningFreq = 4;
	pMe->m_nMorningPulse = 55;
	
	
	add("id1", testcase(this, "Serialization Test", &Test::SerialisationTest));
	suite::main().add("id", this);
    }

    ~Test(){
	delete pMe;

	// no I'm not pedantic, why do you ask? ;-)
	pMe = 0;
    }

    void SerialisationTest(){

	assert_true("Check weight", pMe->m_nWeight == 75);
//	try{
//	    pMe->ToDisk(".", "athlet.xml");
//
//	    Phil::CAthlet* pAthletNew= Phil::CAthlet::FromDisk(".", "athlet.xml");
//
//	    assert_true("are objects equal?", *pAthletNew == *pMe); 
//	}
//	catch(Except::PhilException& e)
//	{
//	    fail("Phil exception thrown");
//	}
//	catch(std::exception& e)
//	{
//	    fail("std::exception thrown");
//	}
//	catch(...)
//	{
//	    fail("Unknown exception thrown");
//	}
    }


private:

    Phil::CAthlet* pMe;


}* theTest = new Test();

} // namespace




#include "testSiRiche.h"
#include "ArbreAbstrait.h"

CPPUNIT_TEST_SUITE_REGISTRATION(testSiRiche);

void testSiRiche::testSiRiche() {
    ifstream fichier("testSi.txt");
    Interpreteur interpreteur(fichier);
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("Test analyse si", interpreteur.analyse());
    
}





#include "NoeudTest.h"
#include "../Interpreteur.h"
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudTest);


void NoeudTest::testEcrire() {
    ifstream fichier("progEcrire.txt");
    Interpreteur interpreteur(fichier);
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("Test analyse si", interpreteur.analyse());
    
}




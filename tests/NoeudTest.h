/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass.h
 * Author: behraf
 *
 * Created on Oct 25, 2017, 5:14:56 PM
 */

#ifndef NOEUDTEST_H
#define NOEUDTEST_H
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

using namespace CppUnit;

class NoeudTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(NoeudTest);  // déclaration d'une suite de tests
    CPPUNIT_TEST(testEcrire);       //test du noeud ecrire
    CPPUNIT_TEST_SUITE_END();       // fin de la suite de tests

public:
    NoeudTest() {};
    virtual ~NoeudTest() {}; 
    void setUp() {};       // utilisé pour initialiser des données communes aux tests
    void tearDown() {};    // utilisé pour "nettoyer" les données communes

private:
    void testEcrire();  // pour tester la méthode écrire
};

#endif 


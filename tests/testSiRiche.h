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

#ifndef TESTSIRICHE_H
#define TESTSIRICHE_H

#include <cppunit/extensions/HelperMacros.h>

class testSiRiche : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(testSiRiche); // déclaration d'une suite de tests

    CPPUNIT_TEST(testSiRiche);          // test du constructeur
    CPPUNIT_TEST(testAjoute);           // test de la méthode Ajoute
    CPPUNIT_TEST(testSyntaxe);          // test de l'analyse de la Syntaxe
    CPPUNIT_TEST(testExecuter);         // test de la méthode exécuter
    CPPUNIT_TEST(testTraduitEnCPP);     // test de la méthode traduitEnCPP

    CPPUNIT_TEST_SUITE_END();       // fin de la suite de tests

public:
    NoeudInstSiRiche();
    virtual ~NoeudInstSiRiche();
    void setUp();       // utilisé pour initialiser des données communes aux tests
    void tearDown();    // utilisé pour "nettoyer" les données communes

private:
    void testSiRiche();
    void testAjoute();
    void testSyntaxe();
    void testExecuter();
    void testTraduitEnCPP();
};

#endif 


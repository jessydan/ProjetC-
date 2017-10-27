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

#ifndef TESTNOEUD_H
#define TESTNOEUD_H

#include <cppunit/extensions/HelperMacros.h>

class testNoeud : public C {
    CPPUNIT_TEST_SUITE(testNoeud); // déclaration d'une suite de tests
    

    CPPUNIT_TEST_SUITE_END();       // fin de la suite de tests

public:
    NoeudInstSiRiche();
    virtual ~NoeudInstSiRiche();
    void setUp();       // utilisé pour initialiser des données communes aux tests
    void tearDown();    // utilisé pour "nettoyer" les données communes

private:
    void testSiRiche();;
};

#endif 


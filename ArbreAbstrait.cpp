#include <stdlib.h>
#include "ArbreAbstrait.h"
#include "Symbole.h"
#include "SymboleValue.h"
#include "Exceptions.h"
#include <typeinfo>

////////////////////////////////////////////////////////////////////////////////
// NoeudSeqInst
////////////////////////////////////////////////////////////////////////////////

NoeudSeqInst::NoeudSeqInst() : m_instructions() {
}

int NoeudSeqInst::executer() {
    for (unsigned int i = 0; i < m_instructions.size(); i++)
        m_instructions[i]->executer(); // on exécute chaque instruction de la séquence
    return 0; // La valeur renvoyée ne représente rien !
}

void NoeudSeqInst::ajoute(Noeud* instruction) {
    if (instruction != nullptr) m_instructions.push_back(instruction);
}

////////////////////////////////////////////////////////////////////////////////
// NoeudAffectation
////////////////////////////////////////////////////////////////////////////////

NoeudAffectation::NoeudAffectation(Noeud* variable, Noeud* expression)
: m_variable(variable), m_expression(expression) {
}

int NoeudAffectation::executer() {
    int valeur = m_expression->executer(); // On exécute (évalue) l'expression
    ((SymboleValue*) m_variable)->setValeur(valeur); // On affecte la variable
    return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudOperateurBinaire
////////////////////////////////////////////////////////////////////////////////

NoeudOperateurBinaire::NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit)
: m_operateur(operateur), m_operandeGauche(operandeGauche), m_operandeDroit(operandeDroit) {
}

int NoeudOperateurBinaire::executer() {
    int og, od, valeur;
    if (m_operandeGauche != nullptr) og = m_operandeGauche->executer(); // On évalue l'opérande gauche
    if (m_operandeDroit != nullptr) od = m_operandeDroit->executer(); // On évalue l'opérande droit
    // Et on combine les deux opérandes en fonctions de l'opérateur
    if (this->m_operateur == "+") valeur = (og + od);
    else if (this->m_operateur == "-") valeur = (og - od);
    else if (this->m_operateur == "*") valeur = (og * od);
    else if (this->m_operateur == "==") valeur = (og == od);
    else if (this->m_operateur == "!=") valeur = (og != od);
    else if (this->m_operateur == "<") valeur = (og < od);
    else if (this->m_operateur == ">") valeur = (og > od);
    else if (this->m_operateur == "<=") valeur = (og <= od);
    else if (this->m_operateur == ">=") valeur = (og >= od);
    else if (this->m_operateur == "et") valeur = (og && od);
    else if (this->m_operateur == "ou") valeur = (og || od);
    else if (this->m_operateur == "non") valeur = (!og);
    else if (this->m_operateur == "/") {
        if (od == 0) throw DivParZeroException();
        valeur = og / od;
    }
    return valeur; // On retourne la valeur calculée
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstSi
////////////////////////////////////////////////////////////////////////////////

NoeudInstSi::NoeudInstSi(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence) {
}

int NoeudInstSi::executer() {
    if (m_condition->executer()) m_sequence->executer();
    return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstTantQue
////////////////////////////////////////////////////////////////////////////////

NoeudInstTantQue::NoeudInstTantQue(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence) {
}

int NoeudInstTantQue::executer() {
    while (m_condition->executer()) {
        m_sequence->executer();
    }
    return 0; // La valeur renvoyée ne représente rien !
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstRepeter
////////////////////////////////////////////////////////////////////////////////

NoeudInstRepeter::NoeudInstRepeter(Noeud* sequence, Noeud* condition)
: m_sequence(sequence), m_condition(condition) {
}

int NoeudInstRepeter::executer() {
    do {
        m_sequence->executer();
    } while (m_condition->executer());
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstSiRiche
////////////////////////////////////////////////////////////////////////////////

NoeudInstSiRiche::NoeudInstSiRiche(std::vector<Noeud*> vectNoeuds)
: m_vectNoeuds(vectNoeuds) {
}

int NoeudInstSiRiche::executer() {
    //on sait que le premier indice du vecteur contient la condition du Si, et la seconde la séquence de celui-ci
    // on sait aussi que le dernier element est la séquence du sinon ( qui n'a pas de condition)
    //m_vectNoeuds.at(0) == condition si
    //m_vectNoeuds.at(1) == séquence si
    Noeud* p;
    bool exit = false;

    for (int i = 0; i < m_vectNoeuds.size() && exit == false; i += 2) { //on parcours le vecteur
        if (i < (m_vectNoeuds.size() - 2)) { // si on n'est pas au dernier élément (soit la séquence du sinon)
            if (m_vectNoeuds.at(i)->executer()) { // si la condition est bonne
                m_vectNoeuds.at(i + 1)->executer(); // on execute la séquence
                exit = true; // si un si || sinonSi est exécuté on sort de la boucle
            }
        }
    }
    if (!exit) { // si on est à la condition du sinon
        m_vectNoeuds[m_vectNoeuds.size() - 1]->executer(); //on execute la sequence de sinon
    }
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstPour
////////////////////////////////////////////////////////////////////////////////

NoeudInstPour::NoeudInstPour(Noeud* affectationDebut, Noeud* conditionArret, Noeud* affectationFin, Noeud* sequence)
: NoeudInstTantQue(conditionArret, sequence), m_affectationDebut(affectationDebut) {
    if (affectationFin != nullptr) {
        m_sequence->ajoute(affectationFin); // on ajoute l'incrémentation à la séquence.
    }
}//

int NoeudInstPour::executer() {
    if (m_affectationDebut != nullptr) { // si la premiere affectation n'est pas nulle
        m_affectationDebut->executer(); // créer l'affectation
    }
    NoeudInstTantQue::executer();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstEcrire
////////////////////////////////////////////////////////////////////////////////

NoeudInstEcrire::NoeudInstEcrire(Noeud* noeudPremierElement, vector<Noeud*> noeudsSupp)
: m_noeud(noeudPremierElement), m_noeudsSupp(noeudsSupp) {
}

int NoeudInstEcrire::executer() {
    Noeud* p;
    p = m_noeud; // on pointe sur le noeud du premier element

    // on regarde si l’objet pointé par p est de type SymboleValue et si c’est une chaîne
    if ((typeid (*p) == typeid (SymboleValue) && *((SymboleValue*) p) == "<CHAINE>")) {
        cout << ((SymboleValue*) p)->getChaine(); //on affiche la chaine de caractere
    } else {
        cout << p->executer(); // on affiche le résultat
    }

    for (int i = 0; i < m_noeudsSupp.size(); i++) {
        cout << " , ";
        p = m_noeudsSupp[i]; // on fait pointer p sur l'element courant du vecteur
        if ((typeid (*p) == typeid (SymboleValue) && *((SymboleValue*) p) == "<CHAINE>")) {
            cout << ((SymboleValue*) p)->getChaine(); //on affiche la chaine de caractere
        } else {
            cout << p->executer(); // on affiche le résultat
        }
    }
    return 0;
}

NoeudInstLire::NoeudInstLire(Noeud* noeud, vector<Noeud*> noeuds)
: m_noeud(noeud), m_noeudsSupp(noeuds) {
}

int NoeudInstLire::executer() {
    // lire va récuper les valeurs dans la console et va les assigner a ses variables mise en parametres
    Noeud* p;
    p = m_noeud; // on pointe sur le noeud m_noeud
    int varTemp = 0;

    cin >> varTemp; //on dnne une valeur a un entier temporaire via la saisie de l'utilisateur
    ((SymboleValue*) p)->setValeur(varTemp); // on initialise la valeur de la variable avec l'entier temporaire

    for (int i = 0; i < m_noeudsSupp.size(); i++) {
        p = m_noeudsSupp[i]; // on fait pointer p sur l'element courant du vecteur
        cin >> varTemp;
        ((SymboleValue*) p)->setValeur(varTemp);
    }

    return 0;
}




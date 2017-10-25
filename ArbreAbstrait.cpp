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

void NoeudSeqInst::traduitEnCPP(ostream & cout,unsigned int indentation) const {
    for (unsigned int i = 0; i < m_instructions.size(); i++) {
        m_instructions[i]->traduitEnCPP(cout, indentation); // on exécute chaque instruction de la séquence
        cout << endl; // La valeur renvoyée ne représente rien !
    }
}

////////////////////////////////////////////////////////////////////////////////
// NoeudAffectation
////////////////////////////////////////////////////////////////////////////////

NoeudAffectation::NoeudAffectation(Noeud* variable, Noeud* expression)
: m_variable(variable), m_expression(expression) {
}

NoeudAffectation::~NoeudAffectation() {
}


int NoeudAffectation::executer() {
    int valeur = m_expression->executer(); // On exécute (évalue) l'expression
    ((SymboleValue*) m_variable)->setValeur(valeur); // On affecte la variable
    return 0; // La valeur renvoyée ne représente rien !
}

void NoeudAffectation::traduitEnCPP(ostream & cout,unsigned int indentation) const {
    m_variable->traduitEnCPP(cout,indentation);
    cout << " = ";
    m_expression->traduitEnCPP(cout, 0);
    cout << ";";
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

void NoeudOperateurBinaire::traduitEnCPP(ostream & cout,unsigned int indentation) const {
    m_operandeGauche->traduitEnCPP(cout,0);
    cout << " "<< m_operateur.getChaine() <<" ";
    m_operandeDroit->traduitEnCPP(cout, 0);
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

void NoeudInstSi::traduitEnCPP(ostream & cout,unsigned int indentation) const {
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

void NoeudInstTantQue::traduitEnCPP(ostream & cout,unsigned int indentation) const {
    cout << setw(4*indentation)<<""<<"while ("; 
    m_condition->traduitEnCPP(cout, 0);// on met la condition d'arrêt dans les paramètres du while
    cout <<") {" <<endl;
    m_sequence->traduitEnCPP(cout, indentation+1); // on met la séquence on augmentant l'indentation
    cout << setw(4*indentation)<<""<<"}";
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

void NoeudInstRepeter::traduitEnCPP(ostream & cout,unsigned int indentation) const {
    cout << setw(4*indentation)<<""<< "do {" << endl; // écris do avec un espace de 4* indentation
    m_sequence->traduitEnCPP(cout, indentation+1);
    cout << setw(4*indentation)<<""<< "} while (";
    m_condition->traduitEnCPP(cout, 0);
    cout << ");";
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

void NoeudInstSiRiche::traduitEnCPP(ostream & cout,unsigned int indentation) const {
    unsigned int i =0;
    cout << setw(4*indentation)<<""<<"if (";// Ecrit "if (" avec un décalage de 4*indentation espaces 
    m_vectNoeuds.at(0)->traduitEnCPP(cout,0);// Traduit la condition en C++ sans décalage 
    cout << ") {"<< endl;// Ecrit ") {" et passe à la ligne  
    m_vectNoeuds.at(1)->traduitEnCPP(cout, indentation+1);// Traduit en C++ la séquence avec indentation augmentée 
    cout << setw(4*indentation)<< "" << "}";// Ecrit "}" avec l'indentation initiale et passe à la ligne 
    
    while(i<m_vectNoeuds.size()-2){ // on parcours le vecteur
         // si on n'est pas sur le dernier élément
        cout <<"else if ("; // il écrite à la suiàte de la précédente accolade
        m_vectNoeuds.at(i)->traduitEnCPP(cout,0);
        cout << ") {" << endl;
        m_vectNoeuds.at(i+1)->traduitEnCPP(cout,indentation+1);
        cout << setw(4*indentation)<<""<<"}";
        i=i+2;
        
    }
    
    cout<<"else {"<<endl;
    m_vectNoeuds.at(i)->traduitEnCPP(cout,indentation+1);
    cout <<setw(4*indentation) <<""<< "}" ;
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
        m_affectationDebut->executer(); // créer l'affectation i=0;
    }
    NoeudInstTantQue::executer();

    return 0;
}

void NoeudInstPour::traduitEnCPP(ostream & cout,unsigned int indentation) const {
    cout << setw(4*indentation) << "while ("<< endl;
    if(m_affectationDebut != nullptr){
        m_affectationDebut->traduitEnCPP(cout, 0); // on met l'affectation dans les parametres du while
        cout << ";";
    }
    
    m_condition->traduitEnCPP(cout, 0); // on met la condition d'arrêt du while dans ses paramètres
    cout << ") {" << endl;
    m_sequence->traduitEnCPP(cout, indentation+1); // on met la séquence 
    cout << setw(4*indentation)<<""<< "}" << endl;
    
 
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
    if ((typeid (*p) == typeid (SymboleValue)) && (*((SymboleValue*) p) == "<CHAINE>" )) {
        cout << ((SymboleValue*) p)->getChaine() ; //on affiche la chaine de caractere du symbole value de p
    } else {
        cout << p->executer() ; // on affiche le résultat
    }

    for (int i = 0; i < m_noeudsSupp.size(); i++) {
        cout << " , ";
        p = m_noeudsSupp[i]; // on fait pointer p sur l'element courant du vecteur
        if ((typeid (*p) == typeid (SymboleValue)) && (*((SymboleValue*) p) == "<CHAINE>" )) {
            cout << ((SymboleValue*) p)->getChaine(); //on affiche la chaine de caractere
        } else {
            cout << p->executer(); // on affiche le résultat
        }
    }
    return 0;
}

void NoeudInstEcrire::traduitEnCPP(ostream & cout,unsigned int indentation) const {
    unsigned int i=0;
    cout <<setw(4*indentation)<<"" <<"cout << " ;
    m_noeud->traduitEnCPP(cout, 0);
    
    while(i<m_noeudsSupp.size()){
        cout <<" << ";
        m_noeudsSupp.at(i)->traduitEnCPP(cout, 0);
        i++;
    }
    cout <<setw(4*indentation)<< " << endl;" ;
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstlire
////////////////////////////////////////////////////////////////////////////////

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


void NoeudInstLire::traduitEnCPP(ostream & cout,unsigned int indentation) const {
    unsigned int i=0;
    cout <<setw(4*indentation)<<""<< "cin >> " ;
    m_noeud->traduitEnCPP(cout, 0); // cin >> variable
    
    while(i<m_noeudsSupp.size()){ // si il y a plusieurs variables
        cout <<" >> ";
        m_noeudsSupp.at(i)->traduitEnCPP(cout, 0);
        i++;
    }
    cout << ";" << endl;
}





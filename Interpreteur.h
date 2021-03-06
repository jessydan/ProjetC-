#ifndef INTERPRETEUR_H
#define INTERPRETEUR_H

#include "Symbole.h"
#include "Lecteur.h"
#include "Exceptions.h"
#include "TableSymboles.h"
#include "ArbreAbstrait.h"
#include <vector>

class Interpreteur {
public:
	Interpreteur(ifstream & fichier);   // Construit un interpréteur pour interpreter
	                                    //  le programme dans  fichier 
                                      
	void analyse();                     // Si le contenu du fichier est conforme à la grammaire,
	                                    //   cette méthode se termine normalement et affiche un message "Syntaxe correcte".
                                            //   la table des symboles (ts) et l'arbre abstrait (arbre) auront été construits
	                                    // Sinon, une exception sera levée

	inline const TableSymboles & getTable () const  { return m_table;    } // accesseur	
	inline Noeud* getArbre () const { return m_arbre; }                    // accesseur
        void traduitEnCPP(std::ostream & cout, unsigned int) const;
	
private:
    Lecteur        m_lecteur;  // Le lecteur de symboles utilisé pour analyser le fichier
    TableSymboles  m_table;    // La table des symboles valués
    Noeud*         m_arbre;    // L'arbre abstrait
    std::vector<Noeud*> vectNoeuds;
    std::vector<SymboleValue*> vectSymbValues;
    const Symbole  chaine; 

    // Implémentation de la grammaire
    Noeud*  programme();   //   <programme> ::= procedure principale() <seqInst> finproc FIN_FICHIER
    Noeud*  seqInst();	   //     <seqInst> ::= <inst> { <inst> }
    Noeud*  inst();	   //        <inst> ::= <affectation> ; | <instSi>
    Noeud*  affectation(); // <affectation> ::= <variable> = <expression> 
    Noeud*  expression();  //  <expression> ::= <facteur> { <opBinaire> <facteur> }
    Noeud*  facteur();     //     <facteur> ::= <entier>  |  <variable>  |  - <facteur>  | non <facteur> | ( <expression> )
                           //   <opBinaire> ::= + | - | *  | / | < | > | <= | >= | == | != | et | ou
    Noeud*  instTantQue(); // <instTantQue> ::= tant que ( <expression> ) <seqInst> finTantQue
    Noeud*  instRepeter(); // <instRepeter> ::= repeter <seqInst> jusqua( <expression> )
    Noeud*  instEcrire();  // <instEcrire>  ::= ecrire( <expression> | <chaine> {, <expression> | <chaine> })
    Noeud*  instLire();    // <instLire>    ::= lire ( <variable> {, <variable> })
    Noeud*  instSiRiche(); // <instSiriche> ::= si(<expression>) <seqInst> {sinonsi(<expression>) <seqInst> }[sinon <seqInst>]finsi (remplace le Si)
    Noeud*  instPour();    // <instPour>    ::= pour( [ <affectation> ] ; <expression> [ <affectation> ]) <seqInst> finpour
    Noeud * instSelon();   // <instSelon>   ::= selon( <variable>) cas <entier> : <seqInst>  {cas <entier>: <seqInst> } [defaut : <seqInst>] finselon
 
    // outils pour simplifier l'analyse syntaxique
    void tester (const string & symboleAttendu) const throw (SyntaxeException);   // Si symbole courant != symboleAttendu, on lève une exception
    void testerEtAvancer(const string & symboleAttendu) throw (SyntaxeException); // Si symbole courant != symboleAttendu, on lève une exception, sinon on avance
    void erreur (const string & mess) const throw (SyntaxeException);             // Lève une exception "contenant" le message mess
    
};

#endif /* INTERPRETEUR_H */

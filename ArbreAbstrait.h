#ifndef ARBREABSTRAIT_H
#define ARBREABSTRAIT_H

// Contient toutes les déclarations de classes nécessaires
//  pour représenter l'arbre abstrait

#include <vector>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#include "Symbole.h"
#include "Exceptions.h"

////////////////////////////////////////////////////////////////////////////////
class Noeud {
// Classe abstraite dont dériveront toutes les classes servant à représenter l'arbre abstrait
// Remarque : la classe ne contient aucun constructeur
  public:
    virtual int  executer() =0 ; // Méthode pure (non implémentée) qui rend la classe abstraite fais les calculs
    virtual void traduitEnCPP(ostream & cout,unsigned int indentation) const =0 ;
    virtual void ajoute(Noeud* instruction) { throw OperationInterditeException(); }
    virtual ~Noeud() {} // Présence d'un destructeur virtuel conseillée dans les classes abstraites
};

////////////////////////////////////////////////////////////////////////////////
class NoeudSeqInst : public Noeud {
// Classe pour représenter un noeud "sequence d'instruction"
//  qui a autant de fils que d'instructions dans la séquence
  public:
     NoeudSeqInst();   // Construit une séquence d'instruction vide
    ~NoeudSeqInst() {} // A cause du destructeur virtuel de la classe Noeud
    int executer();    // Exécute chaque instruction de la séquence
    void ajoute(Noeud* instruction);  // Ajoute une instruction à la séquence
    void traduitEnCPP(ostream & cout,unsigned int indentation) const;


  private:
    vector<Noeud *> m_instructions; // pour stocker les instructions de la séquence
};

////////////////////////////////////////////////////////////////////////////////
class NoeudAffectation : public Noeud {
// Classe pour représenter un noeud "affectation"
//  composé de 2 fils : la variable et l'expression qu'on lui affecte
  public:
     NoeudAffectation(Noeud* variable, Noeud* expression); // construit une affectation
    ~NoeudAffectation(); // A cause du destructeur virtuel de la classe Noeud
    int executer();        // Exécute (évalue) l'expression et affecte sa valeur à la variable
    void traduitEnCPP(ostream & cout,unsigned int indentation) const;
  private:
    Noeud* m_variable;
    Noeud* m_expression;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudOperateurBinaire : public Noeud {
// Classe pour représenter un noeud "opération binaire" composé d'un opérateur
//  et de 2 fils : l'opérande gauche et l'opérande droit
  public:
    NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit);
    // Construit une opération binaire : operandeGauche operateur OperandeDroit
   ~NoeudOperateurBinaire() {} // A cause du destructeur virtuel de la classe Noeud
    int executer();            // Exécute (évalue) l'opération binaire)
    void traduitEnCPP(ostream & cout,unsigned int indentation) const;

  private:
    Symbole m_operateur;
    Noeud*  m_operandeGauche;
    Noeud*  m_operandeDroit;
};


////////////////////////////////////////////////////////////////////////////////
class NoeudInstTantQue : public Noeud {
// Classe pour représenter un noeud "instruction TantQue"
//  et ses 2 fils : la condition du TantQue et la séquence d'instruction associée
  public:
    NoeudInstTantQue(Noeud* condition, Noeud* sequence);
     // Construit une "instruction TantQue" avec sa condition et sa séquence d'instruction
   ~NoeudInstTantQue() {} // A cause du destructeur virtuel de la classe Noeud
    int executer();  // Exécute l'instruction TantQue : TantQue condition vraie on exécute la séquence
    void traduitEnCPP(ostream & cout,unsigned int indentation) const;

  protected:
    Noeud*  m_condition;
    Noeud*  m_sequence;
};
/////////////////////////////////////////////////////////////////////////////////
class NoeudInstRepeter : public Noeud {
// Classe pour représenter un noeud "instruction Repeter"
//  et ses 2 fils : la condition de repeter et la séquence d'instruction associée
  public:
    NoeudInstRepeter(Noeud* sequence, Noeud* condition);
     // Construit une "instruction repeter" avec sa condition et sa séquence d'instruction
   ~NoeudInstRepeter() {} // A cause du destructeur virtuel de la classe Noeud
    int executer();  // Exécute l'instruction Repeter : repeter la séquence tant que la condition est vraie
    void traduitEnCPP(ostream & cout,unsigned int indentation) const;

  private:
    Noeud*  m_condition;
    Noeud*  m_sequence;
};
///////////////////////////////////////////////////////////////////////////////
class NoeudInstSiRiche : public Noeud {
// Classe pour représenter un noeud "instruction Si riche"
//  et ses 2 fils : un vecteur de noeuds qui est composé de condition / séquence ...
//                  un vecteur de noeuds représentant le sinon, ( on a utiliser un noeud vide car c'est plus simple de les manipuler)
  public:
    NoeudInstSiRiche(std::vector<Noeud*> vectNoeuds, std::vector<Noeud*> noeudSinon);
     // Construit une instruction SiRiche avec le vector de noeud mis en paramètre.
   ~NoeudInstSiRiche() {} // A cause du destructeur virtuel de la classe Noeud
    int executer();  // Exécute l'instruction SiRiche : Si la condition est vrai alors, sinonsi la condition est vraie alors ... sinon on excute la séquence
    void traduitEnCPP(ostream & cout,unsigned int indentation) const;

  private:
    std::vector<Noeud*> m_vectNoeuds;
    std::vector<Noeud*> m_vectSinon;

};

///////////////////////////////////////////////////////////////////////////////
class NoeudInstSelon : public Noeud {
// Classe pour représenter un noeud "instruction Selon"
//  et ses multiples fils : une variable, un entier pour chaque cas, et une séquence
//                          les deux vecteurs ne sont là que pour l'enventuel existence de plusieurs cas et d'un défaut
  public:
    NoeudInstSelon(Noeud* variable, Noeud* entier, Noeud* sequence,std::vector<Noeud*> casSupp, std::vector<Noeud*> defaut);
     // Construit une instruction Selon avec le vector de noeud mis en paramètre.
   ~NoeudInstSelon() {} // A cause du destructeur virtuel de la classe Noeud
    int executer();  // Exécute l'instruction Selon 
    void traduitEnCPP(ostream & cout,unsigned int indentation) const;

  private:
    Noeud*  m_variable;
    Noeud*  m_entier;
    Noeud*  m_sequence;
    std::vector<Noeud*> m_casSupp;
    std::vector<Noeud*> m_defaut;

};

///////////////////////////////////////////////////////////////////////////////
class NoeudInstPour :  public NoeudInstTantQue { // on hérite de tant que pour le cas ou pour n'aura que la condition d'arrêt en paramètre
// Classe pour représenter un noeud "instruction pour"
//  et ses 4 fils : l'affectation du début du pour, la condition d'arrêt du pour, l'affectation de fin du pour ,et la séquence d'instruction
  public:
    NoeudInstPour(Noeud* affectationDebut, Noeud* conditionArret, Noeud* affectationFin, Noeud* sequence);
     // Construit une instruction Pour avec les noeuds mis en paramètre.
   ~NoeudInstPour()  {}; // A cause du destructeur virtuel de la classe Noeud
    int executer();  // Exécute l'instruction Pour : Pour (affectationDebut; condition d'arret, affectationFin) on exécute la séquence
    void traduitEnCPP(ostream & cout,unsigned int indentation) const;

  private:
    Noeud*  m_affectationDebut;
};

///////////////////////////////////////////////////////////////////////////////
class NoeudInstEcrire : public Noeud {
// Classe pour représenter un noeud "instruction ecrire"
//  et ses 2 fils : vecteur de noeuds , et vecteur de noeud supplémentaires
  public:
    NoeudInstEcrire(Noeud* noeudPremierElement, vector<Noeud*> noeudsSupp);
     // Construit une instruction ecrire avec les vector de noeuds mis en paramètre.
   ~NoeudInstEcrire() {}; // A cause du destructeur virtuel de la classe Noeud
    int executer();  // Exécute l'instruction ecrire : ecrire ( <expression> | <chaine> puis potentiellement d'autres)
    void traduitEnCPP(ostream & cout,unsigned int indentation) const;
    

  private:
      Noeud* m_noeud;
      std::vector<Noeud*> m_noeudsSupp;
};

///////////////////////////////////////////////////////////////////////////////
class NoeudInstLire : public Noeud {
// Classe pour représenter un noeud "instruction lire"
//  et son fils : noeud *
  public:
    NoeudInstLire(Noeud* noeud, std::vector<Noeud*> noeuds);
     // Construit une instruction lire avec le noeud mis en paramètre.
   ~NoeudInstLire() {}; // A cause du destructeur virtuel de la classe Noeud
    int executer();  // Exécute l'instruction lire : lis les variables inscrits en paramètres
    void traduitEnCPP(ostream & cout,unsigned int indentation) const;
    

  private:
      Noeud* m_noeud;
      std::vector<Noeud*> m_noeudsSupp;
};
#endif /* ARBREABSTRAIT_H */

#include "Interpreteur.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Interpreteur::Interpreteur(ifstream & fichier) :
m_lecteur(fichier), m_table(), m_arbre(nullptr) {
}

void Interpreteur::analyse() {
  m_arbre = programme(); // on lance l'analyse de la première règle
}

void Interpreteur::tester(const string & symboleAttendu) const throw (SyntaxeException) {
  // Teste si le symbole courant est égal au symboleAttendu... Si non, lève une exception
  static char messageWhat[256];
  if (m_lecteur.getSymbole() != symboleAttendu) {
    sprintf(messageWhat,
            "Ligne %d, Colonne %d - Erreur de syntaxe - Symbole attendu : %s - Symbole trouvé : %s",
            m_lecteur.getLigne(), m_lecteur.getColonne(),
            symboleAttendu.c_str(), m_lecteur.getSymbole().getChaine().c_str());
    throw SyntaxeException(messageWhat); // déclecnhe l'exception et arrête le programme
  }
}

void Interpreteur::testerEtAvancer(const string & symboleAttendu) throw (SyntaxeException) {
  // Teste si le symbole courant est égal au symboleAttendu... Si oui, avance, Sinon, lève une exception
  tester(symboleAttendu);
  m_lecteur.avancer();
}

void Interpreteur::erreur(const string & message) const throw (SyntaxeException) {
  // Lève une exception contenant le message et le symbole courant trouvé
  // Utilisé lorsqu'il y a plusieurs symboles attendus possibles...
  static char messageWhat[256];
  sprintf(messageWhat,
          "Ligne %d, Colonne %d - Erreur de syntaxe - %s - Symbole trouvé : %s",
          m_lecteur.getLigne(), m_lecteur.getColonne(), message.c_str(), m_lecteur.getSymbole().getChaine().c_str());
  throw SyntaxeException(messageWhat);
}

void Interpreteur::traduitEnCPP(ostream & cout,unsigned int indentation)const{
    cout << "\n\n// ===================TRADUCTION EN C++================\n"<<endl;
    cout << setw(4*indentation)<<""<<"#include <iostream>"<<endl;
    cout << setw(4*indentation)<<""<<"using namespace std;"<<endl;
    cout << setw(4*indentation)<<""<<"\nint main() {"<< endl;
  
  for (int i = 0 ; i < m_table.getTaille() ; i++){ // pour écrire int i; int j; etc...
      if (m_table[i]=="<VARIABLE>"){
          cout << setw(4* (indentation+1)) << "" << "int " << m_table[i].getChaine()<<";"<<endl;
      }
  }
  getArbre()->traduitEnCPP(cout,indentation+1);// lance l'opération traduitEnCPP sur la racine
  cout <<"\n"<< setw(4*(indentation+1))<<""<<"return 0;"<< endl ; 
  cout << setw(4*indentation)<<"}" << endl ; // Fin d’un programme C++
} 

Noeud* Interpreteur::programme() {
  // <programme> ::= procedure principale() <seqInst> finproc FIN_FICHIER
  testerEtAvancer("procedure");
  testerEtAvancer("principale");
  testerEtAvancer("(");
  testerEtAvancer(")");
  Noeud* sequence = seqInst();
  testerEtAvancer("finproc");
  tester("<FINDEFICHIER>");
  return sequence;

}

Noeud* Interpreteur::seqInst() {
  // <seqInst> ::= <inst> { <inst> }
  NoeudSeqInst* sequence = new NoeudSeqInst();
  do {
    sequence->ajoute(inst());
  } while (m_lecteur.getSymbole() == "<VARIABLE>" || m_lecteur.getSymbole() == "si" || m_lecteur.getSymbole() == "tantque" 
          || m_lecteur.getSymbole()=="repeter" || m_lecteur.getSymbole()=="pour" || m_lecteur.getSymbole()== "ecrire"
          || m_lecteur.getSymbole()=="lire" || m_lecteur.getSymbole()=="selon");
 
  // Tant que le symbole courant est un début possible d'instruction...
  // Il faut compléter cette condition chaque fois qu'on rajoute une nouvelle instruction
  return sequence;
}


Noeud* Interpreteur::inst() {
  // <inst> ::= <affectation>  ; | <instSi> | <instTantQue> 
    try{
        if (m_lecteur.getSymbole() == "<VARIABLE>") {
            Noeud *affect = affectation();
            testerEtAvancer(";");
            return affect;
        }else if (m_lecteur.getSymbole() == "si"){
              return instSiRiche();
        }else if (m_lecteur.getSymbole() == "tantque"){
            return instTantQue();
        }else if (m_lecteur.getSymbole() == "repeter"){
            return instRepeter();
        }else if (m_lecteur.getSymbole() == "pour"){
            return instPour();
        }else if (m_lecteur.getSymbole() == "ecrire"){
            return instEcrire();
        }else if (m_lecteur.getSymbole() == "lire"){
            return instLire();
        }else if(m_lecteur.getSymbole() == "selon"){
            return instSelon();
        }else{
            erreur("Instruction incorrecte");
        }
    }catch(SyntaxeException const& e){ // on récupère l'exception qui a été levée
        cout << e.what() << endl;
        while((m_lecteur.getSymbole()!="si"&& m_lecteur.getSymbole()!="tantque" && m_lecteur.getSymbole()!="pour" &&
               m_lecteur.getSymbole()!="ecrire" && m_lecteur.getSymbole()!="lire"&& m_lecteur.getSymbole()!="finproc" &&
               m_lecteur.getSymbole()!="selon") && m_lecteur.getSymbole()!="<FINDEFICHIER>"){
            m_lecteur.avancer();
        }
    }
}
  

Noeud* Interpreteur::affectation() {
  // <affectation> ::= <variable> = <expression> 
  tester("<VARIABLE>");
  Noeud* var = m_table.chercheAjoute(m_lecteur.getSymbole()); // La variable est ajoutée à la table eton la mémorise
  m_lecteur.avancer();
  testerEtAvancer("=");
  Noeud* exp = expression();             // On mémorise l'expression trouvée
  
  return new NoeudAffectation(var, exp); // On renvoie un noeud affectation
}

Noeud* Interpreteur::expression() {
  // <expression> ::= <facteur> { <opBinaire> <facteur> }
  //  <opBinaire> ::= + | - | *  | / | < | > | <= | >= | == | != | et | ou
  Noeud* fact = facteur();
  while ( m_lecteur.getSymbole() == "+"  || m_lecteur.getSymbole() == "-"  ||
          m_lecteur.getSymbole() == "*"  || m_lecteur.getSymbole() == "/"  ||
          m_lecteur.getSymbole() == "<"  || m_lecteur.getSymbole() == "<=" ||
          m_lecteur.getSymbole() == ">"  || m_lecteur.getSymbole() == ">=" ||
          m_lecteur.getSymbole() == "==" || m_lecteur.getSymbole() == "!=" ||
          m_lecteur.getSymbole() == "et" || m_lecteur.getSymbole() == "ou"   ) {
    Symbole operateur = m_lecteur.getSymbole(); // On mémorise le symbole de l'opérateur
    m_lecteur.avancer();
    Noeud* factDroit = facteur(); // On mémorise l'opérande droit
    fact = new NoeudOperateurBinaire(operateur, fact, factDroit); // Et on construuit un noeud opérateur binaire
  }
  return fact; // On renvoie fact qui pointe sur la racine de l'expression
}

Noeud* Interpreteur::facteur() {
  // <facteur> ::= <entier> | <variable> | - <facteur> | non <facteur> | ( <expression> )
  Noeud* fact = nullptr;
  if (m_lecteur.getSymbole() == "<VARIABLE>" || m_lecteur.getSymbole() == "<ENTIER>") {
    fact = m_table.chercheAjoute(m_lecteur.getSymbole()); // on ajoute la variable ou l'entier à la table
    m_lecteur.avancer();
  } else if (m_lecteur.getSymbole() == "-") { // - <facteur>
    m_lecteur.avancer();
    // on représente le moins unaire (- facteur) par une soustraction binaire (0 - facteur)
    fact = new NoeudOperateurBinaire(Symbole("-"), m_table.chercheAjoute(Symbole("0")), facteur());
  } else if (m_lecteur.getSymbole() == "non") { // non <facteur>
    m_lecteur.avancer();
    // on représente le moins unaire (- facteur) par une soustractin binaire (0 - facteur)
    fact = new NoeudOperateurBinaire(Symbole("non"), facteur(), nullptr);
  } else if (m_lecteur.getSymbole() == "(") { // expression parenthésée
    m_lecteur.avancer();
    fact = expression();
    testerEtAvancer(")");
  } else
    erreur("Facteur incorrect");
  return fact;
}

Noeud* Interpreteur::instSi() {
  // <instSi> ::= si ( <expression> ) <seqInst> finsi
  testerEtAvancer("si");
  testerEtAvancer("(");
  Noeud* condition = expression(); // On mémorise la condition
  testerEtAvancer(")");
  Noeud* sequence = seqInst();     // On mémorise la séquence d'instruction
  testerEtAvancer("finsi");
  return new NoeudInstSi(condition, sequence); // Et on renvoie un noeud Instruction Si
}


Noeud* Interpreteur::instTantQue() {
    // <instTantQue> ::= tantque ( <expression> ) seqInst fintantque
    testerEtAvancer("tantque");
    testerEtAvancer("(");
    Noeud* condition = expression(); // On mémorise la condition
    testerEtAvancer(")");
    Noeud* sequence = seqInst();     // On mémorise la séquence d'instruction
    testerEtAvancer("fintantque");
    return new NoeudInstTantQue(condition, sequence); // Et on renvoie un noeud Instruction tantque
    
}

Noeud* Interpreteur::instRepeter() {
// <instTepeter> ::= repeter <seqInst> jusqua( <expression> )
    testerEtAvancer("repeter");
    Noeud* sequence = seqInst(); // on mémorise la sequence d'instruction
    testerEtAvancer("jusqua");
    testerEtAvancer("(");
    Noeud* condition = expression(); // on mémorise la condition
    testerEtAvancer(")");
    return new NoeudInstRepeter(sequence, condition); // on retourne un noeud de l'instruction répeter
}

Noeud* Interpreteur::instSiRiche() { // revoir le vecteur il ne prends pas assez de noeuds
// <instSiriche> ::= si(<expression>) <seqInst> {sinonsi(<expression>) <seqInst> }[sinon <seqInst>]finsi
// le vecteur contiendra condition|séquence|condition|...|séquence
    
    vector<Noeud*> noeuds;
    vector<Noeud*> noeudSinon;
    
    testerEtAvancer("si");
    testerEtAvancer("(");
    Noeud* conditionSi = expression(); // on créer le noeud pour la première condition
    noeuds.push_back(conditionSi); // on met la condition dans le vecteur de noeuds
    testerEtAvancer(")");
    Noeud* sequenceSi = seqInst(); // séquence d'instruction du Si
    noeuds.push_back(sequenceSi); // on met la séqyuence dans le vecteur de noeuds
    
    while(m_lecteur.getSymbole()=="sinonsi"){
        testerEtAvancer("sinonsi");
        testerEtAvancer("(");
        Noeud* conditionSinonSi = expression(); 
        noeuds.push_back(conditionSinonSi);// on stocke la condition dans le vecteur de noeuds
        testerEtAvancer(")");
        Noeud* sequenceSinonSi = seqInst();
        noeuds.push_back(sequenceSinonSi); // on stocke la sequence dans le vecteur de noeuds
    }
    // pas forcément un sinon.
    if (m_lecteur.getSymbole()=="sinon"){ // on utilise un vecteur car celui ci peut être nul et pourra donc le manipuler plus simplement
        testerEtAvancer("sinon"); // le sinon n'a pas de condition, on se servira de cette différence pour le repérer dans le vecteur
        Noeud* sequenceSinon = seqInst(); 
        noeudSinon.push_back(sequenceSinon);
    }
    
    
    testerEtAvancer("finsi");
    return new NoeudInstSiRiche(noeuds, noeudSinon);
}

Noeud* Interpreteur::instSelon() {
    // <instSelon>   ::= selon( <variable>) cas <entier> : <seqInst>  {cas <entier>: <seqInst> } [defaut : <seqInst>] finselon
    
    testerEtAvancer("selon");
    testerEtAvancer("(");
    Noeud* variable = m_table.chercheAjoute(m_lecteur.getSymbole());//on ajoute la variable à la table de symbole values
    m_lecteur.avancer();
    testerEtAvancer(")");
    testerEtAvancer("cas");
    Noeud* entier = m_table.chercheAjoute(m_lecteur.getSymbole());// on ajoute l'entier à la table des symboles
    m_lecteur.avancer();
    testerEtAvancer(":");
    Noeud* sequence = seqInst();
    
    vector<Noeud*> casSupp;
    vector<Noeud*> defaut;
    Noeud* entier2;
    Noeud* sequence2;
    
    while(m_lecteur.getSymbole()== "cas"){ // tant qu'il y a des cas
        testerEtAvancer("cas");
        entier2 = m_table.chercheAjoute(m_lecteur.getSymbole());
        m_lecteur.avancer();
        casSupp.push_back(entier2);
        testerEtAvancer(":");
        sequence2 = seqInst(); // on créer la séquence
        casSupp.push_back(sequence2);
    }
    
    if (m_lecteur.getSymbole()=="defaut"){ // si le cas par défaut à été renseigné
        testerEtAvancer("defaut");
        testerEtAvancer(":");
        Noeud* sequenceDefaut = seqInst();
        defaut.push_back(sequenceDefaut); // on ajoute la séquence au vecteur du sinon
    }
    
    testerEtAvancer("finselon");
    return new NoeudInstSelon(variable,entier,sequence,casSupp,defaut);
    
}


Noeud* Interpreteur::instPour() { // pour à corriger
    // <instPour>    ::= pour( [ <affectation> ] ; <expression> [ <affectation> ]) <seqInst> finpour
    testerEtAvancer("pour");
    testerEtAvancer("(");
    
    Noeud* affectationDebut = affectation();
    testerEtAvancer(";"); // on avance au paramètre suivant
    Noeud* conditionArret = expression(); // la condition d'arret et forcément une expression
    testerEtAvancer(";");
    
    Noeud* affectationFin = affectation();
    testerEtAvancer(")");
    Noeud* sequence = seqInst();
    testerEtAvancer("finpour");
    //return nullptr;
    return new NoeudInstPour(affectationDebut,conditionArret,affectationFin,sequence); // on retourne un noeud de l'instruction pour
}
 

Noeud* Interpreteur::instEcrire() {
    // <instEcrire>  ::= ecrire( <expression> | <chaine> {, <expression> | <chaine> })
    Noeud* noeud = nullptr;
    Noeud* noeud2 = nullptr;
    testerEtAvancer("ecrire");
    testerEtAvancer("(");

    if (m_lecteur.getSymbole() == "<CHAINE>") {
        noeud = m_table.chercheAjoute(m_lecteur.getSymbole()); // on ajoute la variable ou l'entier à la table
        m_lecteur.avancer();
        
    }else{ // sinon c'est une expression
        noeud = expression();
    }
    
    vector<Noeud*> noeudsSupp;
    
    while(m_lecteur.getSymbole()==","){ // on regarde si il y a d'autres choses à écrire
        testerEtAvancer(",");
        if (m_lecteur.getSymbole() == "<CHAINE>") {
            noeud2 = m_table.chercheAjoute(m_lecteur.getSymbole()); // on ajoute la variable ou l'entier à la table
            m_lecteur.avancer();
            noeudsSupp.push_back(noeud2);
        }else { // si le symbole lu est un entier , ça veut dire que c'est une expression
            noeud2 = expression();
            noeudsSupp.push_back(noeud2);
        }
    }
    testerEtAvancer(")");
    testerEtAvancer(";");
    
    return new NoeudInstEcrire(noeud,noeudsSupp); // on retourn un noeud inst Ecrire
}

Noeud* Interpreteur::instLire(){
    // <instLire>    ::= lire ( <variable> {, <variable> })
    Noeud* noeud = nullptr;
    Noeud* noeud2 =nullptr;
    vector<Noeud*> noeudsLireSupp;
    testerEtAvancer("lire");
    testerEtAvancer("(");
    if (m_lecteur.getSymbole() == "<VARIABLE>"){ // si lecteur lit bien un sylbole de type VARIABLE
        noeud = m_table.chercheAjoute(m_lecteur.getSymbole());//on ajoute la variable à la table de symbole values
        m_lecteur.avancer();
    }
    
    while (m_lecteur.getSymbole()==","){ // tant qu'il y a de variables à lire
        testerEtAvancer(",");
        if (m_lecteur.getSymbole() == "<VARIABLE>"){ // si lecteur lit bien un sylbole de type VARIABLE
            noeud2 = m_table.chercheAjoute(m_lecteur.getSymbole());//on ajoute la variable à la table de symbole values
            noeudsLireSupp.push_back(noeud2);
            m_lecteur.avancer();
        }
    }
    testerEtAvancer(")");
    testerEtAvancer(";");
    
    //return nullptr;
    return new NoeudInstLire(noeud,noeudsLireSupp);
}

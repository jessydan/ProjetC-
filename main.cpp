#include <iostream>
using namespace std;

#include "Interpreteur.h"
#include "Exceptions.h"

int main(int argc, char* argv[]) {
  string nomFich;
  if (argc != 2) {
    cout << "Usage : " << argv[0] << " nom_fichier_source" << endl << endl;
    cout << "Entrez le nom du fichier que voulez-vous interpréter : ";
    getline(cin, nomFich);
  } else
    nomFich = argv[1];
  ifstream fichier(nomFich.c_str());
  try {
    Interpreteur interpreteur(fichier);
    interpreteur.analyse();
    // Si pas d'exception levée, l'analyse syntaxique a réussi
    cout << endl << "================ Syntaxe Correcte" << endl;
    // On affiche le contenu de la table des symboles avant d'exécuter le programme
    cout << endl << "================ Table des symboles avant exécution : " << interpreteur.getTable();
    cout << endl << "================ Execution de l'arbre" << endl;
    // On exécute le programme si l'arbre n'est pas vide
    if (interpreteur.getArbre()!=nullptr){
        interpreteur.getArbre()->executer();
        interpreteur.traduitEnCPP(cout,0);
    }
    // Et on vérifie qu'il a fonctionné en regardant comment il a modifié la table des symboles
    cout << endl << "================ Table des symboles apres exécution : " << interpreteur.getTable();
  } catch (InterpreteurException & e) {
    cout << e.what() << endl;
    //throw; // repropagation de l'exception
  }
    return 0;
}

  //////////////////////////////////////////////////////////////////////////////////
  ////////////////////////  PARTIE TESTS CODES TRADUITS ////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////
  
  /////////////////////////////////////////////////////// TEST SI RICHE ///////////////////////////////////////////////////////////// 
  //test le code généré et le compile
  /*
    int main() {
        int i;
        i = 0;
        if (i == 3) {
            cout << "i=3" << endl;
        }else if (i == 3) {
            cout << "i=3" << endl;
        }else if (i == 4) {
            cout << "i=4" << endl;
        }else {
            cout << "sinon" << endl;
        }

        return 0;
    }
  
  */ 
  /////////////////////////////////////////////////////// TEST TANT QUE /////////////////////////////////////////////////////////////
  // test le code généré et le compile
    /*
     
    int main() {
        int i;
        i = 0;
        while (i <= 3) {
            cout << "test" << endl;
            i = i + 1;
        }

        return 0;
    }
    
    */
  
  /////////////////////////////////////////////////////// TEST REPETER /////////////////////////////////////////////////////////////
  
  /*
    int main() {
        int i;
        i = 0;
        do {
            i = i + 1;
            cout << "testRepeter" << endl;
        } while (i <= 3);

        return 0;
    }

   */
  
  /////////////////////////////////////////////////////// TEST POUR /////////////////////////////////////////////////////////////////
  
  /*
    int main() {
        int j;
        j = 0;
        while (j < 5) {
            cout << "test" << endl;
            j = j + 1;
        }

        return 0;
    }

  */
  /////////////////////////////////////////////////////// TEST LIRE /////////////////////////////////////////////////////////////
  
  /*
    int main() {
        int i;
        int j;
        int k;
        i = 0;
        j = 0;
        k = 0;
        cout << "Veuillez rentrez la valeur de i :" << endl;
        cin >> i;

        cout << "Veuillez rentrez les valeurs de j et de k :" << endl;
        cin >> j >> k;


        return 0;
    }

   */
  
  /////////////////////////////////////////////////////// TEST ECRIRE /////////////////////////////////////////////////////////////
  
  /*
    int main() {
        int i;
        int j;
        int k;
        i = 10;
        j = 3;
        k = 4;
        cout << k << endl;
        cout << "seconde test" << "secondParam test" << "troisiemePAram test" << k << endl;
        cout << "troisieme test" << i + 1 << endl;
        cout << "quatrième test" << i + j << k << endl;

        return 0;
    }

   */
  
  
  


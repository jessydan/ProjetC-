#include <iostream>
using namespace std;

int Selon() {
    int i;
    i = 8;
    switch(i) {
        case 1 : 
            cout << "test num 1"    << endl;

        break;
        case 2 : 
            cout << "test num 2"    << endl;

        break;
        case 5 : 
            cout << "test num 5"    << endl;

        break;
        case 10 : 
            cout << "test num 10"    << endl;

        break;
        default : 
            cout << "test de defaut"    << endl;
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include "Nmer.h"

using namespace std;

int main(){

    // A continuacion se muestra el resultado de ejecutar algunos de los metodos implementados
    // Hay mas metodos implementados de los aqui presentes!!
    Nmer n_mer1;
    Nmer n_mer3;
    Nmer n_mer7;
    Nmer n_mer8;

    string adn;
    ifstream fi;


    fi.open("../datos/1.txt");

    fi >> adn;

    n_mer1.sequenceADN(10,adn);

    fi.close();


    fi.open("../datos/3.txt");

    fi >> adn;

    n_mer3.sequenceADN(10,adn);

    fi.close();


    fi.open("../datos/7.txt");

    fi >> adn;

    n_mer7.sequenceADN(10,adn);

    fi.close();


    fi.open("../datos/8.txt");

    fi >> adn;

    n_mer8.sequenceADN(10,adn);

    fi.close();

    cout << "N_MER1 en preorden: " << endl << endl;

    n_mer1.list_Nmer();

    string pref = "ACT";

    Nmer nuevo = n_mer3.Prefix(pref);

    cout << "N_MER3 ACT*: " << endl << endl;

    nuevo.list_Nmer();

    Nmer nuevo2 = n_mer8;

    nuevo2.union_Nmers(n_mer7);

    cout << "Union N_MER7 y N_MER8:" << endl << endl;

    nuevo2.list_Nmer();

    cout << "Distancia 1.txt - 3.txt: " << n_mer1.Distance(n_mer3);
    cout << "Distancia 7.txt - 8.txt: " << n_mer7.Distance(n_mer8);


	return 0;

}

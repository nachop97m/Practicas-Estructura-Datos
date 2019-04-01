#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>


using namespace std;

template <typename T, typename CMP>
bool load(conjunto<T, CMP> &  cm, const string & s) {
 ifstream fe;
 string cadena;
	int cont = 0;

 cout << "Abrimos "<< s << endl;
 fe.open(s.c_str(), ifstream::in);
 if (fe.fail()){
   cerr << "Error al abrir el fichero " << s << endl;
 } 
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{ 
      getline(fe,cadena,'\n');
    }while (cadena.find("#")==0 && !fe.eof());
    //leo la tabla de mutaciones, una línea cada vez
    while ( !fe.eof() && cont < 10){ 
        //cout << "leo:: "<< cadena << endl;
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
        mutacion mut = mutacion(cadena);
        // Insertar mutación en el conjunto
        cm.insert(mut);
        getline(fe,cadena,'\n');
			cont++;
    }
    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }


class cre_ChrPos {

	public:

		bool operator () (mutacion a, mutacion b){

			return a < b;

		}

};

class de_ChrPos {

	public:

		bool operator () (mutacion a, mutacion b){

			return (!(a < b) && !(a == b));

		}

};

class cre_id {

	public:

		bool operator () (mutacion a, mutacion b){

			return a.getID() < b.getID();

		}

};

class de_id {

	public:

		bool operator () (mutacion a, mutacion b){

			return (!(a.getID() < b.getID()) && !(a.getID() == b.getID()));

		}

};

class cre_Enfermedad{

	public:
		
		bool operator () (enfermedad a, enfermedad b){

				return (a < b);

		}

};

class de_Enfermedad{

	public:
		
		bool operator () (enfermedad a, enfermedad b){

				return ( !(a < b) == !(a == b));

		}

};

int main(int argc, char *argv[]){

	// Mutaciones

	conjunto <mutacion, cre_ChrPos > a;

	//Cargar las mutaciones en vectorSNPs
	load(a, "clinvar_20160831.vcf");

	for (int i=0; i < 10; i++){

		cout << "Chr: " << a.getVector()[i].getChr() << " -- Pos: " 
			  << a.getVector()[i].getPos() << endl;

	}

	conjunto <mutacion, de_ChrPos > b;

	//Cargar las mutaciones en vectorSNPs
	load(b, "clinvar_20160831.vcf");

	for (int i=0; i < 10; i++){

		cout << "Chr: " << b.getVector()[i].getChr() << " -- Pos: " 
			  << b.getVector()[i].getPos() << endl;

	}

	conjunto <mutacion, cre_id > x;

	//Cargar las mutaciones en vectorSNPs
	load(x, "clinvar_20160831.vcf");

	for (int i=0; i < 10; i++){

		cout << "ID: " << x.getVector()[i].getID() << endl;

	}

	conjunto <mutacion, de_id > y;

	//Cargar las mutaciones en vectorSNPs
	load(y, "clinvar_20160831.vcf");

	for (int i=0; i < 10; i++){

		cout << "ID: " << y.getVector()[i].getID() << endl;

	}

	// Enfermedades

	enfermedad uno ("abc", "1", "65");
	enfermedad dos ("abcd", "2", "65");
	enfermedad tres ("abcde", "3", "65");
	enfermedad cuatro ("abcdef", "4", "65");

	conjunto <enfermedad, cre_Enfermedad > z;

	z.insert(uno);
	z.insert(dos);
	z.insert(tres);
	z.insert(cuatro);

	cout << "Enfermedades: conjunto creciente\n" << z << endl;

	conjunto <enfermedad, de_Enfermedad > t;

	t.insert(uno);
	t.insert(dos);
	t.insert(tres);
	t.insert(cuatro);

	cout << "Enfermedades: conjunto decreciente\n" << t << endl;

   return 0;
}

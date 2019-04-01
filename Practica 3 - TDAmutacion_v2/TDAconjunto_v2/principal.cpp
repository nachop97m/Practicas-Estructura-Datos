#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>


using namespace std;
using namespace std::chrono;
	
	/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
  @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/

bool load(conjunto &  cm, const string & s) {
 ifstream fe;
 string cadena;

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
    while ( !fe.eof() ){ 
        //cout << "leo:: "<< cadena << endl;
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
        mutacion mut = mutacion(cadena);
        // Insertar mutación en el conjunto
        cm.insert(mut);
        getline(fe,cadena,'\n');
    }
    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }


bool ef_load(conjunto &  cm, const string & s, int t) {
 ifstream fe;
 string cadena;

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
    while ( !fe.eof() && (cm.size() < t)){
        //cout << "leo:: "<< cadena << endl;
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
        mutacion mut = mutacion(cadena);
        // Insertar mutación en el conjunto
        cm.insert(mut);
        getline(fe,cadena,'\n');
    }
    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }


int main(int argc, char *argv[]){

	conjunto conjuntoMutaciones;
	string query_str; 

	//Cargar las mutaciones en vectorSNPs
	load(conjuntoMutaciones, "clinvar_20160831.vcf");

	//Imprimir número de elementos almacenados en conjuntoMutaciones
	cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<conjuntoMutaciones.size()<<endl;  

	//Imprimir cuántas mutaciones están asociadas al cromosoma 1:
	cout << "Mutaciones asociadas a Chr 1: "<< conjuntoMutaciones.lower_bound2("2")-conjuntoMutaciones.begin()<< endl;

	pair<conjunto::value_type,bool> miPar;

	/**@todo ¿Existe la mutación con ID "rs147165522"? Imprimir la mutación y las enfermedades asociadas */

	miPar= conjuntoMutaciones.find("rs147165522");

	if (miPar.second == false)
		cout << "No existe la mutacion.\n";

	else
		cout << miPar.first;

	/**@todo ¿Existe la mutación en chr/pos "14"/67769578? Imprimir la mutación y las enfermedades asociadas */

	miPar=conjuntoMutaciones.find("67769578",14);

	if (miPar.second == false)
		cout << "No existe la mutacion \n";

	else
		cout <<miPar.first;
	

	/**@todo ¿Cómo podríamos calcular el número de mutaciones del cromosoma 3? (utiliza lower_bound / upper_bound) */
	cout << "El numero de mutaciones asociadas a cromosoma 3 es " 
		<< conjuntoMutaciones.lower_bound2("4")-conjuntoMutaciones.lower_bound2("3") << endl;

	/**@todo Analiza la eficiencia teórica y empírica de las operaciones find, insert y erase */
	high_resolution_clock::time_point start,end;
	duration<double> tiempo_transcurrido;

	conjunto conjuntoMutacionesEficiencia;

	ofstream fo;

	fo.open("eficiencia.dat");

	for (int tam = 250; tam < conjuntoMutaciones.size(); tam += 1000){

        ef_load (conjuntoMutacionesEficiencia, "clinvar_20160831.vcf", tam);

        start = high_resolution_clock::now();
        conjuntoMutacionesEficiencia.find ("MT", 15990);
        end = high_resolution_clock::now();

        tiempo_transcurrido = duration_cast<duration<double> >(end - start);
        fo << tam << " " << tiempo_transcurrido.count() << endl; 
    }

	fo.close();

	/*conjunto conjuntoMutacionesEficiencia2;

	fo.open("eficiencia2.dat");

	for (int tam = 250; tam < conjuntoMutaciones.size(); tam += 1000){

			start = high_resolution_clock::now();
			ef_load (conjuntoMutacionesEficiencia2, "clinvar_20160831.vcf", tam);
			end = high_resolution_clock::now();

			tiempo_transcurrido = duration_cast<duration<double> >(end - start);
			fo << tam << " " << tiempo_transcurrido.count() << endl; 
	}

	fo.close();*/

   return 0;
}

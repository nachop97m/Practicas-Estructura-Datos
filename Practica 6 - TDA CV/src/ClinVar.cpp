/* 
 * ClinVar.cpp
 * 
 * Copyright  (C) Ignacio Pineda Mochon -- Grado Ingenieria Informatica UGR
*/

#include "ClinVar.h"

void clinvar::load (string DB) {

	ifstream fe;
	string cadena;

	cout << "Abrimos "<< DB << endl;
	fe.open(DB.c_str(), ifstream::in);

	if (fe.fail()){

		cerr << "Error al abrir el fichero " << DB << endl;

	} 

	else {

		//leo la cabecera del fichero (líneas que comienzan con #)
		do{ 

			getline(fe,cadena,'\n'); 

		}while (cadena.find('#')!=string::npos && !fe.eof());

		//leo la tabla de mutaciones, una línea cada vez
		while ( !fe.eof() ){ 

        //cout << "leo:: "<< cadena << endl;
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
			const mutacion mut = mutacion(cadena);
        //cout << mut<< endl;
        // Insertar mutación en el conjunto
			this->insert(mut);
			getline(fe,cadena,'\n');

		}

	} // else

	fe.close();

}

void clinvar::insert (const mutacion & x) {

	pair < set<mutacion>::iterator, bool> par = mutDB.insert (x);  // insertar mutacion

	if((par.second) == true){

		set < mutacion > ::iterator its = par.first;

		IDm_map.insert (pair<IDmut,set<mutacion>::iterator>( x.getID(), par.first)); // insertar IDmutacion - iterator mut

		vector<string>::const_iterator itv = x.getGenes().cbegin();
		pair <map<IDgen, list< set<mutacion>::iterator> >::iterator, bool> par2;
		list < set<mutacion>::iterator > lista;
		IDgen auxg;

		while (itv != x.getGenes().cend()){

			par2 = gen_map.insert(pair <IDgen, list < set<mutacion>::iterator > > ((*itv), lista));    // insertar IDgen - list
			auxg = (*(par2.first)).first;

			if (par2.second == true){

				(gen_map[auxg]).push_back(par.first);

			}

			else {

				gen_map[auxg].push_back(par.first);

			}

			itv++;

		}

		vector<enfermedad>::const_iterator itve;
		itve = (x.getEnfermedades()).cbegin();

		while (itve != x.getEnfermedades().cend()){

			EnfDB[(*itve).getID()] = (*itve);  // insertar IDenf - enf
			IDenf_map.insert (pair <IDenf, set <mutacion>::iterator> ((*itve).getID(), par.first)); //insertar IDenf - iterator mut

		}
		
	}

}

bool clinvar::erase (IDmut ID) {

	bool salida = false;
	set<mutacion>::const_iterator it = mutDB.find(ID);

	if (it != mutDB.end()){

		IDm_map.erase(ID);    // borrar del contenedor ID mut - iterator mut

		for (int i=0; i < (*it).getGenes().size(); i++){  // Borrar del contenedor gen - list mut asociadas a gen

			map<IDgen, list< set<mutacion>::iterator> >::iterator itm = gen_map.find ( (*it).getGenes()[i] );
			list< set<mutacion>::iterator>::iterator itl = ((*itm).second).begin();

			while((*(*itl)) != (*it))   // Avanzar hasta el iterador a la mutacion correspondiente
				itl++;

			((*itm).second).erase(itl);  // Borrar iterador a la mutacion de la lista

			if (((*itm).second).empty())  // Si la lista ha quedado vacia
				gen_map.erase (itm);

		}

		for (int i=0; i < (*it).getEnfermedades().size(); i++){  // Comprobar enfermedades asociadas a la mutacion

			bool borrar = true;

			for (multimap<IDenf,set<mutacion>::iterator>::const_iterator c = IDenf_map.find( (*it).getEnfermedades()[i].getID()); c != IDenf_map.cend(); c++){   // Eliminar asociaciones enf - mut de cada una de estas enfermedades

				if (((*c).first == ((*it).getEnfermedades()[i].getID())) && ((*(*c).second).getID() == ID)){

					IDenf_map.erase(c);

				}

				if ((*c).first == (*it).getEnfermedades()[i].getID() && (*(*c).second).getID() != ID)
					borrar = false;

			}

			if (borrar)  // eliminar enfermedad si no estaba asociada a mas mutaciones
				EnfDB.erase((*it).getEnfermedades()[i].getID());

		}

		mutDB.erase(it);  // borrar la mutacion
		salida = true;

	}

	return salida;

}

clinvar::iterator clinvar::find_Mut (IDmut ID){

	clinvar::iterator itc = this->begin();  // Buscar con clinvar::iterator

	for ( ; itc != this->end(); itc++)
		if ( (*itc).getID() == ID)     // si encuentra mutacion con ID
			break;

	return itc;


}

clinvar::iterator clinvar::begin(){

	set<mutacion>::iterator its = mutDB.begin();   // Inicio del contenedor

	clinvar::iterator itc (its);    // clinvar::iterator creado a partir de its

	return itc;

}

clinvar::iterator clinvar::end(){

	set<mutacion>::iterator its = mutDB.end();   // Fin del contenedor

	clinvar::iterator itc (its);    // clinvar::iterator creado a partir de its

	return itc;

}

clinvar::iterator clinvar::lower_bound(string cromosoma, unsigned int posicion){

	clinvar::iterator itc = this->begin();

	for ( ; itc != this->end(); itc++){

		if ( (*itc).getChr() >= cromosoma && (*itc).getPos() >= posicion)    // Devolver iterador a la primera mut con chr/pos >= que los dados
			break;

	} // Si no se encuentra, se devuelve clinvar::iterator::end

	return itc;

}

clinvar::iterator clinvar::upper_bound(string cromosoma, unsigned int posicion){

	clinvar::iterator itc = this->begin();

	for ( ; itc != this->end(); itc++){

		if ( (*itc).getChr() > cromosoma && (*itc).getPos() > posicion)  // Devolver iterador a la primera mut con chr/pos > que los dados
			break;

	} // Si no se encuentra, se devuelve clinvar::iterator::end

	return itc;

}

clinvar::iterator::iterator(){  // constructor vacio iterator

}

clinvar::iterator::iterator(set<mutacion>::iterator its){  // constructor que recibe un set::iterator

	it = its;

}

const mutacion & clinvar::iterator::operator*(){

	return (*it);

}

clinvar::iterator & clinvar::iterator::operator++(){

	it++;

	return (*this);

}

clinvar::iterator & clinvar::iterator::operator++(int i){

	for (int c=0; c < i; c++)
		it++;

	return (*this);

}

clinvar::iterator clinvar::iterator::getIT(){

	return it;

}

bool clinvar::iterator::operator != (iterator itt){   // Para comparaciones en bucles for (ej: iter != a.end())

	return (itt.getIT() != it);

}

vector<enfermedad> clinvar::getEnfermedades(mutacion & mut){

	return mut.getEnfermedades();

}

list<IDenf> clinvar::getEnfermedades(string keyword){

	list<IDenf> lenf;
	map<IDenf,enfermedad>::iterator itm = EnfDB.begin();

	for ( ; itm != EnfDB.end(); itm++)                  // Recorrer contenedor de enfermedades
		if ( ((*itm).second).nameContains(keyword) )     // Si contiene keyword, añadir a la lista la enfermedad que acompaña al ID (su ID)
			lenf.push_back ((*itm).first);

	return lenf;

}

set<IDmut> clinvar::getMutacionesEnf (IDenf ID){

	set<IDmut> ids;
	multimap<IDenf,set<mutacion>::iterator>::iterator itmm = IDenf_map.begin();

	for ( ; itmm != IDenf_map.end(); itmm++)           // Buscar en el multimap el ID de la enfermedad, y añadir las mutaciones al set
		if ( (*itmm).first == ID)								// Con el iterador que acompaña al ID accedemos facilmente al ID de la enfermedad
			ids.insert ( (*((*itmm).second)).getID());

	return ids;

}

set<IDmut> clinvar::getMutacionesGen (IDgen ID){

	set<IDmut> ids;
	map<IDgen, list< set<mutacion>::iterator> >::iterator itm = gen_map.begin();
	list< set<mutacion>::iterator>::iterator itl;

	for ( ; itm != gen_map.end(); itm++){             // Similar al metodo anterior, pero añadiendo los IDs de todas las mutaciones de la lista

		if ( (*itm).first == ID){

			for (itl = ((*itm).second).begin(); itl != ((*itm).second).end(); itl++)
				ids.insert ((*(*itl)).getID());

		}

	}

	return ids;

}

clinvar::gen_iterator::gen_iterator(){     // Constructor vacio

}

clinvar::gen_iterator::gen_iterator(clinvar * p){    // Constructor con puntero a clinvar para inicializar los datos miembro

	ptrclinvar = p;
	itmap = (ptrclinvar->gen_map).begin();
	itlist = ((*itmap).second).begin();

}

const mutacion & clinvar::gen_iterator::operator*(){

	return (*(*itlist));

}

clinvar::gen_iterator & clinvar::gen_iterator::operator++(){

	if (itlist != ((*itmap).second).end())
		itlist++;

	else {       // Si itlist ya apunta al final de la lista, pasar a la siguiente lista del map

		itmap++;
		itlist = ((*itmap).second).begin();

	}

	return (*this);

}

clinvar::gen_iterator & clinvar::gen_iterator::operator++(int i){

	for (int c=0; c < i; c++){

		if (itlist != ((*itmap).second).end())
			itlist++;

		else {       // Si itlist ya apunta al final de la lista, pasar a la siguiente lista del map

			itmap++;
			itlist = ((*itmap).second).begin();

		}

	}

	return (*this);

}

map<IDgen, list< set<mutacion>::iterator> >::iterator clinvar::gen_iterator::getITmap(){

	return itmap;

}

list<set<mutacion>::iterator>::iterator clinvar::gen_iterator::getITlist(){

	return itlist;

}

bool clinvar::gen_iterator::operator != (gen_iterator oit){   // Para comparaciones en bucles for (ej: iter != a.gend())

	bool salida = true;

	if (itmap != oit.getITmap() && itlist != oit.getITlist())
		salida = false;

	return salida;

}

clinvar::enfermedad_iterator clinvar::ebegin(){

	enfermedad_iterator eit = EnfDB.begin();

	return eit;

}

clinvar::enfermedad_iterator clinvar::eend(){

	enfermedad_iterator eit = EnfDB.end();

	return eit;

}

clinvar::gen_iterator clinvar::gbegin(){

	clinvar::gen_iterator its (this);    // Apunta por defecto al inicio (constructor con puntero a clinvar de gen_iterator)

	return its;

}

clinvar::gen_iterator clinvar::gend(){

	clinvar::gen_iterator its (this);

	while ((its.getITmap()) != gen_map.end())     // Avanzar hasta el final
		its++;

	return its;

}

bool clinvar::ProbMutaciones::operator () (mutacion a, mutacion b){   // acceder al caf[0] de las mutaciones y comparar

	float pa = 1 - a.getCaf()[0];
	float pb = 1 - b.getCaf()[0];

	return ((pa >= pb) ? true : false);    // Operador ternario:     cond   ?   cierto  :  falso

}

set<mutacion, clinvar::ProbMutaciones> clinvar::topKMutaciones (int k, string keyword){

	set <mutacion, clinvar::ProbMutaciones> sset;
	priority_queue <mutacion, vector <mutacion>, ProbMutaciones> cola;
	map<IDenf,enfermedad>::iterator itm = EnfDB.begin();
	multimap<IDenf,set<mutacion>::iterator>::iterator itmm;
	unordered_set<IDmut> unset;

	int i = 0;

	while (itm != EnfDB.end() && i < k){    // No meter en la cola mas de k mutaciones

		if ((*itm).second.nameContains(keyword)){    // enfermedad con keyword en su nombre

			itmm = IDenf_map.find ((*itm).first);     // Para tener controlada cada mutacion asociada a dicha enfermedad (iterador al multimap)

			while (itmm != IDenf_map.end()){			// Comenzando por la posicion encontrada en el paso anterior, añadir a la cola
																// todas las mutaciones asociadas a dicha enfermedad
				if ((*itmm).first == (*itm).first)
					if (unset.insert((*((*itmm).second)).getID()).second) // comprobar que no esta ya insertada
						cola.push( *((*itmm).second));							// iterador de la mutacion asociada a la enfermedad
					

				itmm++;   // buscar siguiente mutacion para la misma enfermedad

			}

			i++;   // mutacion insertada, no pasar k

		}

		itm++;

	}

	while (itm != EnfDB.end()){      // igual que la estructura anterior, pero sin comprobar k

		if ((*itm).second.nameContains(keyword)){

			itmm = IDenf_map.find ((*itm).first);

			while (itmm != IDenf_map.end()){

				if ((*itmm).first == (*itm).first){

					if ( 1 - cola.top().getCaf()[0] < 1 - (*((*itmm).second)).getCaf()[0]){   // Comprobar probabilidad de cada mutacion con el
																													  // tope de la cola
						if (unset.insert((*((*itmm).second)).getID()).second){    // Si no estaba insertada

							unset.erase(cola.top().getID());    // sacar la del tope y añadir la nueva (la cola se reordena si es necesario)
							cola.pop();
							cola.push( *((*itmm).second));

						}

					}

				}

				itmm++;

			}

		}

		itm++;

	}

	while (!cola.empty()){     // pasar todas las mutaciones al set

		sset.insert(cola.top());
		cola.pop();
		

	}

	return sset;
}

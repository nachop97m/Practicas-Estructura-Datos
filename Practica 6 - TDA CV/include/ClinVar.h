/* 
 * ClinVar.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano
*/

#ifndef __CLINVAR_H
#define __CLINVAR_H

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <list>
#include <algorithm>
#include <utility>
#include <queue>
#include "enfermedad.h"
#include "mutacion.h"

using namespace std;

//los siguientes typedef permiten identificar en las cabeceras de los métodos
//cuando un string se refiere a un ID de gen, mutacion o enfermedad, respectivamente.
typedef string IDgen;
typedef string IDmut;
typedef string IDenf;

class clinvar{

	private:

	set<mutacion> mutDB; //base de datos que contiene toda la información asociada a una mutacion
	unordered_map<IDmut,set<mutacion>::iterator> IDm_map; // Asocia IDmutacion con mutación
	map<IDgen, list< set<mutacion>::iterator> > gen_map; // Asocia genes con mutaciones
	map<IDenf,enfermedad> EnfDB; // Base de datos de enfermedades
	multimap<IDenf,set<mutacion>::iterator> IDenf_map; // Asocia enfermedad con mutaciones

	public:

	class iterator;
	class gen_iterator;
	class ProbMutaciones;
	/* @brief iterador sobre enfermedades
	*/
	// Nos vale utilizar el iterador del map
	typedef map<IDenf, enfermedad>::iterator enfermedad_iterator;

	void load (string nombreDB);
	void insert (const mutacion & x);
	bool erase (IDmut ID);
	iterator find_Mut (IDmut ID);
	enfermedad_iterator find_Enf(IDenf ID);
	vector<enfermedad> getEnfermedades(mutacion & mut);
	list<IDenf> getEnfermedades(string keyword);
	set<IDmut> getMutacionesEnf (IDenf ID);
	set<IDmut> getMutacionesGen (IDgen ID);
	set<mutacion,ProbMutaciones> topKMutaciones (int k, string keyword);

	/* Métodos relacionados con los iteradores */
	iterator begin();
	iterator end();
	iterator lower_bound(string cromosoma, unsigned int posicion);
	iterator upper_bound(string cromosoma, unsigned int posicion);
	enfermedad_iterator ebegin();
	enfermedad_iterator eend();
	gen_iterator gbegin();
	gen_iterator gend();

	/* @brief iterador sobre mutaciones en orden creciente de cromosoma/posicion
	*/
	class iterator {

		private:
		set<mutacion>::iterator it;

		public:
		iterator();
		iterator(set<mutacion>::iterator its);
		iterator getIT();
		const mutacion & operator*();
		//const - no se puede modificar la mutacion y alterar el orden del set
		iterator & operator++();
		iterator & operator++(int i);
		bool operator != (iterator itt);

	};
	/* @brief iterador sobre mutaciones considerando el orden creciente del ID del gen
	*/

	class gen_iterator {

		public:
		gen_iterator();
		gen_iterator(clinvar * p);
		const mutacion & operator*();
		//const - no se puede modificar la mutacion y alterar el orden del set
		gen_iterator & operator++();
		gen_iterator & operator++(int i);
		bool operator != (gen_iterator oit);
		map<IDgen, list< set<mutacion>::iterator> >::iterator getITmap();
		list<set<mutacion>::iterator>::iterator getITlist();

		private:
		map<IDgen, list< set<mutacion>::iterator> >::iterator itmap;
		list<set<mutacion>::iterator>::iterator itlist;
		clinvar * ptrclinvar;
	};

	class ProbMutaciones {

		public:

		bool operator () (mutacion a, mutacion b);

	};

	private:

	friend class iterator;
	friend class gen_iterator;
	friend class ProbMutaciones;

};

#endif

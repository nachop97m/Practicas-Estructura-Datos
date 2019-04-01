/* 
 * principal.cpp
 * 
 * Copyright  (C) Ignacio Pineda Mochon -- Grado Ingenieria Informatica UGR
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <algorithm>
#include "ClinVar.h"

using namespace std;

int main (){

	clinvar database;

	database.load("clinvar_20160831.vcf");

	clinvar::iterator it;
	clinvar::gen_iterator itg;

	cout << "Mutaciones en orden creciente 'chr-pos': " << endl;
	for (it = database.begin(); it != database.end(); it++)
		cout << *it << endl;

	cout << "Mutaciones en orden creciente 'gen': " << endl;
	for (itg = database.gbegin(); itg != database.gend(); itg++)
		cout << *itg << endl;

	string key;
	cout << "Introduzca una enfermedad: " << endl;
	cin >> key;

	set<mutacion, clinvar::ProbMutaciones> sets = database.topKMutaciones (50, key);
	set<mutacion, clinvar::ProbMutaciones>::iterator itss = sets.begin();

	cout << "50 mutaciones mas probables para la enfermedad " << key << ": " << endl;

	for ( ; itss != sets.end(); itss++)
		cout << *itss << endl;

	return 0;

}

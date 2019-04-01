/**

*/
template <typename T, typename CMP>
conjunto<T,CMP>::conjunto (){

}

template <typename T, typename CMP>
conjunto<T,CMP>::conjunto (const conjunto<T,CMP> & d){

	(*this) = d;

}

template <typename T, typename CMP>
std::vector<mutacion> conjunto<T,CMP>::getVector() const{

	return vm;

}

//Find 1
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator  conjunto<T,CMP>::find (const conjunto<T,CMP>::value_type & e){

	conjunto<T,CMP>::value_type vt;
	bool encontrado = false;

	conjunto<T,CMP>::iterator it;

	for (it = vm.begin(); it != vm.end() && !encontrado; it++)
		if (*it == e)
			encontrado = true;

	return it;

}

//Find 2
template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator  conjunto<T,CMP>::find (const conjunto<T,CMP>::value_type & e) const {

	conjunto<T,CMP>::value_type vt;
	bool encontrado = false;

	conjunto<T,CMP>::const_iterator it;

	for (it = vm.cbegin(); it != vm.cend() && !encontrado; it++)
		if (*it == e)
			encontrado = true;

	return it;

}

//Count
template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type  conjunto<T,CMP>::count (const conjunto<T,CMP>::value_type & e) const {

	conjunto<T,CMP>::size_type st = 0;

	for (int i=0; i < vm.size() && st == 0; i++){

		if (vm[i] == e)
			st = 1;

	}

	return st;

}

//Insert 1
template <typename T, typename CMP>
pair<typename conjunto<T,CMP>::iterator,bool> conjunto<T,CMP>::insert( const conjunto<T,CMP>::value_type & e){

	bool modo = false;
	pair<typename conjunto<T,CMP>::iterator,bool> salida;

	for (typename conjunto<T,CMP>::iterator it = vm.begin(); it != vm.end() && !modo; ){

		if (comp(*it,e) )
			it++;

		else if (!comp(*it, e) && !comp(e,*it)){ // equivalentes segun CMP

			salida.first = vm.end();
			salida.second = false;
			modo = true;
		}

		else {

			salida.first = vm.insert(it, e);
			salida.second = modo = true;

		}

	} // del for

	if (!modo){
		salida.first = vm.insert(vm.end(),e);
		salida.second = true;
	}

	return salida;
}

//Insert 2
template <typename T, typename CMP>
pair<typename conjunto<T,CMP>::iterator,bool> conjunto<T,CMP>::insert(conjunto<T,CMP>::value_type & e){

	bool modo = false;
	pair<typename conjunto<T,CMP>::iterator,bool> salida;

	for (typename conjunto<T,CMP>::iterator it = vm.begin(); it != vm.end() && !modo; ){

		if (comp(*it,e) )
			it++;

		else if (!comp(*it, e) && !comp(e,*it)){ // equivalentes segun CMP

			salida.first = vm.end();
			salida.second = false;
			modo = true;
		}

		else {

			salida.first = vm.insert(it, e);
			salida.second = modo = true;

		}

	} // del for

	if (!modo){
		salida.first = vm.insert(vm.end(),e);
		salida.second = true;
	}

	return salida;
}

//erase 1
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::erase(const conjunto<T,CMP>::iterator position){

	conjunto<T,CMP>::iterator it = position;

	it = vm.erase(position);

	return it;
}

//erase 2
template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::erase(const conjunto<T,CMP>::value_type & val){

	conjunto<T,CMP>::iterator it;
	conjunto<T,CMP>::size_type borrados=0;

	for (it = vm.begin(); it < vm.end(); it++){

		if (*it == val){
			it = conjunto<T,CMP>::erase(it);
			borrados++;
		}
	}


	return borrados;
	
}

template <typename T, typename CMP>
void conjunto<T,CMP>::clear(){

	vm.clear();

}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::size() const {

	return vm.size();

}

template <typename T, typename CMP>
bool conjunto<T,CMP>::empty() const {

	return (size()==0);

}

template <typename T, typename CMP>
conjunto<T,CMP> & conjunto<T,CMP>::operator = (const conjunto<T,CMP> & org){

	if (&org != this){

		vm.clear();
		vm = org.getVector();

	}

	return (*this);

}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::begin(){

	return (vm.begin());

}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::end(){

	return (vm.end());

}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cbegin() const {
	
	return (vm.cbegin());

}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cend() const {

	return (vm.cend());

}

//lower_bound 1
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::lower_bound(const conjunto<T,CMP>::value_type & e){

	return std::lower_bound (conjunto<T,CMP>::begin(), conjunto<T,CMP>::end(), e);

}

//lower_bound 2
template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::lower_bound (const conjunto<T,CMP>::value_type & e) const {

	return std::lower_bound (conjunto<T,CMP>::cbegin(), conjunto<T,CMP>::cend(), e);

}

//upper_bound 1
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::upper_bound(const conjunto<T,CMP>::value_type & e){

	return std::upper_bound(conjunto<T,CMP>::begin(), conjunto<T,CMP>::end(), e);

}

//upper_bound 2
template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::upper_bound(const conjunto<T,CMP>::value_type & e) const {

	return std::upper_bound(conjunto<T,CMP>::cbegin(), conjunto<T,CMP>::cend(), e);

}

template <typename T, typename CMP>
bool conjunto<T,CMP>::cheq_rep() const {

	bool modo = false;
	
	string vect[]={"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "X", "Y", "MT" };
	vector<string> vector_chr(vect, vect+sizeof(vect)/sizeof(string));

	for (int i=0; i < vm.size() && !modo; i++)
		for (int j=0; j < vector_chr.size(); j++)
			if (vm[i].getChr() == vector_chr[j] && vm[i].getPos() > 0)
				modo = true;

	for (int i=0; i < (vm.size() - 1) && modo; i++){

		if ((vm[i]).getChr() == (vm[i+1]).getChr())
			if ( !((vm[i]).getPos() < (vm[i+1]).getPos()))
				modo = false;

	}

	for (int i=0; i < (vm.size() - 1) && modo; i++){

		if ((vm[i]).getChr() != (vm[i+1]).getChr())
			if ( !compare_chr( (vm[i]).getChr(), (vm[i+1]).getChr()) )
				modo = false;

	}

	return modo;

}

bool compare_chr (const string & chr1, const string & chr2){

	bool menor = false;

	const char x[] = "X";
	const char y[] = "Y";
	const char mt[] = "MT";

	const char * c_chr1 = chr1.c_str();  // Transformar el string en char *
	int num = atoi(c_chr1);             // Transformar el char * en int para la comparacion

	// Si chr = X, Y o MT, hay que tener cuidado a la hora de hacer la comparacion, pues num vale 0 con atoi en estos casos
	if (strcmp ( c_chr1, x) == 0)
		num = 23;

	else if (strcmp ( c_chr1, y) == 0)
		num = 24;

	else if (strcmp ( c_chr1, mt) == 0)
		num = 25;

	const char * c_chr2 = chr2.c_str();  // Transformar el string en char *
	int num2 = atoi(c_chr2);                    // Transformar el char * en int para la comparacion

	// Si m.chr = X, Y o MT, hay que tener cuidado a la hora de hacer la comparacion, pues num_m vale 0 con atoi en estos casos
	if (strcmp ( c_chr2, x) == 0)
		num2 = 23;

	else if (strcmp ( c_chr2, y) == 0)
		num2 = 24;

	else if (strcmp ( c_chr2, mt) == 0)
		num2 = 25;

	//Comparacion
	if (num < num2)
		menor=true;

	return menor;

}

template <typename T, typename CMP>
ostream &  operator << ( ostream & sal, const conjunto<T,CMP> & C){

	sal << "conjunto<T,CMP> ordenado de mutaciones:" << endl << endl;

	for (typename conjunto<T,CMP>::const_iterator it=C.cbegin(); it<C.cend(); it++){

		sal << *it << (((it+1) == C.cend()) ? ".\n" : " - ");

   }

	return sal;

}

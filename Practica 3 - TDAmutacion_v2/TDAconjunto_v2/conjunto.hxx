/**

*/

conjunto::conjunto (){

}

conjunto::conjunto (const conjunto &d){

	(*this) = d;

}

std::vector<mutacion> conjunto::getVector() const{

	return vm;

}

pair<conjunto::value_type,bool>  conjunto::find (const string & chr, const unsigned int & pos) const{

	conjunto::value_type vt;
	bool modo = false;

	for (int i =0; i < vm.size() && !modo; i++){

		if ((vm[i].getChr()==chr) && (vm[i].getPos()==pos)){

			vt = vm[i];
			modo = true;

		}

	}

	return std::make_pair(vt, modo);

}

pair<conjunto::value_type,bool>  conjunto::find2 (const string & chr) const{

	conjunto::value_type vt;
	bool modo = false;

	for (int i =0; i < vm.size() && !modo; i++){

		if ((vm[i]).getChr() == chr){

			vt = vm[i];
			modo = true;

		}

	}

	return std::make_pair (vt, modo);
}

pair<conjunto::value_type,bool> conjunto::find (const string & ID) const {

	conjunto::value_type vt;
	bool encontrado = false;

	for (int i=0; i < vm.size() && !encontrado; i++){

		if ((vm[i]).getID() == ID){

			vt = vm[i];
			encontrado = true;

		}

	}

	return std::make_pair (vt, encontrado);

}

pair<conjunto::value_type,bool>  conjunto::find (const conjunto::value_type & e) const {

	conjunto::value_type vt;
	bool encontrado = false;

	for (int i=0; i < vm.size() && !encontrado; i++){

		if (vm[i] == e){

			vt = e;
			encontrado = true;

		}

	}

	return std::make_pair (vt, encontrado);

}

conjunto::size_type  conjunto::count (const string & chr, const unsigned int & pos) const{

	conjunto::size_type st = 0;

	for (int i =0; i < vm.size() && st == 0; i++){

		if ((vm[i]).getChr() == chr && (vm[i]).getPos() == pos)
			st = 1;

	}

	return st;

}

conjunto::size_type conjunto::count (const string & ID) const {

	conjunto::size_type st = 0;

	for (int i=0; i < vm.size() && st == 0; i++){

		if ((vm[i]).getID() == ID)
			st = 1;

	}

	return st;

}

conjunto::size_type  conjunto::count (const conjunto::value_type & e) const {

	conjunto::size_type st = 0;

	for (int i=0; i < vm.size() && st == 0; i++){

		if (vm[i] == e)
			st = 1;

	}

	return st;

}

bool conjunto::insert( const conjunto::value_type & e){

	bool modo = false;

	if ( count(e.getChr(), e.getPos()) == 0 && count(e.getID()) == 0){

		vm.push_back(e);
		modo = true;

	}


	return modo;
}

bool conjunto::erase(const string & chr,const unsigned int &pos){
	
	bool modo = false;

	if (count(chr,pos)){

		int i = 0;

		for ( ;i < vm.size() && !modo ;i++){

			if (vm[i].getChr()==chr && vm[i].getPos()==pos)
				modo=true;	
		

		}
	
		iterator it = vm.begin()+i;
		vm.erase(it);

	}

	return modo;

}

bool conjunto::erase(const string & ID){

	bool salida = false;

	if ((count (ID))){

		int i=0;

		for ( ; i < vm.size() && !salida; i++){

			if ((vm[i]).getID() == ID)			
				salida = true;

		}

		iterator it = vm.begin()+i;
		vm.erase(it);

	}

	return salida;

}

bool conjunto::erase(const conjunto::value_type & e){

	bool salida = false;

	if ((count(e))){

		int i=0;

		for ( ; i < vm.size() && !salida; i++){

			if ((vm[i]).getID() == e.getID())
				salida = true;

		}

		iterator it = vm.begin()+i;
		vm.erase(it);

	}

	return salida;

}

void conjunto::clear(){

	vm.clear();

}

conjunto::size_type conjunto::size() const {

	return vm.size();

}

bool conjunto::empty() const {

	return (size()==0);

}

conjunto & conjunto::operator = (const conjunto & org){

	if (&org != this){

		vm.clear();
		vm = org.getVector();

	}

	return (*this);

}

conjunto::iterator conjunto::begin(){

	return (vm.begin());

}

conjunto::iterator conjunto::end(){

	return (vm.end());

}

conjunto::const_iterator conjunto::cbegin() const {
	
	return (vm.begin());

}

conjunto::const_iterator conjunto::cend() const {

	return (vm.end());

}

conjunto::iterator conjunto::lower_bound(const string & chr, const unsigned int & pos){

	pair <conjunto::value_type, bool> par = find (chr, pos);

	iterator it = std::lower_bound(conjunto::begin(), conjunto::end(),par.first);

	return it;

}

conjunto::iterator conjunto::lower_bound2(const string & chr){

	pair <conjunto::value_type, bool> par = find2 (chr);

	iterator it = std::lower_bound(conjunto::begin(), conjunto::end(),par.first);

	return it;

}

conjunto::iterator conjunto::lower_bound(const conjunto::value_type & e){

	iterator it = std::lower_bound (conjunto::begin(), conjunto::end(), e);

	return it;

}

conjunto::iterator conjunto::upper_bound(const string & chr, const unsigned int & pos){

	pair <conjunto::value_type, bool> par = find (chr, pos);

	iterator it = std::upper_bound(conjunto::begin(), conjunto::end(), par.first);

	return it;

}

conjunto::iterator conjunto::upper_bound(const conjunto::value_type & e){

	iterator it = std::upper_bound(conjunto::begin(), conjunto::end(),e);
	
	return it;

}

bool conjunto::cheq_rep() const {

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

ostream &  operator << ( ostream & sal, const conjunto & C){

	sal << "Conjunto ordenado de mutaciones:" << endl << endl;

	for (conjunto::const_iterator it=C.cbegin(); it<C.cend(); it++){

		sal << *it << (((it+1) == C.cend()) ? ".\n" : " - ");

   }

	return sal;

}


//Constructor vacio
template <typename T, class CMP>
conjunto < T,CMP >::conjunto (){

}


//Constructor de copia
template <typename T, class CMP>
conjunto < T,CMP >::conjunto(const conjunto<T,CMP> &d){

	(*this)=d;

}

//find 
template <typename T, class CMP>
typename conjunto < T,CMP >::iterator conjunto < T,CMP >::find (const conjunto < T,CMP >::value_type & s){

	conjunto < T,CMP >::iterator it;
	bool encontrado = false;
	

	for (it=vm.begin(); it < vm.end() && !encontrado; it++){

		if (*it == s){

			
			encontrado = true;

		}

	}

	return it;

}

//find const
template <typename T, class CMP>
typename conjunto < T,CMP >::const_iterator conjunto < T,CMP >::find(const conjunto < T,CMP >::value_type &s)const{

	conjunto < T,CMP >::const_iterator it;
	bool encontrado=false;

	for (it=vm.cbegin();it<vm.cend();it++)
		if (*it==s)
			encontrado=true;



	return it;



}


//count 
template <typename T, class CMP>
typename conjunto < T,CMP >::size_type  conjunto < T,CMP >::count (const conjunto < T,CMP >::value_type & e) const {

	conjunto < T,CMP >::size_type st;

	for (int i=0; i < vm.size() && st !=0; i++){

		if (vm[i] == e)
			st = 1;

	}

	return st;

}
/*
//ordenar
template <typename T, class CMP>
void conjunto < T,CMP >::ordenar(){


	std::sort(vm.begin(),vm.end());
}
*/



//insert 1
template <typename T, class CMP>
pair<typename conjunto < T,CMP >::iterator,bool> conjunto < T,CMP >::insert( const conjunto < T,CMP >::value_type & e){

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
//insert 2
template <typename T, class CMP>
pair<typename conjunto < T,CMP >::iterator,bool> conjunto < T,CMP >::insert(conjunto < T,CMP >::value_type & e){

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
template <typename T, class CMP>
typename conjunto < T,CMP >::iterator conjunto < T,CMP >::erase(const conjunto < T,CMP >::iterator position){

	conjunto < T,CMP >::iterator it;

	it=vm.erase(position);
	
	
	return it;
}




//erase 2
template <typename T, class CMP>
typename conjunto < T,CMP >::size_type conjunto < T,CMP >::erase(const conjunto < T,CMP >::value_type & val){

	conjunto < T,CMP >::iterator it;
	conjunto < T,CMP >::size_type borrados=0;

	for (it=vm.begin();it<vm.end() ;it++){
		
		if (*it == val){
			erase(it);
			borrados++;
		}
	}


	return borrados;
	
}

//clear
template <typename T, class CMP>
void conjunto < T,CMP >::clear(){

	vm.clear();

}





//size
template <typename T, class CMP>
typename conjunto < T,CMP >::size_type conjunto < T,CMP >::size() const {

	return vm.size();

}



//empty
template <typename T, class CMP>
bool conjunto < T,CMP >::empty() const {

	return (size()==0);

}

//Sobrecarga de " = "
template <typename T, class CMP>
conjunto < T,CMP > & conjunto< T,CMP >::operator=(const conjunto & org){

	if (&org != this){
		vm.clear();
		vm=org.getVector();

	}


	return (*this);
		


}

//iterator begin
template <typename T, class CMP>
iterator conjunto < T,CMP >::begin(){

	return vm.begin();


}


//iterator end
template <typename T, class CMP>
iterator conjunto < T,CMP >::end () {

	return (vm.end());

}

//iterator begin const
template <typename T, class CMP>
const_iterator conjunto < T,CMP >::cbegin()const{
	
	return vm.cbegin();


}


//iterator end const
template <typename T, class CMP>
const_iterator conjunto < T,CMP >::cend() const {

	return (vm.cend());

}

//sbegin
template <typename T, class CMP>
typename conjunto < T,CMP >::secure_iterator conjunto < T,CMP >::sbegin(){

	assert (begin() != NULL);

	secure_iterator it = begin();

	return it;

}

//csbegin
template <typename T, class CMP>
typename conjunto < T,CMP >::const_secure_iterator conjunto < T,CMP >::csbegin() const{

	assert (begin() != NULL);

	const_secure_iterator it = cbegin();

	return it;

}


//send
template <typename T,class CMP>
typename conjunto <T,CMP >::secure_iterator conjunto <T,CMP>::send(){

	assert (end()!=NULL);
	
	secure_iterator it = end();

	return it;
	
}

//csend
template <typename T,class CMP>
typename conjunto <T,CMP>::const_secure_iterator conjunto<T,CMP>::csend() const {

	assert (cend()!=NULL);
	
	const_secure_iterator it = cend();

	return it;


}

// ibegin
template <typename T,class CMP>
typename conjunto <T,CMP >::impar_iterator conjunto <T,CMP>::ibegin(){

	conjunto <T,CMP>::iterator it;
	for (it = begin(); it != end(); it++){

		if ((*it).getPos() % 2 != 0)
			break;

	}

	impar_iterator iit = it;

	return iit;

}

//cibegin
template <typename T,class CMP>
typename conjunto <T,CMP> ::const_impar_iterator conjunto<T,CMP> :: cibegin()const{

	conjunto < T,CMP >::iterator it;

	for (it = cbegin(); it != cend(); it++){

		if ((*it).getPos() %2 != 0)
			break;

	}

	const_impar_iterator cit=it;

	return cit;


}

// iend
template <typename T,class CMP>
typename conjunto <T,CMP >::impar_iterator conjunto <T,CMP>::iend(){

	conjunto <T,CMP>::iterator it;
	for (it = end()-1; it >= begin(); it--){

		if ((*it).getPos() % 2 != 0)
			break;

	}

	it++;

	impar_iterator iit = it;

	return iit;

}

//ciend
template <typename T,class CMP>
typename conjunto <T,CMP>::const_impar_iterator conjunto<T,CMP>::ciend()const{

	conjunto <T,CMP>::iterator it;
	
	for (it=cend-1;it<=cbegin();it--){

		if((*it).getPos()%2!=0)
			break;

	}

	const_impar_iterator cit=it++;

	return cit;

}

//lower_bound 1
template <typename T, class CMP>
typename conjunto < T,CMP >::iterator conjunto < T,CMP >::lower_bound(const conjunto < T,CMP >::value_type & e){

	return std::lower_bound (conjunto < T,CMP >::begin(), conjunto < T,CMP >::end(), e);

}


//lower_bound 2
template <typename T, class CMP>
typename conjunto < T,CMP >::const_iterator conjunto < T,CMP >::lower_bound (const conjunto < T,CMP >::value_type & e) const {

	return std::lower_bound (conjunto < T,CMP >::cbegin(), conjunto < T,CMP >::cend(), e);

}


//upper_bound 1
template <typename T, class CMP>
typename conjunto < T,CMP >::iterator conjunto < T,CMP >::upper_bound(const conjunto < T,CMP >::value_type & val){


	return std::upper_bound (conjunto < T,CMP >::begin(), conjunto < T,CMP >::end(),val);

	

}

//upper_bound 2
template <typename T, class CMP>
typename conjunto < T,CMP >::const_iterator conjunto < T,CMP >::upper_bound(const conjunto < T,CMP >::value_type & val)const{

	
	return std::upper_bound(conjunto < T,CMP >::cbegin(),conjunto < T,CMP >::cend(),val);

}

// class iterator

// constructor vacio
template <typename T, class CMP>
conjunto <T,CMP>::iterator::iterator(){

	elvector = &vm;

}

// constructor de copia
template <typename T, class CMP>
conjunto <T,CMP>::iterator::iterator(const iterator & x){

	if (this != x){

		this->elvector = x.elvector;

	}

}

// constructor: Transforma secure_iterator en iterator
template <typename T, class CMP>
conjunto <T,CMP>::iterator::iterator(const secure_iterator & x){

	this->elvector = x.elvector;

}

// operator *
template <typename T, class CMP>
const T & conjunto <T,CMP>::iterator::operator *(){

	const T dato = *elvector;

	return dato;

}

// operator ++
template <typename T, class CMP>
typename conjunto <T,CMP>::iterator & conjunto <T,CMP>::iterator::operator++(){

	return (elvector++);

}

// operator ++ i
template <typename T, class CMP>
typename conjunto <T,CMP>::iterator conjunto <T,CMP>::iterator::operator++(int i){

	return (elvector = elvector + i);

}

// operator --
template <typename T,class CMP>
typename conjunto <T,CMP>::iterator & conjunto <T,CMP>::iterator::operator--(){

	return (elvector--);

}

//operator -- i
template <typename T, class CMP>
typename conjunto <T,CMP>::iterator conjunto <T,CMP>::iterator::operator--(int i){

	return (elvector = elvector - i);

}

// operator ==
template <typename T,class CMP>
bool conjunto <T,CMP>::iterator::operator==(const iterator & x) const {

	return (this->elvector == x.elvector);

}

// operator !=
template <typename T,class CMP>
bool conjunto <T,CMP>::iterator::operator!=(const iterator & x) const {

	return (!(this == x));

}

//operator =
template <typename T,class CMP>
typename conjunto <T,CMP>::iterator & conjunto <T,CMP>::iterator::operator =(const iterator &x ){

	this->elvector = x.elvector;

	return (this);

}


// class secure_iterator

// constructor vacio
template <typename T, class CMP>
conjunto <T,CMP>::secure_iterator::secure_iterator(){

	elvector = &vm;

}

// constructor de copia
template <typename T, class CMP>
conjunto <T,CMP>::secure_iterator::secure_iterator(const secure_iterator &  x){

	if (this != x){

		this->elvector = x.elvector;

	}

}

// operator ++
template <typename T, class CMP>
typename conjunto <T,CMP>::secure_iterator & conjunto <T,CMP>::secure_iterator::operator++(){

	typename conjunto <T,CMP>::iterator::it aux = elvector + 1;
	typename conjunto <T,CMP>::iterator::it aux2 = vm.end();

	assert (aux <= aux2);

	elvector++;

	return (elvector);

}

// operator ++ i
template <typename T, class CMP>
typename conjunto <T,CMP>::secure_iterator conjunto <T,CMP>::secure_iterator::operator++(int i){

	typename conjunto <T,CMP>::iterator::it aux = elvector + i;
	typename conjunto <T,CMP>::iterator::it aux2 = vm.end();

	assert (aux <= aux2);

	elvector = elvector + i;

	return (elvector);

}

//operator --
template <typename T,class CMP>
typename conjunto <T,CMP>::secure_iterator & conjunto<T,CMP>::secure_iterator::operator--(){
	
	typename conjunto <T,CMP>::iterator::it aux = elvector;
	aux--;
	typename conjunto <T,CMP>::iterator::it aux2 = vm.begin();

	assert (aux >= aux2);
	elvector--;

	return elvector;

}

//operator -- i veces
template <typename T,class CMP>
typename conjunto <T,CMP>::secure_iterator conjunto<T,CMP>::secure_iterator::operator--(int i ){

	typename conjunto <T,CMP>::iterator::it aux = elvector;
	aux = aux - i;
	typename conjunto <T,CMP>::iterator::it aux2 = vm.begin();

	assert (aux >= aux2);
	elvector = elvector-i;

	return elvector;

}

// operator ==
template <typename T,class CMP>
bool conjunto <T,CMP>::secure_iterator::operator==(const secure_iterator & x) const {

	return (this->elvector == x.elvector);

}

// operator !=
template <typename T,class CMP>
bool conjunto <T,CMP>::secure_iterator::operator!=(const secure_iterator & x) const {

	return (!(this == x));

}

//operator =
template <typename T,class CMP>
typename conjunto <T,CMP>::secure_iterator & conjunto <T,CMP>::secure_iterator::operator =(const secure_iterator &x ){

	this->elvector = x.elvector;

	return (this);

}

// class impar_iterator

// constructor vacio
template <typename T, class CMP>
conjunto <T,CMP>::impar_iterator::impar_iterator(){

	elvector = &vm;

}

// constructor de copia
template <typename T, class CMP>
conjunto <T,CMP>::impar_iterator::impar_iterator(const impar_iterator &  x){

	if (this != x){

		this->elvector = x.elvector;

	}

}

// operator ++
template <typename T, class CMP>
typename conjunto <T,CMP>::impar_iterator & conjunto <T,CMP>::impar_iterator::operator++(){

	typename conjunto <T,CMP>::iterator::it aux = elvector + 2;
	typename conjunto <T,CMP>::iterator::it aux2 = vm.end();

	assert (aux <= aux2);

	elvector=elvector+2;

	return (elvector);

}

// operator ++ i
template <typename T, class CMP>
typename conjunto <T,CMP>::impar_iterator conjunto <T,CMP>::impar_iterator::operator++(int i){

	typename conjunto <T,CMP>::iterator::it aux = elvector + (2*i);
	typename conjunto <T,CMP>::iterator::it aux2 = vm.end();

	assert (aux <= aux2);

	elvector = elvector + (i*2);

	return (elvector);

}

// operator ==
template <typename T,class CMP>
bool conjunto <T,CMP>::impar_iterator::operator==(const impar_iterator & x) const {

	return (this->elvector == x.elvector);

}

// operator !=
template <typename T,class CMP>
bool conjunto <T,CMP>::impar_iterator::operator!=(const impar_iterator & x) const {

	return (!(this == x));

}

//operator =
template <typename T,class CMP>
typename conjunto <T,CMP>::impar_iterator & conjunto <T,CMP>::impar_iterator::operator =(const impar_iterator &x ){

	this->elvector = x.elvector;

	return (this);

}


// class const_iterator

// constructor vacio
template <typename T, class CMP>
conjunto <T,CMP>::const_iterator::const_iterator(){

	elvector = &vm;

}

// constructor de copia
template <typename T, class CMP>
conjunto <T,CMP>::const_iterator::const_iterator(const const_iterator & x){

	if (this != x){

		this->elvector = x.elvector;

	}

}

// constructor: Transforma secure_iterator en iterator
template <typename T, class CMP>
conjunto <T,CMP>::const_iterator::const_iterator(const const_secure_iterator & x){

	this->elvector = x.elvector;

}

// operator *
template <typename T, class CMP>
const T & conjunto <T,CMP>::const_iterator::operator *(){

	const T dato = *elvector;

	return dato;

}

// operator ++
template <typename T, class CMP>
typename conjunto <T,CMP>::const_iterator & conjunto <T,CMP>::const_iterator::operator++(){

	return (elvector++);

}

// operator ++ i
template <typename T, class CMP>
typename conjunto <T,CMP>::const_iterator conjunto <T,CMP>::const_iterator::operator++(int i){

	return (elvector = elvector + i);

}

// operator --
template <typename T,class CMP>
typename conjunto <T,CMP>::const_iterator & conjunto <T,CMP>::const_iterator::operator--(){

	return (elvector--);

}

//operator -- i
template <typename T, class CMP>
typename conjunto <T,CMP>::const_iterator conjunto <T,CMP>::const_iterator::operator--(int i){

	return (elvector = elvector - i);

}

// operator ==
template <typename T,class CMP>
bool conjunto <T,CMP>::const_iterator::operator==(const const_iterator & x) const {

	return (this->elvector == x.elvector);

}

// operator !=
template <typename T,class CMP>
bool conjunto <T,CMP>::const_iterator::operator!=(const const_iterator & x) const {

	return (!(this == x));

}

//operator =
template <typename T,class CMP>
typename conjunto <T,CMP>::const_iterator & conjunto <T,CMP>::const_iterator::operator =(const const_iterator &x ){

	this->elvector = x.elvector;

	return (this);

}


// class const_secure_iterator

// constructor vacio
template <typename T, class CMP>
conjunto <T,CMP>::const_secure_iterator::const_secure_iterator(){

	elvector = &vm;

}

// constructor de copia
template <typename T, class CMP>
conjunto <T,CMP>::const_secure_iterator::const_secure_iterator(const const_secure_iterator &  x){

	if (this != x){

		this->elvector = x.elvector;

	}

}

// operator ++
template <typename T, class CMP>
typename conjunto <T,CMP>::const_secure_iterator & conjunto <T,CMP>::const_secure_iterator::operator++(){

	typename conjunto <T,CMP>::iterator::it aux = elvector + 1;
	typename conjunto <T,CMP>::iterator::it aux2 = vm.end();

	assert (aux <= aux2);

	elvector++;

	return (elvector);

}

// operator ++ i
template <typename T, class CMP>
typename conjunto <T,CMP>::const_secure_iterator conjunto <T,CMP>::const_secure_iterator::operator++(int i){

	typename conjunto <T,CMP>::iterator::it aux = elvector + i;
	typename conjunto <T,CMP>::iterator::it aux2 = vm.end();

	assert (aux <= aux2);

	elvector = elvector + i;

	return (elvector);

}

//operator --
template <typename T,class CMP>
typename conjunto <T,CMP>::const_secure_iterator & conjunto<T,CMP>::const_secure_iterator::operator--(){
	
	typename conjunto <T,CMP>::iterator::it aux = elvector;
	aux--;
	typename conjunto <T,CMP>::iterator::it aux2 = vm.begin();

	assert (aux >= aux2);
	elvector--;

	return elvector;

}

//operator -- i veces
template <typename T,class CMP>
typename conjunto <T,CMP>::const_secure_iterator conjunto<T,CMP>::const_secure_iterator::operator--(int i ){

	typename conjunto <T,CMP>::iterator::it aux = elvector;
	aux = aux - i;
	typename conjunto <T,CMP>::iterator::it aux2 = vm.begin();

	assert (aux >= aux2);
	elvector = elvector-i;

	return elvector;

}

// operator ==
template <typename T,class CMP>
bool conjunto <T,CMP>::const_secure_iterator::operator==(const const_secure_iterator & x) const {

	return (this->elvector == x.elvector);

}

// operator !=
template <typename T,class CMP>
bool conjunto <T,CMP>::const_secure_iterator::operator!=(const const_secure_iterator & x) const {

	return (!(this == x));

}

//operator =
template <typename T,class CMP>
typename conjunto <T,CMP>::const_secure_iterator & conjunto <T,CMP>::const_secure_iterator::operator =(const const_secure_iterator &x ){

	this->elvector = x.elvector;

	return (this);

}

// class const_impar_iterator

// constructor vacio
template <typename T, class CMP>
conjunto <T,CMP>::const_impar_iterator::const_impar_iterator(){

	elvector = &vm;

}

// constructor de copia
template <typename T, class CMP>
conjunto <T,CMP>::const_impar_iterator::const_impar_iterator(const const_impar_iterator &  x){

	if (this != x){

		this->elvector = x.elvector;

	}

}

// operator ++
template <typename T, class CMP>
typename conjunto <T,CMP>::const_impar_iterator & conjunto <T,CMP>::const_impar_iterator::operator++(){

	typename conjunto <T,CMP>::iterator::it aux = elvector + 2;
	typename conjunto <T,CMP>::iterator::it aux2 = vm.end();

	assert (aux <= aux2);

	elvector=elvector+2;

	return (elvector);

}

// operator ++ i
template <typename T, class CMP>
typename conjunto <T,CMP>::const_impar_iterator conjunto <T,CMP>::const_impar_iterator::operator++(int i){

	typename conjunto <T,CMP>::iterator::it aux = elvector + (2*i);
	typename conjunto <T,CMP>::iterator::it aux2 = vm.end();

	assert (aux <= aux2);

	elvector = elvector + (i*2);

	return (elvector);

}

// operator ==
template <typename T,class CMP>
bool conjunto <T,CMP>::const_impar_iterator::operator==(const const_impar_iterator & x) const {

	return (this->elvector == x.elvector);

}

// operator !=
template <typename T,class CMP>
bool conjunto <T,CMP>::const_impar_iterator::operator!=(const const_impar_iterator & x) const {

	return (!(this == x));

}

//operator =
template <typename T,class CMP>
typename conjunto <T,CMP>::const_impar_iterator & conjunto <T,CMP>::const_impar_iterator::operator =(const const_impar_iterator &x ){

	this->elvector = x.elvector;

	return (this);

}

bool compare_chr(const string & chr1, const string & chr2){

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


//invariante de representacion
template <typename T, class CMP>
bool conjunto < T,CMP >::cheq_rep()const{
	bool modo=false;
	 
	
	string vec[]={"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "X", "Y", "MT" };
	vector<string> vector_chr(vec,vec+25);

	for(int i =0;i<vm.size() && !modo ;i++)
		for (int j =0;j<vector_chr.size();j++)
			if (vm[i].getChr() == vector_chr[j] && vm[i].getPos() > 0)
				modo= true;


          

	for (int i=0; i < (vm.size() - 1) && !modo; i++){

		if ((vm[i]).getChr() == (vm[i+1]).getChr())
			if ( !((vm[i]).getPos() < (vm[i+1]).getPos()))
				modo = false;

	}

	for (int i=0; i < (vm.size() - 1) && !modo; i++){

		if ((vm[i]).getChr() != (vm[i+1]).getChr())
			if (!compare_chr( (vm[i]).getChr(), (vm[i+1]).getChr()) )
				modo = false;

	}

	return modo;

}








//flujo de salida
template <typename T, class CMP>
ostream &  operator << ( ostream & sal, const conjunto<T,CMP> & C){

	sal << "conjunto<T,CMP> ordenado de mutaciones:" << endl << endl;

	for (typename conjunto<T,CMP>::const_iterator it=C.cbegin(); it<C.cend(); it++){

		sal << *it << (((it+1) == C.cend()) ? ".\n" : " - ");

   }

	return sal;

}










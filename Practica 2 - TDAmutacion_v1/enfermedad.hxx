/** @brief fichero de implementacion de la clase enfermedad

*/

enfermedad::enfermedad(){

	this->name = "";
	this->ID = "";
	this->database = "";

}

enfermedad::enfermedad(const string & name, const string & ID, const string & database){

	this->name = name;
	this->ID = ID;
	this->database = database;

}

void enfermedad::setName(const string & name){
	this->name = name;

}
void enfermedad::setID(const string & ID){
	this->ID=ID;

}
void enfermedad::setDatabase(const string & database){
	this->database=database;

}

string enfermedad::getName()const{

	return this->name;

}

string enfermedad::getID( )const{

	return this->ID;

}

string enfermedad::getDatabase( )const{

	return this->database;

}

enfermedad & enfermedad::operator = (const enfermedad & e){

	this->name = e.getName();
	this->ID = e.getID();
	this->database = e.getDatabase();

	return (*this);
}

string enfermedad::toString() const {

	string cadena = "Nombre: " + name + " -- ID: " + ID + " -- Database: " + database;

	return cadena;

}

bool enfermedad::operator == (const enfermedad & e) const{

	bool iguales = false;

	if (name == e.getName())
		if (ID == e.getID())
			if(database == e.getDatabase())
				iguales = true;

	return iguales;

}

bool enfermedad::operator != (const enfermedad & e) const{

	return (!((*this)==e));

}

bool enfermedad::operator < (const enfermedad & e) const {

	bool menor = false;

	if (name != e.getName()){

		int length = ((e.getName()).length());

		if (name.length() < length)
			length = name.length();

		for (int i=0; i < length && !menor; i++){

			if (name[i] < ((e.getName())[i]))
				menor = true;

		}
	}

	return menor;

}

bool enfermedad::nameContains(const string & str) const {

	bool contiene = true;
	size_t found = name.find(str);

	if (found == string::npos)
		contiene = false;

	return contiene;

}

ostream & operator << ( ostream & os, const enfermedad & e){

	os << "Nombre enfermedad: " << e.getName() << endl;
	os << "ID enfermedad: " << e.getID() << endl;
	os << "Database: " << e.getDatabase() << endl;

	return os;
}

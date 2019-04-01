/** @brief fichero de implementacion de la clase enfermedad

*/

enfermedad::enfermedad(){
	name="";
	ID="";
	database="";
}

enfermedad::enfermedad(const string & name, const string & ID, const string & database){
	this->name=name;
	this->ID=ID;
	this->database=database;
}
  
// @todo implementar el resto de métodos especificados en enfermedad.h  

void enfermedad::setName(const string & name){
	this->name = name;

}
void  enfermedad:: setID(const string & ID){
	this->ID=ID;

}
void enfermedad:: setDatabase(const string & database){
	this->database=database;

}

string enfermedad:: getName( )const{

	return name;

}

string enfermedad:: getID( )const{

	return ID;

}

string enfermedad:: getDatabase( )const{

	return database;

}

enfermedad & enfermedad :: operator =(const enfermedad &p){
	
	if (&p != this){
		this->name=p.name;
		this->ID=p.ID;
        	this->database= p.database;
    	}
    return *this;

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

bool enfermedad::operator < (const enfermedad & e) const {

	bool menor = false;
	bool aux = false;

	if (name != e.getName()){

		int length = name.length();

		if ( ((e.getName()).length()) >= length)
			aux = true;

		for (int i=0; i < length && i < ((e.getName()).length()) && !menor; i++){

			if (name[i] < ((e.getName())[i]))
				menor = true;

		}

		if (aux && !menor)
			menor = true;

	}

	return menor;

}

bool enfermedad::nameContains(const string &str)const{
	size_t found;
	bool modo;
	found = name.find(str);
	if (found == string::npos)
		modo = false;
	else
		modo = true;

	return modo;

}


 
ostream& operator<< ( ostream& os, const enfermedad & e){
	os << "\nNombre de la enfermedad " <<e.getName();
	os << "\nID de la enfermedad " << e.getID();
	os << "\nBase de datos que provee el ID " << e.getDatabase();
	os << endl;
	
	
   return os;

}
   
   
 

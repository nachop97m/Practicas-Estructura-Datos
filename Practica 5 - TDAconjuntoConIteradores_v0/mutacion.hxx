




mutacion::mutacion(){
	ID = "";
	chr="";
	pos=0;
}


mutacion::mutacion(const mutacion& m){

	(*this) = m;

}

mutacion::mutacion(const string & str){

	int i=0;

	// Lectura CHR

	while (str[i] != '\t'){

		chr.push_back (str[i]);
		i++;

	}

	i++;

	// Lectura POS

	string cad_pos;

	while (str[i] != '\t'){

		cad_pos.push_back (str[i]);
		i++;

	}

	pos = atoi(cad_pos.c_str());

	i++;

	//Lectura ID

	while (str[i] != '\t'){

		ID.push_back (str[i]);
		i++;

	}

	i++;
	
	// Lectura Ref_alt

	while (str[i] != '\t'){

		string cad_ref_alt;
		cad_ref_alt.push_back (str[i]);
		ref_alt.push_back (cad_ref_alt);
		i++;

	}

	i++;

	while (str[i] != '\t'){

		while (str[i] != ',' && str[i] != '\t'){

			string cad_ref_alt;
			cad_ref_alt.push_back (str[i]);
			ref_alt.push_back (cad_ref_alt);
			i++;

		}

		if (str[i] != '\t')
			i++;

	}
	
	// Lectura genes

	const string cad_genes = "GENEINFO=";
	string cad_genes_valor="";
	i = str.find (cad_genes);
	i += 9;
	
	
	while (str[i] != ';'){

		while (str[i] != '|' && str[i] != ';'){

			cad_genes_valor.push_back (str[i]);
			i++;

		}

		genes.push_back (cad_genes_valor);
		cad_genes_valor = "";

		if (str[i] != ';')
			i++;

	}
	// Lectura common

	const string cad_common = "COMMON=";

	if (str.find (cad_common) != string::npos){

		i = str.find (cad_common);
		i += 7;
		common = str[i];

	}

	else               // En algunas lineas no existe el campo COMMON
		common = 0;

	// Lectura caf

	const string cad_caf = "CAF=";
	string cad_caf_valores;

	if (str.find (cad_caf) != string::npos){

		i = str.find (cad_caf);
		i += 4;

		while (str[i] != ';'){

			while (str[i] != ',' && str[i] != ';'){

				cad_caf_valores.push_back (str[i]);
				i++;

			}

			caf.push_back (atoi(cad_caf_valores.c_str()));
			cad_caf_valores = "";

			if (str[i] != ';')
				i++;

		}
	}

	// Lectura CLNSIG

	const string cad_cln = "CLNSIG=";

	i = str.find (cad_cln);
	i += 7;

	while (str[i] != ';'){

		while (str[i] != '|' && str[i] != ';'){

			clnsig.push_back (str[i]);
			i++;

		}

		if (str[i] != ';')
			i++;

	}

	// Datos enfermedad

	for (int j=0; j < clnsig.size(); j++){  // Puede haber mas de una enfermedad en cada linea

		const string cad_cln_db = "CLNDSDB=";
		const string cad_cln_id = "CLNDSDBID=";
		const string cad_cln_n = "CLNDBN=";

		string n, id, db;   // Atributos de la enfermedad a leer

		// Database enfermedad

		i = str.find (cad_cln_db);    // Buscar primer atributo de la enfermedad
		i += 8;

		for (int k=0; k < j; k++){    // Controlar si es la primera, segunda, tercera... enfermedad de la misma linea

			while (str[i] != '|' && str[i] != ';')
				i++;

		}

		while (str[i] != '|' && str[i] != ';'){

			db.push_back (str[i]);
			i++;

		}

		// ID enfermedad

		i = str.find (cad_cln_id);    // Buscar primer atributo de la enfermedad
		i += 10;

		for (int k=0; k < j; k++){    // Controlar si es la primera, segunda, tercera... enfermedad de la misma linea

			while (str[i] != '|' && str[i] != ';')
				i++;

		}

		while (str[i] != '|' && str[i] != ';'){

			id.push_back (str[i]);
			i++;

		}

		// Name enfermedad

		i = str.find (cad_cln_n);    // Buscar primer atributo de la enfermedad
		i += 7;

		for (int k=0; k < j; k++){    // Controlar si es la primera, segunda, tercera... enfermedad de la misma linea

			while (str[i] != '|' && str[i] != ';')
				i++;

		}

		while (str[i] != '|' && str[i] != ';'){

			n.push_back (str[i]);
			i++;

		}

		enfermedad enf (n, id, db);   // Crear enfermedad con los datos leidos
		enfermedades.push_back (enf);	// Añadir la enfermedad al vector de enfermedades

	}

}
	
	

void mutacion::setID(const string & id){
	ID=id;


}
void mutacion::setChr(const string & chr1){
	chr=chr1;

}
void mutacion::setPos(const unsigned int & pos1){
	pos =pos1;


}
void mutacion::setRef_alt(const std::vector<string> & ref_alt1){
	ref_alt=ref_alt1;


}
void mutacion::setGenes (const std::vector<string> & genes1){

	genes = genes1;

}

void mutacion::setCommon (const bool & common1){

	common = common1;

}

void mutacion::setCaf (const std::vector<float> & caf1){

	caf = caf1;

}

void mutacion::setEnfermedades (const std::vector<enfermedad> & enfermedades1){

	enfermedades = enfermedades1;

}

void mutacion::setClnsig (const std::vector<int> & clnsig1){

	clnsig = clnsig1;

}


string mutacion::getID( ) const{
	return ID;

}

string mutacion::getChr( ) const{
	return chr;


}
unsigned int mutacion::getPos( ) const{
	return pos;


}
const std::vector<string> & mutacion::getRef_alt () const{
	return ref_alt;


}
const std::vector<string> & mutacion::getGenes () const{
	return genes;

}
bool mutacion::getCommon () const{

	return common;

}

const std::vector<float> & mutacion::getCaf () const{

	return caf;

}

const std::vector<enfermedad> & mutacion::getEnfermedades () const{

	return enfermedades;

}

const std::vector<int> & mutacion::getClnsig () const{

	return clnsig;

}


mutacion & mutacion::operator =(const mutacion &m){
	if (&m != this){
		ID="";
		chr="";
		pos=0;
		ref_alt.clear();
		genes.clear();
		caf.clear();
		enfermedades.clear();
		clnsig.clear();

		ID=m.getID();
		chr=m.getChr();
		pos=m.getPos();
		ref_alt=m.getRef_alt();
		genes=m.getGenes();
		common=m.getCommon();
		caf=m.getCaf();
		enfermedades=m.getEnfermedades();
		clnsig=m.getClnsig();

	}
	return (*this);
		



}

bool mutacion::operator ==(const mutacion &m)const{
	bool iguales = true;
	if (ID.compare(m.getID()) != 0)
		iguales =false;
	
	return iguales;

}

bool mutacion::operator<(const mutacion & m) const{

	bool menor = false;

	string num = chr;
	string num_m = m.getChr();

	if ( num == "X" ) {
		num = "23" ;
	}

	if ( num == "Y" ) {
		num = "24" ;
	}

	if ( num == "MT" ) {
		num = "25" ;
	}

	if ( num_m == "X" ) {
		num_m = "23" ;
	}

	if ( num_m == "Y" ) {
		num_m = "24" ;
	}

	if ( num_m == "MT" ) {
		num_m = "25";
	}

	if ( atoi(num.c_str()) < atoi(num_m.c_str()) )
		menor = true;

	if ( !menor && num == num_m)
		if (pos < m.pos)
			menor = true;

	return menor;
}


ostream & operator << (ostream& os,const mutacion& m){
	os << "\nID de la enfermedad : " << m.getID();
	os << "\nNumero de cromosomas : " << m.getChr();
	os << "\nPósicion del SNP dentro del cromosoma : " << m.getPos();
		
	for (int i=0; i < m.getRef_alt().size(); i++)
		os << "Ref_alt (" << i << "): " << (m.getRef_alt())[i] << endl;

	os << "\n ¿Es el SNP común a la enfermedad? : " << m.getCommon();
	 
	for (int i=0; i < m.getRef_alt().size(); i++)
		os << "Ref_alt (" << i << "): " << (m.getRef_alt())[i] << endl;

	for (int i=0; i < m.getGenes().size(); i++)
		os << "Genes ("<< i <<"): " << (m.getGenes())[i] << endl;

	for (int i=0; i < m.getCaf().size(); i++)
		os << "Caf ("<< i <<"): " << (m.getCaf())[i] << endl;

	for (int i=0; i < m.getEnfermedades().size(); i++)
		os << "Enfermedad ("<< i <<"): " << (m.getEnfermedades())[i] << endl;

	for (int i=0; i < m.getClnsig().size(); i++)
		os << "Clnsig ("<< i <<"): " << (m.getClnsig())[i] << endl;

	return os;
}





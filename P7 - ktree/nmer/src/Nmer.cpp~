#include "Nmer.h"

#include <fstream>

// Constructores
Nmer::Nmer() {
  max_long = 0;
  el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));

}

Nmer::Nmer(ktree<pair<char,int>, 4> & arbol, unsigned int m_long){

    asignar_Nmer(arbol,m_long);

}

void Nmer::list_Nmer() const {
    // implmenentar el recorrido en preorden para el ktree de forma que nos devuelva los Nmers completos y no sólo el nodo.
      recorrido_preorden(el_Nmer.root());
}

unsigned int Nmer::length() const {
   return max_long;
}

Nmer::size_type Nmer::size() const{
  return el_Nmer.size()-1;
}

Nmer & Nmer::operator=(const Nmer & a){

    if (this != &a){

        this->max_long = a.length();
        this->el_Nmer = a.elArbol();   // Operator = ktree

    }

}

Nmer Nmer::Prefix(string adn){

    Nmer nuevo;
    ktree<pair<char,int>,4> aux (pair<char, int> ('-', 0));
    ktree<pair<char,int>,4>::node nodo_aux = aux.root();

    ktree<pair<char,int>,4>::node nodo = el_Nmer.root();
    ktree<pair<char,int>,4>::node::child_iterator it;

    int c;  // A continuacion se utilizara para saber sobre que hijo se trabaja en cada iteracion del segundo bucle

    for(int i=0; i < adn.length(); i++){

        for (it = nodo.begin(), c=0; it != nodo.end(); it++, c++){   // Buscar en los hijos adn[i]

            if ( (*(*it)).first == adn[i] ){

                aux.insert_k_child(nodo_aux, c, (*(*it)));  // Insertar nodo con adn[i] como hijo c del nodo actual del nuevo arbol
                nodo_aux = nodo_aux.k_child(c);             // Actualizar nodo_aux y nodo
                nodo = nodo.k_child(c);
                break;

            }

        }

        if (c > 3)   // adn[i] no estaba insertado en el_Nmer
            break;

    }

    if (c < 4){

        nodo_aux = nodo_aux.parent();  // Preparar la insercion de la rama de cadenas adn*
        nodo = nodo.parent();

        ktree<pair<char,int>,4> rama;
        rama.assing(el_Nmer,nodo);  // Tenemos en rama el subarbol corresondiente a adn*
             // Se necesita un ktree auxiliar 'rama' pues la siguiente funcion lo borrara
        aux.insert_k_child(nodo_aux, c, rama);

        nuevo.asignar_Nmer(aux, this->max_long);  // Nuevo metodo creado (implementado a continuacion de los constructores)

    }  // Si 'adn' no estaba (c>4), devolvera un Nmer vacio (solo con la raiz: ('-', 0) )

    return nuevo;

}

Nmer Nmer::union_Nmers(const Nmer refer){

    Nmer nuevo;
    int m_long = this->max_long;
    ktree<pair<char, int>, 4>::node nd;
    ktree<pair<char, int>, 4>::node nd2;

    if(refer.length() > m_long){   // Se asignara de inicio al nuevo Nmer aquel Nmer que tenga las cadenas mas largas

        m_long = refer.length();
        nuevo = refer;

        nd = (nuevo.elArbol()).root();    // preparar la llamada a la funcion recursiva unir
        nd2 = (this->el_Nmer).root();
        unir(nuevo.elArbol(), nd, nd2);

    }

    else {       // Se asignara de inicio al nuevo Nmer aquel Nmer que tenga las cadenas mas largas

         nuevo = (*this);

         nd = (refer.elArbol()).root();        // preparar la llamada a la funcion recursiva unir
         nd2 = nuevo.elArbol().root();
         unir(nuevo.elArbol(), nd2, nd );

    }

    return nuevo;

}

bool Nmer::containsString(const string adn) const{

    stack< ktree<pair<char,int>,4>::const_node > pila;
    ktree<pair<char,int>,4>::const_node nodo;
    bool cont = true;
    int i;

    pila = recorrido_hojas( (this->el_Nmer).root() );

    while (!pila.empty() && !cont){

        nodo = pila.top();
        pila.pop();

        i = adn.length() - 1;

        cont = true;

        while(!nodo.parent().null() && (i>=0) && cont){

            if((*nodo).first != adn[i]){

                cont = false;

            }

            else{

                i--;
                nodo = nodo.parent();

            }

        }

    }

    return cont;

}

bool Nmer::included(const Nmer refer) const{

    stack< ktree<pair<char,int>,4>::const_node > pila;
    stack<char> pila_aux;

    ktree<pair<char,int>,4>::const_node nod = (this->el_Nmer).root();
    ktree<pair<char,int>,4>::const_node aux;

    string cadena;
    bool content = true;

    pila = this->recorrido_hojas(nod);  // Obtener todas las hojas del arbol de this

    while(!pila.empty() && content){   // Una a una, obtener la cadena para cada hoja

        aux = pila.top();  // Sacar una hoja de la pila
        pila.pop();

        for( ; !aux.null(); aux = aux.parent()){  // Sacar todos los caracterese (uno de cada nodo) hasta llegar a la raiz

            pila_aux.push( (*aux).first );   // Meterlos en la pila auxiliar (Asi es mas facil construir la cadena en orden posteriormente)

        }

        pila_aux.pop();  // Descartar el caracter de la raiz

        while(!pila_aux.empty()){

            cadena.push_back(pila_aux.top());   // Ir sacando caracteres de la pila y añadiendolos al string
            pila_aux.pop();

        }

        content = refer.containsString(cadena);

    }

    return content;

}

void Nmer::sequenceADN(unsigned int tama, const string & adn){

    ktree<pair<char,int>, 4> (pair<char,int>('-',0));
    string subs;
    this->max_long = adn.length();

    for (int i=0; i <= (adn.length()-tama); i++){

        subs = adn.substr(i,tama);
        insertar_cadena(subs);

    }

}

void Nmer::insertar_cadena(const string & cadena){

    ktree<pair<char,int>,4>::node n_act = el_Nmer.root();

    //Este nodo n lo utilizamos para descender por el arbol
    // cadena[i] nos indica el índice del nodo en el nivel i+1;
    // A -> hijo 0; G -> hijo 1; C-> hijo 2; T-> hijo 3

    for (int i=0; i < cadena.length(); i++){

        if (cadena[i] == 'A'){

            if (n_act.k_child(0).null()){// No esta insertado el nodo

                ktree<pair<char,int>,4> aux (pair<char, int> (cadena[i], 1));  // Arbol con 1 nodo: valor a añadir
                el_Nmer.insert_k_child(n_act, 0, aux);     // Insertar el arbol (que solo tiene la raiz) como el k-hiijo correspondiente

            }

            else{ // Ya esta insertado el nodo

                ((*(n_act[0])).second)++;

            }

            n_act = n_act[0];

        }

        else if (cadena[i] == 'G'){

            if (n_act.k_child(1).null()){// No esta insertado el nodo

                ktree<pair<char,int>,4> aux (pair<char, int> (cadena[i], 1));  // Arbol con 1 nodo: valor a añadir
                el_Nmer.insert_k_child(n_act, 1, aux);     // Insertar el arbol (que solo tiene la raiz) como el k-hiijo correspondiente

            }

            else{ // Ya esta insertado el nodo

                ((*(n_act[1])).second)++;

            }

            n_act = n_act[1];

        }

        else if (cadena[i] == 'C'){

            if (n_act.k_child(2).null()){// No esta insertado el nodo

                ktree<pair<char,int>,4> aux (pair<char, int> (cadena[i], 1));  // Arbol con 1 nodo: valor a añadir
                el_Nmer.insert_k_child(n_act, 2, aux);     // Insertar el arbol (que solo tiene la raiz) como el k-hiijo correspondiente

            }

            else{ // Ya esta insertado el nodo

                ((*(n_act[2])).second)++;

            }

            n_act = n_act[2];

        }

        else {

            if (n_act.k_child(3).null()){// No esta insertado el nodo

                ktree<pair<char,int>,4> aux (pair<char, int> (cadena[i], 1));  // Arbol con 1 nodo: valor a añadir
                el_Nmer.insert_k_child(n_act, 3, aux);     // Insertar el arbol (que solo tiene la raiz) como el k-hiijo correspondiente

            }

            else{ // Ya esta insertado el nodo

                ((*(n_act[3])).second)++;

            }

            n_act = n_act[3];

        }

    }

}

bool Nmer::loadSerialized(const string & fichero) {
 string cadena;
 ifstream fe;
 pair<char,int> nulo('x',-1);
 Nmer::String2Base stb;

 fe.open(fichero.c_str(), ifstream::in);
 if (fe.fail()){
    cerr << "Error al abrir el fichero " << fichero << endl;
 }
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{
      getline(fe,cadena,'\n');
    } while (cadena.find("#")==0 && !fe.eof());
    // leemos Nmer_length
     max_long = std::stoi(cadena);
     // leemos cadena serializada
    getline(fe,cadena,'\n');
    el_Nmer.deserialize(cadena,nulo,';',stb);
    fe.close();
    return true;
 } // else
 fe.close();
 return false;
}

float Nmer::Distance(const Nmer & x){

    multimap<int, string, greater<int> > mm;

    stack <ktree<pair<char,int>, 4>::const_node > pila;
    ktree<pair<char,int>, 4>::const_node aux;
    stack < char > pila_aux;

    ktree<pair<char,int>, 4>::const_node nod = (this->el_Nmer).root();
    string cadena;
    int frec = 0;

    // THIS

    pila = this->recorrido_hojas(nod);  // Obtener todas las hojas del arbol de this

    while(!pila.empty()){   // Una a una, obtener la cadena para cada hoja

        aux = pila.top();  // Sacar una hoja de la pila
        pila.pop();

        while ((*aux).first != '-'){

            frec = (*aux).second;

            for( ; !aux.null(); aux = aux.parent()){  // Sacar todos los caracterese (uno de cada nodo) hasta llegar a la raiz

                pila_aux.push( (*aux).first );   // Meterlos en la pila auxiliar (Asi es mas facil construir la cadena en orden posteriormente)

            }

            pila_aux.pop();  // Descartar el caracter de la raiz

            while(!pila_aux.empty()){

                cadena.push_back(pila_aux.top());   // Ir sacando caracteres de la pila y añadiendolos al string
                pila_aux.pop();

            }

            mm.insert(pair<int, string>(frec, cadena));

        }

        aux = aux.parent();

    }

    map<int, string > mapa;
    multimap <int, string>::iterator it;

    int i=0, max_size;

    for (it = mm.begin(); it != mm.end(); it++, i++){

        mapa.insert(pair<int, string> (i, (*it).second));


    }

    // X

    mm.clear();

    nod = (x.elArbol()).root();
    frec = 0;

    pila = this->recorrido_hojas(nod);  // Obtener todas las hojas del arbol de this

    while(!pila.empty()){   // Una a una, obtener la cadena para cada hoja

        aux = pila.top();  // Sacar una hoja de la pila
        pila.pop();

        while ((*aux).first != '-'){

            frec = (*aux).second;

            for( ; !aux.null(); aux = aux.parent()){  // Sacar todos los caracterese (uno de cada nodo) hasta llegar a la raiz

                pila_aux.push( (*aux).first );   // Meterlos en la pila auxiliar (Asi es mas facil construir la cadena en orden posteriormente)

            }

            pila_aux.pop();  // Descartar el caracter de la raiz

            while(!pila_aux.empty()){

                cadena.push_back(pila_aux.top());   // Ir sacando caracteres de la pila y añadiendolos al string
                pila_aux.pop();

            }

            mm.insert(pair<int, string>(frec, cadena));

        }

        aux = aux.parent();

    }

    map<int, string > mapa2;

    i=0;

    for (it = mm.begin(); it != mm.end(); it++, i++){

        mapa2.insert(pair<int, string> (i, (*it).second));


    }

    float dist = 0.0;
    float valor = 0.0;
    float ret;

    map<int, string>::iterator it1;
    map<int, string>::iterator it2;
    bool pert = false;
    int m1, m2;

    max_size = mapa.size();

    if (mapa2.size() > max_size)
        max_size = mapa2.size();

    for(m1 = 0, it1 = mapa.begin(); it1 != mapa.end(); m1++, it1++){

        pert = false;

        for (m2 = 0, it2 = mapa2.begin(); it2 != mapa2.end() && !pert; m2++, it2++){

            if ((*it1).second == (*it2).second){

                pert = true;
                valor = abs(m1 - m2)/max_size;


            }

        }

        if (!pert)
            valor = 1;

        dist += valor;

    }

    ret = dist/(mapa.size());

    return ret;

}

// Metodos propios añadidos

ktree<pair<char,int>,4> & Nmer::elArbol() const{

    ktree<pair<char,int>,4> nuevo (this->el_Nmer);   // La cabecera de este constructor estaba en ktree.h,
                                                     // pero su implementacion no estaba en el .hpp (la hice yo)
    return nuevo;

}

void Nmer::asignar_Nmer(ktree<pair<char,int>, 4> & arbol, unsigned int m_long){

    this->el_Nmer.clear();
    this->el_Nmer = arbol;
    this->max_long = m_long;

}

void Nmer::recorrido_preorden(const ktree<pair<char,int>, 4>::const_node & nod)const{

    ktree<pair<char,int>, 4>::const_node::child_iterator it;

    if (!nod.null()) {

        cout << "  " << (*nod).first << "  " << (*nod).second << endl;   //  acción sobre el nodo v.

        for (it = nod.begin(); it != nod.end(); it++)
            recorrido_preorden(*it);

  }

}

stack< ktree<pair<char,int>,4>::const_node > & Nmer::recorrido_hojas(const ktree<pair<char,int>, 4>::const_node & nod)const{

    ktree<pair<char,int>, 4>::const_node::child_iterator it;
    stack< ktree<pair<char,int>,4>::const_node > pila;
    stack< ktree<pair<char,int>,4>::const_node > aux;
    bool hoja = true;

    if (!nod.null()) {

        for (it = nod.cbegin(); it != nod.cend() && hoja; it++){

            if(!(*it).null())
                hoja = false;

        }

        if (hoja){

            pila.push(nod);

        }

        else{

            for (it = nod.cbegin(); it != nod.cend(); it++){

                aux = recorrido_hojas(*it);

                while (!aux.empty()){

                    pila.push(aux.top());
                    aux.pop();

                }

            }

        }

    }

    return pila;

}

void Nmer::unir(ktree<pair<char,int>, 4> & arb, ktree<pair<char,int>, 4>::node & dest, ktree<pair<char,int>, 4>::node & orig){

    ktree<pair<char,int>, 4>::node::child_iterator it;
    ktree<pair<char,int>, 4>::node::child_iterator itt;
    int i;

    if (!orig.null()){

        (*dest).second = (*dest).second + (*orig).second;  // Union de los nodos

        for(i=0, it = dest.begin(), itt = orig.begin(); it != dest.end() && itt != orig.end(); i++, it++, itt++){  // recorrer los hijos de cada nodo

            if ((*it).null() && !(*itt).null()){  // Si dest no tiene un determinado hijo pero orig si, hay que añadirle dicho hijo a dest

                arb.insert_k_child( dest, i, pair<char, int>((*(*itt)).first, 0));  // Se añade con un 0 en la etiqueta. En la llamada a unir ya se actualizara

            }

            unir(arb, (*it), (*itt));


        }

    }

}

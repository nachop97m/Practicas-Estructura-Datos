
/**
 * @file Nmer.h
 * @brief TDA Nmer
 *   Representa un conjunto de Nmer subsecuencias de tamaño 1 hasta N que se pueden obtener a partir de una cadena de ADN
 * @author Ignacio Pineda Mochon   76668150-L   Ingenieria Informatica - UGR
 * @bug Por espeficicar
 */

#ifndef __NMER_H
#define __NMER_H

#include "ktree.h"
#include <string>
#include <utility>
#include <stack>
#include <map>
#include <cstdlib>

using namespace std;

class Nmer {
public:
  typedef unsigned int size_type;

  /** @brief Constructor primitivo .
      Crea un Nmer de longitud maxima 0, con el valor ('-',0) en la raíz
  */
  Nmer();

  /** @brief Constructor que recibe un arbol y max_long
  *   @param arbol: arbol que se asignara a el_Nmer
  *   @param m_long: maximo nivel del arbol
  */
  Nmer(ktree<pair<char,int>, 4> & arbol, unsigned int m_long);

    /** @brief Imprime los Nmers
   * @todo Debemos de implementar este método de forma que nos garantizemos que se imprimen todos los Nmers.
   */
   void list_Nmer() const;

  /** @brief Máxima longitud de los Nmers almacenados
   */
   unsigned int length()const;

  /** @brief Número de Nmers almacenados
   */
   size_type size() const;

   /** @brief operdor de asignacion
   * @param a: Nmer desde el que se copia
   */
   Nmer & operator=(const Nmer & a);

  /** @brief Devuelve el Nmer (subarbol) asociado a un prefijo
   * @param adn: subcadena por la que han de empezaar los nmer devueltos
   * @todo Por ejemplo, si adn es "ACT", devuelve el Nmer que representa todas las subcadenas que empiezan por "ACT" (ACT*)
   */
   Nmer Prefix(string adn);

   /** @brief Devuelve el Nmer union de this y refer
   * @param refer: Nmer
   * @todo Se devuelve un Nmer donde para cada nodo (representa una secuencia) se computa la suma de las frecuencias en *this y en referencia
   */
   Nmer union_Nmers(const Nmer refer);

  /** @brief Devuelve true si la cadena adn está representada en el árbol
   * @param adn: cadena a buscar en el arbol
   */
   bool containsString(const string adn) const;

   /** @brief Devuelve true si todas las cadenas de this estan en refer
   * @param refer: Nmer donde buscar las cadenas
   * @todo Devuelve true si cada nodo de *this está también representado en reference, es decir, si todas las secuencias representadas
    en el árbol de *this están también incluidas en reference. False en otro caso.
   */
   bool included(const Nmer refer) const;

  /** @brief Construir Nmer a partir de cadena de ADN
   * @param longitud de las subcadenas a extraer
   * @param cadena ADN
   *
   * Construir Nmer a partir de cadena de ADN
   */
  void sequenceADN(unsigned int tama, const string & adn);

  /** @brief insertar nmers a partir de cadena
   * @param cadena para extraer nmers
   *
   *  insertar nmers a partir de cadena
   */
  void insertar_cadena(const string & cadena);

  /** @brief lectura fichero serializado
   * @param nombre_fichero fichero serializado con extension .srl
   *
   * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
   *
   * La cadena original viene descrita en el fichero serializado
   */
  bool loadSerialized(const string & nombre_fichero);

  /** @brief lectura fichero serializado
   * @param nombre_fichero fichero serializado con extension .srl
   *
   */
  float Distance(const Nmer & x);
   // Metodos propios añadidos

    /**@brief Devuelve el arbol de nmers
   *
   */
   ktree<pair<char,int>,4> & elArbol() const;

    /** @brief Elimina el_Nmer y asigna uno nuevo (resetea max_long)
  *   @param arbol: arbol que se asignara a el_Nmer
  *   @param m_long: maximo nivel del arbol
  */
  void asignar_Nmer(ktree<pair<char,int>, 4> & arbol, unsigned int m_long);


   /** @brief Recorre en preorden y muestra en pantalla
   * @param nod: nodo desde el que empezar
   * @todo recorrido en preorden: funcion recursiva
   */
   void recorrido_preorden(const ktree<pair<char,int>, 4>::const_node & nod)const;

   /** @brief Metodo que devuelve una pila con todas las hojas
   * @param nod: nodo desde el que empezar a buscar (raiz)
   * @todo  Cada vez que encuentra una hoja, la añade a una pila, que sera devuelta. Para los que no son hojas, se vuelve
   a buscar a partir de cada hijo una hoja (busqueda recursiva). Los elementos de las pilas devueltas se añaden a la
   pila actual y esta se devuelve
   */
   stack< ktree<pair<char,int>,4>::const_node > & recorrido_hojas(const ktree<pair<char,int>, 4>::const_node & nod)const;

    /** @brief Une los ktree a partir de dest y orig
   * @param dest: nodo raiz del arbol sobre el que se realiza la union
   * @param orig: nodo raiz del arbol del que se leen nodos para la union
   * @todo Metodo recursivo. En dest queda la union de ambos
   */
   void unir(ktree<pair<char,int>, 4> & arb, ktree<pair<char,int>, 4>::node & dest, ktree<pair<char,int>, 4>::node & orig);


private:
  ktree<pair<char,int>,4> el_Nmer; // subsecuencias
  unsigned int max_long; // Mayor longitud de la cadena representada, esto es, el nivel máximo del árbol

  /** @brief Functor para convertir un string en un pair<char,int>
   * se utiliza en loadSerialized
   */
  class String2Base {
   public:
    pair<char,int> operator()( const string & cad) {
	    pair<char,int> salida;
	    salida.first = cad[0];
	    salida.second = std::stoi(cad.substr(1));
	    return salida;
    }
  };

   /** @brief Functor para convertir un pair<char,int> en un string
    * Necesario para serializar un Nmer.
   */
  class Base2String {
   public:
     string operator()( const pair<char,int> & x) {
       string salida = string(1,x.first) + " " +std::to_string(x.second);
       return salida;
     }
  };
};

#endif

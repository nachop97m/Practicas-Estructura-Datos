/* 
 * enfermedad.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano 
*/
#ifndef __ENFERMEDAD_H
#define __ENFERMEDAD_H

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstring>

using namespace std;

//! Clase enfermedad, asociada al TDA enfermedad
/*! enfermedad::enfermedad,  .....
 * Descripción contiene toda la información asociada a una enfermedad almacenada en la BD ClinVar-dbSNP (nombre de la enfermedad, id, BD que provee el id)
 
 @todo Implementa esta clase, junto con su documentación asociada

*/

class enfermedad {
private:
  string  name;       // nombre de la enfermedad. Almacenar completo en minúscula.
  string  ID;         // ID único para la enfermedad
  string  database;   // Base de datos que provee el ID

public:

/** @brief Constructor vacio
*/
 enfermedad (); //Constructor de enfermedad por defecto

/** @brief Constructor con string. Crea el objeto enfermedad inicializando los atributos con los string pasados como argumentos 
  @param[in] name Nombre_enfermedad
  @param[in] ID ID_enfermedad  
  @param[in] database database_enfermedad
*/
 enfermedad (const string & name, const string & ID, const string & database); 

/** @brief Metodos set: modificar el valor de los atributos
*/
 void setName(const string & name);
 void setID(const string & ID);
 void setDatabase(const string & database);

/** @brief Metodos get: obtener el valor de los atributos
*/
 string getName( )const;
 string getID( )const;
 string getDatabase( )const;

/** @brief Sobrecarga del operador de asignacion
  @param[in] e enfermedad
  @return enfermedad & nueva enfermedad con los datos de la enfermedad dada 
*/
 enfermedad & operator=(const enfermedad & e);

/** @brief Devuelve una string con el valor de los atributos de la clase
  @return string cadena 
*/
 string toString() const;

// Operadores relacionales

/** @brief Sobrecarga del operador de comparacion ==
  @param[in] e enfermedad
  @return bool Si ambas enfemedades son iguales o no
*/
 bool operator==(const enfermedad & e) const;

/** @brief Sobrecarga del operador de comparacion !=
  @param[in] e enfermedad
  @return bool Si ambas enfemedades son diferentes o no
*/
 bool operator!=(const enfermedad & e) const;

/** @brief Sobrecarga del operador de comparacion <
  @param[in] e enfermedad
  @return bool si una enfermedad es menor que la otra
*/
 bool operator<(const enfermedad & e) const;	//Orden alfabético por campo name. 

/** @brief Devuelve True si str está incluido en el nombre de la enfermedad
  @param[in] str cadena a buscar
  @return bool contiene o no a la cadena
*/
 bool nameContains(const string & str) const;

};

/** @brief Sobrecarga del operador <<
  @param[in] os flujo de salida
  @param[in] e enfermedad que se envia al flujo
  @return flujo con la enfermedad
*/
 ostream& operator<< ( ostream& os, const enfermedad & e); //imprime enfermedad (con TODOS sus campos)

#include "enfermedad.hxx" // Incluimos la implementacion.

#endif

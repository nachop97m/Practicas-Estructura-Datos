/* 
 * mutacion.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano 
*/
#ifndef __MUTACION_H
#define __MUTACION_H

#include <string>
#include <iostream> 
#include <vector>
#include <stdlib.h>
#include <cstring>

#include "enfermedad.h"

using namespace std;

//! Clase mutacion, asociada a la definición de una mutación/SNP 
/*! mutacion::mutacion,  .....
 * 
 @todo Implementa esta clase, junto con su documentación asociada

*/


class mutacion {
 private:
  string ID;
  string chr; 
  unsigned int pos; 
  std::vector<string> ref_alt; 
  std::vector<string> genes; 
  bool common;
  std::vector<float> caf;
  std::vector<enfermedad> enfermedades;
  std::vector<int> clnsig;

 public:

/**
@brief Constructor  nulo
*/
  mutacion();

/**
@brief Constructor 
@param m objeto de la clase mutacion
*/
  mutacion(const mutacion& m);

/**
@brief Construye un objeto a partir de un string
@param str string con el que se inicializa el objeto
*/
  mutacion(const string & str);   //para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada

 /**
@brief Metodos set para modificar el valor de los atributos de la clase
*/
  void setID(const string & id);
  void setChr(const string & chr);
  void setPos(const unsigned int & pos);
  void setRef_alt(const std::vector<string> & ref_alt);
  void setGenes (const std::vector<string> & genes);  
  void setCommon (const bool & common);
  void setCaf (const std::vector<float> & caf);
  void setEnfermedades (const std::vector<enfermedad> & enfermedades);
  void setClnsig (const std::vector<int> & clnsig);  

  /**
@brief Metodos get para obtener el valor de los atributos de la clase
@return devuelve el vaor de los atributos
*/
  string getID( ) const;
  string getChr( ) const;
  unsigned int getPos( ) const;
  const std::vector<string> & getRef_alt () const;
  const std::vector<string> & getGenes () const;
  bool getCommon () const;
  const std::vector<float> & getCaf () const;
  const std::vector<enfermedad> & getEnfermedades () const;
  const std::vector<int> & getClnsig () const;

/**
@brief Sobrecarga del operador de asignacion
@param m objeto de la clase mutacion
@return referencia a un objeto de la clase mutacion
*/
  mutacion & operator=(const mutacion & m);

/**
@brief Sobrecarga del operador de comparacion
@param m objeto de la clase mutacion
@return devuelve un booleano con un valor diferente dependiendo de si ambas mutaciones son iguales 
*/
  bool operator==(const mutacion & m) const;

/**
@brief Sobrecarga del operador < 
@param m objeto de la clase mutacion
@return devuelve un booleano con un valor diferente dependiendo del valor de pos y chr de cada objeto que se esta comprando 
*/
  bool operator<(const mutacion & m) const;      //El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posición, de menor posición a mayor (orden natural de enteros). 

};

/**
@brief Sobrecarga del operador de flujo de salida << 
@param os flujo en el que se introducen los datos
@param m objeto de la clase mutacion del que se sacan los datos
@return flujo utilizado
*/
  ostream& operator << ( ostream& os, const mutacion& m);   //Imprimir TODOS los campos del objeto mutación.

#include "mutacion.hxx"

#endif

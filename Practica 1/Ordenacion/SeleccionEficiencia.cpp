#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>


using namespace std;
using namespace std::chrono;

void lee_fichero( const char * nf, vector<char> & V) {
 ifstream fe;
  char s;
 fe.open(nf, ifstream::in);
 while ( !fe.eof() )
   { fe >> s;
     if (!fe.eof())
       V.push_back(s);
   }
 fe.close();
}

void generar_aleatorio(vector<int> & V){
  int i;
  for ( i=0; i<V.size();i++){
    V[i]=i;
  }
   random_shuffle(V.begin(),V.end()); //Desordenamos el vector
}

void seleccion(vector<char> & T, int final) {

  vector<char> aux = T;
  int i, j, min, t;

  for (i = 0; i < final - 1; i++) {

    min = i;

    for (j = i + 1; j < final; j++)
      if (aux[j] < aux[min])
         min = j;

         t = aux[min];
         aux[min] = aux[i];
         aux[i] = t;

   }
}

int main(){

  vector<char> Q;

  high_resolution_clock::time_point tantes,tdespues;
  duration<double> tiempo_transcurrido;

  lee_fichero("lema.txt", Q);
  int tama = 100;

  for (; tama < Q.size(); tama +=100){
  tantes = high_resolution_clock::now();
  seleccion (Q, tama);
  tdespues = high_resolution_clock::now();

  tiempo_transcurrido  = duration_cast<duration<double> >(tdespues - tantes);
  cout << tama << " " << tiempo_transcurrido.count() << endl;

  }

  Q.clear();

  // SEGUNDA PARTE

  vector<char> D;
 
  lee_fichero("quijote.txt", D);
  tama = 100;

  for (; tama < D.size(); tama +=1000){
  tantes = high_resolution_clock::now();
  seleccion (D, tama);
  tdespues = high_resolution_clock::now();

  tiempo_transcurrido  = duration_cast<duration<double> >(tdespues - tantes);
  cout << tama << " " << tiempo_transcurrido.count() << endl;

  }

  D.clear();

  return 0;

}

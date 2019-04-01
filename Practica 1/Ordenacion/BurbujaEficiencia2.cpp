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

void burbuja(vector<char> & T, int inicial, int final)
{
 int i, j;
 char aux;
	vector<char> V=T;
 for (i = inicial; i < final - 1; i++)
   for (j = final - 1; j > i; j--)
       if (V[j] < V[j-1])
         {
           aux = V[j];
           V[j] = V[j-1];
           V[j-1] = aux;
         }
}

int main(int argc, char * argv[]){
	int tamanio;
	vector<char> Dicc;
	vector<char> Q;
	high_resolution_clock::time_point start,end;
	duration<double> tiempo_transcurrido;

 
	lee_fichero("lema.txt", Dicc); 
 	lee_fichero("quijote.txt", Q);
	int tama1=100;
	int tama2=100;

	for ( ; tama1<Q.size();tama1+=1000){
	start =  high_resolution_clock::now();;
 
	burbuja(Q,0,tama1);
 
	end=  high_resolution_clock::now();; 
 
	
	tiempo_transcurrido  = duration_cast<duration<double> >(end-start);;
	cout << tama1 << " " << tiempo_transcurrido.count() << endl;
	
	}

	cout << "\n";

	for ( ; tama2<Dicc.size();tama2+=100){
	start =  high_resolution_clock::now();;
 
	burbuja(Dicc,0,tama2);
 
	end=high_resolution_clock::now();; 
 
	
	tiempo_transcurrido  = duration_cast<duration<double> >(end-start);;
	cout << tama2 << " " << tiempo_transcurrido.count() << endl;
	
	}


return 0;

}

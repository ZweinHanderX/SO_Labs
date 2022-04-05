#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

using namespace std;

//Contadores globales
int cnt_global = 0;
int cnt_car_global = 0;
int cnt_par_global = 0;

//Funcion para leer archivos
void procesar_archivo(string archivo){

ifstream file(archivo);
string str;
//Contador de lineas
int cnt = 0;
//Contador de caracteres
int cnt_car = 0;
//Contador de palabras / empieza en 1 porque cuenta palabras por cada espacio que tiene, y no sabe identificar la ultima palabra, pq no tiene un espacio después de esta
int cnt_par = 1;

//Sistema para contar lineas
while(getline(file, str)){

cnt++;

for(int i = 0; i < str.length(); i++){
  
  //Sistema para contar palabras
  if(str[i] == ' '){
      cnt_par++;
  }

  //Sistema para contar caracteres
  cout << str[1];
  cnt_car++;

}

cout<<endl;

}

//Para contar los caracteres se le resta la cantidad de linea, porque suma los salto de linea
cnt_car -= (cnt-1);
cout <<cnt<<" lineas"<< endl;
cout << cnt_car << " caracteres" << endl;
cout <<cnt_par << " palabras" << endl;

cnt_global += cnt;
cnt_car_global += cnt_car;
cnt_par_global += cnt_par;

cout <<endl;

}


int main(int argc, char *argv[]) {

    auto start = chrono::system_clock::now();
    
    string line;
    string fileName;

    //Abrir archivos por argumento
    for(int i = 0; i < argc-1; i++){
        fileName = argv[i+1];
        fileName = fileName + ".txt";
        procesar_archivo(fileName);
    }

    //Impresión de numeros globales
    cout <<cnt_global<<" Total lineas"<< endl;
    cout << cnt_car_global << " Total caracteres" << endl;
    cout <<cnt_par_global << " Total palabras" << endl;
    cout <<endl;

    auto end = chrono::system_clock::now();
    
    chrono::duration<float,milli> duration = end - start;

    cout << "Tiempo de ejecución : " << duration.count() << " s" << endl;


  return 0;
}
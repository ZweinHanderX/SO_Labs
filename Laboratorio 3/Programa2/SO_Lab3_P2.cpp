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

string archivo;

//Funcion para contar las lineas y caracteres del archivo indicado
void *procesarArchivo (void *param) {
  
ifstream file(archivo);
string str;

int cnt = 0;
int cnt_car = 0;
int cnt_par = 1;

	//Sistema para contar lineas
while(getline(file, str))
{
	//contar linea
	cnt++;

	//contar caracteres
	for(int i = 0 ; i<str.length() ; i++)
	{

		//Sistema para contar palabras
		if(str[i] == ' '){
			cnt_par++;
		}

		//Sistema para contar caracteres
		cnt_car++;
	}
}

cout <<endl;

//Para contar los caracteres se le resta la cantidad de linea, porque suma los salto de linea
cnt_car -= (cnt-1);
cout<< cnt<< " lineas " << endl;
cout << cnt_car << " caracteres " << endl;
cout << cnt_par << " palabras "<<endl;

cnt_global += cnt;
cnt_car_global += cnt_car;
cnt_par_global += cnt_par;

pthread_exit(0);

}

//Funcion principal del programa
int main(int argc, char *argv[]) {

auto start = chrono::system_clock::now();

string fileName;

pthread_t threads[argc - 1];
pthread_attr_t attr;

pthread_attr_init (&attr);


//Abrir archivos con los hilos
for(int i = 0; i < argc-1 ; i++){
	cout << "Archivo "<<i+1<<" : "<<endl;
	fileName = argv[i+1];
	fileName = fileName + ".txt";
	archivo = fileName;
	pthread_create(&threads[i+(argc-1)], &attr, procesarArchivo, NULL);
	pthread_join(threads[i+(argc-1)], NULL);
	cout <<endl;
}
cout <<endl;

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

#include "ruta.h"
#include "almacenrutas.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
	if (argc < 2) {
		cout << "Uso: " << argv[0] << " <nombre_archivo>" << endl;
		return -1;
	}

	ifstream f(argv[1]);

	if (!f) {
		cout << "Archivo " << argv[1] << " inexistente o sin permisos para leer" << endl;
	}

	// Leemos rutas
	AlmacenRutas viajes;
	f >> viajes;

	// Mostramos rutas
	cout << viajes;
	
	cout << "Consultando ruta de código > ";
	string c;
	cin >> c;
	cout << viajes.obtenerRuta(c) << endl;
}
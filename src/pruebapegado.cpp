#include "imagen.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char * argv[]) {
	if (argc!=8){
		cout<<"Los parametros son :"<<endl;
		cout<<"1.-La imagen de fondo"<<endl;
		cout<<"2.-La imagen a pegar"<<endl;
		cout<<"3.-La máscara de la imagen a pegar"<<endl;
		cout<<"4.-El nombre de la imagen de salida"<<endl;
		cout<<"5.-La fila donde pegar"<<endl;
		cout<<"6.-La columna donde pegar"<<endl;
		cout<<"7.-Opacidad entre 0 y 255 (0, transparente, 255 opaco)"<<endl;
		return 0;
	}
	Imagen mapa,superpuesta;
	Imagen::Posicion ubicacion(atoi(argv[5]), atoi(argv[6]));

	superpuesta.leer(argv[2],argv[3]).aplicarOpacidad(atoi(argv[7]));

	mapa.leer(argv[1]).superponer(superpuesta, ubicacion).escribir(argv[4], "PPM");
}
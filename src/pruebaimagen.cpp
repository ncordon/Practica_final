#include "imagen.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char * argv[]) {
	/*if (argc!=4){
		cout<<"Los parametros son :"<<endl;
		cout<<"1.-La imagen de entrada"<<endl;
		cout<<"2.-El angulo de rotación (en grados)"<<endl;
		cout<<"3.-El nombre de la imagen de salida"<<endl;
		return 0;
	}
	Imagen I;
	I.leer(argv[1]);
	double angulo = atof(argv[2]);
	angulo = angulo*(M_PI)/180; //Pasamos el angulo radianes
	I.rotar(angulo).escribir(argv[3],"PPM");*/


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
	Imagen I,Ip;
	I.leer(argv[1]);
	Ip.leer(argv[2],argv[3]).aplicarOpacidad(atoi(argv[7]));
	Imagen::Posicion ubicacion(atoi(argv[5]), atoi(argv[6]));

	/*Tipo_Pegado tp=OPACO; //variable de tipo Tipo_Pegado que es un enumerado con los valores OPACO y  BLENDING
	int au= atoi(argv[7]);
	if (au!=0)
	tp=BLENDING;

	*/

	I.superponer(Ip, ubicacion).escribir(argv[4], "PPM");
}
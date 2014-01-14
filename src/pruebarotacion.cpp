#include "imagen.h"
#include "imagenES.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;


void Imagen::reserva(int nr, int nc) {
	m = new Pixel*[nr];
	for (int i = 0; i < nr; ++i)
		m[i] = new Pixel[nc];
}

Imagen::TipoImagen Imagen::leerTipo(ifstream& f) {
	char c1,c2;
	TipoImagen res= IMG_DESCONOCIDO;

	if (f) {
		c1=f.get();
		c2=f.get();
		if (f && c1=='P')
			switch (c2) {
				case '5': res= IMG_PGM; break;
				case '6': res= IMG_PPM; break;
				default: res= IMG_DESCONOCIDO;
			}
	}
	
	return res;
}

char Imagen::saltarSeparadores (ifstream& f) {
	char c;
	do {
		c= f.get();
	} while (isspace(c));
	f.putback(c);
	return c;
}

bool Imagen::leerCabecera (ifstream& f) {
	int maxvalor;

	while (saltarSeparadores(f)=='#')
		f.ignore(10000,'\n');

	f >> colnum >> rownum >> maxvalor;

	if (/*str &&*/ f && rownum>0 && rownum <5000 && colnum >0 && colnum<5000) {
		f.get(); // Saltamos separador
		return true;
	}
	else
		return false;
}
void Imagen::leer(char nombre_archivo[], char nombre_mascara[] = "") {
	ifstream f(nombre_archivo);
	TipoImagen tipo = leerTipo(f);

	if (tipo == IMG_PPM)
		leerPPM(f, nombre_mascara);
	else if (tipo == IMG_PGM)
		leerPGM(f, nombre_mascara);
}

void Imagen::escribir(char nombre_archivo[]) {

}


void Imagen::leerPPM (ifstream& f, const char nmask[]="") {
	bool gestionar_mascara = nmask[0] != '\0';
	ifstream mask;
	if (gestionar_mascara) mask.open(nmask);

	if (gestionar_mascara) leerTipo(mask); // precondición: mask es PGM
	// LeerCabecera(mask...) ?
	if (leerCabecera (f)) {
		reserva(rownum, colnum);

		for (int i = 0; i < rownum; i++) {
			for (int j = 0; j < colnum; j++) {
				f.read(reinterpret_cast<char *>(&m[i][j]),3);
				if (gestionar_mascara)
					mask.read(reinterpret_cast<char *>(&m[i][j].alpha),1);
				else
					m[i][j].alpha = 0xff;
			}
		}
	}
}
void Imagen::leerPGM (ifstream& f, const char nmask[]="") {
	/*bool gestionar_mascara = nmask[0] != '\0';
	if (gestionar_mascara) ifstream mask(nmask);

	if (gestionar_mascara) leerTipo(mask); // precondición: mask es PGM
	// LeerCabecera(mask...) ?
	if (leerCabecera (f)) {
		reserva(rownum, colnum);

		for (int i = 0; i < rownum; i++) {
			for (int j = 0; j < colnum; j++) {
				f.read(reinterpret_cast<char *>(m[i][j]),1);
				m[i][j].b = m[i][j].g = m[i][j].r;
				if (gestionar_mascara)
					mask.read(reinterpret_cast<char *>(&m[i][j].alpha),1);
				else
					m[i][j].alpha = 0xff;
			}
		}
	}*/
}


/** 
 * @brief Obtiene una nueva imagen que es la versión rotada de una imagen de entrada
 * @param Io: imagen de entrada
 * @param angulo: angulo a rotar la imagen de entrada. Debe estar en radianes.
 * @return Una nueva imagen que es la versión rotada de Io.
 * */

Imagen Imagen::rotar(double angulo){
	Imagen& I_input = *this;
	double rads=angulo;
	double coseno = cos(angulo);
	double seno = sin(angulo);
	// Variables para obtener nuevas dimensiones de la imagen
	int newimgrows,newimgcols;
	double new_row_min,new_col_min,new_row_max,new_col_max;
	double x,y;
	// Coordenadas de bordes de imagen a girar
	int corners[4][2]={ {0,0},
						{--colnum,0},
						{--colnum,--rownum},
						{0,--rownum} };
	
	new_row_min = new_col_min = new_row_max = new_col_max = 0;
	newimgrows = newimgcols = 0;
	
	for(int i=0; i<4; ++i)
	{    
		x = corners[i][0]*coseno + corners[i][1]*seno;
		new_col_min=(x < new_col_min ? x : new_col_min);
		new_col_max=(x > new_col_min ? x : new_col_max);
		
		y = -corners[i][0]*seno + corners[i][1]*coseno;
		new_row_min=(y < new_row_min ? y : new_row_min);
		new_row_max=(y > new_row_min ? y : new_row_max);
	}
	
	newimgrows=(unsigned)ceil((double)new_row_max-new_row_min);
	newimgcols=(unsigned)ceil((double)new_col_max-new_col_min);
	
	Imagen I_output(newimgrows,newimgcols);
	
	for(int rows=0;rows<=newimgrows;rows++)
	{
		for(int cols=0;cols<=newimgcols;cols++)
		{
			// Buscamos el pixel antiguo que al rotar da como resultado el nuevo
			int old_col=ceil((cols+new_col_min)*coseno-
							 (rows+new_row_min)*seno);
			int old_row=ceil((cols+new_col_min)*seno+
							 (rows+new_row_min)*coseno);
			
			if((old_row>=0)&&(old_row<I_input.rownum)&&
				(old_col>=0)&&(old_col<I_input.colnum))
				I_output [rows][cols] = (*this)[old_row][old_col];
			else
				I_output[rows][cols] = 0x00ffffff;
		}
	}

	//*this = I_output;
	return I_output;
}

void Imagen::superponer(const Imagen& nueva, Imagen::Posicion lugar) {}


int main(int argc, char * argv[]){
	if (argc!=4){
		cout<<"Los parametros son :"<<endl;
		cout<<"1.-La imagen de entrada"<<endl;
		cout<<"2.-El angulo de rotación (en grados)"<<endl;
		cout<<"3.-El nombre de la imagen de salida"<<endl;
		return 0;
	}
	Imagen I;
	I.leer(argv[1]);
	double angulo=atof(argv[2]);
	angulo = angulo*(M_PI)/180; //Pasamos el angulo radianes
	Imagen nueva= I.rotar(angulo);
	nueva.escribir(argv[3]);  
}
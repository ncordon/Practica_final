#include "imagen.h"
#include "imagenES.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;

/****************** Métodos privados ********************/
void Imagen::reserva(int nr, int nc) {
	m = new Pixel*[nr];
	for (int i = 0; i < nr; ++i)
		m[i] = new Pixel[nc];
}

bool Imagen::leerCabecera (ifstream& input, int& filas, int& columnas){
	// Mayor valor de gris
	int max_gris;
	// Mayor width y length en píxeles de una imagen
	const int max_valor = 5000;
	filas = columnas = 0;
	
	while (saltarSeparadores(input) == '#')
		/// En los ficheros de la práctica pone que la máxima longitud de comentario
		/// es 70, había un 1000 ????
		input.ignore(1000,'\n');
	
	input >> columnas >> filas >> max_gris;
	
	/* DEPURACIÓN
	cout << "Columnas "<<columnas << endl;
	cout << "Filas " <<filas << endl;
	cout << max_gris << endl;
	*/
	
	if (input && filas>0 && filas <max_valor && columnas >0 && columnas<max_valor){
		input.get(); // Saltamos separador
		return true;
	}
	else 
		return false;
}

char Imagen::saltarSeparadores (ifstream& input){
	char c = input.peek();
	
	while (isspace(c)){
		input.get();
		c = input.peek();
	}
	
	return c;
}

Imagen::TipoImagen Imagen::leerTipo(ifstream& input){
	char c1,c2;
	TipoImagen leida;

	if (input) {
		c1=input.get();
		c2=input.get();
		if (input && c1=='P'){
			switch (c2) {
				case '5': leida = PGM;break;
				case '6': leida = PPM; break;
				default : leida = UNKNOWN;
			}
		}
	}
	return leida;
}
/*
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
	}
}*/


void Imagen::leerNetpbm (const char* nombre, const char* mascara) {
	ifstream input(nombre);
	ifstream mask(mascara);
	
	TipoImagen tipo=leerTipo(input);
	
	if (leerCabecera (input, rownum, colnum)) {
		reserva(rownum, colnum);
		// Leemos un PPM
		if (tipo == PPM || tipo == PGM){
			/*Dep*/
			for (int i = 0; i < rownum; i++) {
				for (int j = 0; j < colnum; j++) {
					input.read(reinterpret_cast<char *>(&m[i][j]),1+2*(tipo==PPM)); // Solo para PPM?
					if (tipo == PGM)
						m[i][j].b = m[i][j].g = m[i][j].r;
					if(mascara != NULL)
						mask.read(reinterpret_cast<char *>(&m[i][j].alpha),1);
					else m[i][j].alpha = 0xff;
				}
			}
		}
		else throw invalid_argument ("La imagen no era ni PPM ni PGM");
	}
}

void Imagen::genNetpbm (const char* nombre_archivo, const string& formato){
	ofstream output(nombre_archivo);
	int i,j;
	
	if (output){
		if (formato == "PPM")
			output << "P6" << endl;
		else if (formato == "PGM")
			output << "P5" << endl;
		else{
			output.setstate(ios::failbit);
			return;
		}
		// Imprimimos dimensiones
		output << colnum << ' ' << rownum << endl;
		// Imprimimos máximo valor de gris
		output << 0xff << endl;
		for (i=0; i<rownum; ++i){
			for (j=0; j<colnum; ++j){
				output.write(reinterpret_cast<char*>(&m[i][j]),1+2*(formato=="PPM"));
			}
		}
	}      
}


/****************** Constructores, destructor y operadores ********************/
Imagen::Imagen(const Imagen& a_copiar) {
	colnum = a_copiar.colnum;
	rownum = a_copiar.rownum;

	reserva(rownum, colnum);

	for (int i = 0; i < rownum; ++i)
		for (int j = 0; j < colnum; ++j)
			m[i][j] = a_copiar.m[i][j];
}

Imagen& Imagen::operator=(const Imagen& nueva) {
	Imagen copia(nueva); // Se destruirá en el destructor

	Pixel** aux = m;
	m = copia.m;
	copia.m = aux;

	int iaux = colnum;
	colnum = copia.colnum;
	copia.colnum = iaux;

	iaux = rownum;
	rownum = copia.rownum;
	copia.rownum = iaux;

	return *this;
}

Imagen::~Imagen() {
	cerr << rownum << endl;
	for (int i = 0; i < rownum; ++i)
		delete[] m[i];
	
	delete[] m;
}

/****************** Métodos públicos ********************/

void Imagen::leer(const char* nombre_archivo,const char* mascara) {
	// Leemos PPM o PGM. Podríamos reusar el lector con cualquier otro tipo
	leerNetpbm(nombre_archivo, mascara);
}

void Imagen::escribir(const char* nombre_archivo,const string formato) {
	if (formato == "PPM" || formato == "PGM"){
		genNetpbm(nombre_archivo,formato);
	}
	else
		throw invalid_argument("Formato de salida de tipo desconocido");
}


/** 
 * @brief Obtiene una nueva imagen que es la versión rotada de una imagen de entrada
 * @param Io: imagen de entrada
 * @param angulo: angulo a rotar la imagen de entrada. Debe estar en radianes.
 * @return Una nueva imagen que es la versión rotada de Io.
 * */

Imagen& Imagen::rotar(double angulo, uint8_t opacidad){
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
	
	for(int i=0; i<4; ++i){    
		x = corners[i][0]*coseno + corners[i][1]*seno;
		new_col_min=(x < new_col_min ? x : new_col_min);
		new_col_max=(x > new_col_max ? x : new_col_max);
		
		y = -corners[i][0]*seno + corners[i][1]*coseno;
		new_row_min=(y < new_row_min ? y : new_row_min);
		new_row_max=(y > new_row_max ? y : new_row_max);
	}
	
	newimgrows=(unsigned)ceil((double)new_row_max-new_row_min);
	newimgcols=(unsigned)ceil((double)new_col_max-new_col_min);

	Imagen I_output(newimgrows,newimgcols);
	
	for (int rows=0;rows<newimgrows;rows++){
		for(int cols=0;cols<newimgcols;cols++){
			// Buscamos el pixel antiguo que al rotar da como resultado el nuevo
			int old_col=ceil((cols+new_col_min)*coseno-
							 (rows+new_row_min)*seno);
			int old_row=ceil((cols+new_col_min)*seno+
							 (rows+new_row_min)*coseno);
			
		   if((old_row>=0)&&(old_row<rownum)&&
			  (old_col>=0)&&(old_col<colnum)){
				I_output.m[rows][cols] = m[old_row][old_col];
			}
			else{
				/*I_output->m[rows][cols].r=I_output->m[rows][cols].g=I_output->m[rows][cols].b=0xff;
				// Probar I_output->m[rows][cols] = 0xffffff00
				I_output->m[rows][cols].alpha=opacidad;*/
				I_output.m[rows][cols] = 0xffffff00;
			}
		}
	}

	*this = I_output;

	return *this;
	//return I_output;
}

void Imagen::superponer(const Imagen& nueva, Imagen::Posicion lugar) {}

/*
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
	double angulo=atof(argv[2]);
	angulo = angulo*(M_PI)/180; //Pasamos el angulo radianes
	Imagen nueva= I.rotar(angulo);
	nueva.escribir(argv[3]);  
}*/
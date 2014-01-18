#include "imagen.h"
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

/****************** Métodos privados ********************/
void Imagen::reserva(unsigned int nr, unsigned int nc) {
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
					input.read(reinterpret_cast<char *>(&m[i][j]),1+2*(tipo==PPM));
					if (tipo == PGM)
						m[i][j].b = m[i][j].g = m[i][j].r;
					if (mascara != NULL)
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

	// Ajustamos cantidades de filas y columnas,
	// imprescindible en `copia` para el destructor 
	int iaux = colnum;
	colnum = copia.colnum;
	copia.colnum = iaux;

	iaux = rownum;
	rownum = copia.rownum;
	copia.rownum = iaux;

	return *this;
}

Imagen::~Imagen() {
	for (int i = 0; i < rownum; ++i)
		delete[] m[i];
	
	delete[] m;
}

/****************** Métodos públicos ********************/

Imagen& Imagen::leer(const char* nombre_archivo,const char* mascara) {
	// Leemos PPM o PGM. Podríamos reusar el lector con cualquier otro tipo
	leerNetpbm(nombre_archivo, mascara);
	return *this;
}

Imagen& Imagen::escribir(const char* nombre_archivo,const string formato) {
	if (formato == "PPM" || formato == "PGM"){
		genNetpbm(nombre_archivo,formato);
	}
	else
		throw invalid_argument("Formato de salida de tipo desconocido");

	return *this;
}


/** 
 * @brief Obtiene una nueva imagen que es la versión rotada de una imagen de entrada
 * @param Io: imagen de entrada
 * @param angulo: angulo a rotar la imagen de entrada. Debe estar en radianes.
 * @return Una nueva imagen que es la versión rotada de Io.
 * */

Imagen& Imagen::rotar(double angulo) {
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
            y = corners[i][1]*coseno - corners[i][0]*seno; 
            
            new_col_min=MIN(x,new_col_min);
            new_col_max=MAX(x,new_col_max);
            new_row_min=MIN(y,new_row_min);
            new_row_max=MAX(y,new_row_max);
        }
	
	newimgrows=(unsigned)ceil((double)new_row_max-new_row_min);
	newimgcols=(unsigned)ceil((double)new_col_max-new_col_min);

	Imagen nueva(newimgrows,newimgcols);
	
	for (int rows=0;rows<newimgrows;rows++){
		for(int cols=0;cols<newimgcols;cols++){
			// Buscamos el pixel antiguo que al rotar da como resultado el nuevo
			int old_col=ceil((cols+new_col_min)*coseno-
							 (rows+new_row_min)*seno);
			int old_row=ceil((cols+new_col_min)*seno+
							 (rows+new_row_min)*coseno);
			
			nueva.m[rows][cols] =
				(old_row >= 0 && old_row < rownum && old_col >= 0 && old_col < colnum) ? 
				m[old_row][old_col] :
				0xffffffff; // Valor por defecto: blanco transparente
		}
	}

	*this = nueva;

	return *this;
}

Imagen& Imagen::superponer(const Imagen& nueva, Imagen::Posicion lugar) {
	int v_begin = MAX(MIN(lugar.first, rownum), 0);
	int v_end = MAX(MIN(lugar.first + nueva.rownum, rownum), 0);
	int h_begin = MAX(MIN(lugar.second, colnum), 0);
	int h_end = MAX(MIN(lugar.second + nueva.colnum, colnum), 0);

	for (int i = v_begin; i < v_end; ++i)
		for (int j = h_begin; j < h_end; ++j) {
			int k = i-lugar.first, l = j-lugar.second;
			double opacity = nueva.m[k][l].alpha/255.0;

			m[i][j].r = m[i][j].r*(1-opacity) + nueva.m[k][l].r*opacity;
			m[i][j].g = m[i][j].g*(1-opacity) + nueva.m[k][l].g*opacity;
			m[i][j].b = m[i][j].b*(1-opacity) + nueva.m[k][l].b*opacity;
		}

	return *this;
}

Imagen& Imagen::aplicarOpacidad(uint8_t nuevoalpha) {
	double opacity = nuevoalpha/255.0;

	for (int i = 0; i < rownum; ++i)
		for (int j = 0; j < colnum; ++j)
				m[i][j].alpha *= opacity;

	return *this;
}
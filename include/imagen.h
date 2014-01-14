#ifndef __IMAGEN
#define __IMAGEN

#include <fstream>
#include "pixel.h"
#include "imagenES.h"

using std::ifstream;

class Imagen {
	Pixel ** m;
	int colnum, rownum;

	/**
	  * @brief Tipo de imagen
	  *
	  * Declara una serie de constantes para representar los distintos tipos
	  * de imágenes que se pueden manejar.
	  *
	  * @see LeerTipoImagen
	  */
	enum TipoImagen {
		IMG_DESCONOCIDO, ///< Tipo de imagen desconocido
		IMG_PGM,         ///< Imagen tipo PGM
		IMG_PPM          ///< Imagen tipo PPM
	};

	/**
	  * @brief Consulta el tipo de imagen del archivo y sus dimensiones
	  *
	  * @param nombre indica el nombre del archivo de disco a consultar
	  * @param filas Parámetro de salida con las filas de la imagen.
	  * @param columnas Parámetro de salida con las columnas de la imagen.
	  * @return Devuelve el tipo de la imagen en el archivo
	  *
	  * @see TipoImagen
	  */
	TipoImagen leerTipo(ifstream& f);
	char saltarSeparadores(ifstream& f);
	bool leerCabecera(ifstream& f);


	void leerPPM(ifstream& f, const char nombre_mascara[]);
	void leerPGM(ifstream& f, const char nombre_mascara[]);
	void reserva(int, int);

public:
	struct Posicion {
		unsigned int i, j;
	};
	Imagen() {
		m = 0;
	}
	Imagen(int nr, int nc) {
		reserva(nr, nc);
	};
	~Imagen() {
		for (int i = 0; i < rownum; ++i)
			delete[] m[i];
		delete[] m;
	};
	
	Pixel* operator[](unsigned int i) { // l-value
		return m[i];
	}

	Imagen rotar(double angulo);
	void superponer(const Imagen& nueva, Posicion lugar);

	void leer(char nombre_archivo[], char nombre_mascara[]);
	void escribir(char* nombre_archivo);
};

#endif
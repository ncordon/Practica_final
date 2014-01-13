#ifndef __IMAGEN
#define __IMAGEN

#include "pixel.h"
#include "imagenES.h"

class Imagen {
	Pixel ** m;
	int colnum, rownum;
public:
	struct Posicion {
		unsigned int i, j;
	};
	Imagen() {
		m = 0;
	}
	Imagen(int nr, int nc) {
		m = new Pixel*[nr];
		for (int i = 0; i < nr; ++i)
			m[i] = new Pixel[nc];
	};
	~Imagen() {
		for (int i = 0; i < rownum; ++i)
			delete[] m[i];
		delete[] m;
	};
	
	Pixel* operator[](unsigned int i) { // l-value
		return m[i];
	}
/*	const Pixel* operator[](unsigned int i) const { // r-value
		return m + i;
	}*/

	Imagen rotar(double angulo);
	void superponer(const Imagen& nueva, Posicion lugar);

	void leer(char* nombre_archivo);
	void escribir(char* nombre_archivo);
};

#endif
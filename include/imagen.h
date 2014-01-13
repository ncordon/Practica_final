#ifndef __IMAGEN
#define __IMAGEN

#include "pixel.h"
#include "imagenES.h"

class Imagen {
	Pixel ** m;
	int colnum, rownum;

	bool leerPPM(char* nombre_archivo);
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

	void leer(char* nombre_archivo);
	void escribir(char* nombre_archivo);
};

#endif
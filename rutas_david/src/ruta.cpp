#include "ruta.h"


istream& operator>>(istream& in, Ruta& a_leer) {
	in >> a_leer.code;
	
	int numpuntos;
	in >> numpuntos;

	for (int i = 0; i < numpuntos; ++i) {
		descartaBlancos(in);

		Punto nuevo;
		in >> nuevo;
		a_leer.push_back(nuevo);
	}

	return in;
}

ostream& operator<<(ostream& out, const Ruta& a_mostrar) {
	for (Ruta::const_iterator it = a_mostrar.begin(); it != a_mostrar.end(); ++it) {
		out << *it << " ";
	}

	return out;
}
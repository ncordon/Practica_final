#include "punto.h"

bool operator<(const Punto& uno, const Punto& otro) {
	return uno.lat < otro.lat || (uno.lat == otro.lat && uno.lon < otro.lon);
}

bool operator==(const Punto& uno, const Punto& otro) {
	return uno.lat == otro.lat && uno.lat == otro.lat;
}

ostream& operator<<(ostream& out, const Punto& a_mostrar) {
	out << "(" << a_mostrar.lat << ", " << a_mostrar.lon << ")";
	if (a_mostrar.desc != "")
		out << " \"" << a_mostrar.desc << "\"";

	return out;
}

istream& operator>>(istream& in, Punto& a_leer) {
	char ignored;
	in >> ignored; // Ignoramos '('
	in >> a_leer.lat;
	in >> ignored; // Ignoramos ','
	in >> a_leer.lon;
	in >> ignored; // Ignoramos ')'

	return in;
}
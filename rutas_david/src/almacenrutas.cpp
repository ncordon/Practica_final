#include "almacenrutas.h"

AlmacenRutas::iterator AlmacenRutas::push_back(Ruta nueva) {
	// Hacer copia en memoria dinámica de nueva???
	almacenadas.push_back(nueva);
	AlmacenRutas::iterator nueva_pos = --almacenadas.end();

	for (Ruta::iterator it = nueva.begin(); it != nueva.end(); it++) {
		p_asociadas[*it].push_back(nueva_pos);
	}

	c_asociada[nueva.codigo()] = nueva_pos;

	return nueva_pos;
}

AlmacenRutas::iterator AlmacenRutas::erase(AlmacenRutas::iterator a_borrar) {
	for (Ruta::iterator it = (*a_borrar).begin(); it != (*a_borrar).end(); ++it) {
		vector<iterator>* vecpunto = &p_asociadas[*it];
		vecpunto->erase(find(vecpunto->begin(), vecpunto->end(), a_borrar));
	}

	c_asociada.erase((*a_borrar).codigo());

	return almacenadas.erase(a_borrar);
}

vector<AlmacenRutas::iterator> AlmacenRutas::encontrarRutas(const Punto& incluido) {
	try {
		return p_asociadas.at(incluido);
	} catch(out_of_range& e) {
		vector<AlmacenRutas::iterator> vacio;
		return vacio;
	}
}

Ruta& AlmacenRutas::obtenerRuta(const Ruta::codigo_t& code) {
	try {
		return *(c_asociada.at(code));
	} catch(out_of_range& e) {
		Ruta* vacia = new Ruta;
		return *vacia;
	}
}

istream& operator>>(istream& in, AlmacenRutas& a_leer) {
	string a;
	in >> a;

	if (a == "#Rutas") {
		bool finrutas = false;
		descartaBlancos(in);

		while (!finrutas) {
			if (in.peek() != '#' && in) {
				Ruta rlocal;
				in >> rlocal;
				a_leer.push_back(rlocal);

				descartaBlancos(in);
			} else
				finrutas = true;
		}

		if (in.peek() == '#'){
			in >> a;
			
			if (a == "#Puntos_de_Interes"){
				descartaBlancos(in);
				Punto p;
				while (in >> p) {
					descartaBlancos(in);

					string aux;
					getline(in, aux);

					AlmacenRutas::iterator it;

					for (it = a_leer.begin(); it != a_leer.end(); ++it) {
						Ruta::iterator puntointeres = find((*it).begin(), (*it).end(), p);

						if (puntointeres != (*it).end()) {
							(*puntointeres).descripcion() = aux;
						}  
					}
				}
			}
		}	   
	}

	return in;
}

ostream & operator<<(ostream & out, const AlmacenRutas& a_mostrar){
	AlmacenRutas::const_iterator it;

	for (it = a_mostrar.begin(); it != a_mostrar.end(); ++it){
		out << (*it) << endl;
	}

	return out;
}
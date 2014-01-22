#ifndef _PUNTO
#define _PUNTO

#include <string>
#include <iostream>

using namespace std;

class Punto {
	double lat, /**< Latitud */
		lon; /**< Longitud */
	string desc; /**< Descripción */

public:
	/**
	 * Constructor por defecto
	 */
	Punto() 
		:lat(0), lon(0), desc(""){}

	/**
	 * Constructor con parámetros
	 * @param newlat Latitud
	 * @param newlong Longitud
	 * @param newdesc Descripción
	 */
	Punto(double newlat, double newlong, string newdesc="")
		:lat(newlat), lon(newlong), desc(newdesc) {}

	/**
	 * Consulta latitud
	 * @return latitud
	 */
	double latitud() {
		return lat;
	}

	/**
	 * Consulta longitud
	 * @return longitud
	 */
	double longitud() {
		return lon;
	}

	/**
	 * Modifica descripción
	 * @return descripción (referencia)
	 */
	string& descripcion() {
		return desc;
	}

	/**
	 * Consulta descripción
	 * @return descripción (referencia constante)
	 */
	const string& descripcion() const {
		return desc;
	}

	/**
	 * Operador comparación (menor que)
	 * @param uno primer objeto
	 * @param otro segundo objeto
	 * @return uno < otro
	 */
	friend bool operator<(const Punto& uno, const Punto& otro);

	/**
	 * Operador comparación de igualdad
	 * @param uno primer objeto
	 * @param otro segundo objeto
	 * @return uno == otro
	 */
	friend bool operator==(const Punto& uno, const Punto& otro);

	/**
	 * Operador de flujo de salida
	 * @param out flujo
	 * @param a_mostrar objeto a mostrar
	 * @return flujo de salida
	 */
	friend ostream& operator<<(ostream& out, const Punto& a_mostrar);

	/**
	 * Operador de flujo de entrada
	 * @param in flujo
	 * @param a_leer objeto a leer
	 * @return flujo de entrada
	 */
	friend istream& operator>>(istream& in, Punto& a_leer);
};

#endif
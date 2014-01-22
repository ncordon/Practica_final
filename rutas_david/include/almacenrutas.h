#ifndef _ALMACEN
#define _ALMACEN

#include "punto.h"
#include "ruta.h"
#include "extra.h"
#include <list>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <algorithm>

using namespace std;

class AlmacenRutas {
public:
	typedef list<Ruta>::iterator iterator; /**< Clase iterador */
	typedef list<Ruta>::const_iterator const_iterator; /**< Clase iterador constante */

private:
	list<Ruta> almacenadas; /**< Lista de objetos de Ruta */
	map<Ruta::codigo_t, iterator > c_asociada; /**< Diccionario que asocia códigos con posiciones de rutas */
	map<Punto, vector<iterator> > p_asociadas; /**< Diccionario que asocia Puntos con Rutas a las que pertenecen */

public:
	/**
	 * Inicio, como iterador constante
	 * @return primera ruta del almacén
	 */
	const_iterator begin() const {
		return almacenadas.begin();
	}
	/**
	 * Final, como iterador constante
	 * @return final del almacén
	 */
	const_iterator end() const {
		return almacenadas.end();
	}
	/**
	 * Inicio, como iterador normal
	 * @return primera ruta del almacén
	 */
	iterator begin() {
		return almacenadas.begin();
	}
	/**
	 * Final, como iterador normal
	 * @return final del almacén
	 */
	iterator end() {
		return almacenadas.end();
	}

	/**
	 * Constructor por defecto
	 */
	AlmacenRutas(){}

	/**
	 * Tamaño del almacén
	 * @return cantidad de objetos de Ruta
	 */
	unsigned int size() {
		return almacenadas.size();
	}

	/**
	 * Añadir Ruta
	 * @param nueva Ruta a añadir
	 * @return posición de la ruta
	 */
	iterator push_back(Ruta nueva);

	/**
	 * Borrar Ruta
	 * @param a_borrar Ruta a borrar
	 * @return posición de la ruta anterior
	 */
	iterator erase(iterator a_borrar);

	/**
	 * Rutas que contienen un Punto
	 * @param incluido Punto a buscar en las Rutas
	 * @return vector de posiciones a Rutas en el almacén
	 */
	vector<iterator> encontrarRutas(const Punto& incluido);

	/**
	 * Obtener Ruta de código
	 * @param code Código asociado a la Ruta
	 * @return referencia a la ruta
	 */
	Ruta& obtenerRuta(const Ruta::codigo_t& code);

	/**
	 * Operador de flujo de salida
	 * @param out flujo
	 * @param a_mostrar objeto a mostrar
	 * @return flujo de salida
	 */
	friend ostream& operator<<(ostream& out, const AlmacenRutas& a_mostrar);

	/**
	 * Operador de flujo de entrada
	 * @param in flujo
	 * @param a_leer objeto a leer
	 * @return flujo de entrada
	 */
	friend istream& operator>>(istream& in, AlmacenRutas& a_leer);
};

#endif
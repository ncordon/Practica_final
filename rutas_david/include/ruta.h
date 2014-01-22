#ifndef _RUTA
#define _RUTA

#include "punto.h"
#include "extra.h"
#include <list>
#include <string>

class Ruta {
public:
	typedef std::string codigo_t; /**< Tipo del código de la ruta */
	typedef list<Punto>::iterator iterator; /**< Clase iterador */
	typedef list<Punto>::const_iterator const_iterator; /**< Clase iterador constante */

private:
	list<Punto> camino; /**< Lista de Puntos que representan la Ruta */
	codigo_t code; /**< Código asociado a la ruta */

public:
	/**
	 * Inicio, como iterador constante
	 * @return inicio de la ruta
	 */
	const_iterator begin() const {
		return camino.begin();
	}
	/**
	 * Final, como iterador constante
	 * @return final de la ruta
	 */
	const_iterator end() const {
		return camino.end();
	}
	/**
	 * Inicio, como iterador normal
	 * @return inicio de la ruta
	 */
	iterator begin() {
		return camino.begin();
	}
	/**
	 * Final, como iterador normal
	 * @return final de la ruta
	 */
	iterator end() {
		return camino.end();
	}

	/**
	 * Añadir Punto a la Ruta
	 * @param nuevo Punto a agregar
	 * @return posición del punto
	 */
	iterator push_back(const Punto& nuevo) {
		camino.push_back(nuevo);

		return --camino.end();
	}

	/**
	 * Borrar Punto de la Ruta
	 * @param a_borrar iterador al Punto a borrar
	 * @return posición del Punto anterior
	 */
	iterator erase(iterator a_borrar) {
		return camino.erase(a_borrar);
	}

	/**
	 * Tamaño de la Ruta
	 * @return tamaño
	 */
	unsigned int size() {
		return camino.size();
	}

	/**
	 * Consulta código de la Ruta
	 * @return código (ref. constante)
	 */
	const codigo_t& codigo() const {
		return code;
	}
	
	/**
	 * Modifica cósigo de la Ruta
	 * @return código (ref. variable)
	 */
	codigo_t& codigo() {
		return code;
	}

	/**
	 * Operador de flujo de entrada
	 * @param in flujo
	 * @param a_leer objeto a leer
	 * @return flujo de entrada
	 */
	friend istream& operator>>(istream& in, Ruta& a_leer);

	/**
	 * Operador de flujo de salida
	 * @param out flujo
	 * @param a_mostrar objeto a mostrar
	 * @return flujo de salida
	 */
	friend ostream& operator<<(ostream& out, const Ruta& a_mostrar);
};

#endif
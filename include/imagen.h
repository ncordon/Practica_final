#ifndef __IMAGEN
#define __IMAGEN

#include "pixel.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <string>
#include <map>
#include <fstream>
using namespace std;

/**
 * @class Imagen
 * TDA que permite almacenar una serie de píxeles que representan una imagen,
 * además de las dimensiones de la misma
 */
class Imagen {
	/// Puntero a matriz de píxeles
	Pixel ** m;
	/// Dimensiones
	int colnum, rownum;
	/**
	 * @enum Tipos de imágenes disponibles
	 */
	enum TipoImagen{PPM,PGM,UNKNOWN};
	/**
	 * @brief Permite decodificar una imagen en portable format
	 * @param nombre_archivo
	 * @param mascara máscara de opacidad del archivo
	 * @note Método privado
	 */
	void leerNetpbm (const char* nombre_archivo, const char* mascara=0);
	/**
	 * @brief Permite generar imagen en Portable format
	 * @param nombre_archivo
	 * @note Método privado
	 */
	void genNetpbm (const char* nombre_archivo, const string& formato);
	/**
	 * @brief Permite reservar espacio para almacenar la imagen
	 * @param nr número de filas
	 * @param nc número de columnas
	 * @note Método privado
	 */
	void reserva(unsigned int nr, unsigned int nc);
	/**
	 * @brief Permite leer el tipo de imagen que se va a tratar
	 * @param file flujo de archivo abierto
	 * @return TipoImagen
	 */
	TipoImagen leerTipo(ifstream& input);
	/**
	 * @brief Permite leer la cabecera de una imagen
	 * @param input flujo de archivo abierto
	 * @param filas a rellenar
	 * @param columnas a rellenar
	 * @return true si lectura correcta
	 * 
	 * Extrae los comentarios del fichero, lee las dimensiones, y comprueba
	 * que se encuentren en el rango correcto 
	 */
	bool leerCabecera (ifstream& input, int& filas, int& columnas);
	/**
	 * @brief Permite extraer del flujo separadores como espacios
	 * @param input flujo de archivo abierto
	 * @return último carácter leído que no es un separador
	 */
	char saltarSeparadores (ifstream& input);
	
public:
	/**
	 * @brief ///Falta describir
	 */
	typedef pair<unsigned int,unsigned int> Posicion;    
	/**
	 * @brief Constructor sin parámetros.
	 * Crea imagen vacía
	 */
	Imagen() {
		m = 0;
		rownum = colnum = 0;
	}
	/**
	 * @brief Constructor con parámetros, crea una imagen vacía del tamaño especificado
	 * @param nr número de filas
	 * @param nc número de columnas
	 */
	Imagen(unsigned int nr, unsigned int nc) 
		:rownum(nr), colnum(nc) {
		reserva(nr, nc);
	}

	/**
	 * @brief Constructor de copia
	 * @param a_copiar objeto de Imagen original
	 */
	Imagen(const Imagen& a_copiar);

	/**
	 * @brief Sobrecarga del operador de igualdad
	 * @param nueva Objeto de Imagen a copiar en el actual
	 * @return Referencia al objeto actual
	 */
	Imagen& operator=(const Imagen& nueva);

	/**
	 * @brief Destructor
	 */
	~Imagen();

	/**
	 * @brief Sobrecarga del operador [] para consulta y modificación
	 * @note No comprueba rango
	 */
	Pixel* operator[](unsigned int i) { // l-value
		return m[i];
	}
	/**
	 * @brief Permite rotar la imagen actual
	 * @param angulo de rotación en radianes
	 * @return referencia al objeto actual
	 */
	Imagen& rotar(double angulo);
	/**
	 * @brief Permite realizar un pegado de una imagen sobre la actual
	 */
	Imagen& superponer(const Imagen& nueva, Posicion lugar);
	/**
	 * @brief Permite leer una imagen almacenándo su decodificación en píxeles
	 * @param nombre_archivo
	 */
	Imagen& leer(const char* nombre_archivo, const char* mascara);
	/**
	 * @brief (otra función graciosa)
	 * @param nombre_archivo
	 */
	Imagen& escribir(const char* nombre_archivo, const string formato);
	
	/* Depuración*/
	friend ostream& operator << (ostream& output, const Imagen& img); 
};

#endif
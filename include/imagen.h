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
#include <inttypes.h>

using namespace std;

/**
 * @class Imagen
 * TDA que permite almacenar una serie de píxeles que representan una imagen,
 * y realizar operaciones básicas como lectura, escritura y rotado de la misma.
 *
 * @author I. Cordón, F.D. Charte
 */
class Imagen {
    /**
     * @page repImg Representación del TDA Imagen
     *
     * @section inv Invariante de la representación
     *
     * Una imagen válida contiene una cantidad positiva o 0 de píxeles
     * (objetos de Pixel). El número de filas (`rownum`) y columnas (`colnum`) ha de ser
     * por tanto positivo o 0.
     *
     * @section fa Función de abstracción
     * Un objeto válido *img* del TDA Imagen representa la imagen
     *
     * *img.m[0][0]* *img.m[0][1]* *img.m[0][2]* ...
     *
     * *img.m[1][0]* *img.m[1][1]* *img.m[1][2]* ...
     *
     * *img.m[2][0]* *img.m[2][1]* *img.m[2][2]* ...
     *
     * ...
     * 
     */
	///< Puntero a matriz de píxeles
	Pixel ** m;
	unsigned int colnum, ///< Número de columnas
		rownum; ///< Número de filas
	/**
	 * @enum TipoImagen Tipos de imágenes disponibles
	 */
	enum TipoImagen{PPM,PGM,UNKNOWN};
	/**
	 * @brief Permite decodificar una imagen en Portable format
	 * @param nombre_archivo
	 * @param mascara máscara de opacidad del archivo
	 * @note Método privado
	 */
	void leerNetpbm (const char* nombre_archivo, const char* mascara=0);
	/**
	 * @brief Permite generar imagen en Portable format
	 * @param nombre_archivo
         * @param formato de entre PPM y PGM
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
	 * @param input flujo de archivo abierto
	 * @return Tipo de la Imagen
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
	 * @brief Permite almacenar la posición en filas,columnas de pegado de un país
	 */
	typedef pair<unsigned int,unsigned int> Posicion;    
	/**
	 * @brief Constructor sin parámetros.
	 * Crea imagen vacía
	 */
	Imagen()
            :m(0),rownum(0),colnum(0) {}
	/**
	 * @brief Constructor con parámetros, crea una imagen vacía del tamaño especificado
	 * @param nr número de filas
	 * @param nc número de columnas
	 */
	Imagen(unsigned int nr, unsigned int nc) 
		:rownum(nr),colnum(nc) {
		reserva(nr,nc);
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
         * @brief Permite obtener el número de filas
         */
        int numFilas(){ return rownum; }    
        /**
         * @brief Permite obtener el número de columnas
         */
        int numColumnas(){ return colnum; }
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
	 * @param nueva Imagen a pegar sobre la actual
	 * @param lugar Posición (fila, columna) donde ubicar la Imagen `nueva`
	 * @return referencia al objeto actual
	 */
	Imagen& superponer(const Imagen& nueva, Posicion lugar);
	/**
	 * @brief Aplica una transparencia uniforme en todos los píxeles visibles
	 * @param nuevoalpha nuevo valor de opacidad (de 0x0 a 0xff)
	 * @return referencia al objeto actual
	 */
	Imagen& aplicarOpacidad(uint8_t nuevoalpha);
	/**
	 * @brief Permite leer una imagen almacenándo su decodificación en píxeles
	 * @param nombre_archivo
         * @param mascara de opacidad (Si no hay, se hace pegado opaco)
	 */
	Imagen& leer(const char* nombre_archivo, const char* mascara = 0);
	/**
	 * @brief Permite leer una imagen desde un archivo dado
	 * @param nombre_archivo
         * @param formato para lectura de imagen
	 */
	Imagen& escribir(const char* nombre_archivo, const string formato);
	/**
         * @brief Sobrecarga del operador << para imprimir imágenes
         * @param output flujo de salida
         * @param img a imprimir
         */
	friend ostream& operator << (ostream& output, const Imagen& img); 
};
#endif
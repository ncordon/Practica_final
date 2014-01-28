#ifndef __PAIS
#define __PAIS
#include "imagen.h"
#include "punto.h"

struct Pais;

/**
 * @class Paises
 * 
 * TDA que permite almacenar una serie de Paises, indexándolos mediante su 
 * localización geográfica
 * 
 * @author I. Cordón, F.D. Charte
 */
class Paises : public std::map<Punto,Pais> {
private:
    /**
     * @page repPais Representación del TDA Paises
     *
     * @section inv Invariante de la representación
     *
     * Se acepta cualquier asociación de objetos válidos de Punto
     * y Pais.
     *
     * @section fa Función de abstracción
     * Un objeto válido *p* del TDA Paises representa la secuencia
     *
     * {punto_1: pais_1, punto_2: pais_2, ...}
     * 
     */
    ///< Almacena el path del directorio contenedor de banderas de países
    string dir_banderas;
public:
    /**
     * @brief Constructor sin parámetros
     */
    Paises(){}
    /**
     * @brief Constructor
     * @param dir path al directorio que almacena las banderas
     */
    Paises(string dir):dir_banderas(dir){}
    /**
     * @brief Sobrecarga del operador de lectura
     * @param input
     * @param p instancia del TDA Paises
     * 
     * Dado un flujo de datos, lee del mismo un conjunto de países
     */
    friend istream& operator>>(istream &input, Paises& p);
};

/**
 * @class Pais
 * Se identifican los Países con objetos Punto
 * 
 * @author I. Cordón, F.D. Charte
 */
class Pais {
private:
    /**
     * @page repPais Representación del TDA Pais
     *
     * @section inv Invariante de la representación
     *
     * Se acepta cualquier nombre (`string`) no vacío, y un objeto 
     * válido de la clase Imagen.
     *
     * @section fa Función de abstracción
     * Un objeto válido *p* del TDA Pais representa el País
     *
     * Nombre: *p.nombre_pais*
     * Bandera: *p.bandera_img*
     * 
     */
    ///< Almacena el nombre del país
    string nombre_pais;
    ///< Almacena la imagen de la bandera del país
    Imagen bandera_img;

public:
    /**
     * @brief Constructor por defecto
     * Crea un objeto Pais vacío
     */
    Pais(){}
    /**
     * @brief Constructor con parámetro
     * @param pais
     * @param path_bandera
     */
    Pais(string pais, char* path_bandera)
        :nombre_pais(pais){
        bandera_img.leer(path_bandera);
    }

    string& nombre() {
        return this->nombre_pais;
    }
    const string& nombre() const {
        return this->nombre_pais;
    }
    Imagen& bandera() {
        return this->bandera_img;
    }
    const Imagen& bandera() const {
        return this->bandera_img;
    }
};

#endif
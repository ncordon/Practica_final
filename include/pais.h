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
 */
class Paises: public std::map<Punto,Pais>{
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
    friend istream& operator >>(istream &input, Paises& p);
};

/**
 * @class Pais
 * Se identifican los Países con objetos Punto
 * 
 */
class Pais:public Punto{
    ///< Almacena el nombre del país
    string nombre_pais;
    ///< Almacena la imagen de la bandera del país
    Imagen bandera_img;

public:
    /**
     * @brief Constructor por defecto
     * Crea un objeto Pais vacío
     */
    Pais():Punto(){}
    /**
     * @brief Constructor con parámetros
     * @param latitud
     * @param longitud
     * @param pais
     * @param path_bandera
     */
    Pais(double latitud, double longitud, string pais, char* path_bandera)
        :Punto(latitud,longitud), nombre_pais(pais){
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
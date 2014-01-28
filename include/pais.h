#ifndef __PAIS
#define __PAIS
#include "imagen.h"
#include "punto.h"
#include <set>

class Paises;
class Pais;

typedef std::set<Pais> ConjuntoPaises;

/**
 * @class Paises
 * 
 * TDA que permite almacenar una serie de Paises, indexándolos mediante su 
 * localización geográfica
 * 
 * @author I. Cordón, F.D. Charte
 */
class Paises : public ConjuntoPaises {
private:
    /**
     * @page repPaises Representación del TDA Paises
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
 * Se identifican los Países con objetos Punto, más una bandera
 * 
 * @author I. Cordón, F.D. Charte
 */
struct Pais : public Punto {

    /**
     * @page repPais Representación del TDA Pais
     *
     * @section inv Invariante de la representación
     *
     * Derivado de Punto, y además se acepta cualquier objeto válido
     * de Imagen como *bandera*
     *
     * @section fa Función de abstracción
     * Un objeto válido *p* del TDA Pais representa el País
     *
     * Nombre: *p.desc*
     * Bandera: *p.bandera_img*
     * Ubicación: (*p.first()*, *p.second()*)
     * 
     */
    ///< Almacena la imagen de la bandera del país
    Imagen bandera;

    /**
     * @brief Constructor por defecto
     * Crea un objeto Pais vacío
     */
    Pais()
        :Punto() {}

    /**
     * @brief Constructor con parámetros
     * @param p Punto a inicializar
     */
    Pais(const Punto& p)
        :Punto(p) {}
    /**
     * @brief Constructor con parámetros
     * @param latitud
     * @param longitud
     * @param pais
     * @param path_bandera
     */
    Pais(double latitud, double longitud, string pais, char* path_bandera)
        :Punto(latitud, longitud, pais) {
        bandera.leer(path_bandera);
    }
};


#endif
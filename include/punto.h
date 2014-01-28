#ifndef __PUNTO
#define __PUNTO

#include <string>
#include <iostream>
#include <cmath>
using namespace std;

/**
 * @file punto.h
 */

/**
 * @class Punto
 * 
 * TDA Punto. Permite almacenar y acceder a puntos de RxR que representan la
 * localización geográfica de un punto, via su latitud y su longitud
 * 
 * @author I. Cordón, F.D. Charte
 */

class Punto:public std::pair<double,double> {
    /**
     * @page repPunto Representación del TDA Punto
     *
     * @section inv Invariante de la representación
     *
     * Se acepta cualquier par de flotantes que representen un lugar geográfico
     * puntual en la Tierra. Además, una descripción (puede ser vacía).
     *
     * @section fa Función de abstracción
     * Un objeto válido *pt* del TDA Punto representa el lugar
     *
     * Latitud: *pt.first*
     * Longitud: *pt.second*
     * Descripción: *pt.desc*
     * 
     */
    string desc;         ///< Descripción sobre el punto
public:
    /**
     * @brief Constructor por defecto
     */
    Punto(){}
    /**
     * @brief Constructor con parámetros
     * @param lat Latitud
     * @param lon Longitud
     * @param descripcion Descripción del punto
     */
    Punto (double lat, double lon, string descripcion="")
        :pair(lat,lon),desc(descripcion) {}
    /**
     * @brief Permite modificar la descripción de un punto
     * @return referencia a la descripción del punto
     */
    string& descripcion() { return desc; }
    /**
     * @brief Permite consultar la descripción de un punto
     * @return referencia constante a la descripción del punto
     */
    const string& descripcion() const { return desc; }
    /**
     * @brief Operador de asignación
     * @param otro_punto instancia de Punto a copiar
     * @return referencia a this
     */
    Punto& operator=(const Punto& otro_punto);
    /**
     * @brief Permite leer un punto desde la entrada estándar
     * @param input stream de entrada
     * @param un_punto instancia de Punto a rellenar
     * @return flujo de entrada
     * @note función amiga
     */
    friend istream& operator >>(istream& input, Punto& un_punto);
    /**
     * @brief Permite imprimir un punto
     * @param output stream de salida
     * @param un_punto instancia de Punto a imprimir
     * @return flujo de salida
     * @note función amiga
     */
    friend ostream& operator <<(ostream& output, const Punto& un_punto);
    /**
     * @brief Operador de igualdad
     * @param otro_punto
     * @return true si son iguales
     */
    bool operator ==(const Punto& otro_punto) const {
        return ((otro_punto.first==first) &&
                (otro_punto.second==second) &&
                (otro_punto.desc==desc));
    }
    /**
     * @brief Operador <
     * @param otro_punto
     * Comprueba si el punto es menor que otro_punto en base al orden lexicográfico
     * de sus coordenadas
     */
    bool operator <(const Punto& otro_punto) const {
        return ((first<otro_punto.first)
                || (first==otro_punto.first
                && (second<otro_punto.second)));
    }
    /**
     * @brief Permite calcular la distancia entre dos puntos
     * @param otro_punto al que calcular la distancia
     * @return distancia euclídea entre las coordenadas de ambos puntos
     */
    double distancia (const Punto& otro_punto) {
        return sqrt((first-otro_punto.first)*(first-otro_punto.first)+
                    (second-otro_punto.second)*(second-otro_punto.second));
    }
};
#endif
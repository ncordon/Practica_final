#ifndef __PUNTO
#define __PUNTO

#include <string>
#include <iostream>
using namespace std;

/**
 * @file punto.h
 */

/**
 * @class Punto
 * 
 * TDA Punto. Permite almacenar y acceder a puntos de RxR que representan la
 * localización geográfica de un punto, vía su latitud y su altitud
 * 
 */

class Punto{
private:
    double latitud;             ///< Latitud de un punto    
    double longitud;            ///< Longitud de un punto
    string descripcion;         ///< Descripción sobre el punto
public:
    /**
     * @brief Constructor por defecto
     */
    Punto(){}
    /**
     * @brief Constructor con parámetros
     * @param latitud
     * @param longitud
     * @param descripcion
     */
    Punto (double latitud, double longitud, string descripcion="");
    /**
     * @brief Operador de asignación
     * @param otro_punto instancia de Punto a copiar
     * @return referencia a this
     */
    Punto& operator=(const Punto& otro_punto);
    /**
     * @brief Permite obtener la latitud de un punto
     * @return latitud
     */
    double getLatitud(){ return latitud; }
    /**
     * @brief Permite obtener la longitud de un punto
     * @return longitud
     */
    double getLongitud(){ return longitud; }
    /**
     * @brief Permite obtener la descripción de un punto
     * @return descripción del punto
     */
    string getDescripcion(){ return descripcion; }
    /**
     * @brief Permite agregar o cambiar la descripción del punto
     * @param descripcion cadena con la descripcion deseada
     */
    void setDescripcion(string descripcion){
        this->descripcion=descripcion;
    }
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
    bool operator == (const Punto& otro_punto){
        return ((otro_punto.latitud==this->latitud) &&
                (otro_punto.longitud==this->longitud) &&
                (otro_punto.descripcion==this->descripcion));
    }
    /**
     * @brief Operador <
     * @param otro_punto
     * Comprueba si el punto es menor que otro_punto en base al orden lexicográfico
     * de sus coordenadas
     */
    bool operator < (const Punto& otro_punto)const{
        return ((this->longitud<otro_punto.longitud)
                || (this->longitud==otro_punto.longitud 
                && (this->latitud<otro_punto.latitud)));
    }
};
#endif
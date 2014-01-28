#ifndef __RUTA
#define __RUTA

#include <list>
#include "punto.h"

/**
 * @class Ruta
 * 
 * TDA que permite almacenar una ruta mediante una sucesión de puntos que 
 * representan las coordenadas geográficas de los lugares de la ruta

 * @author I. Cordón, F.D. Charte
 */
class Ruta {
private:
    /**
     * @page repRuta Representación del TDA Ruta
     *
     * @section inv Invariante de la representación
     *
     * Se acepta cualquier número natural o 0 de objetos válidos de Punto.
     *
     * @section fa Función de abstracción
     * Un objeto válido *r* del TDA Ruta representa el camino
     *
     * *r.id*: *r.camino[0]* -> *r.camino[1]* -> ...
     * 
     */
    list <Punto> camino;            ///< Contiene la sucesión de coordenadas
    string id;                      ///< Identificador de la ruta
public:
    /// Iterador
    typedef list<Punto>::iterator iterator;
    /// Iterador constante
    typedef list<Punto>::const_iterator const_iterator;
    
    /**
     * @brief Iterador al inicio de la ruta
     * @return iterador al inicio de la ruta
     */
    iterator begin() {
        return camino.begin();
    }
    /**
     * @brief Iterador al final de la ruta
     * @return iterador al final de la ruta
     */
    iterator end() {
        return camino.end();
    }
    /**
     * @brief Iterador constante al inicio de la ruta
     * @return iterador constante al inicio de la ruta
     */
    const_iterator begin() const {
        return camino.begin();
    }
    /**
     * @brief Iterador constante al final de la ruta
     * @return iterador constante al final de la ruta
     */
    const_iterator end() const {
        return camino.end();
    }
    /**
     * @brief Permite encontrar un punto en la ruta
     * @return iterador a dicho Punto
     */
    iterator find(const Punto &pto) {
        iterator it;
        
        for (it = begin(); it != end() && !((*it) == pto); ++it);
        
        return it;
    }
    /**
     * @brief Constructor sin parámetros
     */
    Ruta() {}
    /**
     * @brief Constructor con parámetros
     * @param camino de Puntos
     * @param id identificador de la ruta
     */
    Ruta(list<Punto> camino, string id="") {
        this->camino=camino;
        this->id=id;
    }
    /**
     * @brief Permite agregar un nuevo punto a la ruta
     * @param pto instancia de la clase Punto
     * @note función inline
     */
    void agrega(const Punto& pto) {
        camino.push_back(pto);
    }
    /**
     * @brief Permite obtener el identificador de la ruta
     * @return identificador
     */
    string& identificador() {
        return id;
    }
    /**
     * @brief Permite modificar el identificador de ruta
     * @return identificador
     */
    const string& identificador() const {
        return id;
    }
    /**
     * @brief Permite borrar un punto de la ruta
     * @param pto a borrar
     * @return true si se hallaba en la ruta
     */
    void elimina(const Punto& pto) {
        camino.remove(pto);
    }

    /**
     * @brief Informa del tamaño de la Ruta
     * @return número de Puntos de la Ruta
     */
    int size() {
        return camino.size();
    }
    /**
     * @brief Permite leer una ruta desde la entrada estándar
     * @param input stream de entrada
     * @param una_ruta instancia de Ruta a rellenar
     * @return flujo de entrada
     * @note función amiga
     */
    friend istream& operator>>(istream& input, Ruta& una_ruta);
    /**
     * @brief Muestra una ruta en la entrada estándar
     * @param output stream de salida
     * @param una_ruta instancia de Ruta a imprimir
     * @return flujo de salida
     * @note función amiga
     */
    friend ostream& operator<<(ostream& output, const Ruta& una_ruta);
};
#endif
    
    
     
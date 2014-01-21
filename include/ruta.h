#ifndef __RUTA
#define __RUTA

#include <list>
#include "punto.h"

/**
 * @class Ruta
 * 
 * TDA que permite almacenar una ruta mediante una sucesión de puntos que 
 * representan las coordenadas geográficas de los lugares de la ruta
 */
class Ruta{
private:
    list <Punto> camino;            ///< Contiene la sucesión de coordenadas
    string id;                      ///< Identificador de la ruta
public:
    /// Iterador
    typedef list<Punto>::iterator iterator;
    /// Iterador constante
    typedef list<Punto>::const_iterator const_iterator;
    
    iterator begin(){
        return camino.begin();
    }
    iterator end(){
        return camino.end();
    }
    const_iterator begin()const{
        return camino.begin();
    }
    const_iterator end()const{
        return camino.end();
    }
    /**
     * @brief Permite encontrar un punto en la ruta
     * @return iterador a dicho Punto
     */
    iterator find(const Punto &pto){
        iterator it;
        
        for (it=begin(); it!=end() && !((*it)==pto);++it){}
        
        return it;
    }
    /**
     * @brief Constructor sin parámetros
     */
    Ruta(){}
    /**
     * @brief Constructor con parámetros
     * @param camino de Puntos
     * @param id identificador de la ruta
     */
    Ruta(list<Punto> camino, string id=""){
        this->camino=camino;
        this->id=id;
    }
    /**
     * @brief Permite agregar un nuevo punto a la ruta
     * @param pto instancia de la clase Punto
     * @note función inline
     */
    void aniade(const Punto& pto){
        camino.push_back(pto);
    }
    /**
     * @brief Permite obtener el identificador de la ruta
     * @return identificador
     */
    string getID(){
        return id;
    }
    /**
     * @brief Permite modificar el identificador de ruta
     * @param id nuevo identificador
     */
    void setID(string id){
        this->id=id;
    }
    /**
     * @brief Permite borrar un punto de la ruta
     * @param pto a borrar
     * @return true si se hallaba en la ruta
     */
    void elimina(const Punto& pto){
        camino.remove(pto);
    }
    int getTamanio(){
        return camino.size();
    }
    /**
     * @brief Permite leer una ruta desde la entrada estándar
     * @param input stream de entrada
     * @param una_ruta instancia de Ruta a rellenar
     * @return flujo de entrada
     * @note función amiga
     */
    friend istream& operator >> (istream& input, Ruta& una_ruta);
    /**
     * @brief Muestra una ruta en la entrada estándar
     * @param output stream de salida
     * @param una_ruta instancia de Ruta a imprimir
     * @return flujo de salida
     * @note función amiga
     */
    friend ostream& operator << (ostream& output, const Ruta& una_ruta);
};
#endif
    
    
     
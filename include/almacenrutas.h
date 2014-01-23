#ifndef __ALMACEN_RUTAS
#define __ALMACEN_RUTAS

#include "ruta.h"
#include <map>
#include <set>
/**
 * @class AlmacenRutas
 * TDA que permite manejar una serie de rutas, y realizar operaciones de inserción,
 * borrado y consulta sobre ellas
 */
class AlmacenRutas{
private:
    map <string,Ruta> almacen;          ///< identificador de Ruta, instancia Ruta
    map <Punto, set<string> > puntos_rutas;///< Rutas en que aparece un Punto
public:
    /**
     * @brief Constructor sin parámetros
     */
    AlmacenRutas(){}
    /**
     * @brief Operador [] de consulta
     * @param id identificador de la Ruta deseada
     * @return referencia constante a la Ruta
     */
    const Ruta& operator[](string& id){
        return almacen[id];
    }
    /**
     * @brief Permite obtener una relación de las rutas en las que se encuentra un pto
     * @param pto para el que se desea obtener la relación de rutas en que aparece
     * @return vector de identificadores de rutas para el punto dado
     */
    const set<string>& rutasIncluyendoPunto (const Punto& pto){
        return puntos_rutas[pto];
    }
    /**
     * @brief Permite reinicializar todo un almacén de rutas
     */
    void clear(){
        almacen.clear();
        puntos_rutas.clear();
    }
    /// Iterador
    typedef map<string,Ruta>::iterator iterator;
    /// Iterador constante
    typedef map<string,Ruta>::const_iterator const_iterator;
    
    iterator begin(){
        return almacen.begin();
    }
    iterator end(){
        return almacen.end();
    }
    const_iterator begin()const{
        return almacen.begin();
    }
    const_iterator end()const{
        return almacen.end();
    }
    /**
     * @brief Permite borrar una ruta del almacén
     * @param id identificador de la Ruta a buscar
     * @return true si la ruta existía
     * @note Eficiencia lineal
     */    
    bool elimina (const string& id);
    /**
     * @brief Permite aniadir una nueva ruta al almacén
     *                  ^ ¿En serio? xD
     * @param una_ruta Ruta a aniadir
     */
    void agrega (Ruta& una_ruta);
    /**
     * @brief Sobrecarga del operador lectura
     * @note Función friend
     */
    friend istream & operator>>(istream& input, AlmacenRutas& un_almacen);
    /**
     * @brief Sobrecarga del operador escritura
     * @note Función friend
     */
    friend ostream & operator<<(ostream& outpu, const AlmacenRutas un_almacen);
};  
#endif    
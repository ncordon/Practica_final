#ifndef __ALMACEN_RUTAS
#define __ALMACEN_RUTAS

#include "ruta.h"
#include <map>
#include <set>
/**
 * @class AlmacenRutas
 * TDA que permite manejar una serie de rutas, y realizar operaciones de inserción,
 * borrado y consulta sobre ellas
 *
 * @author I. Cordón, F.D. Charte
 */
class AlmacenRutas{
private:
    /**
     * @page repAR Representación del TDA AlmacenRutas
     *
     * @section inv Invariante de la representación
     *
     * Se acepta cualquier objeto de Ruta con identificador no vacío
     *
     * @section fa Función de abstracción
     * Un objeto válido *ar* del TDA AlmacenRutas representa la secuencia
     *
     * {*id_1*: *ar.ruta_1*, *id_2*: *ar.ruta_2*, ...}
     * 
     */
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
    const set<string>& rutasIncluyendoPunto (const Punto& pto) {
        return puntos_rutas[pto];
    }
    /**
     * @brief Permite reinicializar todo un almacén de rutas
     */
    void clear() {
        almacen.clear();
        puntos_rutas.clear();
    }
    /// Iterador
    typedef map<string,Ruta>::iterator iterator;
    /// Iterador constante
    typedef map<string,Ruta>::const_iterator const_iterator;
    
    /**
     * @brief Iterador al inicio
     * @return iterador al inicio
     */
    iterator begin(){
        return almacen.begin();
    }
    /**
     * @brief Iterador al final
     * @return iterador al final
     */
    iterator end(){
        return almacen.end();
    }
    /**
     * @brief Iterador constante al inicio
     * @return iterador constante al inicio
     */
    const_iterator begin() const {
        return almacen.begin();
    }
    /**
     * @brief Iterador constante al final
     * @return iterador constante al final
     */
    const_iterator end() const {
        return almacen.end();
    }
    /**
     * @brief Permite borrar una ruta del almacén
     * @param id identificador de la Ruta a buscar
     * @return true si la ruta existía
     * @note Eficiencia lineal
     */    
    bool elimina(const string& id);
    /**
     * @brief Permite añadir una nueva ruta al almacén
     * @param una_ruta Ruta a añadir
     */
    void agrega(Ruta& una_ruta);
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
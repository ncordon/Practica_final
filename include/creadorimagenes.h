#ifndef _CREADOR_IMGS
#define _CREADOR_IMGS

#include "pais.h"
#include "ruta.h"
#include "imagen.h"

/**
 * @class CreadorImagenes
 * 
 * TDA que permite crear Imágenes a través de múltiples Rutas
 * 
 * @author I. Cordón, F.D. Charte
 */
class CreadorImagenes {
private:
    /**
     * @page repCreador Representación del TDA CreadorImagenes
     *
     * @section inv Invariante de la representación
     *
     * Se acepta cualquier Imagen válida para mapa y avion.
     *
     * @section fa Función de abstracción
     * Un objeto válido *c* del TDA CreadorImagenes representa una
     * utilidad capaz de plasmar Rutas sobre el mapa y mediante el
     * avion dados.
     * 
     */
    Imagen mapa; ///< Almacena la imagen de fondo
    Imagen avion; ///< Almacena el avión que se irá moviendo en la ruta

public:
    /**
     * @brief Constructor con parámetros
     * @param newmapa Imagen de fondo a utilizar
     * @param newavion Imagen del avión a mover por la ruta
     */
    CreadorImagenes(const Imagen& newmapa, const Imagen& newavion)
        :mapa(newmapa), avion(newavion) {}

    /**
     * @brief Plasma una Ruta sobre el mapa de fondo
     * @param a_imprimir objeto de Ruta a mostrar
     * @param mundo almacén de Paises de referencia
     * @return Imagen con la ruta representada
     */
    Imagen muestraRuta(Ruta a_imprimir, Paises mundo);
};

#endif
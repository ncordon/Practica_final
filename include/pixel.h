#ifndef __PIXEL
#define __PIXEL

#include "inttypes.h"

/**
 * @struct Pixel
 * 
 * TDA que permite almacenar un pixel codificado en RGB, con una opacidad asaociada
 * 
 * @author I. Cordón, F.D. Charte
 */
struct Pixel {
    /**
     * @page repPixel Representación del TDA Pixel
     *
     * @section inv Invariante de la representación
     *
     * Se acepta cualquier valor de los enteros sin signo de 8 bits.
     * Cada color puede tener por tanto un valor entre 0 y 255 (0x0, 0xff
     * respectivamente), al igual que la opacidad.
     *
     * @section fa Función de abstracción
     * Un objeto válido *px* del TDA Pixel representa el color
     *
     * (*px.r*, *px.g*, *px.b*) con opacidad *px.alpha*.
     * 
     */
    uint8_t r; ///< Rojo
    uint8_t g; ///< Verde
    uint8_t b; ///< Azul
    uint8_t alpha; ///< Valor de opacidad entre 0x0 y 0xff

    /**
     * @brief Constructor por defecto.
     * El valor por defecto de un Pixel es blanco transparente
     */
    Pixel() {
        *this = 0xffffff00;
    }
    /**
     * @brief Operador de asignación
     * @param valor asignado al pixel, del tipo 0xRRGGBBAA
     * @return referencia al objeto actual
     */
    Pixel& operator=(unsigned int valor) {
        r = valor >> 24;
        g = valor >> 16;
        b = valor >> 8;
        alpha = valor;

        return *this;
    }
};

#endif

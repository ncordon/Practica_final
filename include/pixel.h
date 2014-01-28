#ifndef __PIXEL
#define __PIXEL

#include "inttypes.h"

/**
 * @struct Pixel
 * 
 * TDA que permite almacenar un pixel codificado en RGB, con una opacidad asaociada
 * 
 */
struct Pixel {
        ///< RGB y opacidad
	uint8_t r, g, b, alpha;
        /**
         * @brief Constructor por defecto
         */
	Pixel() {
		*this = 0xffffff00;
	}
	/**
         * @brief Operador de asignación
         * @param valor asignado al pixel, con primeros dos números hex asociados
         * a la transparencia
         * @return referencia al objeto actual
         */
	Pixel& operator=(unsigned int valor) {
		*reinterpret_cast<unsigned int*>(this) = valor;

		return *this;
	}
	/**
         * @brief Permite obtener el valor del Píxel como un entero
         * @return entero sin signo con el valor almacenado por el píxel
         */
	operator unsigned int() {
		return *reinterpret_cast<unsigned int*>(this);
	}
};

#endif

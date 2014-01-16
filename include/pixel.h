#ifndef __PIXEL
#define __PIXEL

#include "inttypes.h"

struct Pixel {
	uint8_t r,	/**<-- rojo (de 0x0 a 0xff) */
		g,		/**<-- verde (de 0x0 a 0xff) */
		b,		/**<-- azul (de 0x0 a 0xff) */
		alpha;	/**<-- opacidad (de 0x0, opaco, a 0xff, transparente) */

	/**
	 * @brief Constructor sin parámetros.
	 * Crea píxel por defecto
	 */
	Pixel() {
		*this = 0xffffff00;
	}
	/**
	 * @brief Constructor con parámetro entero.
	 * Crea píxel a partir del valor entero dado
	 * @param nuevo Valor del color
	 */
	Pixel(unsigned int nuevo) {
		*this = nuevo;
	}
	/**
	 * @brief Sobrecarga del operador igualdad para enteros sin signo.
	 * Utiliza un entero sin signo del tipo 0xrrggbbaa para crear el
	 * Pixel {0xrr, 0xgg, 0xbb, 0xaa}
	 * @param nuevo Valor del color
	 * @return referencia al objeto actual 
	 */
	Pixel& operator=(unsigned int nuevo) {
		alpha = (nuevo) & 0xff;
		r = (nuevo >> 24) & 0xff;
		g = (nuevo >> 16) & 0xff;
		b = (nuevo >> 8) & 0xff;

		return *this;
	}

	operator unsigned() {
		// (unsigned)r << 24 | (unsigned)g << 16 | (unsigned)b << 8 | alpha
		unsigned out = (((((r <<= 24) |= g) <<= 16) |= b) <<= 8) |= alpha;
		return out;
	}
};



#endif

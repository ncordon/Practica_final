#ifndef __PIXEL
#define __PIXEL

#include "inttypes.h"

union Pixel2 {
	struct {
		/** El orden de los valores permite asignar el valor
			en el formato 0xRRGGBBAA                         **/
		uint8_t r, g, b, alpha;
	};
	uint32_t valor;
};

struct Pixel {
	uint8_t r, g, b, alpha;

	Pixel() {
		*this = 0xffffff00;
	}
	Pixel& operator=(unsigned int valor) {
		*reinterpret_cast<unsigned int*>(this) = valor;

		return *this;
	}
	operator unsigned int() {
		return *reinterpret_cast<unsigned int*>(this);
	}
};

#endif

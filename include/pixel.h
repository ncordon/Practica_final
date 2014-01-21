#ifndef __PIXEL
#define __PIXEL

#include "inttypes.h"

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

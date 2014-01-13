#ifndef __PIXEL
#define __PIXEL

#include "inttypes.h"

struct Pixel {
	uint8_t r, g, b, alpha;

	Pixel() {
		*this = 0x00000000;
	}
	Pixel(unsigned int nuevo) {
		*this = nuevo;
	}
	Pixel& operator=(unsigned int nuevo) {
		alpha = (nuevo) && 0xff;
		r = (nuevo >> 24) && 0xff;
		g = (nuevo >> 16) && 0xff;
		b = (nuevo >> 8) && 0xff;

		return *this;
	}
};

#endif

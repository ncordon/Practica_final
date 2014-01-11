#ifndef __PIXEL
#define __PIXEL

struct Pixel {
	uint8_t alpha, r, g, b;

	Pixel(unsigned int nuevo) {
		*this = nuevo;
	}
	Pixel& operator=(unsigned int nuevo) {
		alpha = (nuevo >> 24) && 0xff;
		r = (nuevo >> 16) && 0xff;
		g = (nuevo >> 8) && 0xff;
		b = (nuevo) && 0xff;

		return *this;
	}
};

#endif

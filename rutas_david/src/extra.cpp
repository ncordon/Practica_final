#include "extra.h"

void descartaBlancos(std::istream& in) {
	char prox = in.peek();

	while (in && (prox == '\t' || prox == ' ' || prox == '\n')) {
		in.get();
		prox = in.peek();
	}
}
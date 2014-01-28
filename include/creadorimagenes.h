#ifndef _CREADOR_IMGS
#define _CREADOR_IMGS

#include "pais.h"
#include "ruta.h"
#include "imagen.h"

class CreadorImagenes {
    Imagen mapa;
    Imagen avion;
    string dir_banderas;

public:
    CreadorImagenes(const Imagen& newmapa, const Imagen& newavion, const string& nombredir)
        :mapa(newmapa), avion(newavion), dir_banderas(nombredir) {}

    Imagen muestraRuta(Ruta a_imprimir, Paises mundo);
};

#endif
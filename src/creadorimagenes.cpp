#include "creadorimagenes.h"

Imagen CreadorImagenes::muestraRuta(Ruta a_imprimir, Paises mundo) {
    Imagen final(mapa);
    Ruta::iterator it, ultimo = --a_imprimir.end(), siguiente;
    double ang_rot;
    int filas = mapa.numFilas();
    int columnas = mapa.numColumnas();
    Imagen copia_avion(avion);

    for (it = a_imprimir.begin(); it != a_imprimir.end(); ++it){
        ++(siguiente = it);

        // Calculamos punto medio y punto extremo del segmento
        Imagen::Posicion ext((double)(filas/180)*(double)(90-it->first),
            (double)(columnas/360)*(double)(180+it->second));
        Imagen::Posicion md((double)(filas/180)*(double)(-(it->first+siguiente->first)/2+90),
            (double)(columnas/360)*(double)((it->second+siguiente->second)/2+180));
        // Calculo la rotación y pego el avión en la mitad del segmento
        if (it != ultimo){
            copia_avion = avion;
            ang_rot = acos((siguiente->second-it->second)/it->distancia(*siguiente));
            ang_rot = (siguiente->first<it->first ? M_PI*2-ang_rot : ang_rot);
            final.superponer(copia_avion.aplicarOpacidad(0xd0).rotar(ang_rot), md); 
        }

        Paises::iterator p_it = mundo.find(*it);
        // Imprimimos el nombre del país y pegamos su bandera
        if (p_it != mundo.end()) {
            cout << p_it->descripcion() << endl;
            final.superponer(p_it->bandera,ext);
        }
        // Pegamos el avión en el otro extremo del segmento
        final.superponer(copia_avion.aplicarOpacidad(0xd0),ext);        
    }

    return final;
}
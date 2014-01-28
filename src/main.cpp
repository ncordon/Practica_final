#include "almacenrutas.h"
#include "pais.h"
#include "creadorimagenes.h"

int main(int argc, char* argv[]) {
    if (argc != 8) {
        cout << "Los parametros son:" << endl;
        cout << "1. El fichero de países" << endl;
        cout << "2. La imagen del mapa de fondo" << endl;
        cout << "3. El directorio de banderas" << endl;
        cout << "4. El fichero de rutas" << endl;
        cout << "5. La imagen del avión a emplear" << endl;
        cout << "6. La máscara para el pegado de avión" << endl;
        cout << "7. La ruta a mostrar" << endl;
        return -1;
    }

    // Leemos la imagen del mapa y del avión de memoria
    Imagen avion,mapa;
    mapa.leer(argv[2]);
    avion.leer(argv[5], argv[6]);
    string objetivo(argv[7]), dirbanderas(argv[3]);

    // Fichero de rutas
    ifstream f_rutas(argv[4]);
    // Fichero de paises
    ifstream f_paises(argv[1]);

    if (!f_rutas || !f_paises) {
        cerr << "Error: No se ha encontrado el archivo de rutas o de países" << endl;
        return -2;
    }
    
    Paises almacenp(dirbanderas);
    AlmacenRutas almacenr;
    
    // Leo los almacenes de rutas y de países
    f_paises >> almacenp;
    f_rutas >> almacenr;
    
    CreadorImagenes impresor_rutas(mapa, avion);
    Imagen maparuta(impresor_rutas.muestraRuta(almacenr[objetivo], almacenp));

    string nombresalida(argv[7]);
    nombresalida += ".ppm";
    maparuta.escribir(nombresalida.c_str(), "PPM");
}
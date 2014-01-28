#include "almacenrutas.h"
#include "pais.h"
#include "creadorimagenes.h"

int main(int argc, char* argv[]){
    if (argc!=9){
        cout << "Los parametros son :" << endl;
        cout << "1. El fichero de países" << endl;
        cout << "2. La imagen del mapa de fondo" << endl;
        cout << "3. El directorio de banderas" << endl;
        cout << "4. El fichero de rutas" << endl;
        cout << "5. La imagen del avión a emplear" << endl;
        cout << "6. La máscara para el pegado de avión" << endl;
        cout << "7. La ruta a mostrar" << endl;
        cout << "8. El nombre del fichero de salida" << endl;
        return -1;
    }
    // Leemos la imagen del mapa y del avión de memoria
    Imagen avion,mapa;
    mapa.leer(argv[2]);
    avion.leer(argv[5],argv[6]);
    string objetivo(argv[7]), dir(argv[3]);
    // Fichero de rutas
    ifstream f_rutas(argv[4]);
    // Fichero de paises
    ifstream f_paises(argv[1]);
    
    Paises almacenp (dir);
    AlmacenRutas almacenr;
    
    // Leo los almacenes de rutas y de países
    f_paises >> almacenp;
    f_rutas >> almacenr;
    
    CreadorImagenes impresor_rutas(mapa, avion, dir);
    Imagen maparuta(impresor_rutas.muestraRuta(almacenr[objetivo], almacenp));

    maparuta.escribir(argv[8],"PPM");
}
    
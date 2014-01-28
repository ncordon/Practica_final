#include "almacenrutas.h"
#include "pais.h"
char prueba[]="./prueba";

Imagen muestraRuta() {

}

int main(int argc, char* argv[]){
    if (argc!=8){
        cout<<"Los parametros son :"<<endl;
        cout<<"1.-El fichero de países"<<endl;
        cout<<"2.-La imagen del mapa de fondo"<<endl;
        cout<<"3.-El directorio de banderas"<<endl;
        cout<<"4.-El fichero de rutas"<<endl;
        cout<<"5.-La imagen del avión a emplear"<<endl;
        cout<<"6.-La máscara para el pegado de avión"<<endl;
        cout<<"7.-La ruta a mostrar"<<endl;
        return -1;
    }
    // Leemos la imagen del mapa y del avión de memoria
    Imagen avion,mapa,av;
    mapa.leer(argv[2]);
    avion.leer(argv[5],argv[6]);
    av=avion;
    int totalfilas=mapa.numFilas();
    int totalcolumnas=mapa.numColumnas();
    double ang_rot;
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
    
    Ruta mostrar(almacenr[objetivo]);
    Ruta::iterator it, p(mostrar.end()), k;
    --p;
    
    for (it=mostrar.begin(); it!=mostrar.end(); ++it){
        cout << almacenp[*it].nombre() << endl;
        k=it;   ++k;
        // Calculamos punto medio y punto extremo del segmento
        Imagen::Posicion ext((double)(totalfilas/180)*(double)(90-it->first),
                            (double)(totalcolumnas/360)*(double)(180+it->second));
        Imagen::Posicion md((double)(totalfilas/180)*(double)(-(it->first+k->first)/2+90),
                            (double)(totalcolumnas/360)*(double)((it->second+k->second)/2+180));
        // Calculo la rotación y pego el avión en la mitad del segmento
        if (it!=p){
            av=avion;
            ang_rot=acos((k->second-it->second)/it->distancia(*k));
            ang_rot=(k->first<it->first ? M_PI*2-ang_rot : ang_rot);
            mapa.superponer(av.aplicarOpacidad(0xd0).rotar(ang_rot),md); 
        }
        mapa.superponer(almacenp[*it].bandera(),ext).superponer(av.aplicarOpacidad(0xd0),ext);        
    }
    mapa.escribir(prueba,"PPM");
}
    
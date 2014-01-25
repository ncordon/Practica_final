#include "almacenrutas.h"
#include "pais.h"
char prueba[]="./prueba";

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
    Imagen av,mapa,bandera;
    mapa.leer(argv[2]);
    av.leer(argv[5],argv[6]);
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
    cout << mostrar;
    Ruta::iterator p=mostrar.end(), k;
    --p;
    
    for (Ruta::iterator it=mostrar.begin(); it!=mostrar.end(); ++it){
        cout << "País actual: " << almacenp[*it].nombre << endl;
        Imagen::Posicion ubicacion((double)(totalfilas/180)*(double)(90-it->first),
                            (double)(totalcolumnas/360)*(double)(180+it->second)); 
        // Falta completar esta línea  en la rotación
        Imagen avion(av);
        if (it!=p){
            k=it;
            ++k;
            ang_rot=acos((k->second-it->second)/it->distancia(*k));
            ang_rot=(k->first<it->first ? M_PI*2-ang_rot : ang_rot);
        }
        else
            ang_rot=0;
        mapa.superponer(almacenp[*it].bandera,ubicacion).superponer(avion.rotar(ang_rot),ubicacion);
    }
    
    mapa.escribir(prueba,"PPM");
}
    
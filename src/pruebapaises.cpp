#include "pais.h"

int main (int argc, char* argv[]){
    ifstream f_paises ("./datos/paises.txt");
    Paises almacenPaises("./datos/imagenes/banderas");
    cin.get();
    f_paises >> almacenPaises;
    almacenPaises[Punto(34.520418555522845,69.20082090000005)].bandera.escribir("./prueba.ppm","PPM");
}
    
    
#include "almacenrutas.h"
#include <fstream>

int main(int argc, char *argv[]) {

    if (argc!=2) {
        cout<<"Uso del programa: "<< argv[0] << " <fichero de datos>" << endl;
        return -1;
    }
    
    ifstream file(argv[1]);
    
    if (!file){
        cout<<"Error en la apertura del fichero " << argv[1] << endl;
        return -1;
    }
    
    AlmacenRutas mi_almacen;
    // Leemos el fichero de entrada
    file >> mi_almacen;
    
    //Imprimimos el almacén:
    cout << mi_almacen;
    
    // Ahora con iteradores
    AlmacenRutas::iterator it;
    
    for (it = mi_almacen.begin(); it != mi_almacen.end(); ++it){
        Ruta::iterator p;
        cout << it->second.identificador() << '\t'; 
        for (p = it->second.begin(); p!=it->second.end(); ++p){
            
            cout << (*p) << " ";
        }  
        cout << endl;
    }
    
    cout << "Dame una ruta: " << endl;
    Ruta una_ruta;
    cin >> una_ruta;
    
    cout << "Imprimiendo la ruta..." << endl;
    cout << una_ruta;
    
    cout << "Agregamos la ruta al almacén" << endl;
    mi_almacen.agrega(una_ruta);
    cout << mi_almacen;
    
    cout << "Borramos la ruta del almacén" << endl;
    mi_almacen.elimina(una_ruta.identificador());
    cout << mi_almacen;
}

#ifndef __PAIS
#define __PAIS
#include "imagen.h"

const string dir_banderas="./datos/imagenes/banderas/";

struct Pais{
    pair <double,double> coordenadas;
    string nombre;
    Imagen bandera;
    
    /**
     * @brief Constructor sin parámetros
     * Crea un objeto Pais vacío
     */
    Pais(){}
    /**
     * @brief Constructor con parámetros
     * @param latitud
     * @param longitud
     * @param pais
     * @param path_bandera
     */
    Pais(double latitud, double longitud, string pais, char* path_bandera){
        coordenadas=make_pair(latitud,longitud);
        bandera.leer(path_bandera);
        nombre=pais;
    }
};
    

/**
 * @brief Sobrecarga del operador >> para lectura de países
 * @param input flujo de entrada
 * @param un_pais a rellenar
 */
istream& operator >>(istream &input, Pais &un_pais){
    auto eraseDelim=[](istream& input)->void{
        while (input && (input.peek()=='\t' ||input.peek()==' ' || input.peek()=='\n'))
            input.get();
        };
    double latitud,longitud;
    string pais,n_bandera;
    input >> latitud;
    eraseDelim(input);
    input >> longitud;
    eraseDelim(input);
    input >> pais;
    eraseDelim(input);
    input >> n_bandera;
    
    un_pais=Pais(latitud,longitud,pais,(char*)(dir_banderas+'/'+n_bandera).c_str());
}

#endif
#ifndef __PAIS
#define __PAIS
#include "imagen.h"
#include "punto.h"

struct Pais;

/**
 * @class Paises
 * 
 * TDA que permite almacenar una serie de Paises, indexándolos mediante su 
 * localización geográfica
 */
class Paises: public std::map<Punto,Pais>{
    string dir_banderas;
public:
    /**
     * @brief Constructor sin parámetros
     */
    Paises(){}
    /**
     * @brief Constructor
     * @param dir path al directorio que almacena las banderas
     */
    Paises(string dir):dir_banderas(dir){}
    /**
     * @brief Sobrecarga del operador de lectura
     * @param input
     * @param p instancia del TDA Paises
     * 
     * Dado un flujo de datos, lee del mismo un conjunto de países
     */
    friend istream& operator >>(istream &input, Paises& p);
};

/**
 * @struct Pais
 * Se identifican los Países con puntos
 */
struct Pais:public Punto{
    string nombre;
    Imagen bandera;
    
    /**
     * @brief Constructor sin parámetros
     * Crea un objeto Pais vacío
     */
    Pais():Punto(){}
    /**
     * @brief Constructor con parámetros
     * @param latitud
     * @param longitud
     * @param pais
     * @param path_bandera
     */
    Pais(double latitud, double longitud, string pais, char* path_bandera)
        :Punto(latitud,longitud), nombre(pais){
        bandera.leer(path_bandera);
    }
};

istream& operator >>(istream &input, Paises& p){
    auto eraseDelim=[](istream& input)->void{
        while (input && (input.peek()=='\t' ||input.peek()==' ' || input.peek()=='\n'))
            input.get();
    };
    p.clear();
    double latitud,longitud;
    string pais,n_bandera, dir=p.dir_banderas;
    const int TAM_LINEA=1024;
    // Leemos comentarios y cabecera de un fichero de paises
    while (input && input.peek()=='#')
        input.ignore(TAM_LINEA,'\n');
    
    Pais actual;
    
    while(input){
        input >> latitud;
        eraseDelim(input);
        input >> longitud;
        eraseDelim(input);
        input >> pais;
        eraseDelim(input);
        input >> n_bandera;
        actual=Pais(latitud,longitud,pais,(char*)(dir+'/'+n_bandera).c_str());
        p.insert(pair<Punto,Pais>(actual,actual));
    }
    return input;
}

#endif
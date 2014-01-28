#include "pais.h"

istream& operator >>(istream &input, Paises& p){
    // Función que permite extraer del flujo separadores
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
    
    while(input){
        input >> latitud;
        eraseDelim(input);
        input >> longitud;
        eraseDelim(input);
        input >> pais;
        eraseDelim(input);
        input >> n_bandera;

        p.insert(Pais(latitud, longitud, pais,(char*)(dir+'/'+n_bandera).c_str()));
    }
    return input;
}
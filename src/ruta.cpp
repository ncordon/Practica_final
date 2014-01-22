#include <ruta.h>

istream& operator >> (istream& input, Ruta& una_ruta){
    // Función lambda que permite extraer del flujo los caracteres separadores
    auto eraseDelim=[](istream& input)->void{
        while (input && (input.peek()=='\t' ||input.peek()==' ' || input.peek()=='\n'))
            input.get();
        };
    int dim;
    string id;
    Punto actual;
    una_ruta=Ruta();
    
    eraseDelim(input);
    input>>id;
    una_ruta.id=id;
    eraseDelim(input);
    input>>dim;

    for (int i=0; i<dim;++i){
        eraseDelim(input);
        input >> actual;
        if (!input){
            input.setstate(ios::failbit);
            break;
        }
        una_ruta.agrega(actual);
    }
    
    return input;                  
}

ostream& operator << (ostream& output, const Ruta& una_ruta){
    output << una_ruta.id << ' ' << una_ruta.camino.size() << ' ';
        
    for (Ruta::const_iterator it=una_ruta.begin(); it!=una_ruta.end(); ++it){
        output << *it << ' ';
    }
    output << endl;
    return output;
}
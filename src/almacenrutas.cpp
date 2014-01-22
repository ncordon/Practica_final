#include "almacenrutas.h"

istream & operator>>(istream& input, AlmacenRutas& un_almacen){
    auto eraseDelim = [](istream& input) -> void{
        while (input && (input.peek()=='\t' ||input.peek()==' ' || input.peek()=='\n'))
            input.get();
    };
    
    un_almacen.clear();
    string palabra_magica;
    eraseDelim(input);
    input >> palabra_magica;
    
    if (palabra_magica == "#Rutas"){
        bool continuar=true;
        Ruta actual;
        eraseDelim(input);
        
        while (continuar){
            // Mientras podamos seguir leyendo del flujo algo distinto de #
            if (input && input.peek() != '#'){
                input >> actual;
                if (!input){
                    input.setstate(ios::failbit);
                    return input;
                }
                un_almacen.agrega(actual);
                eraseDelim (input);
            }
            else
                continuar = false;
        }
        if (input.peek()=='#'){
            input >> palabra_magica;
            if (palabra_magica == "#Puntos_de_Interes"){
                Punto pto;
                eraseDelim(input);
                while (input >> pto){
                    AlmacenRutas::iterator it;
                    string newdescripcion;
                    getline(input, newdescripcion);

                    for (it = un_almacen.begin(); it!= un_almacen.end();++it){
                        Ruta::iterator p = ((*it).second).find(pto);
                        if (p!=(it->second).end()){
                            (*p).descripcion() = newdescripcion;
                        }  
                        
                    } 
                }
            }
        }
    }
    return input;
}

ostream & operator<<(ostream& output, const AlmacenRutas un_almacen){
    AlmacenRutas::const_iterator it;
    for (it = un_almacen.begin(); it != un_almacen.end(); ++it){
        output << it->second;
    }
    return output;
}

bool AlmacenRutas::elimina (const string& id){
    // log
    map<string,Ruta>::iterator it=almacen.find(id);
    // Comprobamos que se ha encontrado la ruta en el almacén
    if (it != almacen.end()){
        // lineal en la ruta
        for (Ruta::const_iterator p = it->second.begin(); p!=it->second.end(); ++p){
            // log
            map <Punto,set<string> >::iterator k = puntos_rutas.find(*p);
            if(k != puntos_rutas.end()){
                // log
                k->second.erase(id);
            }
        }
        almacen.erase(it);
        return true;
    }

    return false;
}

void AlmacenRutas::agrega (Ruta& una_ruta){
    string id=una_ruta.identificador();
    almacen.insert(pair<string,Ruta>(id,una_ruta));
    
    for (Ruta::const_iterator it=una_ruta.begin(); it!=una_ruta.end(); ++it){
        pair<map<Punto,set<string> >::iterator,bool> ret;
        ret = puntos_rutas.insert(pair<Punto,set<string> >(*it,set<string>()));
        ret.first->second.insert(id);
    }
}
#include <punto.h>

ostream& operator <<(ostream& output, const Punto& un_punto){
    output << "(" << un_punto.latitud << "," << un_punto.longitud << ")";        
    return output;
}

istream& operator >>(istream& input, Punto& un_punto){
    double latitud;
    double longitud;
    
    auto leeSeparador=
                [](istream &input)->bool{
                    char separador;
                    input >> separador;
                    if (separador!='(' && separador!=')' && separador!=','){
                        input.setstate(ios::failbit);
                        return false;
                    }
                    else
                        return true;
                    };
                    
    if (!leeSeparador(input))
        goto Final;
    input >> latitud;
    if (!leeSeparador(input))
        goto Final;
    input >> longitud;
    if (!leeSeparador(input))
        goto Final;
    
    un_punto = Punto (latitud, longitud);
    
    Final:
    return input;
}

Punto::Punto (double latitud, double longitud, string descripcion){
    this->latitud=latitud;
    this->longitud=longitud;
    this->descripcion=descripcion;
}

Punto& Punto::operator=(const Punto& otro_punto){
    longitud=otro_punto.longitud;
    latitud=otro_punto.latitud;
    descripcion=otro_punto.longitud;
    
    return *this;
}
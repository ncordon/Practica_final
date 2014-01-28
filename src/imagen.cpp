#include "imagen.h"
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

/****************** Métodos privados ********************/
void Imagen::reserva(unsigned int nr, unsigned int nc) {
    m = new Pixel*[nr];
    for (int i = 0; i < nr; ++i)
        m[i] = new Pixel[nc];
}

bool Imagen::leerCabecera (ifstream& input, int& filas, int& columnas){
    // Mayor valor de gris
    int max_gris;
    // Mayor width y length en píxeles de una imagen
    const int max_valor = 5000;
    filas = columnas = 0;
    
    while (saltarSeparadores(input) == '#')
        input.ignore(70,'\n');
    
    input >> columnas >> filas >> max_gris;
    
    if (input && filas>0 && filas <max_valor && columnas >0 && columnas<max_valor){
        input.get(); // Saltamos separador
        return true;
    }
    else 
        return false;
}

char Imagen::saltarSeparadores (ifstream& input){
    char c = input.peek();
    
    while (isspace(c)){
        input.get();
        c = input.peek();
    }
    
    return c;
}

Imagen::TipoImagen Imagen::leerTipo(ifstream& input){
    char c1,c2;
    TipoImagen leida;

    if (input) {
        c1=input.get();
        c2=input.get();
        if (input && c1=='P'){
            switch (c2) {
                case '5': leida = PGM;break;
                case '6': leida = PPM; break;
                default : leida = UNKNOWN;
            }
        }
    }
    return leida;
}

void Imagen::leerNetpbm (const char* nombre, const char* mascara) {
    ifstream input(nombre);
    ifstream mask(mascara);
    
    TipoImagen tipo = leerTipo(input);
    bool isPPM = tipo == PPM;
    
    // Avanzamos la máscara hasta la posición de lectura de puntos
    leerTipo(mask);
    leerCabecera(mask, rownum, colnum);
    
    if (leerCabecera (input, rownum, colnum)) {
        reserva(rownum, colnum);
        // Leemos un PPM
        if (tipo == PPM || tipo == PGM){
            /*Dep*/
            for (int i = 0; i < rownum; i++) {
                for (int j = 0; j < colnum; j++) {
                    input.read(reinterpret_cast<char *>(&m[i][j]),1+2*isPPM);

                    if (!isPPM)
                        m[i][j].b = m[i][j].g = m[i][j].r;

                    if (mask)
                        mask.read(reinterpret_cast<char *>(&m[i][j].alpha),1);
                    else
                        m[i][j].alpha = 0xff;
                }
            }
        }
        else throw invalid_argument ("La imagen no era ni PPM ni PGM");
    }
}

void Imagen::genNetpbm (const char* nombre_archivo, const string& formato){
    ofstream output(nombre_archivo);
    int i,j;
    
    if (output){
        if (formato == "PPM")
            output << "P6" << endl;
        else if (formato == "PGM")
            output << "P5" << endl;
        else{
            output.setstate(ios::failbit);
            return;
        }
        // Imprimimos dimensiones
        output << colnum << ' ' << rownum << endl;
        // Imprimimos máximo valor de gris
        output << 0xff << endl;
        for (i=0; i<rownum; ++i){
            for (j=0; j<colnum; ++j){
                output.write(reinterpret_cast<char*>(&m[i][j]),1+2*(formato=="PPM"));
            }
        }
    }      
}


/****************** Constructores, destructor y operadores ********************/
Imagen::Imagen(const Imagen& a_copiar) {
    colnum = a_copiar.colnum;
    rownum = a_copiar.rownum;

    reserva(rownum, colnum);

    for (int i = 0; i < rownum; ++i)
        for (int j = 0; j < colnum; ++j)
            m[i][j] = a_copiar.m[i][j];
}

Imagen& Imagen::operator=(const Imagen& nueva) {
    Imagen copia(nueva); // Se destruirá en el destructor

    Pixel** aux = m;
    m = copia.m;
    copia.m = aux;

    // Ajustamos cantidades de filas y columnas,
    // imprescindible en `copia` para el destructor 
    int iaux = colnum;
    colnum = copia.colnum;
    copia.colnum = iaux;

    iaux = rownum;
    rownum = copia.rownum;
    copia.rownum = iaux;

    return *this;
}

Imagen::~Imagen() {
    for (int i = 0; i < rownum; ++i)
        delete[] m[i];
    
    delete[] m;
}

/****************** Métodos públicos ********************/

Imagen& Imagen::leer(const char* nombre_archivo,const char* mascara) {
    // Leemos PPM o PGM. Podríamos reusar el lector con cualquier otro tipo
    leerNetpbm(nombre_archivo, mascara);
    return *this;
}

Imagen& Imagen::escribir(const char* nombre_archivo,const string formato) {
    if (formato == "PPM" || formato == "PGM"){
        genNetpbm(nombre_archivo,formato);
    }
    else
        throw invalid_argument("Formato de salida de tipo desconocido");

    return *this;
}

Imagen& Imagen::rotar(double angulo) {
    double rads=angulo;
    double coseno = cos(angulo);
    double seno = sin(angulo);

    // Variables para obtener nuevas dimensiones de la imagen
    int newimgrows,newimgcols, oldrows(numFilas()-1),oldcols(numColumnas()-1);
    double new_row_min,new_col_min,new_row_max,new_col_max;
    double x,y;

    // Coordenadas de bordes de imagen a girar
    int corners[4][2]={ {0,0},
                            {oldcols,0},
                            {oldcols,oldrows},
                            {0,oldrows} };
    
    new_row_min = new_col_min = new_row_max = new_col_max = 0;
    newimgrows = newimgcols = 0;
    
        for(int i=0; i<4; ++i){    
            x = corners[i][0]*coseno + corners[i][1]*seno;
            y = corners[i][1]*coseno - corners[i][0]*seno; 
            
            new_col_min=MIN(x,new_col_min);
            new_col_max=MAX(x,new_col_max);
            new_row_min=MIN(y,new_row_min);
            new_row_max=MAX(y,new_row_max);
        }
    
    newimgrows=(unsigned)ceil((double)new_row_max-new_row_min);
    newimgcols=(unsigned)ceil((double)new_col_max-new_col_min);
        
    Imagen nueva(newimgrows,newimgcols);
    
    for (int rows=0;rows<newimgrows;rows++){
        for(int cols=0;cols<newimgcols;cols++){
            // Buscamos la posible antiimagen del píxel nuevo
            int old_col=ceil((cols+new_col_min)*coseno-
                             (rows+new_row_min)*seno);
            int old_row=ceil((cols+new_col_min)*seno+
                             (rows+new_row_min)*coseno);
            
            nueva.m[rows][cols] =
                (old_row >= 0 && old_row < rownum && old_col >= 0 && old_col < colnum) ? 
                m[old_row][old_col] :
                0x00ffffff; // Valor por defecto: blanco transparente
        }
    }
    *this = nueva;
        return *this;
}

Imagen& Imagen::superponer(const Imagen& nueva, Imagen::Posicion lugar) {
    int v_begin = MAX(MIN(lugar.first - nueva.rownum/2, rownum), 0);
    int v_end = MAX(MIN(lugar.first + nueva.rownum/2, rownum), 0);
    int h_begin = MAX(MIN(lugar.second - nueva.colnum/2, colnum), 0);
    int h_end = MAX(MIN(lugar.second + nueva.colnum/2, colnum), 0);

    for (int i = v_begin; i < v_end; ++i){
        for (int j = h_begin; j < h_end; ++j) {
            int k = i - v_begin, l = j - h_begin;
            double opacity = nueva.m[k][l].alpha/255.0;

            m[i][j].r = m[i][j].r*(1-opacity) + nueva.m[k][l].r*opacity;
            m[i][j].g = m[i][j].g*(1-opacity) + nueva.m[k][l].g*opacity;
            m[i][j].b = m[i][j].b*(1-opacity) + nueva.m[k][l].b*opacity;
        }
        }
    return *this;
}

Imagen& Imagen::aplicarOpacidad(uint8_t nuevoalpha) {
    for (int i = 0; i < rownum; ++i)
        for (int j = 0; j < colnum; ++j)
            m[i][j].alpha = (m[i][j].alpha > 0)*nuevoalpha;

    return *this;
}
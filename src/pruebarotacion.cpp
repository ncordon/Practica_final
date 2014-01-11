#include "imagen.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

/** 
 * @brief Obtiene una nueva imagen que es la versión rotada de una imagen de entrada
 * @param Io: imagen de entrada
 * @param angulo: angulo a rotar la imagen de entrada. Debe estar en radianes.
 * @return Una nueva imagen que es la versión rotada de Io.
 * */

Imagen Rota(const Imagen & I_input,double angulo){
    double rads=angulo;
    double coseno = cos(angulo);
    double seno = sin(angulo);
    // Variables para obtener nuevas dimensiones de la imagen
    int newimgrows,newimgcols;
    double new_row_min,new_col_min,new_row_max,new_col_max;
    double x,y;
    // Coordenadas de bordes de imagen a girar
    int corners[4][2]={ {0,0},
                        {--I_input.num_cols(),0},
                        {--I_input.num_cols(),--I_input.numfilas()}
                        {0,--I_input.numfilas()} };
    
    new_row_min = new_col_min = new_row_max = new_col_max = 0;
    newimgrows = newimgcols = 0;
    
    for(int i=0; i<4; ++i)
    {    
        x = corners[i][0]*coseno + corners[i][1]*seno;
        new_col_min=(x < new_col_min ? x : new_col_min);
        new_col_max=(x > new_col_min ? x : new_col_max);
        
        y = -corners[i][0]*seno + corners[i][1]*coseno;
        new_row_min=(y < new_row_min ? y : new_row_min);
        new_row_max=(y > new_row_min ? y : new_row_max);
    }
    
    newimgrows=(unsigned)ceil((double)new_row_max-new_row_min);
    newimgcols=(unsigned)ceil((double)new_col_max-new_col_min);
    
    Imagen I_output(newimgrows,newimgcols);
    
    for(int rows=0;rows<=newimgrows;rows++)
    {
        for(int cols=0;cols<=newimgcols;cols++)
        {
            // Buscamos el pixel antiguo que al rotar da como resultado el nuevo
            int old_col=ceil((cols+new_col_min)*coseno-
                             (rows+new_row_min)*seno);
            int old_row=ceil((cols+new_col_min)*seno+
                             (rows+new_row_min)*coseno);
            
            if((old_row>=0)&&(old_row<I_input.num_filas())&&
                (old_col>=0)&&(old_col<I_input.num_cols()))
                I_output [rows][cols]=I_input[old_row][old_col];
            else
                I_output[rows][cols].R=I_output[rows,cols].G=I_output[rows][cols].B=255;
        }
    }
    return I_output;
}



int main(int argc, char * argv[]){
    if (argc!=4){
        cout<<"Los parametros son :"<<endl;
        cout<<"1.-La imagen de entrada"<<endl;
        cout<<"2.-El angulo de rotación (en grados)"<<endl;
        cout<<"3.-El nombre de la imagen de salida"<<endl;
        return 0;
    }
    Imagen I;
    I.LeerImagen(argv[1]);
    double angulo=atof(argv[2]);
    angulo = angulo*(M_PI)/180; //Pasamos el angulo radianes
    Imagen Iout=Rota(I,angulo);
    Iout.EscribirImagen(argv[3]);  
}
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <iomanip>
#include "rlutil.h"
using namespace std;
#include "interfaz.h"
using namespace rlutil;
#include "entrenamiento.h"
#include "reportes.h"
#include"usuario.h"

//listar la cantidad de usuarios distintos que hayan entrenado mas de 250 minutos en algun registro de entrenamiento


void reporte_2(){
    listar_usuario_x_tiempo250();
}



int buscar_entrenamiento_mayor_a250(){
	Entrenamiento reg;
	FILE* f;
	int pos = 0;
	f = fopen("entrenamientos.dat", "rb");
	if (f == NULL) {
		return -1;
	}
	while (fread(&reg, sizeof(Entrenamiento), 1, f)) {
		if (250 < reg.tiempo) {
			fclose(f);
			return pos;
		}
		pos++;
	}
	fclose(f);
	return -1;
}

void listar_usuario_x_tiempo250(){
    cout << "    LISTA DE USUARIOS QUE ENTRENARON MAS DE 250 MINUTOS"<< endl << endl;
	int codigo, pos;

	pos = buscar_entrenamiento_mayor_a250();
	if (pos >= 0) {
        cout<<endl;
        cout<<"    ---------------------------"<<endl<<endl;
        int cant = cantidad_entrenamientos();
        if (cant == 0){
                msj("No existe el IDusuario 1 ", 15, 3);
            return;
        }

        Entrenamiento *vec;

        vec = (Entrenamiento *) malloc(cant * sizeof(Entrenamiento));
        if (vec == NULL){
                msj("No existe el IDusuario 2 ", 15, 3);
            return;
        }
        FILE *p;
        p = fopen("entrenamientos.dat", "rb");
        if (p == NULL){
            free(vec);
            msj("No existe el IDusuario 3", 15, 3);
            return;
        }
        fread(vec, sizeof(Entrenamiento), cant, p);
        fclose(p);


        bool pri=true;
        int codigog=0;
        int i;
        for(i=0; i<cant; i++){

            if(vec[i].tiempo>250){
                    if(pri ==true){
                             listar_usuario_x_id2(vec[i].IDusuario);
                             codigog=vec[i].IDusuario;
                            pri==false;
                    }

   if( vec[i].IDusuario!=codigog){

                listar_usuario_x_id2(vec[i].IDusuario);
                codigog=vec[i].IDusuario;

                    }
                    }


            }
        cout<<endl;
        free(vec);
	}


	else {
		msj("No existe el IDusuario ", 15, 3);
		return;
	}
}


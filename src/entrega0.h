#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Secuencia.h"


using namespace std;

#ifndef __ENTREGA0__H
#define __ENTREGA0__H

void cargar_archivo(const string& nombreArchivo, vector<Secuencia>& memoria);
void listar_secuencias(const vector<Secuencia>& memoria);
void histograma_secuencia();
void es_subsecuencia();
void enmascarar_subsecuencia();
void guardar_archivo();
void codificar_archivo();
void decodificar_archivo();
void ruta_mas_corta();
void base_remota();
void ayuda();
void ayudaComando(string comando);

#endif

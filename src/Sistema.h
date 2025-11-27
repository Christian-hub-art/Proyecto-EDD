#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include "Secuencia.h"


using namespace std;

#ifndef __ENTREGA0__H
#define __ENTREGA0__H

void cargar_archivo(const string& nombreArchivo, vector<Secuencia>& memoria);
void listar_secuencias(const vector<Secuencia>& memoria);
void histograma_secuencia(const string secuencia, vector<Secuencia>& memoria);
void es_subsecuencia(const string subsecuencia, vector <Secuencia>& memoria);
void enmascarar_subsecuencia(const string subsecuencia, vector <Secuencia>& memoria);
void guardar_archivo(const string& nombreArchivo, const vector<Secuencia>& memoria);
void codificar_archivo();
void decodificar_archivo();
void ruta_mas_corta(string descripcion_secuencia, int i, int j, int x, int y, vector<Secuencia>& memoria);
void base_remota();
void ayuda();
void ayudaComando(string comando);
void codificarArchivo(const string& nombreArchivo, const vector<Secuencia>& memoria);
void decodificarArchivo(const string& archivoEntrada, vector<Secuencia>& memoria);

// Funciones auxiliares

bool comparar_caracteres(char a, char b);
vector <vector<int>> inicios_subsecuencia(const string& subsecuencia, const vector<Secuencia>& memoria);

#endif

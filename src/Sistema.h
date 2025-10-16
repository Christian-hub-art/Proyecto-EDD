#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Secuencia.h"
#include <fstream>
#include "ArbolHuffman.h"


using namespace std;

#ifndef __ENTREGA0__H
#define __ENTREGA0__H

void cargar_archivo(const string& nombreArchivo, vector<Secuencia>& memoria);
void listar_secuencias(const vector<Secuencia>& memoria);
void histograma_secuencia(const string secuencia, vector<Secuencia>& memoria);
void es_subsecuencia(const string subsecuencia, vector <Secuencia>& memoria);
void enmascarar_subsecuencia(const string subsecuencia, vector <Secuencia>& memoria);
void guardar_archivo(const string& nombreArchivo, const vector<Secuencia>& memoria);
void codificar_archivo(const string& nombreArchivo, const vector<Secuencia>& memoria);
string codificar(string dato, map<char, string> &codigos);
void decodificar_archivo(const string& archivoEntrada, vector<Secuencia>& memoria);
string decodificar(string bits, ArbolHuffman &arbol);
void ruta_mas_corta();
void base_remota();
void ayuda();
void ayudaComando(string comando);

// Funciones auxiliares

bool comparar_caracteres(char a, char b);
vector <vector<int>> inicios_subsecuencia(const string& subsecuencia, const vector<Secuencia>& memoria);

#endif

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Secuencia.h"
using namespace std;




bool esComandoValido(const string& comando); // de define la funcion de comando valido
void mostrarComandos(); // se define la funcion de mostrar comandos
void ayudaComando(const string& comando); // se define la funcion de ayuda que mostrara los detalles de cada comando
void cargar ( const string& nombreArchivo, vector<Secuencia>& memoria);
void listarSecuencias(const vector<Secuencia>& memoria);  


#ifndef _ARBOLHUFFMAN_H__
#define _ARBOLHUFFMAN_H__
#include "Secuencia.h"
#include "Nodo.h"
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Compare {
public:
    bool operator()(Nodo* a, Nodo* b);
};

class ArbolHuffman{
    protected:
    Nodo *raiz;
    public:
    ArbolHuffman();
    ~ArbolHuffman();
    Nodo* obtenerRaiz();
    void fijarRaiz(Nodo *nodo);
    void generarCodigo(Nodo *nodo,string codigo, map<char,string> &codigos);
    void Arbol(map<char, int> tablafrecuenia);
    string codificar(string dato, map<char, string> &codigos);
    string decodificar(string bits);
    bool esVacio();
    void codificarArchivo(const string& nombreArchivo, const vector<Secuencia>& memoria);
    void decodificarArchivo(const string& archivoEntrada, vector<Secuencia>& memoria);
};





#endif
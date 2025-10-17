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
    std::map<char, std::string> codigos;
    public:
    ArbolHuffman();
    ~ArbolHuffman();
    Nodo* obtenerRaiz();
    void fijarRaiz(Nodo *nodo);
    void generarCodigo(Nodo *nodo,string codigo, map<char,string> &codigos);
    void construirDesdeFrecuencias(map<char,int> tablafrecuenia);
    bool esVacio();

    
    void imprimirCodigosDeDepuracion();
};





#endif
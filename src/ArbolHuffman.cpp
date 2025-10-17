#include "ArbolHuffman.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdint>
#include <queue>

using namespace std;

bool Compare::operator()(Nodo* a, Nodo* b) {
    return a->obtenerFrecuencia() > b->obtenerFrecuencia();
}

ArbolHuffman::ArbolHuffman(){
    this -> raiz = nullptr;
}

ArbolHuffman::~ArbolHuffman(){
    delete raiz;
}

bool ArbolHuffman::esVacio(){
    return this->raiz==nullptr;
}

Nodo* ArbolHuffman::obtenerRaiz(){
    return this->raiz;
}


void ArbolHuffman::generarCodigo(Nodo *nodo, string codigo, map<char,string> &codigos){
    if (!nodo) {
        return;
    }
    
    // Si es nodo hoja (sin hijos)
   if (!nodo->obtenerIzq() && !nodo->obtenerDer()) {
    if (codigo.empty()) {
        codigos[nodo->obtenerDatos()] = "0";
    } else {
        codigos[nodo->obtenerDatos()] = codigo;
    }
    return;
}


    // Recorrer hijos 
    if (nodo->obtenerIzq()) {
        generarCodigo(nodo->obtenerIzq(), codigo + "0", codigos);
    }
    if (nodo->obtenerDer()) {
        generarCodigo(nodo->obtenerDer(), codigo + "1", codigos);
    }
}

void ArbolHuffman::Arbol(map<char,int> tablafrecuenia){
    if (tablafrecuenia.empty()) {
        raiz = nullptr;
        return;
    }
    
    // Caso especial: un solo símbolo
    if (tablafrecuenia.size() == 1) {
    map<char,int>::iterator it = tablafrecuenia.begin();
    raiz = new Nodo(it->first, it->second);
    return;
}
    
    priority_queue<Nodo*, vector<Nodo*>, Compare> pq;

    for (const pair<char, int> &par : tablafrecuenia) {
        pq.push(new Nodo(par.first, par.second));
    }

    while (pq.size() > 1) {
        Nodo* Izq = pq.top(); 
        pq.pop();
        Nodo* Der = pq.top(); 
        pq.pop();

        Nodo* padre = new Nodo('\0', Izq->obtenerFrecuencia() + Der->obtenerFrecuencia());
        padre->FijarIzq(Izq);
        padre->FijarDer(Der);

        pq.push(padre);
    }
    
    if (!pq.empty())
        raiz = pq.top();
    else
        raiz = nullptr;
}



string ArbolHuffman::decodificar(string bits) {

    string resultado;
    Nodo* actual = raiz;

    for ( int i = 0; i < bits.size(); ++i) {
        char bit = bits[i];
        if (bit == '0')
            actual = actual->obtenerIzq();
        else
            actual = actual->obtenerDer();
        if (actual->obtenerIzq() == nullptr && actual->obtenerDer() == nullptr) {
            resultado += actual->obtenerDatos();
            actual = raiz;
    }
    }

    return resultado;
}

string ArbolHuffman::codificar(string dato, map<char, string> &codigos) {
    string encadenado;

    for (int i = 0; i < dato.size(); ++i) {
        char c = dato[i];
        encadenado += codigos.at(c);
    }

    return encadenado;
}


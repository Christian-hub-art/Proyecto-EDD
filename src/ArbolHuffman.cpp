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

ArbolHuffman::~ArbolHuffman(){
    delete raiz;
}

Nodo* ArbolHuffman::obtenerRaiz(){
    return this->raiz;
}

void ArbolHuffman::fijarRaiz(Nodo *nodo){
    this->raiz = nodo;
}

bool ArbolHuffman::esVacio(){
    return this->raiz==nullptr;
}

void ArbolHuffman::generarCodigo(Nodo *nodo, string codigo, map<char,string> &codigos){
    if (!nodo) {
        return;
    }
    
    // Si es nodo hoja (sin hijos)
    if (!nodo->obtenerIzq() && !nodo->obtenerDer()) {
        // Caso especial: si el árbol tiene solo un nodo, asignar código "0"
        codigos[nodo->obtenerDatos()] = codigo.empty() ? "0" : codigo;
        return;
    }

    // Recorrer hijos con validación
    if (nodo->obtenerIzq()) {
        generarCodigo(nodo->obtenerIzq(), codigo + "0", codigos);
    }
    if (nodo->obtenerDer()) {
        generarCodigo(nodo->obtenerDer(), codigo + "1", codigos);
    }
}

ArbolHuffman::ArbolHuffman(map<char,int> tablafrecuenia){
    if (tablafrecuenia.empty()) {
        raiz = nullptr;
    }
    
    // Caso especial: un solo símbolo
    else if (tablafrecuenia.size() == 1) {
        auto it = tablafrecuenia.begin();
        raiz = new Nodo(it->first, it->second);
    }else
    {
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
    
}
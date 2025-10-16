#include <iostream>
#include "Nodo.h"

using namespace std;

Nodo::Nodo(){
    this -> dato = 0;
    this -> frecuencia = 0;
    this -> hijoIzquierdo = nullptr; 
    this -> hijoDerecho = nullptr;
}

Nodo::Nodo(char data, int fre){
    this -> dato = data;
    this->frecuencia = fre;
    this->hijoIzquierdo = nullptr;
    this->hijoDerecho = nullptr;
}

Nodo::Nodo(Nodo *izq, Nodo *der,int fre){
    this->frecuencia = fre;
    hijoIzquierdo = izq;
    hijoDerecho = der;
}

Nodo::~Nodo(){
    delete hijoDerecho;
    delete hijoIzquierdo;
} 

Nodo* Nodo::obtenerIzq(){
    return this -> hijoIzquierdo;
}

Nodo* Nodo::obtenerDer(){
    return this -> hijoDerecho;
}

void Nodo::FijarIzq(Nodo * nodo){
    this -> hijoIzquierdo = nodo;
}

void Nodo::FijarDer(Nodo * nodo){
    this -> hijoDerecho = nodo;
}

char Nodo::obtenerDatos(){
    return this->dato;
}

int Nodo::obtenerFrecuencia(){
    return this->frecuencia;
}

void Nodo::fijarDatos(char data){
    this->dato = data; 
}

void Nodo::fijarFrecuencia(int fre){
    this->frecuencia = fre;
}

 bool Nodo::esHoja(){
   return (this->hijoIzquierdo == nullptr && this->hijoDerecho == nullptr);
}

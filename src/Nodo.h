#ifndef _NODO_H__
#define _NODO_H__

#include <iostream>

using namespace std;

class Nodo   {
    protected:
        char dato;
        int frecuencia;
        Nodo *hijoIzquierdo;
        Nodo *hijoDerecho;
    public:
        Nodo();
        //para nodo hoja 
        Nodo(char dato, int frecuencia);
        //para nodo interno 
        Nodo(Nodo* izq, Nodo *der, int frecuencia);
        ~Nodo();
        char obtenerDatos();
        Nodo *obtenerIzq();
        Nodo *obtenerDer();
        void FijarIzq(Nodo * nodo);
        void FijarDer(Nodo * nodo);
        int obtenerFrecuencia();
        void fijarDatos(char dato);
        void fijarFrecuencia(int frecuencia);
        bool esHoja();

};


#endif
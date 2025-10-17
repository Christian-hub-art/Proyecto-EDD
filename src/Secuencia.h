#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>
using namespace std;

class Secuencia {
private:
    string nombre;
    string datos;
    int cantidad_por_linea; // cantidad de caracteres que hay en la linea del archivo de origen
public:
    Secuencia(const string& nom) {
        nombre = nom;
        datos = "";
        cantidad_por_linea = 0;
    }
    string getNombre() const;
    void setNombre(const string& nom);
    string getDatos() const;
    void setDatos(const string& dat) ;
    void setDatosPos(int pos, char dat) ;
    int getCantidadPorLinea() const ;
    void setCantidadPorLinea(int cantidad) ;
};

#endif
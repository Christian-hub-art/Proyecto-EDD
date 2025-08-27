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
    string getNombre() const { return nombre; }
    void setNombre(const string& nom) { nombre = nom; }
    string getDatos() const { return datos; }
    void setDatos(const string& dat) { datos = dat; }
    int getCantidadPorLinea() const { return cantidad_por_linea; }
    void setCantidadPorLinea(int cantidad) { cantidad_por_linea = cantidad; }
};

#endif
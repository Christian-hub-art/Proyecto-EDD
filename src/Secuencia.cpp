#include "Secuencia.h"
#include <string>
using namespace std;

string Secuencia::getNombre() const { return nombre; }
void Secuencia::setNombre(const string &nom) { nombre = nom; }
string Secuencia::getDatos() const { return datos; }
void Secuencia::setDatos(const string &dat) { datos = dat; }
void Secuencia::setDatosPos(int pos, char dat) { datos[pos] = dat; }
int Secuencia::getCantidadPorLinea() const { return cantidad_por_linea; }
void Secuencia::setCantidadPorLinea(int cantidad) { cantidad_por_linea = cantidad; }
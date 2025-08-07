#include <iostream>
#include <string>
#include <vector>
#include "entrega0.h"
using namespace std; 

bool esComandoValido(const string& comando) {
    vector<string> comandosValidos = {
        "cargar nombre_archivo",
        "listar_secuencias",
        "histograma descripcion_secuencia"
    };

    for (const string& valido : comandosValidos) {
        if (comando == valido) {
            return true;
        }
    }
    return false;
}
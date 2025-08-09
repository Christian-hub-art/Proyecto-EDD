#include <iostream>
#include <string>
#include <vector>

#include "entrega0.h"
using namespace std; 

bool esComandoValido(const string& comando) {
    vector<string> comandosValidos = {
        "cargar nombre_archivo",
        "listar_secuencias",
        "histograma descripcion_secuencia",   
        "es_subsecuencia",
        "enmascarar",
        "guardar", 
        "ayuda",
        "ayuda cargar nombre_archivo",
        "ayuda listar_secuencias",
        "ayuda histograma descripcion_secuencia",   
        "ayuda es_subsecuencia",
        "ayuda enmascarar",
        "ayuda guardar", 
};

    for (const string& valido : comandosValidos) {
        if (comando == valido) {
            return true;
        }
    }
    return false;
}

void mostrarComandos(){
    cout<<"Comandos validos:"<<endl;
    cout<<"cargar nombre_archivo"<<endl;
    cout<<"listar_secuencias"<<endl;
    cout<<"histograma descripcion_secuencia"<<endl;
    cout<<"es_subsecuencia"<<endl;
    cout<<"enmascarar"<<endl;
    cout<<"guardar"<<endl;
    cout<<"salir"<<endl;
    cout<<"ayuda cargar nombre_archivo"<<endl;
    cout<<"ayuda listar_secuencias"<<endl;
    cout<<"ayuda histograma descripcion_secuencia"<<endl;   
    cout<<"ayuda es_subsecuencia"<<endl;
    cout<<"ayuda enmascarar"<<endl;
    cout<<"ayuda guardar"<<endl;
}

void ayudaComando(const string& comando){
    vector<string> comandos = {
    "ayuda cargar nombre_archivo",
    "ayuda listar_secuencias",
    "ayuda histograma descripcion_secuencia",   
    "ayuda es_subsecuencia",
    "ayuda enmascarar",
    "ayuda guardar", 
    };
    vector<string> descripcion = {
    "Carga en memoria los datos contenidos en el             archivo identificado por nombre_archivo",
    "Imprime la cantidad de secuencias actualmente en        memoria, y luego, en n líneas la información            básica de cada secuencia.", 
    "Imprime el histograma de una secuencia, en caso de      que exista",
    "Determina si una subsecuencia dada por el usuario,      existe dentro de las secuencias cargadas en             memoria.",
    "Enmascara una secuencia dada por el usuario, en         caso de que exista.",
    "Guarda en el archivo nombre_archivo las secuencias      cargadas en memoria"
    };
    
    for (int i =0; i<comandos.size(); i++){
        if (comando == comandos[i]){
            cout<<descripcion[i]<<endl;
            break;
        }
    }

}

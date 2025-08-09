#include <iostream>
#include <string>
#include <vector>

#include "entrega0.h"
using namespace std; 

bool esComandoValido(const string& comando) { // recibe un string comando, con el comando quiso poner
    vector<string> comandosValidos = {   // se define un arreglo tipo vector para implementar todos los cadenas de comandos
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

    for (const string& valido : comandosValidos) { // se valida con el comando de entrada del usuario que si este dentro del vector el comando que digitalizo
        if (comando == valido) {
            return true;
        }
    }
    return false;
}

void mostrarComandos(){  // a partir del comando ayuda se mostraran todos los comandos disponibles dentro del sistemas para digitalizar y tener una guia el usuario
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

void ayudaComando(const string& comando){ // recibe como entrada el comando tipo string que digitalizo el usuario
    vector<string> comandos = {
    "ayuda cargar nombre_archivo",
    "ayuda listar_secuencias",
    "ayuda histograma descripcion_secuencia",   
    "ayuda es_subsecuencia",
    "ayuda enmascarar",
    "ayuda guardar", 
    };
    vector<string> descripcion = { // se define la descripcion de cada comando para que sea detallado sobre su funcionalidad al usuario 
    "Carga en memoria los datos contenidos en el             archivo identificado por nombre_archivo",
    "Imprime la cantidad de secuencias actualmente en        memoria, y luego, en n líneas la información            básica de cada secuencia.", 
    "Imprime el histograma de una secuencia, en caso de      que exista",
    "Determina si una subsecuencia dada por el usuario,      existe dentro de las secuencias cargadas en             memoria.",
    "Enmascara una secuencia dada por el usuario, en         caso de que exista.",
    "Guarda en el archivo nombre_archivo las secuencias      cargadas en memoria"
    };
    
    for (int i =0; i<comandos.size(); i++){ // por medio de un for se busca primero en arreglo tipo vector comando que si sea acorde con el de usuario y luego con el itarador 
                                            // acceder entonces con el comando ya econtrado a la misma posicion en que esta que corresponde a la de su descripcion
        if (comando == comandos[i]){
            cout<<descripcion[i]<<endl;
            break;
        }
    }

}

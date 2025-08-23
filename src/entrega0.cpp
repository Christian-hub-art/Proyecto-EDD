#include "entrega0.h"
#include "Secuencia.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void cargar_archivo(const string& nombreArchivo, vector<Secuencia>& memoria){
  cout<<"Comando ejecutado\n";
  ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << nombreArchivo << " no se encuentra o no puede leerse." << endl;
        return;
    }

    memoria.clear(); // sobrescribir lo que había antes

    string linea, nombreActual, datosActual;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        if (linea[0] == '>') {
            if (!nombreActual.empty()) {
                memoria.push_back({nombreActual, datosActual});
                datosActual.clear();
            }
            nombreActual = linea.substr(1);
        } else {
            datosActual += linea;
        }
    }

    if (!nombreActual.empty()) {
        memoria.push_back({nombreActual, datosActual});
    }

    int n = memoria.size();
    if (n == 0) {
        cout << nombreArchivo << " no contiene ninguna secuencia." << endl;
    } else if (n == 1) {
        cout << "1 secuencia cargada correctamente desde " << nombreArchivo << "." << endl;
    } else {
        cout << n << " secuencias cargadas correctamente desde " << nombreArchivo << "." << endl;
    }
}

void listar_secuencias(){
  cout<<"Comando ejecutado\n";
}

void histograma_secuencia(){
  cout<<"Comando ejecutado\n";
}

void es_subsecuencia(){
  cout<<"Comando ejecutado\n";
}

void enmascarar_subsecuencia(){
  cout<<"Comando ejecutado\n";
}

void guardar_archivo(){
  cout<<"Comando ejecutado\n";
  
}

void codificar_archivo(){
  cout<<"Comando ejecutado\n";
}

void decodificar_archivo(){
  cout<<"Comando ejecutado\n";
}

void ruta_mas_corta(){
  cout<<"Comando ejecutado\n";
}

void base_remota(){
  cout<<"Comando ejecutado\n";
}


void ayuda(){

  cout<<"lista de comandos: "<<endl;
    cout<<"------------------------------------------------"<<endl<<endl;
    cout<<"cargar nombre_archivo"<<endl<<endl;

    cout<<"listar_secuencias"<<endl<<endl;

    cout<<"histograma descripcion_secuencia"<<endl<<endl;

    cout<<"es_subsecuencia subsecuencia"<<endl<<endl;

    cout<<"enmascarar subsecuencia"<<endl<<endl;

    cout<<"guardar nombre_archivo"<<endl<<endl;

    cout<<"codificar nombre_archivo.fabin"<<endl<<endl;

    cout<<"decodificar nombre_archivo.fabin"<<endl<<endl;

    cout<<"ruta_mas_corta descripcion_secuencia i j x y"<<endl<<endl;

    cout<<"base_remota descripcion_secuencia i j"<<endl<<endl;

    cout<<"salir"<<endl<<endl;


}

void ayudaComando(string comando){
  if (strcmp(comando.c_str(), "cargar") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"cargar nombre_archivo"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" Carga en memoria los datos contenidos en el archivo identificado por nombre_archivo."<<endl;
    cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "listar_secuencias") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"listar_secuencias"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" Imprime la cantidad de secuencias actualmente en memoria, y luego, en n líneas (unapara secuencia) la información básica (nombre y cantidad de bases diferentes) de cada secuencia."<<endl;
    cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "histograma") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<" histograma descripcion_secuencia"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" Imprime el histograma de una secuencia, en caso de que exista.Por cada línea se escribe el código y la cantidad de veces que aparece en la secuencia."<<endl;
    cout<<"------------------------------------------------"<<endl<<endl;


  } else if (strcmp(comando.c_str(), "es_subsecuencia") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"es_subsecuencia subsecuencia"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"  Determina si una subsecuencia (secuencia corta de bases) dada por el usuario, existe dentro de las secuencias cargadas en memoria. Si es así, determina la cantidad de veces en las que esta subsecuencia dada se repite."<<endl;
    cout<<"------------------------------------------------"<<endl;


  } else if (strcmp(comando.c_str(), "enmascarar") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"enmascarar subsecuencia"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"Enmascara una subsecuencia (secuencia corta de bases) dada por el usuario, si existe."<<endl;
    cout<<"------------------------------------------------"<<endl;


  } else if (strcmp(comando.c_str(), "guardar") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"guardar nombre_archivo"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"  Guarda en el archivo nombre_archivo las secuencias cargadas en memoria."<<endl;
    cout<<"------------------------------------------------"<<endl<<endl;

  } else if (strcmp(comando.c_str(), "codificar") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"codificar nombre_archivo.fabin"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" Genera el archivo binario con la correspondiente codificación de Huffman, almacenándolo en disco bajo el nombre nombre_archivo.fabin."<<endl;
    cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "decodificar") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"decodificar nombre_archivo.fabin"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" Carga en memoria las secuencias contenidas en el archivo binario nombre_archivo.fabin, que contiene una codificación Huffman.Tenga en cuenta que esto eliminara las secuencias previamente cargadas en memoria."<<endl;
    cout<<"------------------------------------------------"<<endl;


  } else if (strcmp((comando).c_str(), "ruta_mas_corta") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"ruta_mas_corta descripcion_secuencia i j x y"<<endl<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" Imprime en pantalla la secuencia de vértices (bases) del grafo que describen la ruta más corta entre la base ubicada en la posición [i,j] de la matriz de la secuencia descripcion_secuencia y la base ubicada en la posición [x,y] de la misma matriz. Así mismo, imprime el costo total de la ruta, teniendo en cuenta el peso que tiene cada conexión entre bases."<<endl;
    cout<<"------------------------------------------------"<<endl;


  } else if (strcmp((comando).c_str(), "base_remota") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"base_remota descripcion_secuencia i j"<<endl<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" Para la base ubicada en la posición [i,j] de la matriz de la secuencia descripcion_secuencia, el comando busca la ubicación de la misma base (misma letra) más lejana dentro de la matriz. Para esta base remota, el comando imprime en pantalla su ubicación, la secuencia de vértices (bases) que describen la ruta entre la base origen y la base remota, y el costo total de la ruta, teniendo en cuenta el peso que tiene cada conexión entre bases."<<endl;
    cout<<"------------------------------------------------"<<endl;

  } else if (strcmp((comando).c_str(), "salir") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"salir"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"Termina la ejecución de la aplicación."<<endl;
    cout<<"------------------------------------------------"<<endl;

  }else {
    cout << "Comando no reconocido\n";
  }

}

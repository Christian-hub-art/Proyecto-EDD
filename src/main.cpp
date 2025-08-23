#include "entrega0.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

int main() {
  string opcion;
  string entrada;
  int numtokes = 0;
  int index = 0;
  bool comandoValido = true;
  bool salir=false;
  string tokenss;
  do {
    comandoValido = true;
    cout << "$ ";
    getline(cin, entrada);
//-------------------------------distribucion de tokens----------------------------------
    char *c_entrada = new char[entrada.size() + 1];
    strcpy(c_entrada, entrada.c_str());

    // Contar los tokens
    char *token = strtok(c_entrada, " ");
    while (token != nullptr) {
      numtokes++;
      token = strtok(nullptr, " ");
    }

    // Crear un array para almacenar los tokens
    string *tokens = new string[numtokes];
    strcpy(c_entrada, entrada.c_str());

    token = strtok(c_entrada, " ");
    index = 0; // Resetear el índice para la segunda pasada
    while (token != nullptr) {
      tokens[index] = token;
      index++;
      token = strtok(nullptr, " ");
    }
//--------------------------------final de distribucion de tokens------------------------
      
//--------------------------------inicio menu--------------------------------------------
    if (strcmp(tokens[0].c_str(), "ayuda") == 0) {
      if (index == 1) {
        ayuda();
      } else if (index == 2) {
        ayudaComando(tokens[1]);
      }

    } else if (strcmp(tokens[0].c_str(), "cargar") == 0) {
      if (index == 2) {
        cargar_archivo();
      } else {
        comandoValido = false;
      }

    } else if (strcmp(tokens[0].c_str(), "listar_secuencias") == 0) {
      if (index == 1) {
        listar_secuencias();
      } else {
        comandoValido = false;
      }

    } else if (strcmp(tokens[0].c_str(), "histograma") == 0) {
      if (index == 2) {
        histograma_secuencia();
      } else {
        comandoValido = false;
      }

    } else if (strcmp(tokens[0].c_str(), "es_subsecuencia") == 0) {
      if (index == 2) {
        es_subsecuencia();
      } else {
        comandoValido = false;
      }

    } else if (strcmp(tokens[0].c_str(), "enmascarar") == 0) {
      if (index == 2) {
        enmascarar_subsecuencia();
      } else {
        comandoValido = false;
      }

    } else if (strcmp(tokens[0].c_str(), "guardar") == 0) {
      if (index == 2) {
        guardar_archivo();
      } else {
        comandoValido = false;
      }

    } else if (strcmp(tokens[0].c_str(), "codificar") == 0) {
      if (index == 2) {
        codificar_archivo();
      } else {
        comandoValido = false;
      }

    } else if (strcmp(tokens[0].c_str(), "decodificar") == 0) {
      if (index == 2) {
        decodificar_archivo();
      } else {
        comandoValido = false;
      }

    } else if (strcmp(tokens[0].c_str(), "ruta_mas_corta") == 0) {
      if (index == 6) {
        ruta_mas_corta();
      } else {
        comandoValido = false;
      }

      } else if (strcmp(tokens[0].c_str(), "base_remota") == 0) {
      if (index == 4) {
        base_remota();
      } else {
        comandoValido = false;
      }

    } else if (strcmp(tokens[0].c_str(), "salir") == 0){
        salir=true;    
        
    } else {
      cout << "Comando no reconocido\n";
    }

    if (!comandoValido) {
      cout << "\nError en el comando\n";
    }
//--------------------------------fin menu-----------------------------------------------

    tokenss = tokens[0];

    delete[] c_entrada;
    delete[] tokens;
    numtokes = 0;

  } while (!salir);

  return 0;
}

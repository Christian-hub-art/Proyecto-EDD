#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // para dividir el comando en tokens

#include "Secuencia.h"
#include "entrega0.h"
using namespace std; 

int main(int argc, char* argv[]) {
    vector<Secuencia> memoria; 

    string comando;
    while (true) {
        cout << "$";
        getline(cin, comando);  

        if (comando == "salir") {
            break;
        }
        if (comando == "ayuda") {
            mostrarComandos();
            continue; // ya mostramos, no seguimos
        }

        ayudaComando(comando);

        if (esComandoValido(comando)) {
            cout << "Comando ingresado Correctamente " << endl;
        } else {
            cout << "Comando invalido. Revise nuevamente la guia con el comando de ayuda" << endl;
        }

        // Hacermos token para poder manipular las palabras en un vector y asi acceder mas sencillo a estas mismas
        istringstream iss(comando);
        vector<string> tokens;
        string palabra;
        while (iss >> palabra) {
            tokens.push_back(palabra);
        }

        // ahora tokens[0] es el comando, tokens[1] sería el archivo
        if (tokens.size() == 2 && tokens[0] == "cargar") {
            cargar(tokens[1], memoria);
        }
        
        if (tokens[0] == "listar_secuencias" && tokens.size() > 1) {
            cout << "Error: listar_secuencias no recibe parámetros. Prueba con 'ayuda'." << endl;
            continue;
        }
        if (tokens[0] == "listar_secuencias" && tokens.size() == 1) {
            listarSecuencias(memoria);
        }

    }
    return 0; 
}
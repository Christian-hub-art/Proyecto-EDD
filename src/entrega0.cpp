#include <iostream>
#include <string>
#include <vector>
#include "entrega0.h"
using namespace std; 


int main(){
    string comando; // se define una variable tipo string para alamecenar lo que escribe el usuario
    while(true){ // el while true nos sirve para generar ciclos infinitos hasta que el usuario decida colocar el comando salir
        cout<<"$";
        getline(cin,comando); // almacena con espacios la cadena que digitalice el usuario
       
        if (comando=="salir"){ // comando salir rompe el ciclo y termina con el prgrama 
            break;
        }
        if (comando=="ayuda"){ // con elcoamndo ayuda se muestran todos los comandos disponibles que hay
            mostrarComandos();
        }
        
        ayudaComando(comando); // si digitaliza algun comando ayuda comando mostrara los detalles de aquel comando 
        
        if(esComandoValido(comando)){  // le dice al usuario si el comando que dgitalizo si se encuentra o no
            cout<<"Comando ingresado Correctamente "<<endl;
        }
        else{
            cout<<"Comando invalido. Revise nuevamente la guia con el comando de ayuda"<<endl; // valida que el comando se digitalizo mal y le sugiere al usuario el comando ayuda
        }
    }
    
    return 0 ; 
}

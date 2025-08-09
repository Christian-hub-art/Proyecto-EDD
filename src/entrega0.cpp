#include <iostream>
#include <string>
#include <vector>
#include "entrega0.h"
using namespace std; 


int main(){
    string comando;
    while(true){
        cout<<"$";
        getline(cin,comando);
       
        if (comando=="salir"){
            break;
        }
        if (comando=="ayuda"){
            mostrarComandos();
        }
        
        ayudaComando(comando);
        
        if(esComandoValido(comando)){
            cout<<"Comando ingresado Correctamente "<<endl;
        }
        else{
            cout<<"Comando invalido. Revise nuevamente la guia con el comando de ayuda"<<endl;
        }
    }
    
    return 0 ; 
}

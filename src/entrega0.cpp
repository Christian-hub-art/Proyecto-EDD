#include <iostream>
#include <string>
#include <vector>
#include "entrega0.h"
using namespace std; 


int main(){
    string comando;
    while(true){
        cout<<"$";getline(cin,comando);
        if (comando=="salir"){
            break;
        }
        if(esComandoValido(comando)){
            cout<<"Comando ingresado Correctamente "<<endl;
        }
        else{
            cout<<"Comando invalido. Intente nuevamente"<<endl;
        }
    }
    
    return 0 ; 
}
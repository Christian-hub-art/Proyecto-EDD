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
        if (comando=="ayuda"){
            cout<<"Comandos validos:"<<endl;
            cout<<"cargar nombre_archivo"<<endl;
            cout<<"listar_secuencias"<<endl;
            cout<<"histograma descripcion_secuencia"<<endl;
            cout<<"es_subsecuencia"<<endl;
            cout<<"enmascarar"<<endl;
            cout<<"guardar"<<endl;
            cout<<"salir"<<endl;
        }
        if(esComandoValido(comando)){
            cout<<"Comando ingresado    Correctamente "<<endl;
        }
        else{
            cout<<"Comando invalido. Intente nuevamente"<<endl;
        }
    }
    
    return 0 ; 
}

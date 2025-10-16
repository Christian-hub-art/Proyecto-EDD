#include "ArbolHuffman.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdint>
#include <queue>

using namespace std;

bool Compare::operator()(Nodo* a, Nodo* b) {
    return a->obtenerFrecuencia() > b->obtenerFrecuencia();
}

ArbolHuffman::ArbolHuffman(){
    this -> raiz = nullptr;
}

ArbolHuffman::~ArbolHuffman(){
    delete raiz;
}

bool ArbolHuffman::esVacio(){
    return this->raiz==nullptr;
}

// CORREGIDO: Validación de nodos y caso especial árbol de un nodo
void ArbolHuffman::generarCodigo(Nodo *nodo, string codigo, map<char,string> &codigos){
    if (!nodo) {
        return;
    }
    
    // Si es nodo hoja (sin hijos)
    if (!nodo->obtenerIzq() && !nodo->obtenerDer()) {
        // Caso especial: si el árbol tiene solo un nodo, asignar código "0"
        codigos[nodo->obtenerDatos()] = codigo.empty() ? "0" : codigo;
        return;
    }

    // Recorrer hijos con validación
    if (nodo->obtenerIzq()) {
        generarCodigo(nodo->obtenerIzq(), codigo + "0", codigos);
    }
    if (nodo->obtenerDer()) {
        generarCodigo(nodo->obtenerDer(), codigo + "1", codigos);
    }
}

void ArbolHuffman::Arbol(map<char,int> tablafrecuenia){
    if (tablafrecuenia.empty()) {
        raiz = nullptr;
        return;
    }
    
    // Caso especial: un solo símbolo
    if (tablafrecuenia.size() == 1) {
        auto it = tablafrecuenia.begin();
        raiz = new Nodo(it->first, it->second);
        return;
    }
    
    priority_queue<Nodo*, vector<Nodo*>, Compare> pq;

    for (const pair<char, int> &par : tablafrecuenia) {
        pq.push(new Nodo(par.first, par.second));
    }

    while (pq.size() > 1) {
        Nodo* Izq = pq.top(); 
        pq.pop();
        Nodo* Der = pq.top(); 
        pq.pop();

        Nodo* padre = new Nodo('\0', Izq->obtenerFrecuencia() + Der->obtenerFrecuencia());
        padre->FijarIzq(Izq);
        padre->FijarDer(Der);

        pq.push(padre);
    }
    
    if (!pq.empty())
        raiz = pq.top();
    else
        raiz = nullptr;
}

string ArbolHuffman::codificar(string dato, map<char, string> &codigos) {
    string encadenado;

    for (int i = 0; i < dato.size(); ++i) {
        char c = dato[i];
        encadenado += codigos.at(c);
    }

    return encadenado;
}

string ArbolHuffman::decodificar(string bits) {

    string resultado;
    Nodo* actual = this->raiz;

    for ( int i = 0; i < bits.size(); ++i) {
        char bit = bits[i];
        if (bit == '0')
            actual = actual->obtenerIzq();
        else
            actual = actual->obtenerDer();
        if (actual->obtenerIzq() == nullptr && actual->obtenerDer() == nullptr) {
            resultado += actual->obtenerDatos();
            actual = raiz;
    }
    }

    return resultado;
}

void ArbolHuffman::codificarArchivo(const string& nombreArchivo, const vector<Secuencia>& memoria) {
    
    map<char, int> frecuencias;
    for (const Secuencia& secuencia : memoria) {
        const string& datos = secuencia.getDatos();
        for (size_t i = 0; i < datos.size(); ++i) {
            char c = datos[i];
            frecuencias[c]++;
        }
    }

    
    Arbol(frecuencias);             
    map<char, string> codigos;
    generarCodigo(raiz, "", codigos);

    ofstream salida(nombreArchivo + ".fabin", ios::binary);
    if (!salida.is_open()) {
        cerr << "Error al crear archivo binario\n";
        return;
    }

    
    uint16_t n = frecuencias.size();
    salida.write(reinterpret_cast<char*>(&n), sizeof(uint16_t));

    for (const pair<const char, int>& par : frecuencias) {
        unsigned char c = par.first;
        uint64_t f = par.second;
        salida.write(reinterpret_cast<char*>(&c), sizeof(unsigned char));
        salida.write(reinterpret_cast<char*>(&f), sizeof(uint64_t));
    }

    
    uint32_t ns = memoria.size();
    salida.write(reinterpret_cast<char*>(&ns), sizeof(uint32_t));

    
    for (const Secuencia& seq : memoria) {
        const string& nombre = seq.getNombre();
        const string& datos = seq.getDatos();
        int ancho = seq.getCantidadPorLinea();
        uint16_t li = nombre.size();
        salida.write(reinterpret_cast<char*>(&li), sizeof(uint16_t));
        salida.write(nombre.c_str(), li);

        uint32_t wi = static_cast<uint32_t>(datos.size());
        int xi = ancho;
        salida.write(reinterpret_cast<char*>(&wi), sizeof(uint32_t));
        salida.write(reinterpret_cast<char*>(&xi), sizeof(int));

        // Codificar datos con Huffman
        string bits = codificar(datos, codigos);

        // Guardar tamaño real de bits
        uint64_t bitLength = bits.size();
        salida.write(reinterpret_cast<char*>(&bitLength), sizeof(uint64_t));

        // Rellenar con ceros hasta múltiplo de 8
        while (bits.size() % 8 != 0)
            bits += '0';

        // Convertir bits a bytes
        for (size_t i = 0; i < bits.size(); i += 8) {
            bitset<8> byte(bits.substr(i, 8));
            unsigned char b = static_cast<unsigned char>(byte.to_ulong());
            salida.write(reinterpret_cast<char*>(&b), sizeof(unsigned char));
        }
    }

    salida.close();
    cout << " Archivo codificado correctamente: " << nombreArchivo << ".fabin\n";
}

void ArbolHuffman::decodificarArchivo(const string& archivoEntrada, vector<Secuencia>& memoria) {
    ifstream entrada(archivoEntrada, ios::binary);
    if (!entrada.is_open()) {
        cerr << "No se puede abrir el archivo .fabin\n";
        return;
    }

    memoria.clear();

    
    uint16_t n;
    entrada.read(reinterpret_cast<char*>(&n), sizeof(uint16_t));

    map<char, int> frecuencias;
    for (int i = 0; i < n; i++) {
        unsigned char c;
        uint64_t f;
        entrada.read(reinterpret_cast<char*>(&c), sizeof(unsigned char));
        entrada.read(reinterpret_cast<char*>(&f), sizeof(uint64_t));
        frecuencias[c] = f;
    }

    
    Arbol(frecuencias);

    
    uint32_t ns;
    entrada.read(reinterpret_cast<char*>(&ns), sizeof(uint32_t));

   
    for (uint32_t i = 0; i < ns; i++) {
        // Nombre
        uint16_t li;
        entrada.read(reinterpret_cast<char*>(&li), sizeof(uint16_t));
        string nombre(li, '\0');
        entrada.read(&nombre[0], li);
        uint32_t wi;
        int xi;
        entrada.read(reinterpret_cast<char*>(&wi), sizeof(uint32_t));
        entrada.read(reinterpret_cast<char*>(&xi), sizeof(int));

        // Longitud de bits
        uint64_t bitLength;
        entrada.read(reinterpret_cast<char*>(&bitLength), sizeof(uint64_t));

        // Calcular bytes necesarios
        size_t totalBytes = (bitLength + 7) / 8;

        // Leer esos bytes y convertirlos a bits
        string bits;
        bits.reserve(totalBytes * 8);
        for (size_t j = 0; j < totalBytes; ++j) {
            unsigned char byte;
            entrada.read(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
            bitset<8> b(byte);
            bits += b.to_string();
        }

        // Decodificar exactamente bitLength bits
        string contenido = decodificar(bits.substr(0, bitLength));

        // Guardar en memoria
        memoria.push_back(Secuencia(nombre, contenido));
    }

    entrada.close();
    cout << " Archivo decodificado correctamente.\n";
}

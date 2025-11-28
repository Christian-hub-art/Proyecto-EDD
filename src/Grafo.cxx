#ifndef GRAFO_CXX
#define GRAFO_CXX

#include <iostream>
#include <limits>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <set>
#include <cfloat>
#include <functional>
#include "Grafo.hxx"

// Implementación de la clase Grafo

// Constructor
template <class T>
Grafo<T>::Grafo(std::string nombre, int cantidad_por_linea) {
    this->nombre = nombre;
    this->cantidad_por_linea = cantidad_por_linea;
    vertices.clear();
    aristas.clear();
}

// Setters
template <class T>
void Grafo<T>::setVertices(const std::vector<T>& vertices) {
    this->vertices = vertices;
    // Re-inicializar las aristas para coincidir con el nuevo número de vértices
    aristas.clear();
    aristas.resize(vertices.size());
}

template <class T>
void Grafo<T>::setAristas(const std::vector<std::map<int, float>>& aristas) {
    this->aristas = aristas;
}

// Getters
template <class T>
const std::vector<T>& Grafo<T>::getVertices() const {
    return this->vertices;
}

template <class T>
const std::vector<std::map<int, float>>& Grafo<T>::getAristas() const {
    return this->aristas;
}

// Cantidad de vértices
template <class T>
int Grafo<T>::cantVertices() const {
    return vertices.size();
}

// Cantidad de aristas
template <class T>
int Grafo<T>::cantAristas() const {
    int suma = 0;
    for (const std::map<int, float>& mapa : aristas) {
    suma += mapa.size();
    }
    return suma;
}

// Buscar índice de un vértice
template <class T>
int Grafo<T>::buscarVertice(const int x, const int y) const {
    int posicion;
    posicion = x * cantidad_por_linea + y;

    if(posicion <= vertices.size() - 1){
        return posicion;
    }
    return -1;
}

// Insertar un vértice
template <class T>
bool Grafo<T>::insertarVertice(const T& ver) {
    vertices.push_back(ver);
    aristas.emplace_back(); // Añadir un nuevo mapa para las aristas del nuevo vértice
    return true;
}

// Insertar una arista dirigida
template <class T>
bool Grafo<T>::insertarArista(const int x, const int y, const int i, const int j) {
    int i_ori = buscarVertice(x, y);
    int i_des = buscarVertice(i, j);
    if (i_ori == -1 || i_des == -1) return false; // Vértices no encontrados
    // Insertar o actualizar el costo de la arista
    float costo = 1/(1+abs(vertices[i_ori] - vertices[i_des]));
    aristas[i_ori][i_des] = costo;
    aristas[i_des][i_ori] = costo;
    return true;
}

// Buscar costo de una arista
template <class T>
float Grafo<T>::buscarArista(const T &origen, const T &destino) const {
    int i_ori = buscarVertice(origen);
    int i_des = buscarVertice(destino);
    if (i_ori == -1 || i_des == -1) return -1.0f; // Indica que no existe
    auto it = aristas[i_ori].find(i_des);
    if (it != aristas[i_ori].end()) {
        return it->second;
    }
    return -1.0f; // Indica que no existe
}

// Eliminar una arista dirigida
template <class T>
bool Grafo<T>::eliminarArista(const T &origen, const T &destino) {
    int i_ori = buscarVertice(origen);
    int i_des = buscarVertice(destino);
    if (i_ori == -1 || i_des == -1) return false; // Vértices no encontrados
    auto it = aristas[i_ori].find(i_des);
    if (it != aristas[i_ori].end()) {
        aristas[i_ori].erase(it);
        return true;
    }
    return false; // Arista no encontrada
}

// Eliminar una arista no dirigida
template <class T>
bool Grafo<T>::elimAristaNoDir(const T& ori, const T& des) {
    bool res1 = eliminarArista(ori, des);
    bool res2 = eliminarArista(des, ori);
    return res1 && res2;
}

// Eliminar un vértice
template <class T>
bool Grafo<T>::eliminarVertice(const T& ver) {
    int i_ver = buscarVertice(ver);
    if (i_ver == -1) return false; // Vértice no encontrado

    // Eliminar el vértice del vector de vértices
    vertices.erase(vertices.begin() + i_ver);

    // Eliminar todas las aristas salientes de este vértice
    aristas.erase(aristas.begin() + i_ver);

    // Eliminar todas las aristas entrantes a este vértice
    for (std::vector<std::map<int, float>>::iterator it = aristas.begin(); it != aristas.end(); ++it) {
        it->erase(i_ver);
    }

    // Reajustar las claves de los mapas que sean mayores que i_ver
    for (std::vector<std::map<int, float>>::iterator it = aristas.begin(); it != aristas.end(); ++it) {
        std::map<int, float> mapa_actualizado;
        for (std::map<int, float>::const_iterator it_mapa = it->begin(); it_mapa != it->end(); ++it_mapa) {
            int dest = it_mapa->first;
            float cost = it_mapa->second;

            if (dest > i_ver) {
                mapa_actualizado[dest - 1] = cost;
            } else if (dest < i_ver) {
                mapa_actualizado[dest] = cost;
            }
            // Si dest == i_ver, ya se ha eliminado
        }
        *it = std::move(mapa_actualizado);
    }

    return true;
}


// Obtener vecinos de un vértice
template <class T>
std::vector<T> Grafo<T>::vecinosVertice(const T& ver) const {
    int indice = buscarVertice(ver);
    std::vector<T> ver_vecinos;

    if (indice != -1) {
        for (const std::pair<int, float>& arista : aristas[indice]) {
            ver_vecinos.push_back(vertices[arista.first]);
        }
    }

    // Ordenar los vecinos dependiendo de su tipo de dato
    std::sort(ver_vecinos.begin(), ver_vecinos.end());
    return ver_vecinos;
}

template <class T>
std::vector<unsigned long> Grafo<T>::indicesVecinos(int u) const {
    std::vector<unsigned long> vecinos;
    if (u < 0 || u >= cantVertices()) return vecinos;
    for (const std::pair<int, float>& arista : aristas[u]) {
        vecinos.push_back(arista.first);
    }
    return vecinos;
}

// Implementación de DFS
template <class T>
std::vector<T> Grafo<T>::DFS(const T& ver_inicial) {
    std::vector<bool> ver_visitados(cantVertices(), false);
    std::vector<T> caminoDFS;
    std::stack<int> pila_ver;

    int indice_inicial = buscarVertice(ver_inicial);
    if (indice_inicial == -1) {
        // Vértice no encontrado, retornar camino vacío
        return caminoDFS;
    }

    pila_ver.push(indice_inicial);

    while (!pila_ver.empty()) {
        int ver_actual = pila_ver.top();
        pila_ver.pop();

        if (!ver_visitados[ver_actual]) {
            caminoDFS.push_back(vertices[ver_actual]);
            ver_visitados[ver_actual] = true;

            // Insertar vecinos en orden inverso para mantener el orden correcto en el stack
            std::vector<int> vecinos_indices;
            for (const std::pair<int, float>& arista : aristas[ver_actual]) {
                vecinos_indices.push_back(arista.first);
            }

            // Ordenar en orden descendente para que al insertar en el stack, se procesen en orden ascendente
            std::sort(vecinos_indices.begin(), vecinos_indices.end(), [&](int a, int b) {
                return vertices[a] > vertices[b];
            });

            for (const int vecino : vecinos_indices) {
                if (!ver_visitados[vecino]) {
                    pila_ver.push(vecino);
                }
            }
        }
    }

    return caminoDFS;
}


// Implementación de BFS
template <class T>
std::vector<T> Grafo<T>::BFS(const T& ver_inicial) {
    std::vector<bool> ver_visitados(cantVertices(), false);
    std::vector<T> caminoBFS;
    std::queue<int> cola_ver;

    int indice_inicial = buscarVertice(ver_inicial);
    if (indice_inicial == -1) {
        // Vértice no encontrado, retornar camino vacío
        return caminoBFS;
    }

    cola_ver.push(indice_inicial);
    ver_visitados[indice_inicial] = true;

    while (!cola_ver.empty()) {
        int ver_actual = cola_ver.front();
        cola_ver.pop();
        caminoBFS.push_back(vertices[ver_actual]);

        for (const std::pair<int, float>& arista : aristas[ver_actual]) {
            if (!ver_visitados[arista.first]) {
                cola_ver.push(arista.first);
                ver_visitados[arista.first] = true;
            }
        }
    }

    return caminoBFS;
}

// Implementación de Dijkstra
template <class T>
std::vector<std::pair<int, float>> Grafo<T>::dijkstra(unsigned long i_fuente) {
    int numVertices = cantVertices();
    std::vector<float> dist(numVertices, std::numeric_limits<float>::max());
    std::vector<unsigned long> pred(numVertices, static_cast<unsigned long>(-1));
    std::vector<unsigned long> q;


    std::vector<std::pair<int, float>> resultado(numVertices);
    std::vector<unsigned long> vecinos;

    // Inicializar la cola con todos los vértices
    for (unsigned long i = 0; i < cantVertices(); i++) {
        q.push_back(i);
    }


    pred[i_fuente] = i_fuente;
    dist[i_fuente] = 0.0f;


    while (!q.empty()) {
        //Algoritmo de que vertice analizar 
        unsigned long menor= q[0];
        unsigned long borrar=0;
        for(unsigned long i=0; i<cantVertices(); i++ ){
            for(int j=0; j<q.size(); j++ ){
                if (i==q[j]){
                    if(dist[i]<dist[menor]){
                        menor=q[j];
                        borrar=j;
                    }
                }
            }
        }

        q.erase(q.begin()+borrar);
        // fin algotirmo de que sacar 

        vecinos= indicesVecinos(menor);
        for (int i = 0; i < vecinos.size(); ++i) {
            int peso = aristas[menor][vecinos[i]];
            if (dist[menor] + peso < dist[vecinos[i]]) {
                dist[vecinos[i]] = dist[menor] + peso;
                pred[vecinos[i]] = menor;
            }
        }
    }

    for (unsigned long i = 0; i < cantVertices(); i++) {
        resultado[i] = std::make_pair(static_cast<int>(pred[i]), dist[i]);
    }

    return resultado;
}


template <class T>
std::vector<unsigned long> Grafo<T>::construirRutaDijkstra(std::vector<std::pair<int, float>> dijkstra, int i_fuente, int i_destino) {
   
    std::vector<unsigned long> rutita;
    std::vector<unsigned long> rutitaInversa;
   
    //Construir ruta de i_fuente a i_destino
    int predecesor;

    predecesor= pred[i_destino];
    if(!(predecesor ==-1)){
        if(i_destino!=i_fuente)
        rutitaInversa.push_back(i_destino);
        rutitaInversa.push_back((unsigned long) predecesor);
        while(!(predecesor==i_fuente) ){
            predecesor= pred[predecesor];
            rutitaInversa.push_back(predecesor);
        }
        for(int j=rutitaInversa.size()-1; j>-1; j--){
            rutita.push_back(rutitaInversa[j]);
        }
    }

    return rutita;
}

// Implementación de obtenerCosto
template <class T>
double Grafo<T>::obtenerCosto(int id1, int id2) const {
    if (id1 < 0 || id1 >= cantVertices() || id2 < 0 || id2 >= cantVertices()) {
        return -1.0; // Valor inválido para indicar que no existe
    }

    for (std::map<int, float>::const_iterator it = aristas[id1].begin(); it != aristas[id1].end(); ++it) {
        if (it->first == id2) {
            return it->second; // Devolver el costo del segundo coso que es el que es
        }
    }

    return -1.0; // Indica que no existe
}


#endif // GRAFO_CXX
#ifndef GRAFO_HXX
#define GRAFO_HXX

#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <utility> // Para std::pair
#include <set>
#include <functional> // Para std::function en Kruskal y Puentes

template<class T>
class Grafo {
private:
    std::string nombre;
    int cantidad_por_linea;
    std::vector<T> vertices; 
    std::vector<std::map<int, float>> aristas; 

public:
    // Constructor
    Grafo(std::string nombre, int cantidad_por_linea);

    // Setters
    void setVertices(const std::vector<T>& vertices);
    void setAristas(const std::vector<std::map<int, float>>& aristas);

    // Getters
    const std::vector<T>& getVertices() const;
    const std::vector<std::map<int, float>>& getAristas() const;

    // Métodos de consulta
    int cantVertices() const;
    int cantAristas() const;
    int buscarVertice(const int x, const int y ) const;
    float buscarArista(const T &origen, const T &destino) const;
    double obtenerCosto(int id1, int id2) const;

    // Métodos de modificación
    bool insertarVertice(const T& ver);
    bool insertarArista(const int x, const int y, const int i, const int j);
    bool eliminarArista(const T &origen, const T &destino);
    bool elimAristaNoDir(const T& ori, const T& des);
    bool eliminarVertice(const T& ver);

    // Métodos de análisis
    std::vector<T> vecinosVertice(const T& ver) const;
    std::vector<unsigned long> indicesVecinos(int u) const; 
    std::vector<T> DFS(const T& ver_inicial);
    std::vector<T> BFS(const T& ver_inicial);   
    std::vector<std::vector<unsigned long>> dijkstra(unsigned long i_fuente); 
};

#endif // GRAFO_H

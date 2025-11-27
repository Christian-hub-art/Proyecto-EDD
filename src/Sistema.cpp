#include "Sistema.h"
#include "Secuencia.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <bitset>
#include "ArbolHuffman.h"
#include "Grafo.hxx"

using namespace std;



void cargar_archivo(const string &nombreArchivo, vector<Secuencia> &memoria)
{
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << nombreArchivo << " no se encuentra o no puede leerse." << endl;
        return;
    }

    memoria.clear();

    string linea, nombreActual, datosActual;
    bool secuenciaValida = true;
    int cantidadPorLineaActual = 0;
    const string caracteresValidos = "ACGTURYKMSWBDHVNX-";

    while (getline(archivo, linea)) {
        if (linea.empty())
            continue;

        if (linea[0] == '>') {
            // Guardar la secuencia anterior si era válida
            if (!nombreActual.empty() && secuenciaValida) {
                Secuencia seq(nombreActual);
                seq.setDatos(datosActual);
                seq.setCantidadPorLinea(cantidadPorLineaActual);
                memoria.push_back(seq);
            }

            nombreActual = linea.substr(1); 
            datosActual.clear();
            cantidadPorLineaActual = 0;
            secuenciaValida = true;
        } 
        else {
          if (!secuenciaValida) {
                continue; // Saltar las líneas de una secuencia ya marcada como inválida
          }
        
            for (char c : linea) {
                char may = c;
                if (may >= 'a' && may <= 'z')
                    may = may - 32;

                bool valido = false;
                for (int j = 0; j < caracteresValidos.size(); j++) {
                    if (may == caracteresValidos[j]) {
                        valido = true;
                        break;
                    }
                }

                if (!valido) {
                    cout << "Error: secuencia \"" << nombreActual
                         << "\" contiene símbolo no permitido (" << c << ")." << endl;
                    secuenciaValida = false;
                    break;
                }
            }
          if (secuenciaValida) {
            if (datosActual.empty()) {
                cantidadPorLineaActual = linea.length();
            }
            datosActual += linea; // Acumular los datos de la secuencia
          }
        }
    }

    if (!nombreActual.empty() && secuenciaValida) {
        Secuencia seq(nombreActual);
        seq.setDatos(datosActual);
        seq.setCantidadPorLinea(cantidadPorLineaActual);
        memoria.push_back(seq);
    }

    int n = memoria.size();
    if (n == 0)
        cout << nombreArchivo << " no contiene ninguna secuencia válida." << endl;
    else if (n == 1)
        cout << "1 secuencia cargada correctamente desde " << nombreArchivo << "." << endl;
    else
        cout << n << " secuencias cargadas correctamente desde " << nombreArchivo << "." << endl;
}


void listar_secuencias(const vector<Secuencia>& memoria) {
    if (memoria.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }

    cout << "Hay " << memoria.size() << " secuencias cargadas en memoria:" << endl;

    for (size_t i = 0; i < memoria.size(); i++) {
        const string& datos = memoria[i].getDatos();
        bool incompleta = false;
        int conteo = 0;

        for (char base : datos) {
            if (base == '-') {
                incompleta = true;
            } else {
                conteo++;
            }
        }

        if (incompleta)
            cout << "Secuencia " << memoria[i].getNombre() 
                 << " contiene al menos " << conteo << " bases." << endl;
        else
            cout << "Secuencia " << memoria[i].getNombre() 
                 << " contiene " << conteo << " bases." << endl;
    }
}



int indiceBase(char base) {
    const string codigo = "ACGTURYKMSWBDHVNX-"; 
    if (base >= 'a' && base <= 'z')
        base = base - 32;

    for (int i = 0; i < codigo.size(); i++) {
        if (codigo[i] == base)
            return i;
    }
    return -1;
}


void histograma_secuencia(const string secuencia, vector<Secuencia> &memoria)
{
    const vector<char> codigo = {'A','C','G','T','U','R','Y','K','M','S','W','B','D','H','V','N','X','-'};
    vector<int> conteo(codigo.size(), 0);

    bool existente = false;
    Secuencia sec_temp = Secuencia("");

    for (const auto &s : memoria) {
        if (s.getNombre() == secuencia) {
            sec_temp = s;
            existente = true;
            break;
        }
    }

    if (!existente) {
        cout << "Secuencia inválida." << endl;
        return;
    }

    const string &datos = sec_temp.getDatos();
    for (int i = 0; i < datos.size(); i++) {
        int idx = indiceBase(datos[i]);
        if (idx != -1) conteo[idx]++;
    }

    for (int i = 0; i < codigo.size(); i++) {
        if (conteo[i] > 0)
            cout << codigo[i] << " : " << conteo[i] << endl;
    }
}


bool comparar_caracteres(char a, char b)
{
    if (a == b)
        return true;

    if ((a >= 'A' && a <= 'Z' && a + 32 == b) ||
        (a >= 'a' && a <= 'z' && a - 32 == b))
        return true;

    return false;
}

vector<vector<int>> inicios_subsecuencia(const string& subsecuencia, const vector<Secuencia>& memoria)
{
    vector<vector<int>> resultados(memoria.size());

    if (subsecuencia.empty()) return resultados;

    for (size_t i = 0; i < memoria.size(); i++) {
        const Secuencia& sec = memoria[i];
        const string& datos = sec.getDatos();

        if (datos.size() < subsecuencia.size()) continue;

        for (size_t j = 0; j <= datos.size() - subsecuencia.size(); j++) {
            bool coincide = true;

            for (size_t k = 0; k < subsecuencia.size(); k++) {
                if (!comparar_caracteres(subsecuencia[k], datos[j + k])) {
                    coincide = false;
                    break;
                }
            }

            if (coincide) {
                resultados[i].push_back(static_cast<int>(j));
            }
        }
    }

    return resultados;
}



void es_subsecuencia(const string subsecuencia, vector<Secuencia> &memoria)
{
  int conteo = 0;
  vector <vector<int>> inicios;
  if ( memoria.size() == 0){
    cout << "No hay secuencias cargadas en memoria\n";
    return;
  }

  inicios = inicios_subsecuencia(subsecuencia, memoria);

  for(int i=0; i<inicios.size(); i++){
    conteo += inicios[i].size();
  }

  if( conteo == 0){
    cout <<  "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria.\n";
  }else{
    cout << "La subsecuencia dada existe "<< conteo << " veces dentro de las secuencias cargadas en memoria.\n";
  }


  
}

void enmascarar_subsecuencia(const string subsecuencia, vector <Secuencia>& memoria)
{
  int conteo = 0; 
  vector <vector<int>> inicios;
  if ( memoria.size() == 0){
    cout << "No hay secuencias cargadas en memoria\n";
    return;
  }

  inicios = inicios_subsecuencia(subsecuencia, memoria);

  for(int i=0; i<inicios.size(); i++){
    for ( int j = 0; j < inicios[i].size(); j++){
      conteo++;
      for( int k = 0; k < subsecuencia.length(); k++){
        memoria[i].setDatosPos(inicios[i][j]+k , 'X');
      }
    }
  }

  if( conteo == 0){
    cout <<  "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada.\n";
  }else{
    cout << conteo << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.\n";
  }
}

void guardar_archivo(const string &nombreArchivo, const vector<Secuencia> &memoria)
{

  ofstream archivo_salida(nombreArchivo);

  if (!archivo_salida)
  {
    cerr << "Error al abrir el archivo " << nombreArchivo << " para escritura." << endl;
    return;
  }

  for (int i = 0; i < memoria.size(); i++)
  {
    archivo_salida << ">" << memoria[i].getNombre() << endl;
    for (int j = 0; j < memoria[i].getDatos().size(); j += memoria[i].getCantidadPorLinea())
    {
      archivo_salida << memoria[i].getDatos().substr(j, memoria[i].getCantidadPorLinea()) << endl;
    }
  }

  archivo_salida.close();
  cout << "Secuencias guardadas correctamente en " << nombreArchivo << endl;
  
}




void codificarArchivo(const string& nombreArchivo, const vector<Secuencia>& memoria){
  ArbolHuffman arbol;
  map<char, int> frecuencias;
    for (const Secuencia& secuencia : memoria) {
        const string& datos = secuencia.getDatos();
        for (size_t i = 0; i < datos.size(); ++i) {
            char c = datos[i];
            frecuencias[c]++;
        }
    }

    
    arbol.Arbol(frecuencias);             
    map<char, string> codigos;
    arbol.generarCodigo(arbol.obtenerRaiz(), "", codigos);

    ofstream salida(nombreArchivo, ios::binary);
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
        uint16_t li = nombre.size();
        salida.write(reinterpret_cast<char*>(&li), sizeof(uint16_t));
        salida.write(nombre.c_str(), li);
    }


    for (const Secuencia& seq : memoria) {
        const string& datos = seq.getDatos();
        int ancho = seq.getCantidadPorLinea();

        uint32_t wi = static_cast<uint32_t>(datos.size());
        int xi = ancho;

        salida.write(reinterpret_cast<char*>(&wi), sizeof(uint32_t));
        salida.write(reinterpret_cast<char*>(&xi), sizeof(int));

        // Codificar datos con Huffman
        string bits = arbol.codificar(datos, codigos);

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
    cout << " Archivo codificado correctamente: " << nombreArchivo << "\n";
}

void decodificarArchivo(const string& archivoEntrada, vector<Secuencia>& memoria){
  ArbolHuffman arbol;
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

    
    arbol.Arbol(frecuencias);

    
    uint32_t ns;
    entrada.read(reinterpret_cast<char*>(&ns), sizeof(uint32_t));

    for (uint32_t i = 0; i < ns; i++) {
        uint16_t li;
        entrada.read(reinterpret_cast<char*>(&li), sizeof(uint16_t));
        
        string nombre(li, '\0');
        entrada.read(&nombre[0], li);
        
        // Creamos la secuencia vacía y la guardamos
        memoria.push_back(Secuencia(nombre));
    }

   
    for (uint32_t i = 0; i < ns; i++) {
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
        string contenido = arbol.decodificar(bits.substr(0, bitLength));

        memoria[i].setDatos(contenido);
        memoria[i].setCantidadPorLinea(xi);
    }

    entrada.close();
    cout << " Archivo decodificado correctamente.\n";
}

Grafo<char> crearGrafo(string descripcion_secuencia, vector<Secuencia>& memoria){
  int a = 0;
  bool encontrada = false;

  // Buscar la secuencia
  for( a= 0 ; a < memoria.size(); a++){
    if( memoria[a].getNombre() == descripcion_secuencia){
      encontrada = true;
      break;
    }
  }

  if (!encontrada) {
      return Grafo<char>("",0);
  }
  int cantidad_por_linea = memoria[a].getCantidadPorLinea();
  int tamano_secuencia = memoria[a].getDatos().length();
  int indice_max_de_filas = trunc(tamano_secuencia/cantidad_por_linea);
  int cantidad_ultima_fila = tamano_secuencia % cantidad_por_linea;


  Grafo <char> grafo(descripcion_secuencia, cantidad_por_linea);


  // crear vertices
  for ( int v = 0; v < tamano_secuencia; v++){
    grafo.insertarVertice((char)(memoria[a].getDatos()[v]));
  }

  // crear aristas (dentro de la parte rectangular)
  for ( int x = 0; x < indice_max_de_filas; x++){
    for ( int y = 0; y < cantidad_por_linea-1; y++){
      grafo.insertarArista(x, y, x+1, y); // abajo
      grafo.insertarArista(x, y, x, y+1); // derecha
    }
    grafo.insertarArista(x, cantidad_por_linea-1, x+1, cantidad_por_linea-1); // ultima columna abajo
  }
  //crear aristas penultima fila
  int j = 0;
  while( j < cantidad_ultima_fila){
    grafo.insertarArista(indice_max_de_filas-1, j, indice_max_de_filas-2, j); // penultima fila abajo
    j++;
  }

  for (j= 0; j < cantidad_por_linea-1; j++){
    grafo.insertarArista(indice_max_de_filas-1, j, indice_max_de_filas-1, j+1); // penultima fila derecha
  }

  // crear aristas ultima fila
  for( int y = 0; y < cantidad_ultima_fila-1; y++){
    grafo.insertarArista(indice_max_de_filas, y, indice_max_de_filas, y+1); // ultima fila derecha
  }

  cout << "cantidad de aristas: " << grafo.cantAristas() << endl;

  return grafo;
}


void ruta_mas_corta(string descripcion_secuencia, int i, int j, int x, int y, vector<Secuencia>& memoria)
{
  Grafo<char> grafo = crearGrafo(descripcion_secuencia, memoria);
  if( grafo.cantVertices() == 0){
    cout << "No se puede crear el grafo ya que la secuencia no existe\n";
    return;
  }

}

void base_remota()
{
  cout << "Comando ejecutado\n";
}

void ayuda()
{

  cout << "lista de comandos: " << endl;
  cout << "------------------------------------------------" << endl
       << endl;
  cout << "cargar nombre_archivo" << endl
       << endl;

  cout << "listar_secuencias" << endl
       << endl;

  cout << "histograma descripcion_secuencia" << endl
       << endl;

  cout << "es_subsecuencia subsecuencia" << endl
       << endl;

  cout << "enmascarar subsecuencia" << endl
       << endl;

  cout << "guardar nombre_archivo" << endl
       << endl;

  cout << "codificar nombre_archivo.fabin" << endl
       << endl;

  cout << "decodificar nombre_archivo.fabin" << endl
       << endl;

  cout << "ruta_mas_corta descripcion_secuencia i j x y" << endl
       << endl;

  cout << "base_remota descripcion_secuencia i j" << endl
       << endl;

  cout << "salir" << endl
       << endl;
}

void ayudaComando(string comando)
{
  if (strcmp(comando.c_str(), "cargar") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << "cargar nombre_archivo" << endl;
    cout << "------------------------------------------------" << endl;
    cout << " Carga en memoria los datos contenidos en el archivo identificado por nombre_archivo." << endl;
    cout << "------------------------------------------------" << endl;
  }
  else if (strcmp(comando.c_str(), "listar_secuencias") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << "listar_secuencias" << endl;
    cout << "------------------------------------------------" << endl;
    cout << " Imprime la cantidad de secuencias actualmente en memoria, y luego, en n líneas (unapara secuencia) la información básica (nombre y cantidad de bases diferentes) de cada secuencia." << endl;
    cout << "------------------------------------------------" << endl;
  }
  else if (strcmp(comando.c_str(), "histograma") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << " histograma descripcion_secuencia" << endl;
    cout << "------------------------------------------------" << endl;
    cout << " Imprime el histograma de una secuencia, en caso de que exista.Por cada línea se escribe el código y la cantidad de veces que aparece en la secuencia." << endl;
    cout << "------------------------------------------------" << endl
         << endl;
  }
  else if (strcmp(comando.c_str(), "es_subsecuencia") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << "es_subsecuencia subsecuencia" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "  Determina si una subsecuencia (secuencia corta de bases) dada por el usuario, existe dentro de las secuencias cargadas en memoria. Si es así, determina la cantidad de veces en las que esta subsecuencia dada se repite." << endl;
    cout << "------------------------------------------------" << endl;
  }
  else if (strcmp(comando.c_str(), "enmascarar") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << "enmascarar subsecuencia" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Enmascara una subsecuencia (secuencia corta de bases) dada por el usuario, si existe." << endl;
    cout << "------------------------------------------------" << endl;
  }
  else if (strcmp(comando.c_str(), "guardar") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << "guardar nombre_archivo" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "  Guarda en el archivo nombre_archivo las secuencias cargadas en memoria." << endl;
    cout << "------------------------------------------------" << endl
         << endl;
  }
  else if (strcmp(comando.c_str(), "codificar") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << "codificar nombre_archivo.fabin" << endl;
    cout << "------------------------------------------------" << endl;
    cout << " Genera el archivo binario con la correspondiente codificación de Huffman, almacenándolo en disco bajo el nombre nombre_archivo.fabin." << endl;
    cout << "------------------------------------------------" << endl;
  }
  else if (strcmp(comando.c_str(), "decodificar") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << "decodificar nombre_archivo.fabin" << endl;
    cout << "------------------------------------------------" << endl;
    cout << " Carga en memoria las secuencias contenidas en el archivo binario nombre_archivo.fabin, que contiene una codificación Huffman.Tenga en cuenta que esto eliminara las secuencias previamente cargadas en memoria." << endl;
    cout << "------------------------------------------------" << endl;
  }
  else if (strcmp((comando).c_str(), "ruta_mas_corta") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << "ruta_mas_corta descripcion_secuencia i j x y" << endl
         << endl;
    cout << "------------------------------------------------" << endl;
    cout << " Imprime en pantalla la secuencia de vértices (bases) del grafo que describen la ruta más corta entre la base ubicada en la posición [i,j] de la matriz de la secuencia descripcion_secuencia y la base ubicada en la posición [x,y] de la misma matriz. Así mismo, imprime el costo total de la ruta, teniendo en cuenta el peso que tiene cada conexión entre bases." << endl;
    cout << "------------------------------------------------" << endl;
  }
  else if (strcmp((comando).c_str(), "base_remota") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << "base_remota descripcion_secuencia i j" << endl
         << endl;
    cout << "------------------------------------------------" << endl;
    cout << " Para la base ubicada en la posición [i,j] de la matriz de la secuencia descripcion_secuencia, el comando busca la ubicación de la misma base (misma letra) más lejana dentro de la matriz. Para esta base remota, el comando imprime en pantalla su ubicación, la secuencia de vértices (bases) que describen la ruta entre la base origen y la base remota, y el costo total de la ruta, teniendo en cuenta el peso que tiene cada conexión entre bases." << endl;
    cout << "------------------------------------------------" << endl;
  }
  else if (strcmp((comando).c_str(), "salir") == 0)
  {
    cout << "------------------------------------------------" << endl;
    cout << "salir" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Termina la ejecución de la aplicación." << endl;
    cout << "------------------------------------------------" << endl;
  }
  else
  {
    cout << "Comando no reconocido\n";
  }
}

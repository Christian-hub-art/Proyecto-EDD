#include "Sistema.h"
#include "Secuencia.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include "ArbolHuffman.h"
#include <bitset>
#include <cstdint>

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
    const string caracteresValidos = "ACGTURYKMSWBDHVNX-";

    while (getline(archivo, linea)) {
        if (linea.empty())
            continue;

        if (linea[0] == '>') {
            if (!nombreActual.empty() && secuenciaValida) {
                memoria.back().setDatos(datosActual);
            }

            nombreActual = "";
            for (int i = 1; i < linea.size(); i++) {
                nombreActual += linea[i];
            }

            memoria.push_back({nombreActual});
            datosActual.clear();
            secuenciaValida = true;
        } 
        else {
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
                    memoria.back().setCantidadPorLinea(linea.size());
                }
                datosActual += linea;
            }else{
              memoria.pop_back();
              datosActual.clear();
            }
        }
    }

    if (!memoria.empty() && secuenciaValida) {
        memoria.back().setDatos(datosActual);
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
  
}

void codificar_archivo(const string& nombreArchivo, const vector<Secuencia>& memoria) {
    // --- PASO 1: Validar que hay secuencias en memoria ---
    if (memoria.empty()) {
        std::cout << "(no hay secuencias cargadas) No hay secuencias cargadas en memoria." << std::endl;
        return;
    }

    // --- PASO 2: Calcular la tabla de frecuencias ---
    std::map<char, int> mapaFrecuencias;
    for (const Secuencia& seq : memoria) {
        for (char base : seq.getDatos()) {
            mapaFrecuencias[base]++;
        }
    }

    // --- PASO 3: Construir el árbol y generar los códigos ---
    ArbolHuffman arbol;
    arbol.construirDesdeFrecuencias(mapaFrecuencias);
   

    std::map<char, std::string> codigos;
     arbol.generarCodigo(arbol.obtenerRaiz(), "", codigos);

    // --- PASO 4: Abrir el archivo de salida en modo binario ---
    std::ofstream archivoSalida(nombreArchivo, std::ios::binary);
    if (!archivoSalida.is_open()) {
        std::cout << "(mensaje de error) No se pueden guardar las secuencias cargadas en " << nombreArchivo << "." << std::endl;
        return;
    }

    // --- PASO 5: Escribir la cabecera del archivo .fabin ---
    
    // n: Cantidad de bases diferentes (2 bytes) [cite: 182]
    short n_bases = mapaFrecuencias.size();
    archivoSalida.write(reinterpret_cast<const char*>(&n_bases), sizeof(short));

    // Tabla de frecuencias: n veces (c_i, f_i) [cite: 183]
    // c_i: Código de la base (1 byte)
    // f_i: Frecuencia (8 bytes, usamos long long para asegurar)
    for (const auto& par : mapaFrecuencias) {
        char caracter = par.first;
        long long frecuencia = par.second;
        archivoSalida.write(&caracter, sizeof(char));
        archivoSalida.write(reinterpret_cast<const char*>(&frecuencia), sizeof(long long));
    }

    // ns: Cantidad de secuencias (4 bytes) [cite: 184]
    int ns = memoria.size();
    archivoSalida.write(reinterpret_cast<const char*>(&ns), sizeof(int));
    
    // --- PASO 6: Escribir los datos de cada secuencia ---
    for (const Secuencia& seq : memoria) {
        // li: Tamaño del nombre (2 bytes) [cite: 185]
        short nombreLen = seq.getNombre().length();
        archivoSalida.write(reinterpret_cast<const char*>(&nombreLen), sizeof(short));

        // sij: Caracteres del nombre [cite: 186]
        archivoSalida.write(seq.getNombre().c_str(), nombreLen);

        // wi: Longitud de la secuencia (8 bytes) [cite: 187]
        long long secuenciaLen = seq.getDatos().length();
        archivoSalida.write(reinterpret_cast<const char*>(&secuenciaLen), sizeof(long long));
        
        // xi: Justificación (ancho de línea) (2 bytes) [cite: 188]
        short justificacion = seq.getCantidadPorLinea(); // Necesitarás este método en tu clase Secuencia
        archivoSalida.write(reinterpret_cast<const char*>(&justificacion), sizeof(short));
        
        // binary_code: La secuencia codificada [cite: 189]
        std::string bufferBits = "";
        for (char base : seq.getDatos()) {
            bufferBits += codigos[base];
        }

        // --- Manejo de bits y padding ---
        unsigned char byte = 0;
        int bitCount = 0;
        for (char bit : bufferBits) {
            byte = (byte << 1) | (bit - '0');
            bitCount++;
            if (bitCount == 8) {
                archivoSalida.write(reinterpret_cast<const char*>(&byte), sizeof(unsigned char));
                byte = 0;
                bitCount = 0;
            }
        }
        // Escribir los bits restantes (padding con ceros a la derecha)
        if (bitCount > 0) {
            byte <<= (8 - bitCount);
            archivoSalida.write(reinterpret_cast<const char*>(&byte), sizeof(unsigned char));
        }
    }

    archivoSalida.close();
    std::cout << "Secuencias codificadas y almacenadas en " << nombreArchivo << "." << std::endl;
}

string codificar(string dato, map<char, string> &codigos) {
    string encadenado;

    for (int i = 0; i < dato.size(); ++i) {
        char c = dato[i];
        encadenado += codigos.at(c);
    }

    return encadenado;
}

void decodificar_archivo(const string& nombreArchivo, vector<Secuencia>& memoria) {
    // --- PASO 1: Validar extensión y abrir el archivo en modo binario ---
    if (nombreArchivo.length() < 6 || nombreArchivo.substr(nombreArchivo.length() - 6) != ".fabin") {
        std::cout << "(mensaje de error) No se pueden cargar las secuencias desde " << nombreArchivo << "." << std::endl;
        return;
    }
    std::ifstream archivoEntrada(nombreArchivo, std::ios::binary);
    if (!archivoEntrada.is_open()) {
        std::cout << "(mensaje de error) No se pueden cargar las secuencias desde " << nombreArchivo << "." << std::endl;
        return;
    }

    // --- PASO 2: Limpiar la memoria actual ---
    memoria.clear();

    // --- PASO 3: Leer la cabecera del archivo ---
    
    // n: Cantidad de bases diferentes (2 bytes)
    short n_bases;
    archivoEntrada.read(reinterpret_cast<char*>(&n_bases), sizeof(short));
    if (archivoEntrada.gcount() != sizeof(short)) { // Verificar que la lectura fue exitosa
        std::cout << "(mensaje de error) El archivo esta corrupto o tiene un formato invalido." << std::endl;
        return;
    }

    // Tabla de frecuencias: n veces (c_i, f_i)
    std::map<char, int> mapaFrecuencias;
    for (int i = 0; i < n_bases; ++i) {
        char caracter;
        long long frecuencia;
        archivoEntrada.read(&caracter, sizeof(char));
        archivoEntrada.read(reinterpret_cast<char*>(&frecuencia), sizeof(long long));
        mapaFrecuencias[caracter] = static_cast<int>(frecuencia); // Convertir de nuevo a int para tu árbol
    }

    // --- PASO 4: Reconstruir el árbol de Huffman ---
    ArbolHuffman arbol;
    arbol.construirDesdeFrecuencias(mapaFrecuencias);

    // ns: Cantidad de secuencias (4 bytes)
    int ns;
    archivoEntrada.read(reinterpret_cast<char*>(&ns), sizeof(int));

    // --- PASO 5: Leer y decodificar cada secuencia ---
    for (int i = 0; i < ns; ++i) {
        // li: Tamaño del nombre (2 bytes)
        short nombreLen;
        archivoEntrada.read(reinterpret_cast<char*>(&nombreLen), sizeof(short));

        // sij: Caracteres del nombre
        std::string nombreSecuencia(nombreLen, '\0');
        archivoEntrada.read(&nombreSecuencia[0], nombreLen);

        // wi: Longitud de la secuencia (8 bytes)
        long long secuenciaLen;
        archivoEntrada.read(reinterpret_cast<char*>(&secuenciaLen), sizeof(long long));
        
        // xi: Justificación (ancho de línea) (2 bytes)
        short justificacion;
        archivoEntrada.read(reinterpret_cast<char*>(&justificacion), sizeof(short));

        // --- Decodificar el binary_code ---
        std::string contenidoDecodificado = "";
        Nodo* nodoActual = arbol.obtenerRaiz();
        
        // Manejo especial para árboles con un solo nodo
        if (!nodoActual->obtenerIzq() && !nodoActual->obtenerDer()) {
             contenidoDecodificado = std::string(secuenciaLen, nodoActual->obtenerDatos());
             // Hay que "consumir" los bytes del archivo aunque no los usemos
             long long bytesAvanzar = (secuenciaLen + 7) / 8; // Aproximar al byte superior
             archivoEntrada.seekg(bytesAvanzar, std::ios_base::cur);
        } else {
            unsigned char byte;
            while (contenidoDecodificado.length() < secuenciaLen && archivoEntrada.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
                for (int bit = 7; bit >= 0 && contenidoDecodificado.length() < secuenciaLen; --bit) {
                    // Moverse en el árbol según el bit
                    if ((byte >> bit) & 1) {
                        nodoActual = nodoActual->obtenerDer();
                    } else {
                        nodoActual = nodoActual->obtenerIzq();
                    }
                    
                    // Si llegamos a una hoja
                    if (!nodoActual->obtenerIzq() && !nodoActual->obtenerDer()) {
                        contenidoDecodificado += nodoActual->obtenerDatos();
                        nodoActual = arbol.obtenerRaiz(); // Volver a la raíz para el siguiente caracter
                    }
                }
            }
        }
        
        // --- Guardar la secuencia decodificada en memoria ---
        Secuencia seq(nombreSecuencia, ""); // Crear objeto Secuencia
        seq.setDatos(contenidoDecodificado);
        seq.setCantidadPorLinea(justificacion); // Necesitarás este método en tu clase Secuencia
        memoria.push_back(seq);
    }

    archivoEntrada.close();
    std::cout << "Secuencias decodificadas desde " << nombreArchivo << " y cargadas en memoria." << std::endl;
}

string decodificar(string bits, ArbolHuffman &arbol) {

    string resultado;
    Nodo* actual = arbol.obtenerRaiz();

    for ( int i = 0; i < bits.size(); ++i) {
        char bit = bits[i];
        if (bit == '0')
            actual = actual->obtenerIzq();
        else
            actual = actual->obtenerDer();
        if (actual->obtenerIzq() == nullptr && actual->obtenerDer() == nullptr) {
            resultado += actual->obtenerDatos();
            actual = arbol.obtenerRaiz();
    }
    }

    return resultado;
}

void ruta_mas_corta()
{
  cout << "Comando ejecutado\n";
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

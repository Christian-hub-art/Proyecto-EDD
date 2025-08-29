#include "Sistema.h"
#include "Secuencia.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void cargar_archivo(const string &nombreArchivo, vector<Secuencia> &memoria)
{
  cout << "Comando ejecutado\n";
  ifstream archivo(nombreArchivo);

  if (!archivo.is_open())
  {
    cout << nombreArchivo << " no se encuentra o no puede leerse." << endl;
    return;
  }

  memoria.clear(); // sobrescribir lo que había antes

  string linea, nombreActual, datosActual;
  while (getline(archivo, linea))
  {
    if (linea.empty())
      continue;

    if (linea[0] == '>')
    {
      if (nombreActual.empty())
      {
        nombreActual = linea.substr(1);
        memoria.push_back({nombreActual});
        datosActual.clear();
        nombreActual.clear();
      }
    }
    else
    {
      if (datosActual.empty())
      {
        memoria.back().setCantidadPorLinea(linea.size());
      }
      datosActual += linea;
      memoria.back().setDatos(datosActual);
    }
  }

  int n = memoria.size();
  if (n == 0)
  {
    cout << nombreArchivo << " no contiene ninguna secuencia." << endl;
  }
  else if (n == 1)
  {
    cout << "1 secuencia cargada correctamente desde " << nombreArchivo << "." << endl;
  }
  else
  {
    cout << n << " secuencias cargadas correctamente desde " << nombreArchivo << "." << endl;
  }
}

void listar_secuencias(const vector<Secuencia>& memoria){
    if (memoria.empty()) {
        cout << "(no hay secuencias cargadas) No hay secuencias cargadas en memoria." << endl;
        return;
    }

    cout << "resultado exitoso Hay " << memoria.size() 
         << " secuencias cargadas en memoria:" << endl;

    for (size_t i = 0; i < memoria.size(); i++) {
        cout << "Secuencia " << memoria[i].getNombre();
	
	bool encontrar = false;
	vector < char > aux;

	for(int j = 0; j < memoria[i].getDatos().size(); j++){
 		char letra = memoria[i].getDatos()[j];
		if(letra == '-'){
		encontrar = true;
		continue;
		}
	
 	
		bool encontrar2 = false;

		for(int z = 0; z < aux.size(); z++){
			if(aux[z] == letra){
			encontrar2 = true;
			break;
			}		
		} 	
	
		if(!encontrar2){
		aux.push_back(letra);
		}
	}

	if(!encontrar){
	cout<<" tiene "<<aux.size()<<" bases."<<endl;
	}else{
	cout<<" tiene al menos "<<aux.size()<<" bases."<<endl;
	}

    }
}


void histograma_secuencia(const string secuencia, vector<Secuencia> &memoria)
{

  vector<char> codigo = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};

  vector<int> conteo(codigo.size(), 0);

  bool existente = false;

  Secuencia sec_temp = Secuencia("");
  for (int i = 0; i < memoria.size(); i++)
  {
    if (secuencia == memoria[i].getNombre())
    {
      sec_temp = memoria[i];
      existente = true;
      break;
    }
  }

  if (!existente)
  {
    cout << "La secuencia no existe\n";
    return;
  }

  for (int i = 0; i < sec_temp.getDatos().size(); i++)
  {
    char letra = sec_temp.getDatos()[i];
    for (int j = 0; j < codigo.size(); j++)
    {
      if (letra == codigo[j])
      {
        conteo[j]++;
        break;
      }
    }
  }

  for (int i = 0; i < codigo.size(); i++)
  {
    cout << codigo[i] << " : " << conteo[i] << endl;
  }

  
}

bool comparar_caracteres(char subsecuencia_char, char secuencia_char)
{
  subsecuencia_char = toupper(subsecuencia_char);
  secuencia_char = toupper(secuencia_char);

  // Si los caracteres son iguales, hay una coincidencia
  if (subsecuencia_char == secuencia_char)
  {
    return true;
  }

  // Lógica para las bases especiales usando if/else if
  if (secuencia_char == 'R')
  {
    if (subsecuencia_char == 'A' || subsecuencia_char == 'G')
      return true;
  }
  else if (secuencia_char == 'Y')
  {
    if (subsecuencia_char == 'C' || subsecuencia_char == 'T' || subsecuencia_char == 'U')
      return true;
  }
  else if (secuencia_char == 'K')
  {
    if (subsecuencia_char == 'G' || subsecuencia_char == 'T' || subsecuencia_char == 'U')
      return true;
  }
  else if (secuencia_char == 'M')
  {
    if (subsecuencia_char == 'A' || subsecuencia_char == 'C')
      return true;
  }
  else if (secuencia_char == 'S')
  {
    if (subsecuencia_char == 'C' || subsecuencia_char == 'G')
      return true;
  }
  else if (secuencia_char == 'W')
  {
    if (subsecuencia_char == 'A' || subsecuencia_char == 'T' || subsecuencia_char == 'U')
      return true;
  }
  else if (secuencia_char == 'B')
  {
    if (subsecuencia_char == 'C' || subsecuencia_char == 'G' || subsecuencia_char == 'T' || subsecuencia_char == 'U')
      return true;
  }
  else if (secuencia_char == 'D')
  {
    if (subsecuencia_char == 'A' || subsecuencia_char == 'G' || subsecuencia_char == 'T' || subsecuencia_char == 'U')
      return true;
  }
  else if (secuencia_char == 'H')
  {
    if (subsecuencia_char == 'A' || subsecuencia_char == 'C' || subsecuencia_char == 'T' || subsecuencia_char == 'U')
      return true;
  }
  else if (secuencia_char == 'V')
  {
    if (subsecuencia_char == 'A' || subsecuencia_char == 'C' || subsecuencia_char == 'G')
      return true;
  }
  else if (secuencia_char == 'N')
  {
    if (subsecuencia_char == 'A' || subsecuencia_char == 'C' || subsecuencia_char == 'G' || subsecuencia_char == 'T' || subsecuencia_char == 'U')
      return true;
  }

  return false;
}

vector <vector<int>> inicios_subsecuencia(const string& subsecuencia, const vector<Secuencia>& memoria){
  vector < vector <int>> resultados( memoria.size());
  bool es_subsecuencia; 
  for (int num_sec = 0; num_sec < memoria.size(); num_sec++){
    Secuencia sec = memoria[num_sec];
    for(int i=0 ; i<sec.getDatos().size() - subsecuencia.length()+1; i++){
       es_subsecuencia = true; 
      for( int j= 0; j< subsecuencia.length(); j++){
        if( !comparar_caracteres(subsecuencia[j] ,sec.getDatos()[i+j]) )
        {
          es_subsecuencia = false;
          break;
        }
      }
      if(es_subsecuencia){
        resultados[num_sec].push_back(i);
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
    cout <<  "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria.";
  }else{
    cout << "La subsecuencia dada existe "<< conteo << " veces dentro de las secuencias cargadas en memoria.";
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
    cout <<  "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada.";
  }else{
    cout << conteo << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.";
  }
}

void guardar_archivo(const string &nombreArchivo, const vector<Secuencia> &memoria)
{

  std::ofstream archivo_salida(nombreArchivo);

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

void codificar_archivo()
{
  cout << "Comando ejecutado\n";
}

void decodificar_archivo()
{
  cout << "Comando ejecutado\n";
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

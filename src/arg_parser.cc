/**
  * Universidad de La Laguna
  * Escuela Superior de Ingenieria y Tecnologia
  * Grado en Ingenieria Informatica
  * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
  * Curso: 2º
  * Practica 1:  Hormiga de Langton
  * Autor: Ignacio Andres Rivera Barrientos
  * Correo: alu0101675053@ull.edu.es
  * Fecha: 05/02/2026

  * Archivo arg_parser.cc: Implementacion de la clase ArgParser y funciones utilizadas.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  */
#include "arg_parser.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>



/**
 * @brief Checks if a file exists and can be opened.
 * @param filename Path to the file.
 * @return true if the file can be opened, false otherwise.
 *
 * This is used by the argument parser to validate the input file
 * without fully processing it.
 */
bool FileExists(const std::string& filename) {
  std::ifstream file(filename);
  return file.good();   // true si existe y se pudo abrir
}



/**
 * @brief Prints the expected input file format (assignment format).
 *
 * This function is only used when showing help information.
 * It is kept as a static helper because it is only needed in this file.
 */
static void PrintFormatINPUT() {
  std::cout
    << "\nFormato del archivo input.txt\n"
    << "-----------------------------\n"
    << "Linea 1: Tamaño de la cinta: sizeX sizeY\n"
    << "Linea 2: Posición inicial y orientación de la hormiga\n"
    << "         (0=izquierda, 1=derecha, 2=arriba, 3=abajo): x y dir\n"
    << "Línea 3..n: Posiciones de las celdas negras (valor 1):\n"
    << "x y\n\n";
}



/**
 * @brief Parses command line arguments and returns the input file path.
 * @param argc Number of arguments.
 * @param argv Array of argument strings.
 * @return Input file path, or empty string if help was requested.
 * @throws std::invalid_argument if number of arguments is incorrect.
 * @throws std::runtime_error if input file does not exist or cannot be opened.
 *
 * Supported usage:
 *  - program input.txt
 *  - program --help / -h
 */
std::string ArgParser::Parse(int argc, char* argv[]) {
  // Help: imprime y no es error
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0) {
      PrintHelp(argv[0]);
      return "";  // main() puede hacer return 0;
    }
  }

  // Esperamos exactamente 1 argumento de entrada: prog input.txt
  if (argc != 2) {
    PrintUsage(argv[0]);
    throw std::invalid_argument("Numero de argumentos invalido.");
  }

  const std::string input_file = argv[1];
  if (!FileExists(input_file)) {
    PrintUsage(argv[0]);
    throw std::runtime_error("El fichero de entrada no existe o no se puede abrir: " + input_file);
  }

  return input_file;
}



/**
 * @brief Prints a short usage message.
 * @param progname Program name (argv[0]).
 */
void ArgParser::PrintUsage(const char* progname) {
  std::cout << "Uso: " << progname << " input.txt \n"
            << "Pruebe con --help o -h para mas informacion.\n";
}



/**
 * @brief Prints full help information for the program.
 * @param progname Program name (argv[0]).
 *
 * It includes a brief description and the expected input format.
 */
void ArgParser::PrintHelp(const char* progname) {
  std::cout << "Simulador del comportamiento de la hormiga de Langton\n"
            << "Uso: " << progname << " input.txt\n";
  PrintFormatINPUT();
}

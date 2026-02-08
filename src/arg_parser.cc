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

bool FileExists(const std::string& filename) {
  std::ifstream file(filename);
  return file.good();   // true si existe y se pudo abrir
}


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

void ArgParser::PrintUsage(const char* progname) {
  std::cout << "Uso: " << progname << " input.txt \n"
            << "Pruebe con --help o -h para mas informacion.\n";
}

void ArgParser::PrintHelp(const char* progname) {
  std::cout << "Simulador del comportamiento de la hormiga de Langton\n"
            << "Uso: " << progname << " input.txt\n";
  PrintFormatINPUT();
}

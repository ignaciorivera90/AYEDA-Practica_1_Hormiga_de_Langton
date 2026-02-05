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
    << "------------------------\n"
    << "Linea 1: Tamaño de la cinta: base x altura\n"
    << "Linea 2: Posición inicial y orientación de la hormiga (0, 1, 2 y 3 respectivamente izquierda, arriba, derecha, abajo): posicionX posicionY orientación\n"
    << "Línea 3..n: Posiciones de las celdas negras (valor binario 1):\n"
    << "posicionX posicionY\n"
    << "posicionX posicionY\n"
    << "posicionX posicionY\n\n";
}

std::string ArgParser::Parse(int argc, char* argv[]) {
  std::string input_file;

  // Help
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0) {
      PrintHelp(argv[0]);
      exit(1);
    }
  }
  // Esperamos 2 argumentos, el archivo de entrada
  if (argc == 2) {
    if (!FileExists(argv[1])) {
      PrintUsage(argv[0]);
      exit(1);
    }
    input_file = argv[1];
    return input_file;
  }

  PrintUsage(argv[0]);
  exit(1);
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

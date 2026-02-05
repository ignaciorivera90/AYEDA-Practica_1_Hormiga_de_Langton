#include <iostream>
#include <string>
#include "simulator.h"
#include "arg_parser.h"

int main(int argc, char* argv[]) {
  std::string input_file = ArgParser::Parse(argc, argv);
  // 1) leer filename si existe
  // 2) crear Simulator
  // 3) simulator.Run()
  // 4) preguntar save
  return 0;
}

#include <iostream>
#include <string>
#include <exception>

#include "simulator.h"
#include "arg_parser.h"

int main(int argc, char* argv[]) {
  try {
    std::string input_file = ArgParser::Parse(argc, argv);
    if (input_file.empty()) return 0;
    
    Simulator sim(input_file);
    sim.Run();
  } catch (const std::exception& e) {
    std::cerr << "\n[ERROR] " << e.what() << "\n";
    return 1;
  }
  return 0;
}


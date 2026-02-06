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

  * Archivo tape.h: Implentacion de la clase Tape.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  */

#include <fstream> 
#include <sstream>
#include "tape.h"



Tape::Tape(int size_x, int size_y) {
  size_x_ = size_x;
  size_y_ = size_y;
  world_.resize(size_x);                 // tamaño en X
  for (int i = 0; i < size_x; ++i) {
    world_[i].resize(size_y, false);   // tamaño en Y + rellenar con 0
  }

}

Tape::Tape(const std::string &filename) {
  std::ifstream input(filename);   // abrir archivo

  if (!input.is_open()) {
    std::cerr << "No se pudo abrir el archivo" << std::endl;
    exit(1);
  }

  std::string line;
  int line_number{1};
  while (std::getline(input, line)) {   // leer línea por línea
    std::istringstream iss(line);
    if(line_number == 1) {
      int size_x;
      int size_y;
      if (iss >> size_x >> size_y) {
        size_x_ = size_x;
        size_y_ = size_y;
      } else {
        std::cerr << "Error leyendo tamaño del mundo" << std::endl;
        std::cerr << "Se mantiene el valor anterior" << std::endl;
      }
    }

    if(line_number == 2) {
      
    }



    ++line_number;
  }

  input.close();
}



void Tape::SetCell(int coords_x, int coords_y, bool value) {

}



void Tape::FlipCell(int coords_x, int coords_y) {

}



void Tape::InBounds(int coords_x, int coords_y) const {

}



const bool Tape::GetCell(int coords_x, int coords_y) const {

  return false;
}



void Tape::ModifyAnt(int coords_x, int coords_y, Direction dir) {

}



void Tape::LoadFromFile(const std::string &filename) {

}



void Tape::SaveToFile(const std::string &filename, int ant_x, int ant_y, int ant_dir) const {

}

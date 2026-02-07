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
  *      06/02/2026 - Creacion de las implementaciones de la clase tape y sus comentarios
  *      07/02/2026 - Termino de las implementaciones de la clase tape y sus comentarios
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
  LoadFromFile(filename);
}



void Tape::SetCell(int coords_x, int coords_y, bool value) {
  world_[coords_x][coords_y] = value;
}



void Tape::FlipCell(int coords_x, int coords_y) {
  world_[coords_x][coords_y] = !world_[coords_x][coords_y];
}



bool Tape::InBounds(int coords_x, int coords_y) const {
  if ((0 <= coords_x <= size_x_) && (0 <= coords_y <= size_y_)) {
    return true;
  } else {
    return false;
  }
}



const bool Tape::GetCell(int coords_x, int coords_y) const {
  return world_[coords_x][coords_y];
}



void Tape::ModifyAnt(int coords_x, int coords_y, Direction dir) {
  if ((0 <= coords_x <= size_x_) && (0 <= coords_y <= size_y_)) {
    ant_->SetPosition(coords_x, coords_y);
    ant_->SetDirection(dir);
  } else {
    std::cerr << "Error modificando coordenadas de la hormiga y direccion" << std::endl;
    std::cerr << "Se mantiene el valor anterior" << std::endl;
  }
}



void Tape::LoadFromFile(const std::string &filename) {
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
      int coords_x;
      int coords_y;
      int dir;
      if ((iss >> coords_x >> coords_y >> dir) && (0 <= coords_x <= size_x_) && (0 <= coords_y <= size_y_)) {
        ant_->SetPosition(coords_x, coords_y);
        ant_->SetDirection(Direction(dir));
      } else {
        std::cerr << "Error leyendo coordenadas de la hormiga y direccion" << std::endl;
        std::cerr << "Se mantiene el valor anterior" << std::endl;
      }
    }

    if (line_number <= 3) {
      int black_x;
      int black_y;
      if ((iss >> black_x >> black_y) && (0 <= black_x <= size_x_) && (0 <= black_y <= size_y_)) {
        SetCell(black_x, black_y, 1);
      } else {
        std::cerr << "Error leyendo coordenadas de la celda negra en la linea " << line_number << std::endl;
        std::cerr << "No se ingresa el la celda negra" << std::endl;
      }
    }

    ++line_number;
  }

  input.close();
}



void Tape::SaveToFile(const std::string &filename) const {
  std::ofstream output(filename);   // abrir archivo

  if (!output.is_open()) {
    std::cerr << "No se pudo abrir el archivo" << std::endl;
    exit(1);
  }

  int ant_x = ant_->posicion_x();
  int ant_y = ant_->posocion_y();

  for (int i = 0; i < size_x_; ++i) {
    for (int j = 0; j < size_y_; ++j) {
      if (i == ant_x && j == ant_y) {
        output << ant_;          // imprime la hormiga
      } else {
        output << world_[i][j];     // imprime 0 o 1
      }
    }
    output << "\n";                 // salto de línea por fila
  }

  output.close();
}

std::ostream &operator<<(std::ostream &out, const Tape &tape) {
  int ant_x = tape.ant_->posicion_x();
  int ant_y = tape.ant_->posocion_y();

  for (int i = 0; i < tape.size_x(); ++i) {
    for (int j = 0; j < tape.size_y(); ++j) {
      if (i == ant_x && j == ant_y) {
        out << tape.ant_;          // imprime la hormiga
      } else {
        out << tape.GetCell(i, j);     // imprime 0 o 1
      }
    }
    out << "\n";                 // salto de línea por fila
  }
}

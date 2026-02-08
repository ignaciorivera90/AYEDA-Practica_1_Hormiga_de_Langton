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
#include <stdexcept>
#include "colors.h"
#include "tape.h"



/**
 * @brief Constructs a tape with fixed dimensions and initializes all cells to white (0/false).
 *        Also places the ant in the center of the tape with an initial direction.
 * @param size_x Width of the tape (X dimension).
 * @param size_y Height of the tape (Y dimension).
 * @note This implementation currently allocates an Ant dynamically (ant_).
 */
Tape::Tape(int size_x, int size_y) {
  size_x_ = size_x;
  size_y_ = size_y;
  world_.resize(size_y);                 // tamaño en y
  for (int i = 0; i < size_y; ++i) {
    world_[i].resize(size_x, false);   // tamaño en x + rellenar con 0
  }
  ant_ = nullptr; // colocar la hormiga en el centro del mundo
}



/**
 * @brief Constructs a tape by loading its configuration from a text file.
 * @param filename Path to the input file.
 * @note The file is expected to follow the format described in the assignment.
 */
Tape::Tape(const std::string &filename) {
  ant_ = nullptr;   // temporal hasta leer línea 2
  LoadFromFile(filename);
}



/**
 * @brief Sets the value (color) of a cell in the tape.
 * @param coords_x X coordinate of the cell.
 * @param coords_y Y coordinate of the cell.
 * @param value Cell value (false=white, true=black).
 * @throw std::out_of_range if coordinates are outside the tape bounds.
 */
void Tape::SetCell(int coords_x, int coords_y, bool value) {
  CheckBoundsOrThrow(coords_x, coords_y, "Tape::SetCell");
  world_[coords_y][coords_x] = value;
}



/**
 * @brief Toggles a cell value: white <-> black.
 * @param coords_x X coordinate.
 * @param coords_y Y coordinate.
 * @throw std::out_of_range if coordinates are outside the tape bounds.
 */
void Tape::FlipCell(int coords_x, int coords_y) {
  CheckBoundsOrThrow(coords_x, coords_y, "Tape::FlipCell");
  world_[coords_y][coords_x] = !world_[coords_y][coords_x];
}



/**
 * @brief Returns the value (color) of a cell.
 * @param coords_x X coordinate.
 * @param coords_y Y coordinate.
 * @return true if the cell is black, false if white.
 * @throw std::out_of_range if coordinates are outside the tape bounds.
 */
const bool Tape::GetCell(int coords_x, int coords_y) const {
  CheckBoundsOrThrow(coords_x, coords_y, "Tape::GetCell");
  return world_[coords_y][coords_x];
}



/**
 * @brief Updates the ant position and direction if the provided coordinates are valid.
 * @param coords_x New X coordinate for the ant.
 * @param coords_y New Y coordinate for the ant.
 * @param dir New direction for the ant.
 * @note If coordinates are invalid, the current implementation prints an error and keeps previous values.
 */
void Tape::ModifyAnt(Ant* ant) {
  ant_ = ant;
}



/**
 * @brief Loads tape size, ant initial state and black cells from a text file.
 * @param filename Path to the input file.
 * @note Expected format:
 *  Line 1: size_x size_y
 *  Line 2: ant_x ant_y direction
 *  Line 3..n: black_x black_y
 */
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
        world_.resize(size_y);                 // tamaño en y
        for (int i = 0; i < size_y; ++i) {
          world_[i].resize(size_x, false);   // tamaño en x + rellenar con 0
        }
      } else {
        std::cerr << "Error leyendo tamaño del mundo" << std::endl;
        std::cerr << "Se mantiene el valor anterior" << std::endl;
      }
    }

    if(line_number == 2) {
      int coords_x;
      int coords_y;
      int dir;
      if ((iss >> coords_x >> coords_y >> dir) && (0 <= coords_x && coords_x < size_x_) && (0 <= coords_y && coords_y < size_y_)) {
        ant_->SetPosition(coords_x, coords_y);
        ant_->SetDirection(Direction(dir));
      } else {
        std::cerr << "Error leyendo coordenadas de la hormiga y direccion" << std::endl;
        std::cerr << "Se mantiene el valor anterior" << std::endl;
      }
    }

    if (line_number >= 3) {
      int black_x;
      int black_y;
      if ((iss >> black_x >> black_y) && (0 <= black_x && black_x < size_x_) && (0 <= black_y && black_y < size_y_)) {
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



/**
 * @brief Saves the current simulation state to a text file using the assignment format.
 * @param filename Path to the output file.
 * @note It writes:
 *  Line 1: size_x size_y
 *  Line 2: ant_x ant_y direction
 *  Line 3..n: coordinates of black cells
 */
void Tape::SaveToFile(const std::string &filename) const {
  std::ofstream output(filename);   // abrir archivo

  if (!output.is_open()) {
    std::cerr << "No se pudo abrir el archivo" << std::endl;
    exit(1);
  }

  output << size_x_ << " " << size_y_ << "\n";  // primera línea: tamaño del mundo
  output << ant_->posicion_x() << " " << ant_->posicion_y() << " " << ant_->direction() << "\n"; // segunda línea: posición y dirección de la hormiga

  for (int y = 0; y < size_y_; ++y) {
    for (int x = 0; x < size_x_; ++x) {
      if (world_[y][x] == 1) {
        output << x << " " << y << "\n";              // imprime para celda negra
      }
    }
  }
  output.close();
}



/**
 * @brief Prints the tape in text mode, including the ant position and orientation.
 *        White cells are displayed as ' ' and black cells as 'X' (optionally colored).
 * @param out Output stream.
 * @param tape Tape to print.
 * @return Output stream (for chaining).
 */
std::ostream &operator<<(std::ostream &out, const Tape &tape) {
  int ant_x = tape.ant_->posicion_x();
  int ant_y = tape.ant_->posicion_y();
  Direction_Sprite dir_sprite = tape.ant_->direction_sprite();

  for (int y = 0; y < tape.size_y(); ++y) {
    for (int x = 0; x < tape.size_x(); ++x) {
      if (x == ant_x && y == ant_y) {
        if (tape.GetCell(x, y)) {
          out << ORANGE << BG_BLACK << std::string(1, dir_sprite) << RESET;
        } else {
          out << ORANGE << BG_WHITE << std::string(1, dir_sprite) << RESET;
        }
      } else {
        if (tape.GetCell(x, y)) {
          out  << BG_BLACK << 'X' << RESET;              // imprime 1 para celda negra
        } else {
          out << BG_WHITE << ' ' << RESET;              // imprime 0 para celda blanca
        }
      }
    }
    out << "\n";                 // salto de línea por fila
  }
  return out;
}



/**
 * @brief Checks if coordinates are within bounds. If not, prints an error and throws.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param where String indicating where the check was called from (for debugging).
 * @throw std::out_of_range if (x,y) is outside [0..size_x-1]x[0..size_y-1].
 */
void Tape::CheckBoundsOrThrow(int x, int y, const char* where) const {
  if (x < 0 || x >= size_x_ || y < 0 || y >= size_y_) {
    std::cerr << "[ERROR] " << where
              << ": coordenadas fuera de rango (" << x << ", " << y << ")"
              << " con tamaño (" << size_x_ << ", " << size_y_ << ")\n";
    throw std::out_of_range("Tape index out of range");
  }
}



/**
 * @brief Returns whether coordinates are inside the tape bounds.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @return true if inside bounds, false otherwise.
 */
bool Tape::InBounds(int x, int y) const {
  return (0 <= x && x < size_x_) && (0 <= y && y < size_y_);
}



/**
 * @brief Move constructor. Transfers the internal state from another Tape.
 * @param other Source Tape object to move from.
 *
 * This constructor moves the world grid and copies the pointer to the ant.
 * The source object is left in a safe empty state (no ant and size 0).
 */
Tape::Tape(Tape&& other) noexcept
  : size_x_(other.size_x_),
    size_y_(other.size_y_),
    world_(std::move(other.world_)),
    ant_(other.ant_) {
  other.ant_ = nullptr;
  other.size_x_ = 0;
  other.size_y_ = 0;
}



/**
 * @brief Move assignment operator. Transfers the state from another Tape.
 * @param other Source Tape object to move from.
 * @return Reference to this Tape.
 *
 * This operator moves the world grid and copies the pointer to the ant.
 * The source object is reset to an empty state. No memory is deleted because
 * the ant pointer is non-owning (Tape does not manage its lifetime).
 */
Tape& Tape::operator=(Tape&& other) noexcept {
  if (this != &other) {
    delete ant_;  // liberar lo actual

    world_  = std::move(other.world_);
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;
    ant_    = other.ant_;

    other.ant_ = nullptr;
    other.size_x_ = 0;
    other.size_y_ = 0;
  }
  return *this;
}
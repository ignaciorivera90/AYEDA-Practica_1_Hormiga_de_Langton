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

  * Archivo ant.cc: Implementacion de la clase Ant.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  *      06/02/2026 - Creacion de las implementaciones de la clase ant y sus comentarios
  *      07/02/2026 - Creacion del metodo de Step
  */

#include "ant.h"
#include "tape.h"
#include <sstream>     


Ant::Ant(int x, int y, Direction dir) {
  posicion_x_ = x;
  posicion_y_ = y;
  direction_ = dir;
  switch (dir) {
    case LEFT:
      direction_sprite_ = SPRITE_LEFT;
      break;

    case RIGHT:
      direction_sprite_ = SPRITE_RIGHT;
      break;

    case UP:
      direction_sprite_ = SPRITE_UP;
      break;

    case DOWN:
      direction_sprite_ = SPRITE_DOWN;
      break;
  
    default:
      break;
  }
}



/**
 * @param x
 * @param y
 * @brief change position
 */
void Ant::SetPosition(int x, int y) {
  posicion_x_ = x;
  posicion_y_ = y;
}



/**
 * @param dir
 * @brief change direccion
 */
void Ant::SetDirection(Direction dir) {
  direction_ = dir;
  switch (dir) {
    case LEFT:
      direction_sprite_ = SPRITE_LEFT;
      break;

    case RIGHT:
      direction_sprite_ = SPRITE_RIGHT;
      break;

    case UP:
      direction_sprite_ = SPRITE_UP;
      break;

    case DOWN:
      direction_sprite_ = SPRITE_DOWN;
      break;
  
    default:
      break;
  }
}



/**
 * @param tape
 * @brief perform a step in the simulation
 * @brief If it's over a white cell, change the color to black, rotate 90 degrees to the left, and move forward one cell.
 * @brief If it's over a black cell, change the color to white, rotate 90 degrees to the right, and move forward one cell.
 */
void Ant::Step(Tape &tape) {
  if(tape.GetCell(posicion_x_, posicion_y_)) {
    tape.FlipCell(posicion_x_, posicion_y_);
    TurnRight();
    MoveForward(tape);
  } else {
    tape.FlipCell(posicion_x_, posicion_y_);
    TurnLeft();
    MoveForward(tape);
  }
}



/**
 * @brief Change direction 90 degrees to the left
 */
void Ant::TurnLeft() {
  switch (direction_) {
    case LEFT:
      direction_ = DOWN;
      direction_sprite_ = SPRITE_DOWN;
      break;

    case RIGHT:
      direction_ = UP;
      direction_sprite_ = SPRITE_UP;
      break;

    case UP:
      direction_ = LEFT;
      direction_sprite_ = SPRITE_LEFT;
      break;

    case DOWN:
      direction_ = RIGHT;
      direction_sprite_ = SPRITE_RIGHT;
      break;
  
    default:
      break;
  }
}



/**
 * @brief Change direction 90 degrees to the right
 */
void Ant::TurnRight() {
  switch (direction_) {
    case LEFT:
      direction_ = UP;
      direction_sprite_ = SPRITE_UP;
      break;

    case RIGHT:
      direction_ = DOWN;
      direction_sprite_ = SPRITE_DOWN;
      break;

    case UP:
      direction_ = RIGHT;
      direction_sprite_ = SPRITE_RIGHT;
      break;

    case DOWN:
      direction_ = LEFT;
      direction_sprite_ = SPRITE_LEFT;
      break;
  
    default:
      break;
  }
}



/**
 * @brief move forward
 */
void Ant::MoveForward(const Tape& tape) {
  // Calcula siguiente posición SIN modificar todavía
  int next_x = posicion_x_;
  int next_y = posicion_y_;

  switch (direction_) {
    case Direction::LEFT:  --next_x; break;
    case Direction::RIGHT: ++next_x; break;
    case Direction::UP:    --next_y; break;
    case Direction::DOWN:  ++next_y; break;
  }

  // Comprueba límites con Tape
  if (!tape.InBounds(next_x, next_y)) {
    // Lanza excepción con info útil
    std::ostringstream oss;
    oss << "Ant::MoveForward: intento de salir de la cinta. "
        << "pos=(" << posicion_x_ << "," << posicion_y_ << "), "
        << "next=(" << next_x << "," << next_y << ")";
    throw std::out_of_range(oss.str());
  }

  // Si es válido, entonces sí actualiza
  posicion_x_ = next_x;
  posicion_y_ = next_y;
}



/**
 * @param out
 * @param ant
 * @brief overloading the output operator to display the ant
 */
std::ostream &operator<<(std::ostream &out, const Ant &ant) {
  out << ant.direction_sprite_;
  return out;
}


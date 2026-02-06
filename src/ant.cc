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
  */

#include "ant.h"
#include "tape.h"



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



void Ant::SetPosition(int x, int y) {
  posicion_x_ = x;
  posicion_y_ = y;
}



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



void Ant::Step(Tape &tape) {
  
}



void Ant::TurnLeft() {
  switch (direction_) {
    case LEFT:
      direction_ = DOWN;
      break;

    case RIGHT:
      direction_ = UP;
      break;

    case UP:
      direction_ = LEFT;
      break;

    case DOWN:
      direction_ = RIGHT;
      break;
  
    default:
      break;
  }
}



void Ant::TurnRight() {
  switch (direction_) {
    case LEFT:
      direction_ = UP;
      break;

    case RIGHT:
      direction_ = DOWN;
      break;

    case UP:
      direction_ = RIGHT;
      break;

    case DOWN:
      direction_ = LEFT;
      break;
  
    default:
      break;
  }
}



void Ant::MoveForward() {
  switch (direction_) {
    case LEFT:
      --posicion_x_;
      break;

    case RIGHT:
      ++posicion_x_;
      break;

    case UP:
      ++posicion_y_;
      break;

    case DOWN:
      --posicion_y_;
      break;
  
    default:
      break;
  }
}

std::ostream &operator<<(std::ostream &out, const Ant &ant) {
  out << ant.direction_sprite_;
  return out;
}

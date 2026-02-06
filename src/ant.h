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

  * Archivo ant.h: Declaracion de la clase Ant.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  */
 
#ifndef ANT_H
#define ANT_H

#include <iostream>
class Tape;  // forward declaration

enum Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN
};

enum Direction_Sprite {
  SPRITE_UP    = '^',
  SPRITE_LEFT  = '<', 
  SPRITE_DOWN  = 'v', 
  SPRITE_RIGHT = '>'  
};

class Ant {
 public:
  Ant(int x, int y, Direction dir);

  const int posicion_x() const { return posicion_x_; }
  const int posocion_y() const { return posicion_y_; }
  const Direction direction() const { return direction_; }
  const Direction_Sprite direction_sprite() const { return direction_sprite_; }
  void SetPosition(int x, int y);
  void SetDirection(Direction dir);

  //Movimiento
  // ejecuta 1 paso completo usando Tape
  void Step(Tape& tape);

  // Visualización 
  friend std::ostream& operator<<(std::ostream& out, const Ant& ant);

 private:
  int posicion_x_{0};
  int posicion_y_{0};
  Direction direction_{UP};
  Direction_Sprite direction_sprite_{SPRITE_UP};

  void TurnLeft();
  void TurnRight();
  void MoveForward();
};

#endif

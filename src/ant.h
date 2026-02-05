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

class Ant {
 public:
  enum class Direction {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3
  };

  // --- Constructores ---
  Ant(int x = 0, int y = 0, Direction dir = Direction::UP);

  // --- Consultas ---
  int GetX() const;
  int GetY() const;
  Direction GetDirection() const;

  // --- Modificación ---
  void SetPosition(int x, int y);
  void SetDirection(Direction dir);

  // --- Movimiento ---
  // ejecuta 1 paso completo usando Tape
  void Step(Tape& tape);

  // --- Visualización ---
  friend std::ostream& operator<<(std::ostream& os, const Ant& ant);

 private:
  int x_;
  int y_;
  Direction dir_;

  // Helpers privados (súper recomendados)
  void TurnLeft();
  void TurnRight();
  void MoveForward();
};

#endif

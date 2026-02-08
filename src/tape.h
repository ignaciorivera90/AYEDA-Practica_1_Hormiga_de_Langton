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

  * Archivo tape.h: Declaracion de la clase Tape.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  *      06/02/2026 - Creacion de las declaraciones de la clase tape y sus comentarios
  */
#ifndef TAPE_H
#define TAPE_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include "ant.h"
class Ant; // forward declaration

class Tape {
 public:
  Tape(int size_x, int size_y);
  Tape(const std::string& filename);   // inicialización leyendo fichero
  ~Tape() { delete ant_; }

  //Getters
  const int size_x() const { return size_x_; }
  const int size_y() const { return size_y_; }

  //Setters
  void SetCell(int coords_x, int coords_y, bool value); //se usa para ingresar las celdas 
  void FlipCell(int coords_x, int coords_y);         // cambia blanco<->negro

  //Metodos
  const bool GetCell(int coords_x, int coords_y) const;    // color: 0 blanca, 1 negra
  void ModifyAnt(int coords_x, int coords_y, Direction dir); // para colocar la hormiga
  bool InBounds(int x, int y) const;

  //Para leer otro mundo o dibujar el mundo actual
  void LoadFromFile(const std::string& filename);
  void SaveToFile(const std::string& filename) const;

  //Salida
  friend std::ostream& operator<<(std::ostream& os, const Tape& tape);

 private:
  int size_x_{0};
  int size_y_{0};
  std::vector<std::vector<bool>> world_;
  Ant* ant_ = nullptr;

  void CheckBoundsOrThrow(int x, int y, const char* where) const;
};

#endif

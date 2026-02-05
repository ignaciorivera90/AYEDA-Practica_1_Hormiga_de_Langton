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

  * Archivo simulator.h: Declaracion de la clase simulator.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  */
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>
#include "tape.h"
#include "ant.h"

class Simulator {
 public:
  // --- Constructores ---
  Simulator(int size_x, int size_y,
            int ant_x, int ant_y,
            Ant::Direction dir);

  Simulator(const std::string& filename);  // inicialización completa desde fichero

  // --- Control ---
  void Run();         // bucle principal de simulación
  void Step();        // un paso
  bool Finished() const;

  // --- Guardado ---
  void Save(const std::string& filename) const;

 private:
  Tape tape_;
  Ant ant_;

  unsigned long steps_;
  bool finished_;

  // Helpers
  void PrintState() const;
  bool AntOutOfBounds() const;
};

#endif

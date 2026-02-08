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

  * Archivo simulator.cc: Implementacion de la clase simulator.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  *      07/02/2026 - Implementaciones de los metodos y comentarios
  */
#include "simulator.h"
#include <iostream>




Simulator::Simulator(std::string filename) {
  

}



void Simulator::Run() {

}



void Simulator::Save(const std::string &filename) const {
  tape_.SaveToFile(filename);
}



void Simulator::Step() {
  ant_.Step(tape_);
}

bool Simulator::Finished() const {
    return ;
}

void Simulator::PrintState() const {
  
}

bool Simulator::AntOutOfBounds() const
{
    return false;
}

Simulator::Simulator(int width, int height, int ant_x, int ant_y, Direction dir) {
  
}

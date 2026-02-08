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
  *      08/02/2026 - Modificaciones en el la clase
  */
#include "simulator.h"
#include "funciones.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include <stdexcept>   // std::out_of_range, std::invalid_argument, std::runtime_error

// Funciones auxiliares para lectura de entrada y validación



int ReadUserAction() {
  std::string input;
  std::getline(std::cin, input);

  if (input.empty()) return 2;
  if (input == "q" || input == "Q") return 1;
  return 3;
}



static std::string ReadLine() {
  std::string line;
  std::getline(std::cin, line);
  return line;
}




static int ReadInt(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    std::string s = ReadLine();
    try {
      size_t pos = 0;
      int v = std::stoi(s, &pos);
      if (pos != s.size()) throw std::invalid_argument("extra");
      return v;
    } catch (...) {
      std::cout << "Entrada no válida.\n";
    }
  }
}





static unsigned long ReadULong(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    std::string s = ReadLine();
    try {
      size_t pos = 0;
      unsigned long v = std::stoul(s, &pos);
      if (pos != s.size()) throw std::invalid_argument("extra");
      return v;
    } catch (...) {
      std::cout << "Entrada no válida.\n";
    }
  }
}




static bool AskYesNo(const std::string& question) {
  while (true) {
    std::cout << question << " (s/n): ";
    std::string ans = ReadLine();
    if (ans == "s" || ans == "S") return true;
    if (ans == "n" || ans == "N") return false;
    std::cout << "Respuesta no válida.\n";
  }
}

// Clase Simulator




Simulator::Simulator(const std::string& filename) : tape_(1, 1), ant_(0, 0, UP) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("No se pudo abrir el fichero de entrada: " + filename);
  }

  int size_x = 0, size_y = 0;
  int ax = 0, ay = 0;
  int dir_int = 0;

  // Línea 1: tamaño
  if (!(file >> size_x >> size_y)) {
    throw std::invalid_argument("Formato inválido: línea 1 (tamaño)");
  }

  // Línea 2: hormiga (x y dir)
  if (!(file >> ax >> ay >> dir_int)) {
    throw std::invalid_argument("Formato inválido: línea 2 (hormiga)");
  }

  if (size_x <= 0 || size_y <= 0) {
    throw std::invalid_argument("Tamaño inválido (debe ser mayor a 0).");
  }
  if (dir_int < 0 || dir_int > 3) {
    throw std::invalid_argument("Dirección inválida (debe ser 0..3).");
  }

  // Construimos el estado real
  tape_ = Tape(size_x, size_y);
  ant_  = Ant(ax, ay, static_cast<Direction>(dir_int));

  if (!tape_.InBounds(ax, ay)) {
    throw std::invalid_argument("La posición inicial de la hormiga está fuera de rango.");
  }

  // Línea 3..n: celdas negras
  int bx = 0, by = 0;
  while (file >> bx >> by) {
    if (!tape_.InBounds(bx, by)) {
      throw std::invalid_argument("Celda negra fuera de rango en fichero.");
    }
    tape_.SetCell(bx, by, true);
  }

  steps_ = 0;
  finished_ = false;
}



void Simulator::Run() {
  while (true) {
    clrscr();
    std::cout << "===== Hormiga de Langton =====" << std::endl;
    std::cout << "1) Mostrar estado actual del mundo" << std::endl;
    std::cout << "2) Mostrar recorrido de la hormiga en el mundo actual paso a paso" << std::endl;
    std::cout << "3) Mostrar recorrido de la hormiga en el mundo actual n numero de pasos" << std::endl;
    std::cout << "4) Guardar estado" << std::endl;
    std::cout << "0) Salir" << std::endl;
    std::cout << "==================================" << std::endl;

    int op = ReadInt("Introduce un numero > ");
    clrscr();

    if (op == 1) {
      PrintState();
      std::cout << "Pulsa ENTER para continuar...";
      pressEnter();
      clrscr();
      continue;
    }

    if (op == 2) {
      while (true) {
        PrintState();
        std::cout << "Pulsa ENTER para el siguiente paso, o 'q' + ENTER para volver al menu: ";
        int action = ReadUserAction();
        if (action == 1) {  // Quit
          clrscr();
          break;
        } else if (action == 2) {  // Solo ENTER
          // Continúa al siguiente paso
          Step();
          clrscr();
        } else {
          clrscr();
          std::cout << "Opcion no valida." << std::endl;
          std::cout << "Pulsa ENTER para continuar...";
          pressEnter();
          clrscr();
          continue;
        }
        if (Finished()) {
          clrscr();
          std::cout << "\n[FIN] Simulación terminada." << std::endl;
          if (AskYesNo("¿Deseas guardar el estado final?")) {
            std::cout << "Fichero de salida: ";
            std::string out = ReadLine();
            if (!out.empty()) Save(out);
          }
          return;
        }
      }
      continue;
    }

    if (op == 3) {
      unsigned long n = ReadULong("N pasos: ");
      for (unsigned long i = 0; i < n && !Finished(); ++i) {
        Step();
      }
      if (Finished()) {
        clrscr();
        std::cout << "\n[FIN] Simulación terminada." << std::endl;
        if (AskYesNo("¿Deseas guardar el estado final?")) {
          std::cout << "Fichero de salida: ";
          std::string out = ReadLine();
          if (!out.empty()) Save(out);
        }
        return;
      }
      PrintState();
      std::cout << "Pulsa ENTER para continuar y volver al menu...";
      pressEnter();
      clrscr();
      continue;
    }

    if (op == 4) {
      std::cout << "Fichero de salida: ";
      std::string out = ReadLine();

      if (out.empty()) {
        std::cout << "Nombre vacío. No se guarda.\n";
      } else {
        Save(out);
        std::cout << "Estado guardado en '" << out << "'\n";
      }

      std::cout << "Pulsa ENTER para volver al menu...";
      pressEnter();
      clrscr();
      continue;
    } 

    if (op == 0) {
      // Requisito: antes de terminar, preguntar si desea guardar el estado final
      if (AskYesNo("¿Deseas guardar el estado final antes de salir?")) {
        std::cout << "Fichero de salida: ";
        std::string out = ReadLine();
        if (!out.empty()) Save(out);
        std::cout << "Estado guardado en '" << out << "'" << std::endl;
        std::cout << "Pulsa ENTER para salir...";
        pressEnter();
        clrscr();
      }
      return;
    }

    std::cout << "Opcion no valida." << std::endl;
    std::cout << "Pulsa ENTER para continuar...";
    pressEnter();
    clrscr();
  }
}

void Simulator::Save(const std::string& filename) const {
  tape_.SaveToFile(filename);
}


void Simulator::Step() {
  if (finished_) return;

  try {
    ant_.Step(tape_);     // puede lanzar out_of_range si sale fuera
    ++steps_;
    if (AntOutOfBounds()) finished_ = true;
  } catch (const std::out_of_range& e) {
    // si sale fuera se termina 
    std::cerr << "[FIN] La hormiga intentó salir de la cinta: " << e.what() << "\n";
    finished_ = true;
  }
}

bool Simulator::Finished() const {
  return finished_;
}

void Simulator::PrintState() const {
  std::cout << "\nSteps: " << steps_ << std::endl;
  std::cout << tape_ << std::endl << std::endl;
}

bool Simulator::AntOutOfBounds() const {
  return !tape_.InBounds(ant_.posicion_x(), ant_.posicion_y());
}

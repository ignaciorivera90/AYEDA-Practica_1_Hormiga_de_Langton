#ifndef TAPE_H
#define TAPE_H

#include <vector>
#include <string>
#include <iostream>

class Tape {
 public:
  // --- Constructores ---
  Tape(int size_x = 0, int size_y = 0);
  Tape(const std::string& filename);   // inicialización leyendo fichero

  // --- Consultas ---
  int GetSizeX() const;
  int GetSizeY() const;

  bool InBounds(int x, int y) const;   // útil para evitar salir
  bool GetCell(int x, int y) const;    // color: 0 blanca, 1 negra

  // --- Modificación ---
  void SetCell(int x, int y, bool value);
  void FlipCell(int x, int y);         // cambia blanco<->negro

  // --- I/O ---
  void LoadFromFile(const std::string& filename);
  void SaveToFile(const std::string& filename,
                  int ant_x, int ant_y, int ant_dir) const;

  // --- Visualización ---
  friend std::ostream& operator<<(std::ostream& os, const Tape& tape);

 private:
  int size_x_;
  int size_y_;

  // Representación interna: matriz de bool/char
  // (te conviene char para imprimir más fácil y ahorrar líos)
  std::vector<std::vector<bool>> cells_;

  // Helpers privados
  void InitWhite();
};

#endif

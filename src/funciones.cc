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

  * Archivo funciones.cc: Implementacion de funciones utiles.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  */


#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "funciones.h"



/**
 * @brief show menu
 */
void menu (int &option) {
  std::cout << "1. Cargar nuevo mundo" << std::endl;     
  std::cout << "2. Mostrar recorrido de la hormiga" << std::endl;
  std::cout << "3. Guardar estado actual del mundo" << std::endl;
  std::cout << "4. Salir del programa" << std::endl;
  std::cout << "Introduce un numero > ";
  std::cin >> option;
};



/**
 * @brief Check that the opcode is correct
 */
bool CheckOption(const int &option) {
  std::vector<int> opciones = {1, 2, 3, 4};
  for (const int& num : opciones) {
    if (option == num) {
      return true;
    }
  }
  std::cerr << "Error: A usado una opcion incorrecta" << std::endl;
  return false;
}



/**
 * @brief function that waits for the user to press any key
 */
void pressanykey() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  std::cin.get(); 
}



/**
 * @brief function that waits for the user to press enter
 */
void pressEnter() {
  std::string dummy;
  std::getline(std::cin, dummy);  // espera hasta que el usuario pulse ENTER
}



/**
 * @brief function to clear the standard ouput
 */
void clrscr() {
  system("clear");
}


#include "Tiempo.hpp"

std::chrono::time_point<std::chrono::steady_clock> Tiempo::tiempoInicial = std::chrono::steady_clock::now();

double Tiempo::getTiempo(){
  auto tiempoFinal = std::chrono::steady_clock::now();
  std::chrono::duration<double> tiempo = tiempoFinal - tiempoInicial;
  
  return tiempo.count();
};
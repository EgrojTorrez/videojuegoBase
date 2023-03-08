#pragma once
#include <chrono>

class Tiempo
{
  public:
    static std::chrono::time_point<std::chrono::steady_clock> tiempoInicial;
    static double getTiempo();
};
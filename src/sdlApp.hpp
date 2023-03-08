#pragma once

#include <SDL.h>
#include <vector>
#include <string>

class SDLApp{
  private: 
    SDLApp();
    bool onInit();
    void onEvento(SDL_Event *evento);
    void onFisicaUpdate(double dt);
    void onFrameUpdate(double dt);
    void onLimpiar();
    void renderTexto(SDL_Renderer* ren, int x, int y, std::string texto, int fontsize, SDL_Color color, std::string font="SunnySpells");
    bool esta_corriendo;
    int WIDTH;
    int HEIGHT;

    SDL_Window* vnt;
    SDL_Surface* vntsurf;
    SDL_Renderer* render;
  
  public:
    SDL_Color bgColor;
    static int onCorrer();
    static void setBgColor(Uint8 rojo, Uint8 verde, Uint8 azul);
    static SDLApp& get();
    static bool estaCorriendo() {return get().esta_corriendo;};
};

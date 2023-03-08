#pragma once
#include <SDL.h>

class MouseOyente
{
  private:
    MouseOyente();
    int scrollX;
    int scrollY;
    int xPos;
    int yPos;
    int lastX;
    int lastY;
    bool mouseBoton[3];
    bool estaArrastrando;
    bool estaMoviendo;
  public:
    static MouseOyente& get();
    static void eventoMovimiento(SDL_Event *e);
    static void eventoPresionado(SDL_Event *e);
    static void eventoScroll(SDL_Event *e);

    static int getX(){return get().xPos;};
    static int getY(){return get().yPos;};
    static int getDX(){return get().lastX - get().xPos;};
    static int getDY(){return get().lastY - get().yPos;};
    static int getScrollX(){return get().scrollX;};
    static int getScrollY(){return get().scrollY;};
    static bool esArrastrado(){return get().estaArrastrando;};
    static bool seMueve(){return get().estaMoviendo;};
};

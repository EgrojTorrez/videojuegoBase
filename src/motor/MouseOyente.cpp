#include "MouseOyente.hpp"

MouseOyente::MouseOyente()
{
  scrollX = 0;
  scrollY = 0;
  xPos = 0;
  yPos = 0;
  lastX = 0;
  lastY = 0;
  for(auto i=0; i<3;++i)
    mouseBoton[i] = false;
};

MouseOyente& MouseOyente::get()
{
  static MouseOyente instancia;
  return instancia;
};

void MouseOyente::eventoMovimiento(SDL_Event *e)
{
  if (e->type == SDL_MOUSEMOTION)
  {
    get().lastX = get().xPos;
    get().lastY = get().yPos;
    get().xPos = e->motion.x;
    get().yPos = e->motion.y;
    get().estaMoviendo = true;
    get().estaArrastrando = get().mouseBoton[0] | get().mouseBoton[1] | get().mouseBoton[2];
  }
  else 
  {
    get().estaMoviendo = false;
  }
};

void MouseOyente::eventoPresionado(SDL_Event *e)
{
  if (e->type == SDL_MOUSEBUTTONDOWN)
  {
    switch (e->button.button)
    {
      case SDL_BUTTON_LEFT:
        get().mouseBoton[SDL_BUTTON_LEFT-1] = true;
        break;
      case SDL_BUTTON_RIGHT:
        get().mouseBoton[SDL_BUTTON_RIGHT-1] = true;
        break;
      default:
        get().mouseBoton[SDL_BUTTON_MIDDLE-1] = true;
        break;
    }
  }
  if(e->type == SDL_MOUSEBUTTONUP)
  {
    switch (e->button.button)
    {
      case SDL_BUTTON_LEFT:
        get().mouseBoton[SDL_BUTTON_LEFT-1] = false;
        break;
      case SDL_BUTTON_RIGHT:
        get().mouseBoton[SDL_BUTTON_RIGHT-1] = false;
        break;
      default:
        get().mouseBoton[SDL_BUTTON_MIDDLE-1] = false;
        break;
    }
    get().estaArrastrando = false;
  }
};

void MouseOyente::eventoScroll(SDL_Event *e)
{
  if (e->type == SDL_MOUSEWHEEL)
  {
    get().scrollX = e->wheel.x;
    get().scrollY = e->wheel.y;
  }
};

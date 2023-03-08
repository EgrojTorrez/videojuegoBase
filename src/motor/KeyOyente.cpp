#include "KeyOyente.hpp"

KeyOyente::KeyOyente()
{
  for(auto i=0; i<350;++i)
    keys[i] = false;
};

KeyOyente& KeyOyente::get()
{
  static KeyOyente instancia;
  return instancia;
};	

void KeyOyente::keyPresionado(SDL_Event *e)
{
  if(e->type == SDL_KEYDOWN)
    get().keys[e->key.keysym.sym] = true;
  else if(e->type == SDL_KEYUP)
    get().keys[e->key.keysym.sym] = false;
};



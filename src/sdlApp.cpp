#include "sdlApp.hpp"
#include "utilidad/Tiempo.hpp"
#include "motor/KeyOyente.hpp"
#include "motor/MouseOyente.hpp"
#include <SDL_ttf.h>

SDLApp::SDLApp()
{
  vnt = nullptr;
  vntsurf = nullptr;
  render = nullptr;
  bgColor.r = 255;
  bgColor.g = 255;
  bgColor.b = 255;
  bgColor.a = 255;

  esta_corriendo = true;
  WIDTH = 1024;
  HEIGHT = 720;
};


bool SDLApp::onInit()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    return false;
  }
  get().vnt = SDL_CreateWindow("Juego", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, get().WIDTH, get().HEIGHT, SDL_WINDOW_OPENGL);
  TTF_Init();
  if (get().vnt == nullptr)
  {
    printf("No se pudo crear la ventana: %s\n", SDL_GetError());
    return false;
  }
  SDL_SetHint(SDL_HINT_RENDER_BATCHING, "opengl");
  get().render = SDL_CreateRenderer(get().vnt, -1, SDL_RENDERER_ACCELERATED);
  if (get().render == NULL)
  {
    printf("No se pudo crear el render por: %s\n", SDL_GetError());
    return false;
  }
  SDL_SetRenderDrawColor(get().render, get().bgColor.r, get().bgColor.g, get().bgColor.b, SDL_ALPHA_TRANSPARENT);

  return true;
};

void SDLApp::onEvento(SDL_Event *evento){
  if (evento->type == SDL_QUIT)
  {
    get().esta_corriendo = false;
  }
  MouseOyente::get().eventoMovimiento(evento);
  MouseOyente::get().eventoPresionado(evento);
  MouseOyente::get().eventoScroll(evento);

  KeyOyente::get().keyPresionado(evento);
};

void SDLApp::onFisicaUpdate(double dt){
  printf("Esta presionando W %d\n", KeyOyente::get().estaPresionado(SDLK_w));
};
void SDLApp::onFrameUpdate(double dt){
  SDL_RenderClear(get().render);

  int mx = MouseOyente::get().getX();
  int my = MouseOyente::get().getY();
  std::string pm = "mouse(" + std::to_string(mx) + "," + std::to_string(my) + ")";
  renderTexto(get().render, 815, 630, pm, 20, SDL_Color{0,0,0}, "onuava");

  renderTexto(get().render, (get().WIDTH/2)-100, (get().HEIGHT/2)-100, "SI FUNCIONA", 50, SDL_Color{0,0,255});
  // fps
  renderTexto(get().render, get().WIDTH-100, 30, std::to_string((int)(1/dt))+ "fps", 18, SDL_Color{0,135,62}, "onuava");

  SDL_RenderPresent(get().render);
  SDL_SetRenderDrawColor(get().render, get().bgColor.r, get().bgColor.g, get().bgColor.b, SDL_ALPHA_TRANSPARENT);
};
void SDLApp::onLimpiar(){
  SDL_DestroyRenderer(get().render);
  SDL_FreeSurface(get().vntsurf);
  SDL_DestroyWindow(get().vnt);
  SDL_Quit();
};

SDLApp &SDLApp::get()
{
  static SDLApp instancia;
  return instancia;
};

int SDLApp::onCorrer()
{
  double inicio = Tiempo::getTiempo();

  if (get().onInit() == false)
  {
    return -1;
  }
  SDL_Event eventos;
  double dt = 0;
  while (get().estaCorriendo())
  {
    while (SDL_PollEvent(&eventos))
    {
      get().onEvento(&eventos);
    };

    if (dt >= 0)
    {
      get().onFisicaUpdate(dt);
      get().onFrameUpdate(dt);
    };
    double fin = Tiempo::getTiempo();
    dt = fin - inicio;
    inicio = fin;
  };
  
  get().onLimpiar();

  return 0;
};

void SDLApp::renderTexto(SDL_Renderer* ren, int x, int y, std::string texto, int fontsize, SDL_Color color, std::string font)
{
  std::string ff = "assets\\fonts\\" + font + ".ttf";
  TTF_Font* fontTipo = TTF_OpenFont(ff.c_str(), fontsize);

  if(fontTipo == NULL){
    printf("No se encontro la fuente: %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Surface* surftexto = TTF_RenderText_Solid(fontTipo, texto.c_str(), color);
  SDL_Texture *textexto = SDL_CreateTextureFromSurface(ren, surftexto);
  SDL_Rect rectexto;
  rectexto.x = x;
  rectexto.y = y;
  rectexto.w = surftexto->w;
  rectexto.h = surftexto->h;

  SDL_RenderCopy(ren, textexto, NULL, &rectexto);

  TTF_CloseFont(fontTipo);
  SDL_DestroyTexture(textexto);
  SDL_FreeSurface(surftexto);
};

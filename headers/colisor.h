#include "SDL2/SDL.h"

bool colisor_verificator(SDL_Rect r1, SDL_Rect r2, int velocidadex, int velocidadey) {
  r1.x += velocidadex;
  r1.y += velocidadey;
  if( r1.x + r1.w > r2.x && r2.x + r2.w > r1.x &&
    r1.y + r1.h > r2.y && r2.y + r2.h > r1.y) {
    return true;
  }
  return false;
}
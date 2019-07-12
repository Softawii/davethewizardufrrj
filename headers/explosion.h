#include "SDL2/SDL.h"
typedef struct {
    float x;
    float y;
    int range;
    SDL_Rect rR;
    SDL_Rect sR;
}MEGUMIN;

void explosionMobs (float * x, float * y, SDL_Rect * rR, MEGUMIN * exp, SDL_Rect * rRcam) {
    exp->x = *x; exp->y = *y;
    exp->range = rR->w;

    exp->rR.x = exp->x - rRcam->x;
    exp->rR.y = exp->y - rRcam->y;
    exp->rR.w = exp->range; exp->rR.h = exp->range;
}
// morrer // // 
void animarexplosaodeMob(int * morrer, MEGUMIN * explodir, SDL_Rect rRcam) {
    const int aumento = 3;
    if(*morrer >= aumento * 0 && *morrer <= aumento * 1) {
        explodir->rR.x = explodir->x - rRcam.x;
        explodir->rR.y = explodir->y - rRcam.y;
        explodir->sR.x = 0; explodir->sR.x = 0; 
        explodir->sR.w = 32; explodir->sR.h = 32;
        *morrer = *morrer + 1;
    }
    else if(*morrer > aumento * 1 && *morrer <= aumento * 2) {
        explodir->rR.x = explodir->x - rRcam.x;
        explodir->rR.y = explodir->y - rRcam.y;
        explodir->sR.x = 32;
        *morrer = *morrer + 1;
    }
    else if(*morrer > aumento * 2 && *morrer <= aumento * 3) {
        explodir->rR.x = explodir->x - rRcam.x;
        explodir->rR.y = explodir->y - rRcam.y;
        explodir->sR.x = 64;
        *morrer = *morrer + 1;
    }
    else if(*morrer > aumento * 3 && *morrer <= aumento * 4) {
        explodir->rR.x = explodir->x - rRcam.x;
        explodir->rR.y = explodir->y - rRcam.y;
        explodir->sR.x = 96;
        *morrer = *morrer + 1;
    }
    else if(*morrer > aumento * 4 && *morrer <= aumento * 5) {
        explodir->rR.x = explodir->x - rRcam.x;
        explodir->rR.y = explodir->y - rRcam.y;
        explodir->sR.x = 128;
        *morrer = *morrer + 1;
    }
    else if(*morrer > aumento * 5 && *morrer <= aumento * 6) {
        explodir->rR.x = explodir->x - rRcam.x;
        explodir->rR.y = explodir->y - rRcam.y;
        explodir->sR.x = 160;
        *morrer = *morrer + 1;
    }
    //printf("--%i && %i\n", explodir->sR.x, *morrer);
}
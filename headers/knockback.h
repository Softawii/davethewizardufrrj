#include "SDL2/SDL.h"

typedef struct {
    int mobNUMEROtemp;
    int mobNUMERO;
    char mobTYPE;
    bool emKBACK;
}KBACK;

void takeKnockback (KBACK * kb,  SDL_Rect PlayerRect, SDL_Rect MeatRect, float * gX, float * gY, float velocidade, SDL_Rect rRw[], int numWall) {
    static int j = 0;
    bool colidir = false;
    if(j <= 30 && kb->emKBACK) {
        // X //
        if(PlayerRect.x - (MeatRect.x + MeatRect.w/2) < 0) {
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(PlayerRect, rRw[i],  -1 * velocidade, 0);
            }
            if(!colidir){
                *gX -= velocidade;
            }
        }
        else if(PlayerRect.x - (MeatRect.x + MeatRect.w/2) > 0) {
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(PlayerRect, rRw[i], velocidade, 0);
            }
            if(!colidir){
                *gX +=  velocidade;
            }
        }
        // Y //
        if(PlayerRect.y - (MeatRect.y + MeatRect.h/2) < 0) {
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(PlayerRect, rRw[i], velocidade, 0);
            }
            if(!colidir){
                *gY -= velocidade;
            }
        }
        else if(PlayerRect.y - (MeatRect.y + MeatRect.h/2) > 0) {
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(PlayerRect, rRw[i],  velocidade, 0);
            }
            if(!colidir){
                *gY += velocidade;
            }
        }
        j++;
    }
    else if(j > 30 && kb->emKBACK) {
        j = 0;
        kb->emKBACK = false;
    }
}

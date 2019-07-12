#include "SDL2/SDL.h"
#include <stdbool.h>

typedef struct {
    int contadorrgb;
    int contadoranime;
    bool ativo;

    int x;
    int y;

    SDL_Rect rR;
    SDL_Rect sR;
} CRISTAL;

void cristalAnimated (CRISTAL * cristal, SDL_Texture * cristalTex, SDL_Rect rRcam) {


    // animando movimento //


    if(cristal->ativo) 
    {
        cristal->sR.w = 10; cristal->sR.h = 31;
        if(cristal->contadoranime >= 0 && cristal->contadoranime < 24) {
            cristal->sR.x = 0; cristal->sR.y = 0;
        }
        else if(cristal->contadoranime >= 24 && cristal->contadoranime < 48) {
            cristal->sR.x = 16; cristal->sR.y = 0;
        }
        else if(cristal->contadoranime >= 48 && cristal->contadoranime < 72) {
            cristal->sR.x = 32; cristal->sR.y = 0;
        }
        else if(cristal->contadoranime >= 72 && cristal->contadoranime < 96) {
            cristal->sR.x = 16; cristal->sR.y = 0;
        }
        else {
            cristal->contadoranime = 0;
        }
        cristal->contadoranime++;
    }
    if(!cristal->ativo) {
        cristal->sR.x = 43; cristal->sR.y = 0;
        cristal->sR.w = 15; cristal->sR.h = 31;
       SDL_SetTextureColorMod(cristalTex, 50, 50, 50);
    }


    // animar rgb //


    if(cristal->ativo) 
    {
        if(cristal->contadorrgb >= 0 && cristal->contadorrgb < 8) {
            SDL_SetTextureColorMod( cristalTex, 0xe1, 0x39, 0x39 );
        }
        else if(cristal->contadorrgb >= 8 && cristal->contadorrgb < 16) {
            SDL_SetTextureColorMod( cristalTex, 0xe1, 0x39, 0x87 );
        }
        else if(cristal->contadorrgb >= 16 && cristal->contadorrgb < 24) {
            SDL_SetTextureColorMod( cristalTex, 0x7d, 0x39, 0xe1 );
        }
        else if(cristal->contadorrgb >= 24 && cristal->contadorrgb < 32) {
            SDL_SetTextureColorMod( cristalTex, 0x47, 0x39, 0xe1 );
        }
        else if(cristal->contadorrgb >= 32 && cristal->contadorrgb < 40) {
            SDL_SetTextureColorMod( cristalTex, 0x39, 0x72, 0xe1 );
        }
        else if(cristal->contadorrgb >= 40 && cristal->contadorrgb <= 48) {
            SDL_SetTextureColorMod( cristalTex, 0x39, 0xb2, 0xe1 );
        }
        cristal->contadorrgb++;
        if(cristal->contadorrgb > 48) {
            cristal->contadorrgb = 0;
        }
    }
       
            
    cristal->rR.x = cristal->x - rRcam.x;
    cristal->rR.y = cristal->y - rRcam.y;
    cristal->rR.w = cristal->sR.w * 2;
    cristal->rR.h = cristal->sR.h * 2;
}
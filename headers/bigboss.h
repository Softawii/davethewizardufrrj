
#include <time.h>
#include <stdio.h> // FUNCOES BASICAS // se necessario
#include <stdlib.h>
#include <stdbool.h> // BOOLEANAS //
#include <math.h> // matematica top /
#include <time.h>
#include "SDL2/SDL.h" //SDL LIBRARY //
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"


typedef struct {
    // VIDA DO MOB //
    int life;
    int lifemaxima;
    // POS TELA //
    float x;
    float y;
    // VELOCIDADE E MECANICA BASE//
    float velocidade;
    int distancia;
    float seguir;
    bool dir;
    // POS KB //
    int espera;
    int i;
    int contador;
    int maximo;
    int kbdelay;
    // DELAY ENTRE TIROS //
    int delay;
    int j;
    // ANIMACAO DE MORTE //
    int morrer;
    int k;
    // ANIMACAO DE MOVIMENTO //
    int contadoranime;
    // RECTS DO BOSS //
    SDL_Rect rR;
    SDL_Rect sR;

    // PROJETIL //
    float xx;
    float yy;
    float velmx[8];
    float velmy[8];
    float velpx[8];
    float velpy[8];
    float posx[8];
    float posy[8];
    // RECTS DOS PROJETEIS //
    SDL_Rect rRp[8];  

    // CHAT //
    bool chat1;
    bool chat2;
}BIGBOSS;


void MAGIC_BIGBOSS (SDL_Rect ArmaRect, SDL_Rect MageRect, BIGBOSS * bigboss, int * coins,int* pontos, int *danoeffect, int *key) {
    bool colidir = false;
    if(bigboss->life >= 0) {
        colidir = colisor_verificator(ArmaRect, MageRect, 0, 0);
         if(colidir && bigboss->kbdelay == 0) {
            bigboss->life = bigboss->life - (1 * *danoeffect);
            bigboss->kbdelay = 1;
            printf("[Console]O BIGBOSS agora tem %i de vida.\n", bigboss->life);
            if(bigboss->life < 0) {
                *coins += 15;
                *pontos+= 127 * 27;
                *key += 1;
            }
        }
        if(bigboss->kbdelay <= 30 && bigboss->kbdelay > 0) {
            //printf("-%i\n", mage->delay);
            bigboss->kbdelay++;
        }
        else if(bigboss->kbdelay > 30) {
            bigboss->kbdelay = 0;
        }
    }
    return;
}


void BIGBOSS_PLAYER (SDL_Rect MeatRect, SDL_Rect PlayerRect, int * MeatStatus, int * life, int * invencible, KBACK * kb, int * MeatLife, SDL_Rect Projeteis[]) {
    bool colidir = false;
    if(*MeatStatus == 1 && *MeatLife >= 0) {
        colidir = colisor_verificator(MeatRect, PlayerRect, 0, 0);
        if(colidir) {
            kb->emKBACK = true;
            kb->mobNUMERO = kb->mobNUMEROtemp;
            kb->mobTYPE = 'B';

            *MeatStatus = -1;
            *life = *life - 2;
            *invencible = 1;
        }
        for(int i = 0; i < 8 && !colidir; i++) 
        {
            colidir = colisor_verificator(PlayerRect, Projeteis[i], 0, 0);
            if(colidir) {
                *MeatStatus = -1;
                *life = *life - 1;
                *invencible = 1;
            }
        }

    }
}

void bigBossEngine (BIGBOSS * bigboss, SDL_Rect * rR, SDL_Rect rRw[], int numWall, int * life, int * invencible, KBACK * kb, SDL_Rect rRcam)
{
    static bool colidir = false;
    // COLIDIR COM O PLAYER //
    BIGBOSS_PLAYER(bigboss->rR, *rR, &bigboss->espera, life, invencible, kb, &bigboss->life, bigboss->rRp);
    // SEGUIR O PLAYER //
    
    if(sqrt(pow(rR->x + rR->w - bigboss->rR.x,2) + pow(rR->y + rR->h - bigboss->rR.y,2)) <= bigboss->distancia * bigboss->seguir && bigboss->life >= 0 && bigboss->chat1){
        bigboss->seguir = 8;
        if(rR->x - (bigboss->rR.x + bigboss->rR.w/2) <= 0) {
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(bigboss->rR, rRw[i], -bigboss->velocidade , 0);
            }
            if(!colidir){
                bigboss->x -= bigboss->velocidade ;
            }
        }
        else if(rR->x - (bigboss->rR.x + bigboss->rR.w/2) > 0) {
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(bigboss->rR, rRw[i], bigboss->velocidade , 0);
            }
            if(!colidir){
                bigboss->x += bigboss->velocidade ;
            }
        }
        //olhando para y//
        if(rR->y - (bigboss->rR.y) <= 0 ){
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(bigboss->rR, rRw[i], 0, -bigboss->velocidade );
            }
            if(!colidir){
                bigboss->y -= bigboss->velocidade ;
            }
        }
        else if(rR->y - (bigboss->rR.y) > 0){
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(bigboss->rR, rRw[i], 0, bigboss->velocidade);
            }
            if(!colidir){
                bigboss->y += bigboss->velocidade;
            }
        }
    }
    if(bigboss->espera == -1) {
        bigboss->contador++;
        if(bigboss->contador > bigboss->maximo) {
            bigboss->contador = 0;
            bigboss->espera = 1;
        }
    }
    if(rR->x + rR->w < bigboss->rR.x) {
        bigboss->dir = false;
    }
    else {
        bigboss->dir = true;
    }



    /*

    int xx[8];
    int yy[8];
    float velmx[8];
    float velmy[8];
    float velpx[8];
    float velpy[8];

     */




    if(bigboss->life <= bigboss->lifemaxima/2)
    {
        //printf("[Console] O BOSS TA PISTOL!!\n");
        bigboss->velocidade = 0.6;
        // MARCANDO POS INICIAL //
        if(bigboss->j == 0)
        {
            for(int i = 0; i < 8; i++)
            {
              bigboss->velmx[i] = 0;
              bigboss->velmy[i] = 0;
            }
            bigboss->xx = bigboss->x;
            bigboss->yy = bigboss->y;

        }  
        //  DELAY ENTRE TIROS //
        if(bigboss->j < bigboss->delay)
        {
            bigboss->j++;
        }
        else
        {
            bigboss->j = 0;
        }
        // MECANICAS //
        if(bigboss->j > 0) 
        {
            for(int i = 0; i < 8; i++) 
            {
                colidir = false;
                for(int j = 0; j < numWall && !colidir; j++) {
                    colidir = colisor_verificator(bigboss->rRp[i], rRw[i], 0, 0);
                }
                if(colidir) {
                    printf("oi\n");
                    // pos em x //
                    bigboss->posx[i] = -10000;
                    bigboss->velmx[i] = 0;

                    // pos em y //
                    bigboss->posy[i] = -10000;
                    bigboss->velmy[i] = 0;

                }
                
                // MOVIMENTANDO EM X //
                bigboss->velmx[i] += bigboss->velpx[i];
                bigboss->posx[i] = bigboss->xx + bigboss->velmx[i];

                // MOVIMENTANDO EM Y //
                bigboss->velmy[i] += bigboss->velpy[i];
                bigboss->posy[i] = bigboss->yy + bigboss->velmy[i];

                // RECT EM FUNCAO DA CAMERA //
                bigboss->rRp[i].x = bigboss->posx[i] - rRcam.x;
                bigboss->rRp[i].y = bigboss->posy[i] - rRcam.y;
                bigboss->rRp[i].w = 28;
                bigboss->rRp[i].h = 28;
            }
        }
    }
    return;
}


void bigBossAnimated(BIGBOSS * bigboss, SDL_Rect * rRcam) {
    // loop de jogar na tela //
    bigboss->rR.x = bigboss->x - rRcam->x;
    bigboss->rR.y = bigboss->y - rRcam->y;

    if(bigboss->contadoranime >= 56) {
        bigboss->contadoranime = 0;
    }
    else if(bigboss->contadoranime >= 0 && bigboss->contadoranime < 7) {
        bigboss->sR.x = 2; bigboss->sR.y = 54; bigboss->sR.w = 14; bigboss->sR.h = 18;
    }
    else if(bigboss->contadoranime >= 7 && bigboss->contadoranime < 14) {
        bigboss->sR.x = 17; bigboss->sR.y = 53; bigboss->sR.w = 14; bigboss->sR.h = 18;
    }
    else if(bigboss->contadoranime >= 14 && bigboss->contadoranime < 21) {
        bigboss->sR.x = 33; bigboss->sR.y = 55; bigboss->sR.w = 14; bigboss->sR.h = 18;
    }
    else if(bigboss->contadoranime >= 21 && bigboss->contadoranime < 28) {
        bigboss->sR.x = 50; bigboss->sR.y = 56; bigboss->sR.w = 14; bigboss->sR.h = 18;
    }
    if(bigboss->contadoranime > 28) {
        bigboss->contadoranime = 0;
    }
    bigboss->contadoranime++;
    bigboss->rR.w = bigboss->sR.w * 5; bigboss->rR.h = bigboss->sR.h * 5;

}
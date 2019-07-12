#include "SDL2/SDL.h"
#include <stdbool.h>


typedef struct {
  int life; // a vida //
  float velocidade; // quantos pixels anda por frame //
  int distancia; // o quanto ele ve antes de te seguir //
  float x; // posicoes ficticeas em x//
  float y; // posicao ficticea em y //
  bool agressivo; // vai meter a porrada ? //
  int espera; // se ele bateu e tem que esperar pra bater dnovo //
  int i; // aquela auxiliar que eu amo <3 //
  bool dir; // direita? //
  int damage; // dano que ele da //
  int contador; // serve pra animar //
  int maximo; // maximo de espera //
  int delay; // delayzin basico //
  int morrer; // animacao de morte //
  float seguir;
  
  SDL_Rect sR;
  SDL_Rect rR;
} MEATBOX;

void MEATBOX_PLAYER (SDL_Rect MeatRect, SDL_Rect PlayerRect, int * MeatStatus, int * life, int * invencible, KBACK * kb, int * MeatLife);



// ESSA FUNCAO ANIMA O MEATBOX //

void meatboxAnimated (MEATBOX * meatbox, SDL_Rect * rRcam) {

    // loop de jogar na tela //
    meatbox->rR.x = meatbox->x - rRcam->x;
    meatbox->rR.y = meatbox->y - rRcam->y;

    if(meatbox->i >= 56) {
        meatbox->i = 0;
    }
    else if(meatbox->i >= 0 && meatbox->i < 7) {
        meatbox->sR.x = 0; meatbox->sR.y = 0; meatbox->sR.w = 23; meatbox->sR.h = 34;
    }
    else if(meatbox->i >= 7 && meatbox->i < 14) {
        meatbox->sR.x = 31; meatbox->sR.y = 0; meatbox->sR.w = 23; meatbox->sR.h = 34;
    }
    else if(meatbox->i >= 14 && meatbox->i < 21) {
        meatbox->sR.x = 64; meatbox->sR.y = 0; meatbox->sR.w = 22; meatbox->sR.h = 34;
    }
    else if(meatbox->i >= 21 && meatbox->i < 28) {
        meatbox->sR.x = 94; meatbox->sR.y = 0; meatbox->sR.w = 26; meatbox->sR.h = 34;
    } 
    else if(meatbox->i >= 28 && meatbox->i < 35) {
        meatbox->sR.x = 126; meatbox->sR.y = 0; meatbox->sR.w = 22; meatbox->sR.h = 34;
    }  
    else if(meatbox->i >= 35 && meatbox->i < 42) {
        meatbox->sR.x = 159; meatbox->sR.y = 0; meatbox->sR.w = 22; meatbox->sR.h = 34;
    }
    else if(meatbox->i >= 42 && meatbox->i < 49) {
        meatbox->sR.x = 191; meatbox->sR.y = 0; meatbox->sR.w = 22; meatbox->sR.h = 34;
    }
    else if(meatbox->i >= 49 && meatbox->i < 56) {
        meatbox->sR.x = 223; meatbox->sR.y = 0; meatbox->sR.w = 23; meatbox->sR.h = 34;
    }
    meatbox->i++;
    meatbox->rR.w = meatbox->sR.w * 1.5; meatbox->rR.h = meatbox->sR.h * 1.5;
}

// ESSA FUNCAO DEFINE O COMPORTAMENTO DO MEATBOX //

void meatboxEngine (MEATBOX * meatbox, SDL_Rect * rR, SDL_Rect rRw[], int numWall, int * life, int * invencible, KBACK * kb) {
    static bool colidir = false;
    // COLIDIR COM O PLAYER //
    MEATBOX_PLAYER(meatbox->rR, *rR, &meatbox->espera, life, invencible, kb, &meatbox->life);
    // SEGUIR O PLAYER //
    if(sqrt(pow(rR->x + rR->w - meatbox->rR.x,2) +pow(rR->y + rR->h - meatbox->rR.y,2)) <= meatbox->distancia * meatbox->seguir && meatbox->life >= 0){
        meatbox->seguir = 1.3;
        if(rR->x - (meatbox->rR.x + meatbox->rR.w/2) <= 0) {
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(meatbox->rR, rRw[i], -2 * meatbox->espera, 0);
            }
            if(!colidir){
                meatbox->x -= meatbox->velocidade * meatbox->espera;
            }
        }
        else if(rR->x - (meatbox->rR.x + meatbox->rR.w/2) > 0) {
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(meatbox->rR, rRw[i], 2 * meatbox->espera, 0);
            }
             if(!colidir){
                meatbox->x += meatbox->velocidade * meatbox->espera;
            }
        }
        //olhando para y//
        if(rR->y - (meatbox->rR.y) <= 0 ){
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(meatbox->rR, rRw[i], 0, -2 * meatbox->espera);
            }
            if(!colidir){
                meatbox->y -= meatbox->velocidade * meatbox->espera;
            }
        }
        else if(rR->y - (meatbox->rR.y) > 0){
            colidir = false;
            for(int i = 0; i < numWall && !colidir; i++) {
                colidir = colisor_verificator(meatbox->rR, rRw[i], 0, 2 * meatbox->espera);
            }
            if(!colidir){
                meatbox->y += meatbox->velocidade * meatbox->espera;
            }
        }
    }
    if(meatbox->espera == -1) {
        meatbox->contador++;
        if(meatbox->contador > meatbox->maximo) {
            meatbox->contador = 0;
            meatbox->espera = 1;
        }
    }
    if(rR->x + rR->w < meatbox->rR.x) {
        meatbox->dir = false;
    }
    else {
        meatbox->dir = true;
    }
  return;
}

// ESSA FUNCAO VERIFICA A COLISAO DO MEATBOX COM O PLAYER //

void MEATBOX_PLAYER (SDL_Rect MeatRect, SDL_Rect PlayerRect, int * MeatStatus, int * life, int * invencible, KBACK * kb, int * MeatLife) {
    bool colidir = false;
    if(*MeatStatus == 1 && *MeatLife >= 0) {
        colidir = colisor_verificator(MeatRect, PlayerRect, 0, 0);
        if(colidir) {
            kb->emKBACK = true;
            kb->mobNUMERO = kb->mobNUMEROtemp;
            kb->mobTYPE = 'M';

            *MeatStatus = -1;
            *life = *life - 2;
            *invencible = 1;
        }
    }
}

// ESSA FUNCAO VERIFICA A COLISAO DO PROJETIL COM O MEATBOX //

void MAGIC_MEATBOX (SDL_Rect ArmaRect, SDL_Rect MeatRect, MEATBOX * meatbox, int * coins,int* pontos, int *danoeffect) {
    bool colidir = false;
    if(meatbox->life >= 0) {
        colidir = colisor_verificator(ArmaRect, MeatRect, 0, 0);
        if(colidir && meatbox->delay == 0) {
            meatbox->life = meatbox->life - (1 * *danoeffect);
            meatbox->delay = 1;
            printf("[Console]O MeatBox agora tem %i de vida.\n", meatbox->life);
            if(meatbox->life < 0) {
                *coins += 10;
                *pontos+= 10 * 20;
            }
        }
        if(meatbox->delay <= 30 && meatbox->delay > 0) {
            //printf("-%i\n", meatbox->delay);
            meatbox->delay++;
        }
        else if(meatbox->delay > 30) {
            meatbox->delay = 0;
        }
    }
    return;
}


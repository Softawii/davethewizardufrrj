#include "SDL2/SDL.h"

typedef struct {
    int life;
    int distancia;
    int delay;
    bool dir;
    bool jogar;
    int i;
    int morrer;
    int damage;
    float x;
    float y;
    int xp; // x do projetil //
    int yp; // y do projetil //
    float velpx; // velocidade do projetil //
    float velpy;
    float velmx; // movimento do projetil //
    float velmy;
    int espera;
    SDL_Rect posRect; // fixar pos do player em x no momento do ataque //
    int j;
    float distx;
    float disty;
    int xx;
    int yy;
    float temp;
    SDL_Rect rR;
    SDL_Rect sR;
    SDL_Rect rRp;
    SDL_Rect sRp;
} MAGE;


void MAGIC_MAGE (SDL_Rect ArmaRect, SDL_Rect MageRect, MAGE * mage, int * coins,int* pontos, int *danoeffect, int *key) {
    bool colidir = false;
    if(mage->life >= 0) {
        colidir = colisor_verificator(ArmaRect, MageRect, 0, 0);
        if(colidir && mage->espera == 0) {
            mage->life = mage->life - (1 * *danoeffect);
            mage->espera = 1;
            printf("[Console]O Mage agora tem %i de vida.\n", mage->life);
            if(mage->life < 0) {
                *coins += 15;
                *pontos+= 15 * 23;
                *key += 1;
            }
        }
        if(mage->espera <= 30 && mage->espera > 0) {
            //printf("-%i\n", mage->delay);
            mage->espera++;
        }
        else if(mage->espera > 30) {
            mage->espera = 0;
        }
    }
    return;
}



void MAGE_PLAYER (SDL_Rect ProjetilRect, SDL_Rect PlayerRect, int * life, int * invencible, int * MageLife) {
    bool colidir = false;
    if(*invencible == 0 && *MageLife >= 0) {
        colidir = colisor_verificator(ProjetilRect, PlayerRect, 0, 0);
        if(colidir) {
            *life = *life - 2;
            *invencible = 1;
        }
    }
}

void mageEngine (MAGE * mage, SDL_Rect * rRcam, SDL_Rect * playerRect, int * life, int * invencible, SDL_Rect rRw[], int numWall) {
    bool colidir = false;
    static float vel = 6;
    /*
    static float mage->distx;
    static float mage->disty;
    static int x;
    static int y;
    static float vel = 5;
    static float temp;
    */


    MAGE_PLAYER (mage->rRp, *playerRect, life, invencible, &mage->life);

    if(sqrt(pow(playerRect->x + playerRect->w - mage->rR.x,2) +pow(playerRect->y + playerRect->h - mage->rR.y,2)) <= mage->distancia && mage->life >= 0) {
        // X //
        if(mage->i == 0) {
            mage->posRect.x = playerRect->x; mage->posRect.w = playerRect->w;
            mage->posRect.y = playerRect->y;mage->posRect.h = playerRect->h;
            mage->distx = mage->rR.x - mage->posRect.x;
            mage->disty = mage->rR.y - mage->posRect.y;
            mage->jogar = true;
            if(mage->distx < 0)
                mage->distx *= -1;
            if(mage->disty < 0)
                mage->disty *= -1;
            mage->velpx = mage->distx / (mage->delay/4);
            mage->velpy = mage->disty / (mage->delay/4);
            // VERIFICANDO OS EIXOS COORDENADOS //
            if(mage->posRect.x < mage->rR.x) { //  esquerda //
                mage->xx = -1;
                //printf("E ");
            }
            else if(mage->posRect.x >= mage->rR.x) { // direita //
                //printf("D ");
                mage->xx = 1;
            }
            if(mage->posRect.y <= mage->rR.y) {// cima //
                //printf("C ");
                mage->yy = -1;
            }
            else if(mage->posRect.y > mage->rR.y) { // baixo //
                //printf("B ");
                mage->yy = 1;
            }
            //printf("\n");

            // jogando na velocidade //
            mage->temp = sqrt(pow(mage->velpx, 2) + pow(mage->velpy, 2));
            mage->temp = vel / mage->temp;
            mage->velpx *= mage->temp;
            mage->velpy *= mage->temp;
        }
    }
    else if(sqrt(pow(playerRect->x + playerRect->w - mage->rR.x,2) +pow(playerRect->y + playerRect->h - mage->rR.y,2)) > mage->distancia) {
        if(mage->i == 0) {
            mage->jogar = false;
            mage->velpx = 0;
            mage->velpy = 0;
        }
    }
    if(mage->xx == 1 && mage->yy == 1 && mage->jogar)  // direita e baixo //
    { 
        // direita //
        mage->velmx += mage->velpx;
        mage->xp = mage->x + mage->velmx;
        //baixo //
        mage->velmy += mage->velpy;
        mage->yp = mage->y + mage->velmy;
    }
    else if(mage->xx == -1 && mage->yy == 1 && mage->jogar)  // esquerda e baixo //
    { 
        // esquerda //
        mage->velmx -= mage->velpx;
        mage->xp = mage->x + mage->velmx;
        //baixo //
        mage->velmy += mage->velpy;
        mage->yp = mage->y + mage->velmy;
    }
    else if(mage->xx == -1 && mage->yy == -1 && mage->jogar)  // esquerda e cima //
    { 
        // esquerda //
        mage->velmx -= mage->velpx;
        mage->xp = mage->x + mage->velmx;
        //cima //
        mage->velmy -= mage->velpy;
        mage->yp = mage->y + mage->velmy;
    }
    else if(mage->xx == 1 && mage->yy == -1 && mage->jogar)  // esquerda e cima //
    { 
        // esquerda //
        mage->velmx += mage->velpx;
        mage->xp = mage->x + mage->velmx;
        //cima //
        mage->velmy -= mage->velpy;
        mage->yp = mage->y + mage->velmy;
    }
    mage->i++;

    for(int i = 0; i < numWall; i++) {
        colidir = colisor_verificator(mage->rRp, rRw[i], 0, 0);
        if(colidir) {
            mage->xp = mage->x;
            mage->velmx = 0;
            mage->yp = mage->y;
            mage->velmy = 0;
            mage->velpx = 0;
            mage->velpy = 0;
        }
    }
 

    if(mage->i >= mage->delay) 
    {
        mage->xp = mage->x;
        mage->velmx = 0;
        mage->yp = mage->y;
        mage->velmy = 0;
        mage->i = 0;
    }


    if(playerRect->x + playerRect->w < mage->rR.x) {
        mage->dir = false;
    }
    else {
        mage->dir = true;
    }

}

void mageAnimated(MAGE * mage, SDL_Rect * rRcam) {
    // loop de jogar na tela //
    mage->rR.x = mage->x - rRcam->x;
    mage->rR.y = mage->y - rRcam->y;

    if(mage->j >= 56) {
        mage->j = 0;
    }
    else if(mage->j >= 0 && mage->j < 7) {
        mage->sR.x = 0; mage->sR.y = 0; mage->sR.w = 13; mage->sR.h = 17;
    }
    else if(mage->j >= 7 && mage->j < 14) {
        mage->sR.x = 17; mage->sR.y = 0; mage->sR.w = 12; mage->sR.h = 17;
    }
    else if(mage->j >= 14 && mage->j < 21) {
        mage->sR.x = 32; mage->sR.y = 0; mage->sR.w = 13; mage->sR.h = 17;
    }
    else if(mage->j >= 21 && mage->j < 28) {
        mage->sR.x = 47; mage->sR.y = 0; mage->sR.w = 14; mage->sR.h = 17;
    }
    if(mage->j > 28) {
        mage->j = 0;
    }
    mage->j++;
    mage->rR.w = mage->sR.w * 1.5; mage->rR.h = mage->sR.h * 1.5;

    mage->rRp.x = mage->xp - rRcam->x; mage->rRp.w = 14;
    mage->rRp.y = mage->yp - rRcam->y; mage->rRp.h = 14;

    mage->sRp.x = 62; mage->sRp.w = 14; 
    mage->sRp.y = 2;  mage->sRp.h = 14;
}
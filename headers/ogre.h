#include "SDL2/SDL.h"

//srand(time(NULL));

typedef struct {
    int life; // vida que o mob tem //
    int velocidade; // o quanto ele anda por frame //
    bool troca; // o randimizador de direcao //
    int direct; // a direcao que ele ta andando agr //
    int damage; // quanto dano ele da //
    float x; // pos ficticea de x //
    float y; // pos ficticea de y //
    int espera; // tempo esperando ate o maximo //
    int maximo;
    int i;
    int delay;
    int loop;
    int danodelay;
    int morrer;
    bool dir;
    SDL_Rect rR; // jogar na tela //
    SDL_Rect sR; // pegar da text // 
}OGRE;

// ESSA FUNCAO ANIMA O MEATBOX //

void ogreAnimated (OGRE * ogre, SDL_Rect * rRcam) {

    // loop de jogar na tela //
    ogre->rR.x = ogre->x - rRcam->x; // trocando o rect em funcao da camera //
    ogre->rR.y = ogre->y - rRcam->y; // trocando o rect em funcao da camera //

    if(ogre->i >= 56) {
        ogre->i = 0;
    }
    else if(ogre->i >= 0 && ogre->i < 7) {
        ogre->sR.x = 32; ogre->sR.y = 0; ogre->sR.w = 20; ogre->sR.h = 28;
    }
    else if(ogre->i >= 7 && ogre->i < 14) {
        ogre->sR.x = 63; ogre->sR.y = 0; ogre->sR.w = 22; ogre->sR.h = 28;
    }
    else if(ogre->i >= 14 && ogre->i < 21) {
        ogre->sR.x = 96; ogre->sR.y = 0; ogre->sR.w = 22; ogre->sR.h = 28;
    }
    else if(ogre->i >= 21 && ogre->i < 28) {
        ogre->sR.x = 128; ogre->sR.y = 0; ogre->sR.w = 20; ogre->sR.h = 28;
    } 
    else if(ogre->i >= 28 && ogre->i < 35) {
        ogre->sR.x = 160; ogre->sR.y = 0; ogre->sR.w = 20; ogre->sR.h = 28;
    }  
    else if(ogre->i >= 35 && ogre->i < 42) {
        ogre->sR.x = 192; ogre->sR.y = 0; ogre->sR.w = 20; ogre->sR.h = 28;
    }
    else if(ogre->i >= 42 && ogre->i < 49) {
        ogre->sR.x = 223; ogre->sR.y = 0; ogre->sR.w = 22; ogre->sR.h = 28;
    }
    else if(ogre->i >= 49 && ogre->i < 56) {
        ogre->sR.x = 0; ogre->sR.y = 0; ogre->sR.w = 20; ogre->sR.h = 28;
    }
    ogre->i++;
    ogre->rR.w = ogre->sR.w * 1.5; ogre->rR.h = ogre->sR.h * 1.5;
}

// OGRO RANDOMIZAR NUMERO //
// uso o randomizador para dizer se o ogro ira trocar de direcao ou nao! //
bool ogreRandomizerNumber () {
    //srand(time(NULL)); // fazendo seed //
    static int randomizer;
    randomizer = (rand() % 100) + 1;

    //printf("%i\n", randomizer);
    if(randomizer < 25 && randomizer >= 0)
        return false;
    else
        return true;
}
void ogreDirect(int * direct) {
    
    //srand(time(NULL)); // fazendo seed //
    static int temp;

    temp = 1 + (rand() % 4);
    while(temp == *direct)
        temp = 1 + (rand() % 4);

    *direct = temp;
    return;
}

// COLISAO DE OGRE COM PLAYER //

void OGRE_PLAYER (SDL_Rect OgreRect, SDL_Rect PlayerRect, int * OgreStatus, int * life, int * invencible, KBACK * kb, int * OgreLife) {
    bool colidir = false;
    if(*OgreStatus == 1 && *OgreLife >= 0) {
        colidir = colisor_verificator(OgreRect, PlayerRect, 0, 0);
        if(colidir) {
            kb->emKBACK = true;
            kb->mobNUMERO = kb->mobNUMEROtemp;
            kb->mobTYPE = 'O';

            *OgreStatus = -1;
            *life = *life - 1;
            *invencible = 1;
        }
    }
}

// ESSA FUNCAO VERIFICA A COLISAO DO PROJETIL COM O MEATBOX //

void MAGIC_OGRE (SDL_Rect ArmaRect, SDL_Rect OgreRect, OGRE * ogre, int * coins, int* pontos, int * danoeffect) {
    bool colidir = false;
    if(ogre->life >= 0) {
        colidir = colisor_verificator(ArmaRect, OgreRect, 0, 0);
        if(colidir && ogre->danodelay == 0) {
            ogre->life = ogre->life - (1 * *danoeffect);
            ogre->danodelay = 1;
            printf("[Console]O ogro agora tem %i de vida.\n", ogre->life);
            if(ogre->life < 0){
                *coins += 5;
                *pontos+= 5 * 15;
            }
        }
        if(ogre->danodelay <= 30 && ogre->danodelay > 0) {
            //printf("-%i\n", meatbox->delay);
            ogre->danodelay++;
        }
        else if(ogre->danodelay > 30) {
            ogre->danodelay = 0;
        }
    }
    return;
}


// ESSA FUNCAO DEFINE O COMPORTAMENTO DO MEATBOX //

void ogreEngine (OGRE * ogre, SDL_Rect * rR, SDL_Rect rRw[], int numWall, int * life, int * invencible, KBACK * kb) {
    //srand(time(NULL));
    //COLIDIR COM PLAYER//
    OGRE_PLAYER(ogre->rR, *rR, &ogre->espera, life, invencible, kb, &ogre->life);
    if(ogre->espera != 1) {
        if(ogre->delay < 30)
            ogre->delay++ ;
        else
        {
            ogre->delay = 1;
            ogre->espera = 1;
        }
        
    }
    // MOVIMENTACAO DOIDA DELE//
    static bool colidir = false;
    ogre->troca = ogreRandomizerNumber();
    if(ogre->troca && ogre->loop == 1) 
    {
        ogreDirect(&ogre->direct);
        ogre->loop++;
    }
    if(ogre->loop > 1 && ogre->loop < 60) 
    {
        ogre->loop++;
    }
    else if(ogre->loop >= 60) 
    {
        ogre->loop = 1;
    }
    colidir = false;
    if(ogre->direct == 1) { // direita //
        for(int i = 0; i < numWall && !colidir; i++) {
            colidir = colisor_verificator(ogre->rR, rRw[i], ogre->velocidade * ogre->espera, 0);
            if(colidir)
                ogreDirect(&ogre->direct);
        }
        if(!colidir) {
            ogre->x += ogre->velocidade * ogre->espera;
        }
        colidir = false;
    }
    else if(ogre->direct == 2) { // esquerda //
        for(int i = 0; i < numWall && !colidir; i++) {
            colidir = colisor_verificator(ogre->rR, rRw[i], -ogre->velocidade * ogre->espera, 0);
            if(colidir)
                ogreDirect(&ogre->direct);
        }
        if(!colidir) {
            ogre->x -= ogre->velocidade * ogre->espera;
        }
        colidir = false;
    }
    else if(ogre->direct == 3) { // cima //
        for(int i = 0; i < numWall && !colidir; i++) {
            colidir = colisor_verificator(ogre->rR, rRw[i], 0, -ogre->velocidade * ogre->espera);
            if(colidir)
                ogreDirect(&ogre->direct);
        }
        if(!colidir) {
            ogre->y -= ogre->velocidade * ogre->espera;
        }
        colidir = false;
    }
    else if(ogre->direct == 4) { // baixo //
        for(int i = 0; i < numWall && !colidir; i++) {
            colidir = colisor_verificator(ogre->rR, rRw[i], 0, ogre->velocidade * ogre->espera);
            if(colidir)
                ogreDirect(&ogre->direct);
        }
        if(!colidir) {
            ogre->y += ogre->velocidade * ogre->espera;
        }
        colidir = false;
    }
    if(rR->x + rR->w < ogre->rR.x) {
        ogre->dir = false;
    }
    else {
        ogre->dir = true;
    }
}
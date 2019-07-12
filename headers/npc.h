#include "SDL2/SDL.h"

// para gatos e cachorros //

typedef struct {
    int contadoranime;
    float velocidade;
    float inicialx;
    float inicialy;
    float x;
    float y;
    int type;
    int sentido;
    int maximo;
    char texto[50];
    int icon;

    SDL_Rect rR;
    SDL_Rect sR;

}ANIMALS;

                /* 
    // BREVE RESUMO SOBRE TYPES && SENTIDOS//
// CADA TYPE REPRESENTA UM TIPO DE ANIMAL DIFERENTE //
    // ESTAO CLASSIFICADOS ABAIXO :) //
sentido:
    1 = cima
    2 = baixo
    3 = esquerda
    4 = direita 

    // TYPES //
    1 = dog
    2 = cat
            */
void animationAnimals(ANIMALS * animals, SDL_Rect rRcam) {
    // definindo a direcao //
    if(animals->sentido == 1 || animals->sentido == 2) 
    {
        animals->sR.w = 30; animals->sR.h = 40;
        // defindo o rect em x // 
        if(animals->contadoranime >= 0 && animals->contadoranime < 8) 
        {
            animals->sR.x = 2;
        }
        else if(animals->contadoranime >= 8 && animals->contadoranime < 16)
        {
            animals->sR.x = 54;
        }
        else if(animals->contadoranime >= 16 && animals->contadoranime < 24) 
        {
            animals->sR.x = 106;
        }
        // definindo o rect em y //
        if(animals->sentido == 2) 
        {
            animals->sR.y = 0;
        }
        else if(animals->sentido == 1)
        {
            animals->sR.y = 216;
        }
        // soma para definir qual sera a animacao //
        if(animals->contadoranime < 24)
        {
            animals->contadoranime++;
        }
        else
        {
            animals->contadoranime = 0;
        }
    }
    else if(animals->sentido == 3 || animals->sentido == 4) 
    {
        animals->sR.w = 32; animals->sR.h = 40; animals->sR.y = 72;
        // defindo o rect em x // 
        if(animals->contadoranime >= 0 && animals->contadoranime < 8) 
        {
            animals->sR.x = 0;
        }
        else if(animals->contadoranime >= 8 && animals->contadoranime < 16)
        {
            animals->sR.x = 52;
        }
        else if(animals->contadoranime >= 16 && animals->contadoranime < 24) 
        {
            animals->sR.x = 104;
        }
        // soma para definir qual sera a animacao //
        if(animals->contadoranime < 24)
        {
            animals->contadoranime++;
        }
        else
        {
            animals->contadoranime = 0;
        }
    }

    animals->rR.x = animals->x - rRcam.x;
    animals->rR.y = animals->y - rRcam.y;
    animals->rR.w = animals->sR.w * 0.7; 
    animals->rR.h = animals->sR.h * 0.7;

}

void AnimalMechanic (ANIMALS * animals) {
    if(animals->sentido == 3 || animals->sentido == 4)
    {
        // trocando o sentido //
        if(animals->x > animals->inicialx + animals->maximo)
            animals->sentido = 3;

        else if(animals->x < animals->inicialx - animals->maximo)
            animals->sentido = 4; 
        
        // mundando o x //
        if(animals->sentido == 4)
            animals->x += animals->velocidade;
        else if(animals->sentido == 3)
            animals->x -= animals->velocidade;
    }
    if(animals->sentido == 1 || animals->sentido == 2)
    {
        // trocando o sentido //
        if(animals->y > animals->inicialy + animals->maximo)
            animals->sentido = 1;

        else if(animals->y < animals->inicialy - animals->maximo)
            animals->sentido = 2; 
        
        // mundando o x //
        if(animals->sentido == 2)
            animals->y += animals->velocidade;
        else if(animals->sentido == 1)
            animals->y -= animals->velocidade;
    }
}

typedef struct {
    int x;
    int y;

    int sentido;
    int type;
    char texto[75];
    char texto2[75];
    int icon;
    bool talk;
    bool talk2;

    SDL_Rect rR;
    SDL_Rect sR;
}NPC;

            /*
        1 = cima
        2 = baixo
        3 = esquerda
        4 = direita 
            */
void NPCmechanic (NPC * npc, SDL_Rect rRcam, SDL_Rect rR) {

    // PADRAO //
    npc->sR.w = 19;
    npc->sR.h = 29;

    // TYPE //
    npc->sR.x = 0; npc->sR.w = 15;
    if(npc->type == 1)
        npc->sR.y = 0;
    else if(npc->type == 2)
        npc->sR.y = 21;
    else if(npc->type == 3) 
        npc->sR.y = 38;
    else if(npc->type == 4) 
        npc->sR.y = 55;

    if(npc->type == 1)
        npc->sR.h = 20;
    else
        npc->sR.h = 16;

    // RECT IN SCREEN //
    npc->rR.x = npc->x - rRcam.x;
    npc->rR.y = npc->y - rRcam.y;
    npc->rR.w = npc->sR.w * 1.7;
    npc->rR.h = npc->sR.h * 1.7;
    
    // SENTIDO //
    if(rR.x + rR.w/2 <= npc->rR.x + rR.w/2)
        npc->sentido = 1;
    else
        npc->sentido = 2;
    
}

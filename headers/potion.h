#include "SDL2/SDL.h"
#include <stdbool.h>

void regenerar(BOOK* book,int * life,bool * regeneffect, bool * regeneffectkeydown, Mix_Chunk * regen, Mix_Chunk * error) {    

    if(book->potion.cura > 0 && *life < 5-1 ){
      *life = *life+2;
      book->potion.cura--;
      printf("[Console] 1 coracao regenerado! Agora voce tem %i pocoes!\n", book->potion.cura);
      *regeneffectkeydown = true;
      Mix_PlayChannel(7, regen, 0);
    }
    else if(book->potion.cura > 0 && *life == 4) {
      *life = 5;
      book->potion.cura--;
      *regeneffect = false;
      printf("[Console] meio coracao regenerado! Agora voce tem %i pocoes!\n", book->potion.cura);
      *regeneffectkeydown = true;
      Mix_PlayChannel(7, regen, 0);
    }
    else if(book->potion.cura <= 0 || *life >= 5) {
      printf("[Console] Voce nao tem pocoes ou sua vida esta cheia!\n");
      *regeneffectkeydown = true;
      *regeneffect = false;
      Mix_PlayChannel(4, error, 0);
    }
}

void velocidadeextra(BOOK * book, float * potionvel, bool * veleffect, bool * veleffectkeydown, int * counter, Mix_Chunk * regen, Mix_Chunk * error) {
    if(book->potion.velocidade > 0 && *counter == 0){
      book->potion.velocidade--;
      *potionvel = 1.5;
      *counter = 1;
      printf("[Console] VELOCIDADE EXTRA ADICIONADA! %i pocoes restantes.\n", book->potion.velocidade);
      *veleffectkeydown = true;
      Mix_PlayChannel(7, regen, 0);
    }
    else if(*counter > 0 && *counter < 300) {
      *counter = *counter + 1;
    }
    else if(*counter >= 300) {
      *counter = 0;
      *potionvel = 1;
      *veleffectkeydown = false;
      *veleffect = false;
      printf("[Console] Fim da Velocidade Extra!\n");
    }
    else if(book->potion.velocidade <= 0) {
      printf("[Console] SEM POCOES!!\n");
      *veleffectkeydown = true;
      *veleffect = false;
      Mix_PlayChannel(4, error, 0);
    }
}

void danoextra(BOOK * book, int * dano, bool * danoeffect, bool * danoeffectkeydown, int * counter, Mix_Chunk * regen, Mix_Chunk * error) {
    if(book->potion.dano > 0 && *counter == 0){
      book->potion.dano--;
      *dano = 2;
      *counter = 1;
      printf("[Console] VELOCIDADE EXTRA ADICIONADA! %i pocoes restantes.\n", book->potion.velocidade);
      *danoeffectkeydown = true;
      Mix_PlayChannel(7, regen, 0);
    }
    else if(*counter > 0 && *counter < 300) {
      *counter = *counter + 1;
    }
    else if(*counter >= 300) {
      *counter = 0;
      *dano = 1;
      *danoeffectkeydown = false;
      *danoeffect = false;
      printf("[Console] Fim da Velocidade Extra!\n");
    }
    else if(book->potion.velocidade <= 0) {
      printf("[Console] SEM POCOES!!\n");
      *danoeffectkeydown = true;
      *danoeffect = false;
      Mix_PlayChannel(4, error, 0);
    }
}
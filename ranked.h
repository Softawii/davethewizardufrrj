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


SDL_Renderer * renderizador;
SDL_Window * Janaleia;

SDL_Rect rGameOver = {230, 30, 100, 500};
SDL_Rect rScore = {200, 180, 100, 500};
SDL_Rect rRmensagem  = {180, 60, 100, 500};
SDL_Rect rRtexto = {320, 90, 50, 200};
TTF_Font* rRfonte;
SDL_Surface* fonteTexto ;
SDL_Color color51 = {255,255,255}; // branco como a neve //
SDL_Color color52 = {71,71,71};
SDL_Color color53 = {120,120,120}; 
SDL_Texture* textoFinal[10];
char textofinalchar[15];

void textoInput (SDL_Renderer * renderizar, SDL_Window * window, int xp);

void fontesend(void){
  static const int FONTSIZE = 24;
  static const int FONTSIZE2 = 28;
  rRfonte = TTF_OpenFont("fontes/fontetop.ttf", FONTSIZE);
  fonteTexto = TTF_RenderText_Solid(rRfonte, textofinalchar, color51);
  textoFinal[0] = SDL_CreateTextureFromSurface(renderizador, fonteTexto);
  SDL_QueryTexture(textoFinal[0], NULL, NULL, &rRtexto.w, &rRtexto.h);
  //SDL_BlitSurface(fontePote, NULL, render, NULL);
  SDL_FreeSurface(fonteTexto);
}
void alterarfonteend(void){
  // huds.rRcura.x = 15; huds.rRcura.y = 42; huds.rRcura.w = 15; huds.rRcura.h = 16.5; //
  // SDL_Rect textRect = {12.5,60, 100, 500}; //
  fonteTexto = TTF_RenderText_Solid(rRfonte, textofinalchar, color51);
  textoFinal[0] = SDL_CreateTextureFromSurface(renderizador, fonteTexto);

  SDL_QueryTexture(textoFinal[0], NULL, NULL, &rRtexto.w, &rRtexto.h);
}

/*

sprintf(numerodepocoes, "PAUSE");
huds.rRcoin.x -= 240;
huds.rRcoin.y += 170;
alterarfonte(book.keys, huds.rRcoin, 3);
huds.rRcoin.x += 240;
huds.rRcoin.y -= 170;
SDL_RenderCopy(render, text[0], NULL, &textRect);

 */
void fileVerificator (SCORE atual) 
{
    SCORE top[5];
    FILE * p_arquivo;
    SCORE aux;

	p_arquivo = fopen("score/score.bin", "r+");
    rewind(p_arquivo);
	fread(&top, sizeof(SCORE), 5, p_arquivo);
    // ordenar pra leitura //
	for(int i = 0; i < 5; i++) {
        for(int j = i + 1; j < 5; j++) {
            if(top[i].pontuacao < top[j].pontuacao) {
                aux = top[i];
                top[i] = top[j];
                top[j] = aux;
            }
        }
    }
    // verificar correspondencia //
    for(int i = 0; i < 5; i++) {
        if(atual.pontuacao > top[i].pontuacao) {
            if(i != 4) {
                top[4] = top[i];
                top[i] = atual;
                break;
            }
            if(i == 4) {
                top[i] = atual;
            }
        }
    }
    // arrumar a ordem //
    for(int i = 0; i < 5; i++) {
        for(int j = i + 1; j < 5; j++) {
            if(top[i].pontuacao < top[j].pontuacao) {
                aux = top[i];
                top[i] = top[j];
                top[j] = aux;
            }
        }
    }
    // print debug //
    //for(int i = 0; i < 5; i++) {
    //   printf("[%i] %s %i\n", i, top[i].NOME, top[i].pontuacao);
    //}
    rewind(p_arquivo);
    fwrite(&top, sizeof(SCORE), 5, p_arquivo);
    fclose(p_arquivo);
}

void textoInput (SDL_Renderer * renderizar, SDL_Window * window, int xp) {
  SCORE atual;
  int i = 0;
  int maximum = 10;
  rRtexto.x = 320;

  for(int i = 0; i < 10; i++) {
      textofinalchar[i] = '\0';
  }

  renderizador = renderizar;
  Janaleia = window;
  SDL_Event event;
  static char inputmensagem[50] = "DIGITE SEU NOME:";
  static char gamemoverchar[50] = "GAME OVER";
  SDL_Rect sinputmsg = {320, 200, 500, 500};
  static char textoteste[10];
  bool inputmoment = true;
  SDL_StartTextInput();
  fontesend();
  bool backspace = false;
  SDL_RenderClear(renderizador);

    // digte seu nome : //
    fonteTexto = TTF_RenderText_Solid(rRfonte, inputmensagem, color51);
    textoFinal[1] = SDL_CreateTextureFromSurface(renderizador, fonteTexto);

    SDL_QueryTexture(textoFinal[1], NULL, NULL, &rRmensagem.w, &rRmensagem.h);

    // game over //
    strcpy(gamemoverchar, "GAME OVER");
    fonteTexto = TTF_RenderText_Solid(rRfonte, gamemoverchar, color51);
    textoFinal[2] = SDL_CreateTextureFromSurface(renderizador, fonteTexto);

    SDL_QueryTexture(textoFinal[2], NULL, NULL, &rGameOver.w, &rGameOver.h);

    // xp //
    sprintf(gamemoverchar, "%.6i PONTOS", xp);
    fonteTexto = TTF_RenderText_Solid(rRfonte, gamemoverchar, color51);
    textoFinal[3] = SDL_CreateTextureFromSurface(renderizador, fonteTexto);

    SDL_QueryTexture(textoFinal[3], NULL, NULL, &rScore.w, &rScore.h);

  while(inputmoment) 
  {
    while(SDL_PollEvent(&event)) 
    {
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && !backspace)
        {
            textofinalchar[i] = '\0';
            i--;
            strcat(textofinalchar, event.text.text); 
            //printf("%s\n", textofinalchar);
            rRtexto.x += 8;
            alterarfonteend();
            backspace = true;
        }
        if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_BACKSPACE)
        {
            backspace = false;
        }



        if(event.type == SDL_QUIT)
        {
          inputmoment = false;
        }
        else if(event.type == SDL_TEXTINPUT && i < maximum) 
        {
            i++;
            strcat(textofinalchar, event.text.text); 
            //printf("%s\n", textofinalchar);
            rRtexto.x -= 10;

            alterarfonteend();
        }
        else if(event.key.keysym.sym == SDLK_RETURN)
        {
            inputmoment = false;
        }
    }
    SDL_RenderClear(renderizador);
    SDL_RenderCopy(renderizador, textoFinal[3], NULL, &rScore);
    SDL_RenderCopy(renderizador, textoFinal[2], NULL, &rGameOver);
    SDL_RenderCopy(renderizador, textoFinal[1], NULL, &rRmensagem);
    SDL_RenderCopy(renderizador, textoFinal[0], NULL, &rRtexto);
    SDL_RenderPresent(renderizador);

    SDL_Delay(1000/60);
  }
  //textofinalchar[i+1] = '\0';
  SDL_RenderClear(renderizador);
  SDL_StopTextInput();

    strcpy(atual.NOME, textofinalchar);
    atual.pontuacao = xp;

    fileVerificator(atual);
}
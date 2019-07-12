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

SDL_Rect rRmensagem  = {12.5,60, 100, 500};
SDL_Rect rRtexto = {12.5, 60, 100, 200};
TTF_Font* rRfonte;
SDL_Surface* fonteTexto ;
SDL_Color color51 = {255,255,255}; // branco como a neve //
SDL_Color color52 = {71,71,71};
SDL_Color color53 = {120,120,120}; 
SDL_Texture* textoFinal[10];
char textofinalchar[50];

void fontesend(void){
  static const int FONTSIZE = 12;
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

  SDL_QueryTexture(textoFinal[0], NULL, NULL, &rRmensagem.w, &rRmensagem.h);
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
void textoInput (SDL_Renderer * renderizar, SDL_Window * window) {

  renderizador = renderizar;
  Janaleia = window;
  SDL_Event event;
  static char inputmensagem[50] = "DIGITE SEU NOME:";
  SDL_Rect sinputmsg = {320, 200, 500, 500};
  static char textoteste[10];
  bool inputmoment = true;
  SDL_StartTextInput();
  fontesend();
  SDL_RenderClear(renderizador);
  while(inputmoment) 
  {
      while(SDL_PollEvent(&event)) 
      {
        if(event.type == SDL_QUIT)
        {
          inputmoment = false;
        }
        else if(event.type == SDL_TEXTINPUT) 
        {
          //system("clear");
          strcat(textofinalchar, event.text.text); 
          printf("%s\n", textofinalchar);

         alterarfonteend();
        }
        else if(event.key.keysym.sym == SDLK_RETURN)
        {
            inputmoment = false;
        }
    SDL_RenderCopy(renderizador, textoFinal[0], NULL, &rRtexto);
    SDL_RenderPresent(renderizador);

    SDL_Delay(1000/60);
  }
  SDL_RenderClear(renderizador);

  SDL_StopTextInput();
}
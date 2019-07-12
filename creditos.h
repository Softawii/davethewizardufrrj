//MINI BOSS SLIME EM DESENVOLVIMENTO! //
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
    int x;
    int y;
} MOUSE3;

// BIBLIOTECAS PROPRIAS //

int *globalx3, *globaly3;
int mapaw3 = 1080, mapah3 = 900;
int ww3=640,hh3=400;

SDL_Surface * fundoSurf3;
SDL_Texture * fundoTex3;

MOUSE3 mouse3;

bool click3;
bool clickfalse3;
bool loop3;


//fonte//
// SDL_Rect riconpotion = {15, 42, 15, 16.5};
SDL_Rect textRect3 = {12.5,60, 100, 500};
TTF_Font* fonte3;
SDL_Surface* fontePronto3;
SDL_Color color31 = {255,255,255}; // branco como a neve //
SDL_Color color32 = {71,71,71};
SDL_Color color33 = {120,120,120}; 
SDL_Texture* text3[10];
char menu3[50] = "JOGAR";

Mix_Music * music3;

SDL_Rect cam3 = {0,0, 640, 400};

SDL_Window* gJanelaReal3= NULL; // CRIANDO JANELA //
SDL_Renderer* renderer3;// Render da Screen //

SDL_Event loopevent3;


bool rescalar3(void){
   if(loopevent3.type ==SDL_WINDOWEVENT)
      if(loopevent3.type ==SDL_WINDOWEVENT_RESIZED)
      {
        ww3=loopevent3.window.data1;
        hh3=loopevent3.window.data2;
    }
}

void fontes3(void){
  static const int FONTSIZE = 24;
  fonte3 = TTF_OpenFont("fontes/fontetop.ttf", FONTSIZE);
  fontePronto3 = TTF_RenderText_Solid(fonte3, menu3, color31);
  text3[0] = SDL_CreateTextureFromSurface(renderer3, fontePronto3);
  SDL_QueryTexture(text3[0], NULL, NULL, &textRect3.w, &textRect3.h);
  SDL_FreeSurface(fontePronto3);
}
void alterarfonte3(SDL_Rect fonteRect, SDL_Color color){
  // huds.rRcura.x = 15; huds.rRcura.y = 42; huds.rRcura.w = 15; huds.rRcura.h = 16.5; //
  // SDL_Rect textRect2 = {12.5,60, 100, 500}; //
  fontePronto3 = TTF_RenderText_Solid(fonte3, menu3, color);
  text3[0] = SDL_CreateTextureFromSurface(renderer3, fontePronto3);

  //textRect2.x = potionRect.x - 2,5;
  //textRect2.y = potionRect.y + 18;

  SDL_QueryTexture(text3[0], NULL, NULL, &textRect3.w, &textRect3.h);
}



void mouse2F3 (MOUSE3 * mouse3) {
  static int width, height;
  static float wf, hf;
  SDL_GetMouseState( &mouse3->x, &mouse3->y); // pegando a pos do mouse2 //
  SDL_GetWindowSize(gJanelaReal3, &width, &height);
  //printf("%i %i ", width, height);
  wf = (float)width / 640;
  hf = (float)height / 400;
  mouse3->x /= wf;
  mouse3->y = (mouse3->y / hf);
  //printf(" // %i %i\n", mouse2->x, mouse2->y);
}


void iniciarfundo3 (void) {
  music3 = Mix_LoadMUS("songs/menu2.mp3");

  fundoSurf3 = IMG_Load("img/overworld.png");
  fundoTex3 = SDL_CreateTextureFromSurface(renderer3, fundoSurf3);
  SDL_QueryTexture(fundoTex3, NULL, NULL, &mapaw3, &mapah3);
  SDL_FreeSurface(fundoSurf3);

}

void renderizarfundo3 (void) {
  static int sentidox = 1;
  static int sentidoy = 1;

  cam3.x = *globalx3 - 320;
  cam3.y = *globaly3 - 200;

  if(cam3.x < 0) {
    sentidox = 1;
    cam3.x = 0;
  }
  if(cam3.y < 0){
    sentidoy = 1;
    cam3.y = 0;
  }
  if(cam3.x + cam3.w >= mapaw3) {
    sentidox = -1;
    cam3.x = mapaw3 - 640;
  }
  if(cam3.y + cam3.h >= mapah3) {
    sentidoy = -1;
    cam3.y = mapah3 - 400;
  }

  *globalx3 += sentidox;
  *globaly3 += sentidoy;

  SDL_RenderClear(renderer3);
  // 4B0082
  SDL_RenderCopy(renderer3, fundoTex3, &cam3, NULL);

  
  SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);


   sprintf(menu3, "CREDITOS:");
   textRect3.x = 20; textRect3.y = 15;
   alterarfonte3(textRect3, color33);
   SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);

   sprintf(menu3, "PROGRAMACAO, DIRECAO  e MUSICA:");
   textRect3.x = 20; textRect3.y = 55;
   alterarfonte3(textRect3, color33);
   SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);
  
   sprintf(menu3, "NICOLAS MAGALHAES SILVA");
   textRect3.x = 20; textRect3.y = 95;
   alterarfonte3(textRect3, color32);
   SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);

   sprintf(menu3, "YAN CARLOS DE FIGUEIREDO MACHADO");
   textRect3.x = 20; textRect3.y = 115;
   alterarfonte3(textRect3, color32);
   SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);
   
   sprintf(menu3, "ARTE:");
   textRect3.x = 20; textRect3.y = 155;
   alterarfonte3(textRect3, color33);
   SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);

   sprintf(menu3, "0x72");
   textRect3.x = 20; textRect3.y = 180;
   alterarfonte3(textRect3, color32);
   SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);
  
   sprintf(menu3, "FINAL BOSS BLUES");
   textRect3.x = 20; textRect3.y = 205;
   alterarfonte3(textRect3, color32);
   SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);

   sprintf(menu3, "e outros..");
   textRect3.x = 20; textRect3.y = 230;
   alterarfonte3(textRect3, color32);
   SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);

   sprintf(menu3, "SFX:");
   textRect3.x = 20; textRect3.y = 270;
   alterarfonte3(textRect3, color33);
   SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);

   sprintf(menu3, "SubspaceAudio");
   textRect3.x = 20; textRect3.y = 295;
   alterarfonte3(textRect3, color32);
   SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);

   



  sprintf(menu3, "VOLTAR");
  textRect3.x = 20; textRect3.y = 340;
   if(mouse3.x >= 20 && mouse3.x < 143 && mouse3.y >= 347 && mouse3.y <= 368) {
    alterarfonte3(textRect3, color31);
    
  }
  else {
    alterarfonte3(textRect3, color32); 
  }
  SDL_RenderCopy(renderer3, text3[0], NULL, &textRect3);





  SDL_RenderPresent(renderer3); 
}
void verificarInteracao3(void) {
  if(mouse3.x >= 20 && mouse3.x < 143 && mouse3.y >= 347 && mouse3.y <= 368) {
    if(click3 && !clickfalse3) {
      clickfalse3 = true;
      printf("[Console]ADEUS :/\n");
      loop3 = false;
    }
  }
}

int creditos(SDL_Renderer * renderer, SDL_Window * Janelona, int * globalXzada, int * globalYzada) {
    
    globalx3 = globalXzada;
    globaly3 = globalYzada;
    loop3 = true;
    renderer3= renderer;
    gJanelaReal3 =Janelona;
   
      iniciarfundo3();
      fontes3();

      Mix_PlayMusic(music3, -1);
      Mix_VolumeMusic(30);

      while(loop3) {

        rescalar3();
        SDL_RenderSetLogicalSize(renderer3, 640, 400);

        while(SDL_PollEvent(&loopevent3)){
        //X to close//
        if(loopevent3.type == SDL_QUIT)
          loop3 = false;
        if(loopevent3.type == SDL_MOUSEBUTTONDOWN && !click3) {
          if(loopevent3.button.button == SDL_BUTTON_LEFT) {
            click3 = true;
          }
        }
        if(loopevent3.type == SDL_MOUSEBUTTONUP) {
          if(loopevent3.button.button == SDL_BUTTON_LEFT) {
            click3 = false;
            clickfalse3 = false;
          }   
        }
      }
      verificarInteracao3();
      mouse2F3(&mouse3);
      renderizarfundo3();


      SDL_Delay(1000/30);
    }
    SDL_DestroyTexture(fundoTex3);
 
  }

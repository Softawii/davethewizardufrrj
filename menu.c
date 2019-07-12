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

#include "pontos.h"
#include "ranked.h"
#include "overworld.h"
#include "creditos.h"


typedef struct {
    int x;
    int y;
} MOUSE;

// BIBLIOTECAS PROPRIAS //

int globalx = 500, globaly = 400;
int mapaw = 1080, mapah = 900;
int ww=640,hh=400;

SDL_Surface * fundoSurf;
SDL_Texture * fundoTex;

SDL_Surface * logoSurf;
SDL_Texture * logoTex;
SDL_Rect sLogo = {62, 148, 1146, 431};
SDL_Rect rLogo = {176.75, 48.70, 286.5, 107.75};

MOUSE mouse2;
bool click;
bool clickfalse;
bool loop;


//fonte//
// SDL_Rect riconpotion = {15, 42, 15, 16.5};
SDL_Rect textRect2 = {12.5,60, 100, 500};
TTF_Font* fonte;
SDL_Surface* fontePronto;
SDL_Color color2 = {255,255,255}; // branco como a neve //
SDL_Color color3 = {71,71,71}; // branco como a neve //
SDL_Texture* text[10];
char menu2[50] = "JOGAR";

Mix_Music * music;

SDL_Rect cam = {0,0, 640, 400};

SDL_Window* gJanelaReal = NULL; // CRIANDO JANELA //
SDL_Renderer* renderer;// Render da Screen //

SDL_Event loopevent;


bool rescalar2(void){
   if(loopevent.type ==SDL_WINDOWEVENT)
      if(loopevent.type ==SDL_WINDOWEVENT_RESIZED)
      {
        ww=loopevent.window.data1;
        hh=loopevent.window.data2;
    }
}

void fontes2(void){
  static const int FONTSIZE = 24;
  fonte = TTF_OpenFont("fontes/fontetop.ttf", FONTSIZE);
  fontePronto = TTF_RenderText_Solid(fonte, menu2, color2);
  text[0] = SDL_CreateTextureFromSurface(renderer, fontePronto);
  SDL_QueryTexture(text[0], NULL, NULL, &textRect2.w, &textRect2.h);
  SDL_FreeSurface(fontePronto);
}
void alterarfonte2(SDL_Rect fonteRect, SDL_Color color){
  // huds.rRcura.x = 15; huds.rRcura.y = 42; huds.rRcura.w = 15; huds.rRcura.h = 16.5; //
  // SDL_Rect textRect2 = {12.5,60, 100, 500}; //
  fontePronto = TTF_RenderText_Solid(fonte, menu2, color);
  text[0] = SDL_CreateTextureFromSurface(renderer, fontePronto);

  //textRect2.x = potionRect.x - 2,5;
  //textRect2.y = potionRect.y + 18;

  SDL_QueryTexture(text[0], NULL, NULL, &textRect2.w, &textRect2.h);
}


bool janela (void) {
  bool success = true;
  // START //
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Ocolor2reu um imprevisto! :(, %s\n", SDL_GetError());
      success = false;
      // A TELA NÃO INICIOU //
  }
  else {
    printf("[Console]SDL iniciado!\n");
    SDL_Delay(100);
    //VARIAVEIS//
    gJanelaReal = SDL_CreateWindow("Dave, The Wizard!", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, ww,hh, SDL_WINDOW_RESIZABLE);
      if(gJanelaReal == NULL) {
          printf("Ocolor2reu um imprevisto! :(, %s\n", SDL_GetError()); 
            success = false;
        }
      else{
          renderer = SDL_CreateRenderer(gJanelaReal, -1, 0);
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
  }
  //FIM//
  return success;
}

void mouse2F (MOUSE * mouse2) {
  static int width, height;
  static float wf, hf;
  SDL_GetMouseState( &mouse2->x, &mouse2->y); // pegando a pos do mouse2 //
  SDL_GetWindowSize(gJanelaReal, &width, &height);
  //printf("%i %i ", width, height);
  wf = (float)width / 640;
  hf = (float)height / 400;
  mouse2->x /= wf;
  mouse2->y = (mouse2->y / hf);
  //printf(" // %i %i\n", mouse2->x, mouse2->y);
}


void iniciarfundo (void) {
  music = Mix_LoadMUS("songs/menu.mp3");

  fundoSurf = IMG_Load("img/overworld.png");
  fundoTex = SDL_CreateTextureFromSurface(renderer, fundoSurf);
  SDL_QueryTexture(fundoTex, NULL, NULL, &mapaw, &mapah);
  SDL_FreeSurface(fundoSurf);

  logoSurf = IMG_Load("img/wizardlogo.png");
  logoTex = SDL_CreateTextureFromSurface(renderer, logoSurf);
  SDL_FreeSurface(logoSurf);
}

void renderizarfundo (void) {
  static int sentidox = 1;
  static int sentidoy = 1;

  cam.x = globalx - 320;
  cam.y = globaly - 200;

  if(cam.x < 0) {
    sentidox = 1;
    cam.x = 0;
  }
  if(cam.y < 0){
    sentidoy = 1;
    cam.y = 0;
  }
  if(cam.x + cam.w >= mapaw) {
    sentidox = -1;
    cam.x = mapaw - 640;
  }
  if(cam.y + cam.h >= mapah) {
    sentidoy = -1;
    cam.y = mapah - 400;
  }

  globalx += sentidox;
  globaly += sentidoy;

  SDL_RenderClear(renderer);
  // 4B0082
  SDL_RenderCopy(renderer, fundoTex, &cam, NULL);

  sprintf(menu2, "JOGAR");
  textRect2.x = 272; textRect2.y = 220;
  if(mouse2.x >= 266 && mouse2.x < 375 && mouse2.y >= 225 && mouse2.y <= 250) {
    alterarfonte2(textRect2, color2);
  }
  else {
    alterarfonte2(textRect2, color3); 
  }
  SDL_RenderCopy(renderer, text[0], NULL, &textRect2);

  sprintf(menu2, "PONTUACAO");
  textRect2.x = 238; textRect2.y = 260;
  if(mouse2.x >= 235 && mouse2.x < 416 && mouse2.y >= 264 && mouse2.y <= 287) {
    alterarfonte2(textRect2, color2);
  }
  else {
    alterarfonte2(textRect2, color3); 
  }
  SDL_RenderCopy(renderer, text[0], NULL, &textRect2);

  sprintf(menu2, "CREDITOS");
  textRect2.x = 245; textRect2.y = 300;
  if(mouse2.x >= 244 && mouse2.x < 401 && mouse2.y >= 306 && mouse2.y <= 327) {
    alterarfonte2(textRect2, color2);
  }
  else {
    alterarfonte2(textRect2, color3); 
  }
  SDL_RenderCopy(renderer, text[0], NULL, &textRect2);

  sprintf(menu2, "SAIR");
  textRect2.x = 284; textRect2.y = 340;
  if(mouse2.x >= 282 && mouse2.x < 365 && mouse2.y >= 347 && mouse2.y <= 368) {
    alterarfonte2(textRect2, color2);
  }
  else {
    alterarfonte2(textRect2, color3); 
  }
  SDL_RenderCopy(renderer, text[0], NULL, &textRect2);

  SDL_RenderCopy(renderer, logoTex, &sLogo, &rLogo);




  SDL_RenderPresent(renderer); 
}
void verificarInteracao(void) {
  if(mouse2.x >= 266 && mouse2.x < 375 && mouse2.y >= 225 && mouse2.y <= 250) {
    if(click && !clickfalse) {
      clickfalse = true;
      Mix_HaltMusic();
      printf("[Console]ENTRANDO NO JOGO\n");
      gameloop(renderer, gJanelaReal);
      loop = true;
      printf("[Console] VOLTANDO AO MENU\n");
      Mix_PlayMusic(music, -1);
      iniciarfundo();
      fontes2();
    }
  }
  else if(mouse2.x >= 235 && mouse2.x < 416 && mouse2.y >= 264 && mouse2.y <= 287) {
    if(click && !clickfalse) {
      clickfalse = true;
      printf("[Console]VENDO A POUNTUACAO\n");
      pontos(renderer, gJanelaReal, &globalx, &globaly);
      loop = true;
      printf("[Console] VOLTANDO AO MENU\n");
      iniciarfundo();
      fontes2();
    }
  }
  else if(mouse2.x >= 244 && mouse2.x < 401 && mouse2.y >= 306 && mouse2.y <= 327) {
    if(click && !clickfalse) {
      clickfalse = true;
      printf("[Console]ENTRANDO NOS CREDITOS\n");
      creditos(renderer, gJanelaReal, &globalx, &globaly);
      loop = true;
      printf("[Console] VOLTANDO AO MENU\n");
      iniciarfundo();
      fontes2();

    }
  }
  else if(mouse2.x >= 282 && mouse2.x < 365 && mouse2.y >= 347 && mouse2.y <= 368) {
    if(click && !clickfalse) {
      clickfalse = true;
      printf("[Console]ADEUS :/\n");
      loop = false;
    }
  }
}

int main (void) {
    
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Volume(1, 50);
    loop = true;
    if(!janela()) {
      printf("FALHA AO ABRIR!\n");
    }
    else {
      
      iniciarfundo();
      fontes2();

      Mix_PlayMusic(music, -1);
      Mix_VolumeMusic(30);

      while(loop) {

        rescalar2();
        SDL_RenderSetLogicalSize(renderer, 640, 400);

        while(SDL_PollEvent(&loopevent)){
        //X to close//
        if(loopevent.type == SDL_QUIT)
          loop = false;
        if(loopevent.type == SDL_MOUSEBUTTONDOWN && !click) {
          if(loopevent.button.button == SDL_BUTTON_LEFT) {
            click = true;
          }
        }
        if(loopevent.type == SDL_MOUSEBUTTONUP) {
          if(loopevent.button.button == SDL_BUTTON_LEFT) {
            click = false;
            clickfalse = false;
          }   
        }
      }
      mouse2F(&mouse2);
      renderizarfundo();
      verificarInteracao();
      SDL_Delay(1000/30);
    }
    SDL_DestroyTexture(fundoTex);
    SDL_DestroyTexture(logoTex);

    Mix_HaltMusic();

    Mix_Quit();
    SDL_Quit();
    TTF_Quit();  
  }
}
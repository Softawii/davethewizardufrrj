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
} MOUSE4 ;

typedef struct {
    char NOME[15];
    int pontuacao;
}SCORE;

SCORE top[5];
// BIBLIOTECAS PROPRIAS //

int *globalx4, *globaly4;
int mapaw4  = 1080, mapah4  = 900;
int ww4 =640,hh4 =400;

SDL_Surface * fundoSurf4 ;
SDL_Texture * fundoTex4 ;

MOUSE4  mouse4 ;

bool click4 ;
bool clickfalse4 ;
bool loop4 ;

//fonte//
// SDL_Rect riconpotion = {15, 42, 15, 16.5};
SDL_Rect textRect4  = {12.5,60, 100, 500};
SDL_Rect textRect5 = {12.5, 60, 100, 200};
TTF_Font* fonte4 ;
SDL_Surface* fontePronto4 ;
SDL_Color color41 = {255,255,255}; // branco como a neve //
SDL_Color color42 = {71,71,71};
SDL_Color color43 = {120,120,120}; 
SDL_Texture* text4[10];
char menu4[50] = "JOGAR";

Mix_Music * music4;

SDL_Rect cam4 = {0,0, 640, 400};

SDL_Window* gJanelaReal4= NULL; // CRIANDO JANELA //
SDL_Renderer* renderer4;// Render da Screen //

SDL_Event loopevent4;


bool rescalar4(void){
   if(loopevent4.type ==SDL_WINDOWEVENT)
      if(loopevent4.type ==SDL_WINDOWEVENT_RESIZED)
      {
        ww4=loopevent4.window.data1;
        hh4=loopevent4.window.data2;
    }
}

void fontes4(void){
  static const int FONTSIZE = 24;
  fonte4 = TTF_OpenFont("fontes/fontetop.ttf", FONTSIZE);
  fontePronto4 = TTF_RenderText_Solid(fonte4, menu4, color41);
  text4[0] = SDL_CreateTextureFromSurface(renderer4, fontePronto4);
  SDL_QueryTexture(text4[0], NULL, NULL, &textRect4.w, &textRect4.h);
  SDL_FreeSurface(fontePronto4);
}
void alterarfonte4(SDL_Rect fonteRect, SDL_Color color, char menuzada[]){
  // huds.rRcura.x = 15; huds.rRcura.y = 42; huds.rRcura.w = 15; huds.rRcura.h = 16.5; //
  // SDL_Rect textRect2 = {12.5,60, 100, 500}; //
  fontePronto4 = TTF_RenderText_Solid(fonte4, menuzada, color);
  text4[0] = SDL_CreateTextureFromSurface(renderer4, fontePronto4);

  //textRect2.x = potionRect.x - 2,5;
  //textRect2.y = potionRect.y + 18;

  SDL_QueryTexture(text4[0], NULL, NULL, &textRect4.w, &textRect4.h);
}



void mouse2F4 (MOUSE4 * mouse4) {
  static int width, height;
  static float wf, hf;
  SDL_GetMouseState( &mouse4->x, &mouse4->y); // pegando a pos do mouse2 //
  SDL_GetWindowSize(gJanelaReal4, &width, &height);
  //printf("%i %i ", width, height);
  wf = (float)width / 640;
  hf = (float)height / 400;
  mouse4->x /= wf;
  mouse4->y = (mouse4->y / hf);
  //printf(" // %i %i\n", mouse2->x, mouse2->y);
}


void iniciarfundo4 (void) {
  music4 = Mix_LoadMUS("songs/menu2.mp4");

  fundoSurf4 = IMG_Load("img/overworld.png");
  fundoTex4 = SDL_CreateTextureFromSurface(renderer4, fundoSurf4);
  SDL_QueryTexture(fundoTex4, NULL, NULL, &mapaw4, &mapah4);
  SDL_FreeSurface(fundoSurf4);

}

void renderizarfundo4 (void) {
  SDL_Event event;
  static int sentidox = 1;
  static int sentidoy = 1;

  cam4.x = *globalx4 - 320;
  cam4.y = *globaly4 - 200;

  if(cam4.x < 0) {
    sentidox = 1;
    cam4.x = 0;
  }
  if(cam4.y < 0){
    sentidoy = 1;
    cam4.y = 0;
  }
  if(cam4.x + cam4.w >= mapaw4) {
    sentidox = -1;
    cam4.x = mapaw4 - 640;
  }
  if(cam4.y + cam4.h >= mapah4) {
    sentidoy = -1;
    cam4.y = mapah4 - 400;
  }

  *globalx4 += sentidox;
  *globaly4 += sentidoy;

  SDL_RenderClear(renderer4);
  // 4B0082
  SDL_RenderCopy(renderer4, fundoTex4, &cam4, NULL);

  
  SDL_RenderCopy(renderer4, text4[0], NULL, &textRect4);


  sprintf(menu4, "RANKING DE PONTOS");
  textRect4.x = 160; textRect4.y = 20;
    alterarfonte4(textRect4, color42, menu4);   
   SDL_RenderCopy(renderer4, text4[0], NULL, &textRect4);

  sprintf(menu4, "PONTOS");
  textRect4.x = 440; textRect4.y = 50;
  alterarfonte4(textRect4, color42, menu4);
 
  SDL_RenderCopy(renderer4, text4[0], NULL, &textRect4);

    sprintf(menu4, "NOME");
  textRect4.x = 20; textRect4.y = 50;
    alterarfonte4(textRect4, color42, menu4);
 
   SDL_RenderCopy(renderer4, text4[0], NULL, &textRect4);



  for(int i=0;i<5;i++)
  {
      sprintf(menu4, "%s",top[i].NOME);
    textRect4.x = 20; textRect4.y =80+(50*i);
     alterarfonte4(textRect4, color42, menu4);
    
    SDL_RenderCopy(renderer4, text4[0], NULL, &textRect4);

    sprintf(menu4, "%.6d",top[i].pontuacao);
    textRect4.x = 480; textRect4.y = 80 +(50*i);
     alterarfonte4(textRect4, color42, menu4);
    
    SDL_RenderCopy(renderer4, text4[0], NULL, &textRect4);
  }
  sprintf(menu4, "VOLTAR");
  textRect4.x = 20; textRect4.y = 340;
   if(mouse4.x >= 20 && mouse4.x < 143 && mouse4.y >= 347 && mouse4.y <= 468) {
    alterarfonte4(textRect4, color41, menu4);  
  }
  else {
    alterarfonte4(textRect4, color42, menu4); 
  }
  SDL_RenderCopy(renderer4, text4[0], NULL, &textRect4);


 





  SDL_RenderPresent(renderer4); 
}
void verificarInteracao4(void) {
  if(mouse4.x >= 20 && mouse4.x < 143 && mouse4.y >= 347 && mouse4.y <= 368) {
    if(click4 && !clickfalse4) {
      clickfalse4 = true;
      printf("[Console]ADEUS :/\n");
      loop4 = false;
    }
  }
}



int pontos(SDL_Renderer * renderer, SDL_Window * Janelona, int * globalXzada, int * globalYzada) {
    FILE* p_arquivo;
    p_arquivo= fopen("score/score.bin","r");
    fread(&top,sizeof(SCORE),5,p_arquivo);
    fclose(p_arquivo);

 
    
    globalx4 = globalXzada;
    globaly4 = globalYzada;
    loop4 = true;
    renderer4= renderer;
    gJanelaReal4 =Janelona;
   
      iniciarfundo4();
      fontes4();

      //Mix_PlayMusic(music4, -1);
      Mix_VolumeMusic(30);

      while(loop4) {

        rescalar4();
        SDL_RenderSetLogicalSize(renderer4, 640, 400);

        while(SDL_PollEvent(&loopevent4)){
        //X to close//
        if(loopevent4.type == SDL_QUIT)
          loop4 = false;
        if(loopevent4.type == SDL_MOUSEBUTTONDOWN && !click4) {
          if(loopevent4.button.button == SDL_BUTTON_LEFT) {
            click4 = true;
            //textoInput();
          }
        }
        if(loopevent4.type == SDL_MOUSEBUTTONUP) {
          if(loopevent4.button.button == SDL_BUTTON_LEFT) {
            click4 = false;
            clickfalse4 = false;
          }   
        }
      }
      verificarInteracao4();
      mouse2F4(&mouse4);
      renderizarfundo4();
      //textoInput();

      SDL_Delay(1000/30);
    }
    SDL_DestroyTexture(fundoTex4);
 
  }

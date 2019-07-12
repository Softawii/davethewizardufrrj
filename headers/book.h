#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"



SDL_Rect RectTextBook = {30,375, 100, 500};
TTF_Font* BookFont;
SDL_Surface* FontPotion;
SDL_Color color = {255,255,255}; // branco como a neve //
SDL_Texture* bookText[10];
char potionNumber[5] = "10";

SDL_Event eventos;
typedef struct {
    int velocidade;
    int cura;
    int dano;
}POTION;

typedef struct {
    bool ativo;
    bool aberto;
    int coins;
    int keys;
    int pontos;
    int life;
    POTION potion;

    SDL_Rect rR;
}BOOK;

Mix_Chunk* menu;
Mix_Chunk* clickmenu;




void bookInteraction(PONTEIROMOUSE* mouse,SDL_Window* gJanela,SDL_Event* event,BOOK* book);



void bookFonts(SDL_Renderer * render){
  static const int FONTSIZEBOOK = 12;
  BookFont = TTF_OpenFont("fontes/fontetop.ttf", FONTSIZEBOOK);
  FontPotion = TTF_RenderText_Solid(BookFont, potionNumber, color);
  bookText[0] = SDL_CreateTextureFromSurface(render, FontPotion);
  SDL_QueryTexture(bookText[0], NULL, NULL, &RectTextBook.w, &RectTextBook.h);
  SDL_FreeSurface(FontPotion);
}

void bookOpen (BOOK * book,SDL_Renderer* render, char numerodepocoes[],SDL_Color cor ,SDL_Surface* fontePote,SDL_Event*event,SDL_Texture* bookTex,TTF_Font* fonte2,SDL_Texture* text[],SDL_Window* gJanela,PONTEIROMOUSE* mouse) {
    bool loop = true;
    static bool audioIniciar=false;
    if(!audioIniciar)
    {
        menu = Mix_LoadWAV("sfx/menu.wav");
        clickmenu = Mix_LoadWAV("sfx/clickmenu.wav");
        audioIniciar = true;
    }

    //SDL_Rect textRect = {30,375, 100, 500};//
    Mix_PlayChannel(4,menu,0);
    while(loop){
    bookInteraction(mouse,gJanela,event,book);
    //renderizar();

    SDL_RenderCopy(render, bookTex, NULL, NULL);

    // CURA //
    book->rR.x = 115; book->rR.y = 155; book->rR.w = 100; book->rR.h = 500;
    sprintf(numerodepocoes, "%.2d - COMPRAR (15 moedas)", book->potion.cura);
    fontePote = TTF_RenderText_Solid(fonte2, numerodepocoes, cor);
    text[1] = SDL_CreateTextureFromSurface(render, fontePote);
    SDL_QueryTexture(text[1], NULL, NULL, &book->rR.w, &book->rR.h);
    
    SDL_RenderCopy(render, text[1], NULL, &book->rR);

    // VELOCIDADE //
    book->rR.x = 115; book->rR.y = 230; book->rR.w = 100; book->rR.h = 500;
    sprintf(numerodepocoes, "%.2d - COMPRAR (20 moedas)", book->potion.velocidade);
    fontePote = TTF_RenderText_Solid(fonte2, numerodepocoes, cor);
    text[2] = SDL_CreateTextureFromSurface(render, fontePote);
    SDL_QueryTexture(text[2], NULL, NULL, &book->rR.w, &book->rR.h);
    
    SDL_RenderCopy(render, text[2], NULL, &book->rR);

    // DANO //
    book->rR.x = 115; book->rR.y = 308; book->rR.w = 100; book->rR.h = 500;
    sprintf(numerodepocoes, "%.2d - COMPRAR (25 moedas)", book->potion.dano);
    fontePote = TTF_RenderText_Solid(fonte2, numerodepocoes, cor);
    text[3] = SDL_CreateTextureFromSurface(render, fontePote);
    SDL_QueryTexture(text[3], NULL, NULL, &book->rR.w, &book->rR.h);
    
    SDL_RenderCopy(render, text[3], NULL, &book->rR);

    // DANO //
    book->rR.x = 115; book->rR.y = 28; book->rR.w = 100; book->rR.h = 500;
    sprintf(numerodepocoes, "%d", book->coins);
    fontePote = TTF_RenderText_Solid(fonte2, numerodepocoes, cor);
    text[4] = SDL_CreateTextureFromSurface(render, fontePote);
    SDL_QueryTexture(text[4], NULL, NULL, &book->rR.w, &book->rR.h);
    
    SDL_RenderCopy(render, text[4], NULL, &book->rR);





    SDL_RenderPresent(render);
    //printf("eu estive aq!\n");
    while(SDL_PollEvent(event)){
        //X to close//
        if(event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_b) {
          loop = false;
          break;
        }
    }
    SDL_Delay(1000/60);
  }
  book->aberto = false;
  printf("[Console] Fechando livro\n");
}
void bookInteraction(PONTEIROMOUSE* mouse,SDL_Window* gJanela,SDL_Event* event,BOOK* book)
{

    static double hf;
    static double wf;
    static int width;
    static int height;
    static double temp;

    static bool interaction= false;
    static bool end=true;

    SDL_GetMouseState( &mouse->x, &mouse->y); // pegando a pos do mouse //
    SDL_GetWindowSize(gJanela, &width, &height);
    wf = (float)width / 640;
    hf = (float)height / 400;
    mouse->x /= wf;
    mouse->y = (mouse->y / hf);

    //CLIQUES//

    if(event->type == SDL_MOUSEBUTTONDOWN) {
      if(event->button.button == SDL_BUTTON_LEFT) {
        interaction=true;
      }
    }
  if(event->type == SDL_MOUSEBUTTONUP) {
      if(event->button.button == SDL_BUTTON_LEFT) {
        interaction=false;
        end=true;
      }
    }

    //reconhecer
    if(interaction && end)
    {
        if((mouse->x>=182 && mouse->x <=349) &&(mouse->y>=160 && mouse->y<=181))
        {
            if(book->coins>=15)
            {
                Mix_PlayChannel(4,clickmenu,0);
                end=false;
                book->coins-=15;
                book->potion.cura++;
                interaction=false;
            }
        }
         if((mouse->x>=197 && mouse->x <=360) &&(mouse->y>=237 && mouse->y<=255))
        {
            if(book->coins>=20)
            {
                Mix_PlayChannel(4,clickmenu,0);
                end=false;
                book->coins-=20;
                book->potion.velocidade++;
                interaction=false;
            }
        }
         if((mouse->x>=197 && mouse->x <=360) &&(mouse->y>=315 && mouse->y<=333))
        {
            if(book->coins>=25)
            {
                Mix_PlayChannel(4,clickmenu,0);
                end=false;
                book->coins-=25;
                book->potion.dano++;
                interaction=false;
            }
        }
    }



   
}
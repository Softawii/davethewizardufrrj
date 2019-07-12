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

// BIBLIOTECAS PROPRIAS //
#include "headers/colisor.h"
#include "headers/knockback.h"
#include "headers/meatbox.h"
#include "headers/ogre.h"
#include "headers/explosion.h"
#include "headers/mage.h"
#include "headers/player.h"
#include "headers/cristal.h"
#include "headers/npc.h"
#include "headers/book.h"
#include "headers/potion.h"
#include "headers/bigboss.h"

#define LIFE 5
#define LIFEMOB1 3
#define DELAY_PROJETIL 60
#define SENTINELAPROJETIL 2

//test//
SDL_Rect temp;
//VARIAVEIS, SURFACES, ETC//
int sala=2, checkSala = 2;
int w=1280,h=800;
bool gaming = true; //GAME LOOP//
float gX = 3692, gY = 97; //MOVIMENTAÇÃO//
//float gX = 1531, gY = 491; //MOVIMENTAÇÃO//
int xd,xe,yb,yc; //VARIAVEIS EXTRAS//

// BOOK //
BOOK book;
SDL_Surface * bookSurf;
SDL_Texture * bookTex;

// TUTORIAL //
SDL_Surface * tutorialSurf;
SDL_Texture * tutorialTex;
bool houvetutorial = false;

// BIGBOSS//
BIGBOSS bigboss[1];
SDL_Surface * bigbossSurf;
SDL_Texture * bigbossTex;

// DOG && CAT //
SDL_Surface * dog1Surf;
SDL_Texture * dog1Tex;
SDL_Surface * cat1Surf;
SDL_Texture * cat1Tex;
ANIMALS animals[2];
int animalsmax = 2;
// NPC //
SDL_Surface * npcSurf;
SDL_Texture * npcTex;
NPC npc[4];
int npcmax = 4;
// IRMAO
NPC irmao;
// ANCIAO //
NPC anciao;

// MEAT BOX //
SDL_Surface* meatboxSurf;
SDL_Texture* meatboxTex;
MEATBOX meatbox[10];
int meatboxMobs = 10;

// OGRE //
SDL_Surface* ogreSurf;
SDL_Texture* ogreTex;
OGRE ogre[9];
int ogreMobs = 9;

// MAGE //

MAGE mage[8];
SDL_Surface* mageSurf;
SDL_Texture* mageTex;
int mageMobs = 8;

// EXPLOSION //
MEGUMIN explodir;
SDL_Surface* explodirSurf;
SDL_Texture* explodirTex;

// CRISTAL //
SDL_Surface* cristalSurf;
SDL_Texture* cristalTex;
CRISTAL cristal[7];
static int cristalQuantidade = 7;

// MOUSE //
PONTEIROMOUSE mouse;
SDL_Cursor* cursor;
SDL_Surface* colorCursor;

// MISSAO //
DESAFIOS missao;

// PORTAO //
SDL_Surface* portaoSurf;
SDL_Texture* portaoTex;
PORTAO portao;

//COLISOES//
bool colisao = false;
//MAP//
SDL_Rect rRcam = {0,0,640, 400};
SDL_Texture* mapTex; //textura da wall//
SDL_Surface* mapSurf; //surface da wall//
SDL_Texture* mapTex2; //textura da wall//
SDL_Surface* mapSurf2; //surface da wall//
int mapw = 6360;
int maph = 2880;
bool pause = false;

//WALL//
SDL_Rect rRw[400];
SDL_Texture* wallTex; //textura da wall//
SDL_Surface* wallSurf; //surface da wall//
int numWall = 400;

struct CHEST {
  bool estado;
  int x;
  int y;
  SDL_Rect pos;
};
typedef struct CHEST CHEST;
CHEST chest[5];
int numChest = 5;
SDL_Rect sChestF = {0,0, 16, 16};
SDL_Rect sChestA = {32, 0, 16, 16};
SDL_Surface* chestSurf;
SDL_Texture* chestTex;

SDL_Rect rPortal[2];
SDL_Rect sPortal;
SDL_Surface * portalSurf;
SDL_Texture * portalTex;

// MINI BOSS//
SDL_Surface* minibossSurf;
SDL_Texture* minibossTex;
struct MINIBOSS {
  SDL_Rect posTela;
  SDL_Rect posCorte;
  int life;
  int velocidade;
  int posicaox;
  int posicaoy;
  int direcao;
  int andando;
  bool sala;
};
typedef struct MINIBOSS MINIBOSS;
MINIBOSS miniboss[1];
SDL_Rect rBossBar = {212,370, 217, 12};
SDL_Rect sBossBar = {0, 0, 217, 12};
SDL_Rect rBossLife;
SDL_Rect sBossLife = {220, 1, 9, 9};

// MOUSE //
PONTEIROMOUSE mouse;
SDL_Cursor* cursor;
SDL_Surface* colorCursor;
/*
mage->sRp.x = 62; mage->sRp.w = 14; 
    mage->sRp.y = 2;  mage->sRp.h = 14;
 */
//PLAYER//

bool firsttimeunderworld = false;
bool firsttimeoverworld = false;
bool wakeup;

SDL_Surface * projSurf;
SDL_Texture * projTex;
SDL_Rect projsR = {62,14,2,14};

SDL_Rect rR;
SDL_Rect sR;
SDL_Texture* playerTex; //textura do Personagem
SDL_Surface* playerSurf; //Surface do Player
SDL_Texture* objectTex; //textura de objtos//
SDL_Surface* objectSurf; // surface de objetos//
int life = LIFE; //VIDA DO PLAYER//
int coins = 0;
int invencible = 0; //INVENCIBILIDADE DE DANO//
KBACK kback; 
float const vel = 2.1; // VELOCIDADE DO PLAYER //
char sentido = 'b';
bool cajado = false; //se esta equipando o cajado magico topzudo//
bool interagir = false; // se estamos interagindo com algum item maneiro //
bool regeneffect = false;
bool regeneffectkeydown = false;
bool projetilstop;


float potionvel = 1;
bool veleffect;
bool veleffectkeydown;
int velffectcounter = 0;

int danofx = 1;
bool danoeffect;
bool danoeffectkeydown;
int danocounter = 0;
  //cajado//
bool projetil = false;
SDL_Rect rProjetil;
SDL_Rect sProjetil;

SDL_Surface * cajadoSurf;
SDL_Texture * cajadoTex;
CAJADO staff;
SDL_Point centerstaff;
//hud//
SDL_Rect rH; //rect HUD//
SDL_Texture* heartTex; //textura do Personagem
SDL_Surface* heartSurf; //Surface do Player
SDL_Texture* HUDTex; // textura dos huds*//
SDL_Surface* HUDSurf; // surface dos huds//
// pocao //
typedef struct {
  SDL_Rect sRcura;
  SDL_Rect rRcura;

  SDL_Rect sRvel;
  SDL_Rect rRvel;

  SDL_Rect sRdano;
  SDL_Rect rRdano;

  SDL_Rect sRcoin;
  SDL_Rect rRcoin;

  SDL_Rect sRkey;
  SDL_Rect rRkey;

  SDL_Rect sRstaff;
  SDL_Rect rRstaff;
}HUD;

HUD huds;

SDL_Rect siconpotion = {37, 11, 10, 11};
SDL_Rect riconpotion = {15, 42, 15, 16.5};
//int chaves = 0;
//int book.potion.cura = 2;  
// CAIXAS DE DIALOGO//
SDL_Surface* dialogboxSurf;
SDL_Texture* dialogboxTex;
SDL_Rect sDialogBox = {1,2,539, 114};
SDL_Rect rDialogBox = {50,280, 539, 114}; 
bool emDialogo = false;
SDL_Surface * iconSurf;
SDL_Texture * iconTex;

SDL_Surface* fadeSurf;//fade in-out surface//
SDL_Texture* fadeTex;
int fadeAlpha = 0;

SDL_Window* gJanela = NULL; // CRIANDO JANELA //

SDL_Renderer* render;// Render da Screen //

SDL_Event event; //LER EVENTOS//

//AUDIO//
Mix_Chunk* damage;
Mix_Chunk* death;
Mix_Chunk* hitwall;
Mix_Chunk* welcome;
Mix_Chunk* projetilhit;
Mix_Chunk* projetilstart;
Mix_Chunk* projetilend;
Mix_Chunk* walk;
Mix_Chunk* warning;
//Mix_Chunk* cannon;
Mix_Chunk* regen;
Mix_Chunk* interactioneffect;
Mix_Chunk* error;
Mix_Chunk* openchest;
Mix_Chunk* killenemys;
Mix_Chunk* cristalsounds;
Mix_Chunk* opendoor;
Mix_Music* overworld;
Mix_Music* underworld;
Mix_Chunk* talk;



//fonte//
// SDL_Rect riconpotion = {15, 42, 15, 16.5};
SDL_Rect textRect = {12.5,60, 100, 500};
TTF_Font* fonte;
TTF_Font* fonte2;
SDL_Surface* fontePote;
SDL_Surface* fonteDialogo;
SDL_Color cor = {255,255,255}; // branco como a neve //
SDL_Texture* text[10];
char numerodepocoes[50] = "10";


//CHAMADA//
bool janela (void);
void surfaces (void);
bool renderizar(void);
void renderizarBaus(void);
bool rescalar(void);
void movements (void);
void makemovements(void);
void teladeAnimacaoIN (void);
void teladeAnimacaoOUT (void);
int mob (int i, bool colid, SDL_Rect r1);
void teladeAnimacao (void);
bool collision(SDL_Rect r1, SDL_Rect r2, int velocidadex, int velocidadey);
void salaCamera();
void salaAtual();
void slimeAnimated(int i);
void interaction(void);
void blocksinteractive(void);
void verificator(void);
bool wall_agua(int i);
void renderizarparedes(void);
void iniciarCanhoes (void);
void player_canhao(void);
void fontes(void);
//void alterarfonte(int i);
void renderizarMiniBoss(void);
void abrirDialogbox (char texto[], char texto2[], char texto3[], char texto4[], int yicon) ;
// FUNCOES //
                                                                               //INICIAÇÃO//


// INICIAR BIGBOSS //
void bigbossStart(void)
{
  bigboss[0].life = 50; bigboss[0].lifemaxima = 50; bigboss[0].x = 4875; bigboss[0].y = 234;
  bigboss[0].velocidade = 1.5; bigboss[0].distancia = 600; bigboss[0].seguir = 1;
  bigboss[0].dir = true; bigboss[0].espera = 1; bigboss[0].i = 0; bigboss[0].contador = 0;
  bigboss[0].maximo = 60; bigboss[0].delay = 60; bigboss[0].j = 0; bigboss[0].k = 0;
  bigboss[0].contadoranime = 0; bigboss[0].morrer = 0; bigboss[0].kbdelay = 0;
  bigboss[0].chat1 = false; bigboss[0].chat2 = false;

  // tiro 0 - 0 GRAUS PRA CIMA//
  bigboss[0].velpx[0] = 0; bigboss[0].velpy[0] = -5;
  // tiro 0 - 45 GRAUS PRA CIMA//
  bigboss[0].velpx[1] = -5; bigboss[0].velpy[1] = -5;
  // tiro 0 - 90 GRAUS PRA CIMA//
  bigboss[0].velpx[2] = -5; bigboss[0].velpy[2] = 0;
  // tiro 0 - 135 GRAUS PRA CIMA//
  bigboss[0].velpx[3] = -5; bigboss[0].velpy[3] = 5;
  // tiro 0 - 180 GRAUS PRA CIMA//
  bigboss[0].velpx[4] = 0; bigboss[0].velpy[4] = 5;
  // tiro 0 - 225 GRAUS PRA CIMA//
  bigboss[0].velpx[5] = 5; bigboss[0].velpy[5] = 5;
  // tiro 0 - 270 GRAUS PRA CIMA//
  bigboss[0].velpx[6] = 5; bigboss[0].velpy[6] = 0;
  // tiro 0 - 315 GRAUS PRA CIMA//
  bigboss[0].velpx[7] = 5; bigboss[0].velpy[7] = -5;

}



//PLAYERSTART//
void playerStart (void) {

  firsttimeunderworld = false;
  firsttimeoverworld = false;
  cajado = false;
  wakeup = false;

  xd = 0; xe = 0; yc = 0; yb = 0;

  //gX = 3692, gY = 97;
  gX = 1494; gY = 241;
  //gX = 4900; gY = 988;
  kback.mobNUMERO = 0; // NUMERO DO MOB //
  kback.mobTYPE = 'M'; // M = MEATBOX //
  kback.emKBACK = false;

  rProjetil.x = -5000;
  rProjetil.y = -5000;

  staff.sR.x = 0; staff.sR.y = 0; staff.sR.w = 8; staff.sR.h = 30;
  staff.rR.x = 0; staff.rR.y = 0; staff.rR.w = 12; staff.rR.h = 45;

  book.aberto = false; book.ativo = false; book.coins = 000; book.keys = 00;
  book.potion.cura = 00; book.potion.dano = 0; book.potion.velocidade = 0;
  book.pontos = 0;book.life = LIFE;

  portao.x = 3672; portao.y = 504;
  portao.contador = 0;
  
  //HUD //
  //SDL_Rect siconpotion = {37, 11, 10, 11};
  //SDL_Rect riconpotion = {15, 42, 15, 16.5};

  huds.rRcura.x = 15; huds.rRcura.y = 42; huds.rRcura.w = 15; huds.rRcura.h = 16.5;
  huds.sRcura.x = 38; huds.sRcura.y = 11; huds.sRcura.w = 10; huds.sRcura.h = 11;

  huds.rRvel.x = 45; huds.rRvel.y = 42; huds.rRvel.w = 15; huds.rRvel.h = 16.5;
  huds.sRvel.x = 49; huds.sRvel.y = 11; huds.sRvel.w = 10; huds.sRvel.h = 11;

  huds.rRdano.x = 75; huds.rRdano.y = 42; huds.rRdano.w = 15; huds.rRdano.h = 16.5;
  huds.sRdano.x = 60; huds.sRdano.y = 11; huds.sRdano.w = 10; huds.sRdano.h = 11;

  huds.sRcoin.x = 88; huds.sRcoin.y = 12; huds.sRcoin.w = 8; huds.sRcoin.h = 8;  
  huds.rRcoin.x = 550; huds.rRcoin.y = 10; huds.rRcoin.w = 16; huds.rRcoin.h = 16;

  huds.sRkey.x = 72; huds.sRkey.y = 13; huds.sRkey.w = 14; huds.sRkey.h = 7;  
  huds.rRkey.x = 600; huds.rRkey.y = 10; huds.rRkey.w = 21; huds.rRkey.h = 10.5;

  huds.sRstaff.x = 16; huds.sRstaff.y = 1; huds.sRstaff.w = 8; huds.sRstaff.h = 30; 
  huds.rRstaff.x = 600; huds.rRstaff.y = 350; huds.rRstaff.w = 12; huds.rRstaff.h = 45;

}
// CRISTAL START //
void cristalStart (void) {
  cristal[0].contadorrgb = 0; cristal[0].contadoranime = 0;
  cristal[0].x = 3000+532; cristal[0].y = 607; cristal[0].ativo = true; // cristal da de baixo

  cristal[1].contadorrgb = 0; cristal[1].contadoranime = 0;
  cristal[1].x = 3000+1033; cristal[1].y = 173; cristal[1].ativo = true; //cristal la de cima

  cristal[2].contadorrgb = 0; cristal[2].contadoranime = 0;
  cristal[2].x = 3000+820; cristal[2].y = 183; cristal[2].ativo = true; // cristal do meio

  cristal[3].contadorrgb = 0; cristal[3].contadoranime = 0; 
  cristal[3].x = 3000+480; cristal[3].y = 202; cristal[3].ativo = true;   // cristal cima esquerda

  // ASH //
  cristal[4].contadorrgb = 0; cristal[4].contadoranime = 0; 
  cristal[4].x = 5135; cristal[4].y = 1892; cristal[4].ativo =true;   // cristal baixo

  cristal[5].contadorrgb = 0; cristal[5].contadoranime = 0; 
  cristal[5].x = 5040; cristal[5].y = 997; cristal[5].ativo = true;   // cristal cima esquerda

  cristal[6].contadorrgb = 0; cristal[6].contadoranime = 0; 
  cristal[6].x = 6042; cristal[6].y = 1103; cristal[6].ativo =true;   // cristal cima esquerda
}

// INIICAR MAGE //
void mageStart (void) {
  // MAGE 0 //
  if(cristal[1].ativo) {
    mage[0].life = 1; mage[0].distancia = 900; mage[0].delay = 90; mage[0].dir = false;
    mage[0].i = 0; mage[0].morrer = 0; mage[0].damage = 3; mage[0].x = 3000+975;
    mage[0].y = 200; mage[0].xp = mage[0].x; mage[0].y; mage[0].yp = mage[0].y;
    mage[0].velmx = 0; mage[0].velmy = 0; mage[0].j = 0; mage[0].espera = 0;
  }
  // MAGE 1//s
  if(cristal[3].ativo) {
    mage[1].life = 1; mage[1].distancia = 900; mage[1].delay = 90; mage[1].dir = false;
    mage[1].i = 0; mage[1].morrer = 0; mage[1].damage = 3; mage[1].x = 3000+488;
    mage[1].y = 358; mage[1].xp = mage[1].x; mage[1].y; mage[1].yp = mage[1].y;
    mage[1].velmx = 0; mage[1].velmy = 0; mage[1].j = 0; mage[1].espera = 0;
  }
  // MAGE ASH 1 //
  if(cristal[4].ativo) {
    mage[2].life = 1; mage[2].distancia = 900; mage[2].delay = 90; mage[2].dir = false;
    mage[2].i = 0; mage[2].morrer = 0; mage[2].damage = 3; mage[2].x = 5012;
    mage[2].y = 1920; mage[2].xp = mage[2].x; mage[2].y; mage[2].yp = mage[2].y;
    mage[2].velmx = 0; mage[2].velmy = 0; mage[2].j = 0; mage[2].espera = 0;
  }
   if(cristal[5].ativo) {
    mage[3].life = 1; mage[3].distancia = 900; mage[3].delay = 90; mage[3].dir = false;
    mage[3].i = 0; mage[3].morrer = 0; mage[3].damage = 3; mage[3].x = 4728;
    mage[3].y = 1065; mage[3].xp = mage[3].x; mage[3].y; mage[3].yp = mage[3].y;
    mage[3].velmx = 0; mage[3].velmy = 0; mage[3].j = 0; mage[3].espera = 0;

    mage[4].life = 1; mage[4].distancia = 900; mage[4].delay = 90; mage[4].dir = false;
    mage[4].i = 0; mage[4].morrer = 0; mage[4].damage = 3; mage[4].x = 5317;
    mage[4].y = 1118; mage[4].xp = mage[4].x; mage[4].y; mage[4].yp = mage[4].y;
    mage[4].velmx = 0; mage[4].velmy = 0; mage[4].j = 0; mage[4].espera = 0;
  }
  if(cristal[6].ativo) {
    mage[5].life = 1; mage[5].distancia = 900; mage[5].delay = 90; mage[5].dir = false;
    mage[5].i = 0; mage[5].morrer = 0; mage[5].damage = 3; mage[5].x = 6280;
    mage[5].y = 1215; mage[5].xp = mage[5].x; mage[5].y; mage[5].yp = mage[5].y;
    mage[5].velmx = 0; mage[5].velmy = 0; mage[5].j = 0; mage[5].espera = 0;

    mage[6].life = 1; mage[6].distancia = 900; mage[6].delay = 90; mage[6].dir = false;
    mage[6].i = 0; mage[6].morrer = 0; mage[6].damage = 3; mage[6].x = 5904;
    mage[6].y = 1050; mage[6].xp = mage[6].x; mage[6].y; mage[6].yp = mage[6].y;
    mage[6].velmx = 0; mage[6].velmy = 0; mage[6].j = 0; mage[6].espera = 0;

    mage[7].life = 1; mage[7].distancia = 900; mage[7].delay = 90; mage[7].dir = false;
    mage[7].i = 0; mage[7].morrer = 0; mage[7].damage = 3; mage[7].x = 6162;
    mage[7].y = 1024; mage[7].xp = mage[7].x; mage[7].y; mage[7].yp = mage[7].y;
    mage[7].velmx = 0; mage[7].velmy = 0; mage[7].j = 0; mage[7].espera = 0;
  }

  printf("[Console]OS MAGOS IRAO QUEIMAR SUA ALMA!\n");
}
// INICIAR MEATBOX //
void meatboxStart (void) {
  static bool start = true;
  if(start) {
    meatbox[0].life = -1; meatbox[1].life = -1; meatbox[2].life = -1;
    meatbox[3].life = -1; meatbox[4].life = -1; meatbox[5].life = -1;
    meatbox[6].life = -1; meatbox[7].life = -1; meatbox[8].life = -1;
    meatbox[9].life = -1;
    start = false;
  }
  // MEATBOX 0 //
  if(cristal[4].ativo && meatbox[0].life < 0) {
    meatbox[0].life = 2; meatbox[0].velocidade = 1.5; meatbox[0].distancia = 450; meatbox[0].i = 0;
    meatbox[0].x = 4946; meatbox[0].y = 2078; meatbox[0].agressivo = false; meatbox[0].espera = 1;
    meatbox[0].sR.w = 23;meatbox[0].sR.h = 34; meatbox[0].sR.y = 0; meatbox[0].dir = true; meatbox[0].damage = 2;
    meatbox[0].contador = 0; meatbox[0].maximo = 60; meatbox[0].delay = 0; meatbox[0].morrer = 0; meatbox[0].seguir = 1;
  }
  // meatbox 1 //
  if(cristal[4].ativo && meatbox[1].life < 0) {
    meatbox[1].life = 2; meatbox[1].velocidade = 1.5; meatbox[1].distancia = 450; meatbox[1].i = 0;
    meatbox[1].x = 5427; meatbox[1].y = 2074; meatbox[1].agressivo = false; meatbox[1].espera = 1;
    meatbox[1].sR.w = 23;meatbox[1].sR.h = 34; meatbox[1].sR.y = 0; meatbox[1].dir = true; meatbox[1].damage = 2;
    meatbox[1].contador = 0; meatbox[1].maximo = 60; meatbox[1].delay = 0; meatbox[1].morrer = 0; meatbox[1].seguir = 1;
  }
  // meatbox 2 //
  if(cristal[5].ativo && meatbox[5].life < 0) {
    meatbox[5].life = 2; meatbox[5].velocidade = 1.5; meatbox[5].distancia = 450; meatbox[5].i = 0;
    meatbox[5].x = 4818; meatbox[5].y = 1219; meatbox[5].agressivo = false; meatbox[5].espera = 1;
    meatbox[5].sR.w = 23;meatbox[5].sR.h = 34; meatbox[5].sR.y = 0; meatbox[5].dir = true; meatbox[5].damage = 2;
    meatbox[5].contador = 0; meatbox[5].maximo = 60; meatbox[5].delay = 0; meatbox[5].morrer = 0; meatbox[5].seguir = 1;
  }
  if(cristal[5].ativo && meatbox[6].life < 0) {
    meatbox[6].life = 2; meatbox[6].velocidade = 1.5; meatbox[6].distancia = 450; meatbox[6].i = 0;
    meatbox[6].x = 5186; meatbox[6].y = 1409; meatbox[6].agressivo = false; meatbox[6].espera = 1;
    meatbox[6].sR.w = 23;meatbox[6].sR.h = 34; meatbox[6].sR.y = 0; meatbox[6].dir = true; meatbox[6].damage = 2;
    meatbox[6].contador = 0; meatbox[6].maximo = 60; meatbox[6].delay = 0; meatbox[6].morrer = 0; meatbox[6].seguir = 1;
  }

  if(cristal[6].ativo) {
    if(meatbox[7].life < 0) {
      meatbox[7].life = 2; meatbox[7].velocidade = 1.5; meatbox[7].distancia = 450; meatbox[7].i = 0;
      meatbox[7].x = 5932; meatbox[7].y = 1195; meatbox[7].agressivo = false; meatbox[7].espera = 1;
      meatbox[7].sR.w = 23;meatbox[7].sR.h = 34; meatbox[7].sR.y = 0; meatbox[5].dir = true; meatbox[7].damage = 2;
      meatbox[7].contador = 0; meatbox[7].maximo = 60; meatbox[7].delay = 0; meatbox[7].morrer = 0; meatbox[7].seguir = 1;
    }
    else {
      meatbox[7].life = 2;
    }
    if(meatbox[8].life < 0) {
      meatbox[8].life = 2; meatbox[8].velocidade = 1.5; meatbox[8].distancia = 450; meatbox[8].i = 0;
      meatbox[8].x = 6212; meatbox[8].y = 1332; meatbox[8].agressivo = false; meatbox[8].espera = 1;
      meatbox[8].sR.w = 23;meatbox[8].sR.h = 34; meatbox[8].sR.y = 0; meatbox[6].dir = true; meatbox[8].damage = 2;
      meatbox[8].contador = 0; meatbox[8].maximo = 60; meatbox[8].delay = 0; meatbox[8].morrer = 0; meatbox[8].seguir = 1;
    }
    else {
      meatbox[8].life = 2;
    }
    if(meatbox[9].life < 0) {
      meatbox[9].life = 2; meatbox[9].velocidade = 1.5; meatbox[9].distancia = 450; meatbox[9].i = 0;
      meatbox[9].x = 5715; meatbox[9].y = 828; meatbox[9].agressivo = false; meatbox[9].espera = 1;
      meatbox[9].sR.w = 23;meatbox[9].sR.h = 34; meatbox[9].sR.y = 0; meatbox[6].dir = true; meatbox[9].damage = 2;
      meatbox[9].contador = 0; meatbox[9].maximo = 60; meatbox[9].delay = 0; meatbox[9].morrer = 0; meatbox[9].seguir = 1;
    }
    else {
      meatbox[9].life = 2;
    }
  }
  printf("[Console] MEATBOX PRONTO PARA MATAR!\n");
}
// INICIAR OGRE //
void ogreStart (void) {
  // OGRE 0 //
  if(cristal[2].ativo) {
    ogre[0].life = 1; ogre[0].velocidade = 2; ogre[0].troca = false; ogre[0].direct = 1; ogre[0].dir = false;
    ogre[0].damage = 1; ogre[0].x = 3000+554; ogre[0].y = 169; ogre[0].espera = 1; ogre[0].maximo = 60; 
    ogre[0].i = 0; ogre[0].delay = 1; ogre[0].loop = 1; ogre[0].danodelay = 0; ogre[0].morrer = 0;
  }
  // OGRE 1 //
  if(cristal[2].ativo) {
    ogre[1].life = 1; ogre[1].velocidade = 2; ogre[1].troca = false; ogre[1].direct = 1; ogre[1].dir = false;
    ogre[1].damage = 1; ogre[1].x = 3000+ 942; ogre[1].y = 233; ogre[1].espera = 1; ogre[1].maximo = 60; 
    ogre[1].i = 0; ogre[1].delay = 1; ogre[1].loop = 1; ogre[1].danodelay = 0; ogre[1].morrer = 0;
  }
  // OGRE 2 //
  if(cristal[2].ativo) {
    ogre[2].life = 1; ogre[2].velocidade = 2; ogre[2].troca = false; ogre[2].direct = 1; ogre[2].dir = false;
    ogre[2].damage = 1; ogre[2].x = 3000+1129; ogre[2].y = 796; ogre[2].espera = 1; ogre[2].maximo = 60; 
    ogre[2].i = 0; ogre[2].delay = 1; ogre[2].loop = 1; ogre[2].danodelay = 0; ogre[2].morrer = 0;
  }
  // OGRE 3 //
  if(cristal[2].ativo) {
    ogre[3].life = 1; ogre[3].velocidade = 2; ogre[3].troca = false; ogre[3].direct = 1; ogre[3].dir = false;
    ogre[3].damage = 1; ogre[3].x =3000+429; ogre[3].y = 386; ogre[3].espera = 1; ogre[3].maximo = 60; 
    ogre[3].i = 0; ogre[3].delay = 1; ogre[3].loop = 1; ogre[3].danodelay = 0; ogre[3].morrer = 0;
  }

  if(cristal[5].ativo) {
    ogre[4].life = 1; ogre[4].velocidade = 2; ogre[4].troca = false; ogre[4].direct = 1; ogre[4].dir = false;
    ogre[4].damage = 1; ogre[4].x = 5186; ogre[4].y = 1409; ogre[4].espera = 1; ogre[4].maximo = 60; 
    ogre[4].i = 0; ogre[4].delay = 1; ogre[4].loop = 1; ogre[4].danodelay = 0; ogre[4].morrer = 0;

    ogre[5].life = 1; ogre[5].velocidade = 2; ogre[5].troca = false; ogre[5].direct = 1; ogre[5].dir = false;
    ogre[5].damage = 1; ogre[5].x = 4559; ogre[5].y = 1240; ogre[5].espera = 1; ogre[5].maximo = 60; 
    ogre[5].i = 0; ogre[5].delay = 1; ogre[5].loop = 1; ogre[5].danodelay = 0; ogre[5].morrer = 0;

    ogre[6].life = 1; ogre[6].velocidade = 2; ogre[6].troca = false; ogre[6].direct = 1; ogre[6].dir = false;
    ogre[6].damage = 1; ogre[6].x = 5471; ogre[6].y = 1436; ogre[6].espera = 1; ogre[6].maximo = 60; 
    ogre[6].i = 0; ogre[6].delay = 1; ogre[6].loop = 1; ogre[6].danodelay = 0; ogre[6].morrer = 0;

    ogre[7].life = 1; ogre[7].velocidade = 2; ogre[7].troca = false; ogre[7].direct = 1; ogre[7].dir = false;
    ogre[7].damage = 1; ogre[7].x = 5705; ogre[7].y = 705; ogre[7].espera = 1; ogre[7].maximo = 60; 
    ogre[7].i = 0; ogre[7].delay = 1; ogre[7].loop = 1; ogre[7].danodelay = 0; ogre[7].morrer = 0;

    ogre[8].life = 1; ogre[8].velocidade = 2; ogre[8].troca = false; ogre[8].direct = 1; ogre[8].dir = false;
    ogre[8].damage = 1; ogre[8].x = 4594; ogre[8].y = 1348; ogre[8].espera = 1; ogre[8].maximo = 60; 
    ogre[8].i = 0; ogre[8].delay = 1; ogre[8].loop = 1; ogre[8].danodelay = 0; ogre[8].morrer = 0;
  }
  printf("[Console] OGROS AO ATAQUE!\n");
}
void iniciarNPC (void) {
  // icon gato = 175 // cachorro = 150 //
  animals[0].inicialx = 857; animals[0].inicialy = 732; animals[0].contadoranime = 0;
  animals[0].x = animals[0].inicialx; animals[0].y = animals[0].inicialy; animals[0].icon = 175;
  animals[0].maximo = 100; animals[0].sentido = 3; animals[0].type = 2; animals[0].velocidade = 0.5;
  strcpy(animals[0].texto, "AMBER: Bom Dia, Dave.... Oops, MEOW!!!");

  animals[1].inicialx = 193; animals[1].inicialy = 185; animals[1].contadoranime = 0;
  animals[1].x = animals[1].inicialx; animals[1].y = animals[1].inicialy; animals[1].icon = 150;
  animals[1].maximo = 100; animals[1].sentido = 2; animals[1].type = 1; animals[1].velocidade = 0.5;
  strcpy(animals[1].texto, "COPPER: AUAU, Proteger!!! AUAU o.o");
  
  // icon npc // guerreiro = 0 // barbudo = 25 // menina = 50 // anciao = 75 //
  // bau = 100 // placa = 125 //
  npc[0].sentido = 2; npc[0].x = 752; npc[0].y = 595; npc[0].type = 1; npc[0].icon = 0;
  strcpy(npc[0].texto, "SENTINELA: Bom Dia, Dave! O anciao lhe procura...");
  strcpy(npc[0].texto2, "SENTINELA: Eae camarada, tudo bem?");


  npc[1].sentido = 2; npc[1].x = 346; npc[1].y = 622; npc[1].type = 3; npc[1].icon = 50;
  strcpy(npc[1].texto, "DORELLA: Acho que ha algo muito ruim com o anciao...");
  strcpy(npc[1].texto2, "DORELLA: Uau! Esse e o cajado do anciao?");


  npc[2].sentido = 2; npc[2].x = 860; npc[2].y = 325; npc[2].type = 1; npc[2].icon = 0;
  strcpy(npc[2].texto, "SENTINELA: Vamos jogar D&D?");
  strcpy(npc[2].texto2, "SENTINELA: Por favor.... Vamos jogar D&D!!!");

  npc[3].sentido = 2; npc[3].x = 248; npc[3].y = 145; npc[3].type = 3; npc[3].icon = 50;
  strcpy(npc[3].texto, "SRa NIMBUS: O velho ta desesperado te chamando ae!");
  strcpy(npc[3].texto2, "SRa NIMBUS: Te desejo sorte na sua aventura!");

  irmao.sentido = 2; irmao.x = 1630; irmao.y = 142; irmao.type = 2; irmao.icon = 25;
  irmao.talk = false;

  anciao.sentido = 2; anciao.x = 2518; anciao.y = 119; anciao.type = 4; anciao.icon = 75;
  anciao.talk = false; anciao.talk2 = false;
}

void iniciarChests (void) {
  // chest 1 //
  chest[0].estado = true;
  chest[0].x = 2472;
  chest[0].y = 335;
  chest[0].pos.x = chest[0].x - rRcam.x; chest[0].pos.y = chest[0].y - rRcam.y;
  chest[0].pos.w = 32; chest[0].pos.h = 32;
  //char chest[0].texto[100] = "Oi";
  // fim chest 1 //
   // chest 2 //
  chest[1].estado = true;
  chest[1].x =3000+475;
  chest[1].y = 335;
  chest[1].pos.x = chest[1].x - rRcam.x; chest[1].pos.y = chest[1].y - rRcam.y;
  chest[1].pos.w = 32; chest[1].pos.h = 32;

  chest[2].estado = true;
  chest[2].x =5604;
  chest[2].y = 675;
  chest[2].pos.x = chest[2].x - rRcam.x; chest[2].pos.y = chest[2].y - rRcam.y;
  chest[2].pos.w = 32; chest[2].pos.h = 32;

  chest[3].estado = true;
  chest[3].x =4444;
  chest[3].y = 981;
  chest[3].pos.x = chest[3].x - rRcam.x; chest[3].pos.y = chest[3].y - rRcam.y;
  chest[3].pos.w = 32; chest[3].pos.h = 32;

  chest[4].estado = true;
  chest[4].x =5973;
  chest[4].y = 572;
  chest[4].pos.x = chest[4].x - rRcam.x; chest[4].pos.y = chest[4].y - rRcam.y;
  chest[4].pos.w = 32; chest[4].pos.h = 32;
}

void renderizarMiniBoss(void) {
  //printf("I,m here\n");

  if(rR.x >= 4436 - rRcam.x && rR.x <= 4436 + 652 - rRcam.x && 
    rR.y >= 0 - rRcam.y && rR.y <= 932 - rRcam.y) {
    //printf("I,m here\n");
    rBossLife.x = rBossBar.x + 4; rBossLife.y = rBossBar.y + 1;
    //PARTE SUJEITA A MUDANCAS//
    rBossLife.w = bigboss[0].life * 4.22; rBossLife.h = 9;
    //renderizar();
    SDL_RenderCopy(render, minibossTex, &sBossLife, &rBossLife);
    SDL_RenderCopy(render, minibossTex, &sBossBar, &rBossBar);
  }
}

void dialogoMiniboss(void) {
    bool ativos = false;
    if(bigboss[0].life <= 0) {
        abrirDialogbox("Klyn: MEUS PARABENS, HUMANO...", 
        "ACABOU COM TODA MINHA NACAO....", "", "", 200);
        book.pontos+=4000;
        gaming = false;
        xe=0;xd=0;yc=0;;yb=0;
    }
    if(rR.x >= 4903 - rRcam.x && rR.x <= 4903 + 57 - rRcam.x && 
    rR.y >= 851 - rRcam.y && rR.y <= 851 + 38 - rRcam.y) 
    {

    for(int i = 0; i < 7 && !ativos; i++) {
      ativos = cristal[i].ativo;
    }

    if(ativos) {
      abrirDialogbox("VOCE NAO CUMPRIU SEUS OBJETIVOS!!", "", "", "", 125);
      gY += 15;
      xe=0;xd=0;yc=0;;yb=0;
    }
    else 
    {
      if(!bigboss[0].chat1) {
        abrirDialogbox("Klyn: VOCE TEVE OUSADIA DE", 
        "INVADIR MEUS TERRITORIOS", 
        "DESTRUIR MEUS CRISTAIS E ACABAR", 
        "COM MEUS SUDITOS?!?!?", 200);
        abrirDialogbox("Klyn: IREI MATA-LO PARA MOSTRAR", 
        "MEU PODER E VINGAR MEU POVO", "SEU VERME!!!", "", 200);
        bigboss[0].chat1 = true;
        xe=0;xd=0;yc=0;;yb=0;
      }
      
    }

    
  }
}

void fontes(void){
  static const int FONTSIZE = 12;
  static const int FONTSIZE2 = 28;
  fonte = TTF_OpenFont("fontes/fontetop.ttf", FONTSIZE);
  fonte2 = TTF_OpenFont("fontes/fontetop.ttf", FONTSIZE2);
  fontePote = TTF_RenderText_Solid(fonte, numerodepocoes, cor);
  text[0] = SDL_CreateTextureFromSurface(render, fontePote);
  SDL_QueryTexture(text[0], NULL, NULL, &textRect.w, &textRect.h);
  //SDL_BlitSurface(fontePote, NULL, render, NULL);
  SDL_FreeSurface(fontePote);
}
void alterarfonte(int quantidade, SDL_Rect potionRect, int i){
  // huds.rRcura.x = 15; huds.rRcura.y = 42; huds.rRcura.w = 15; huds.rRcura.h = 16.5; //
  // SDL_Rect textRect = {12.5,60, 100, 500}; //
  fontePote = TTF_RenderText_Solid(fonte, numerodepocoes, cor);
  text[0] = SDL_CreateTextureFromSurface(render, fontePote);

  textRect.x = potionRect.x - 2,5;
  textRect.y = potionRect.y + 18;

  SDL_QueryTexture(text[0], NULL, NULL, &textRect.w, &textRect.h);
}
void audio(void) {
  damage = Mix_LoadWAV("sfx/damage.wav");
  death = Mix_LoadWAV("sfx/death.wav");
  hitwall = Mix_LoadWAV("sfx/hitwall.wav");
  welcome = Mix_LoadWAV("sfx/welcome.wav");
  projetilhit = Mix_LoadWAV("sfx/projetilhit.wav");
  projetilstart = Mix_LoadWAV("sfx/projetilstart.wav");
  projetilend = Mix_LoadWAV("sfx/projetilend.wav");
  walk = Mix_LoadWAV("sfx/walk.wav");
  warning = Mix_LoadWAV("sfx/warning.wav");
  //cannon = Mix_LoadWAV("sfx/cannon.wav");
  error = Mix_LoadWAV("sfx/error.wav");
  regen = Mix_LoadWAV("sfx/regen.wav");
  interactioneffect = Mix_LoadWAV("sfx/interaction.wav");
  openchest = Mix_LoadWAV("sfx/openchest.wav");
  overworld = Mix_LoadMUS("songs/overworld.mp3");
  underworld = Mix_LoadMUS("songs/underworld.mp3");
  killenemys = Mix_LoadWAV("sfx/killenemys.wav");
  cristalsounds = Mix_LoadWAV("sfx/cristal.wav");
  opendoor = Mix_LoadWAV("sfx/opendoor.wav");
  talk = Mix_LoadWAV("sfx/talk.wav");

}
void surfaces (void) {
                                                                   //Gerando Texturas e Sprites do Player//
  // CURSOR //
  colorCursor = IMG_Load("sprites/pointer.png");
  cursor = SDL_CreateColorCursor(colorCursor, 0, 0);
  //cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
  SDL_SetCursor(cursor);
  //PLAYER SPRITES//
  playerSurf = IMG_Load("sprites/char.png");
  playerTex = SDL_CreateTextureFromSurface(render, playerSurf);
  SDL_FreeSurface(playerSurf);
  //WALL//
  wallSurf = IMG_Load("sprites/wall.png");
  wallTex = SDL_CreateTextureFromSurface(render, wallSurf);
  SDL_FreeSurface(wallSurf);
  //MAP//
  mapSurf = IMG_Load("img/totalworld.png");
  mapTex = SDL_CreateTextureFromSurface(render, mapSurf);
  SDL_QueryTexture(mapTex, NULL, NULL, &mapw, &maph);
  SDL_FreeSurface(mapSurf);
  //MAP//
  mapSurf2 = IMG_Load("img/totalworldlight.png");
  mapTex2 = SDL_CreateTextureFromSurface(render, mapSurf2);
  SDL_QueryTexture(mapTex2, NULL, NULL, &mapw, &maph);
  SDL_FreeSurface(mapSurf2);
  //HEART//
  heartSurf = IMG_Load("sprites/hud_heart.png");
  heartTex = SDL_CreateTextureFromSurface(render, heartSurf);
  SDL_FreeSurface(heartSurf);
  //FADE//
  fadeSurf = IMG_Load("img/fade.png");
  fadeTex = SDL_CreateTextureFromSurface(render, fadeSurf);
  SDL_FreeSurface(fadeSurf);
  //OBJETOS//
  objectSurf = IMG_Load("sprites/objetos.png");
  objectTex = SDL_CreateTextureFromSurface(render, objectSurf);
  SDL_FreeSurface(objectSurf);
  //HUD ITENS//
  HUDSurf = IMG_Load("sprites/icon.png");
  HUDTex = SDL_CreateTextureFromSurface(render, HUDSurf);
  SDL_FreeSurface(HUDSurf);
  //bau
  chestSurf = IMG_Load("sprites/chest.png");
  chestTex = SDL_CreateTextureFromSurface(render, chestSurf);
  SDL_FreeSurface(chestSurf);
  // MINIBOSS//
  minibossSurf = IMG_Load("sprites/bossbar.png");
  minibossTex = SDL_CreateTextureFromSurface(render, minibossSurf);
  SDL_FreeSurface(minibossSurf);
  // baixas de dialogo//
  dialogboxSurf = IMG_Load("sprites/dialogbox.png");
  dialogboxTex = SDL_CreateTextureFromSurface(render, dialogboxSurf);
  SDL_FreeSurface(dialogboxSurf);
   // MEAT BOX //
  meatboxSurf = IMG_Load("sprites/meatbox.png");
  meatboxTex = SDL_CreateTextureFromSurface(render, meatboxSurf);
  SDL_FreeSurface(meatboxSurf);
  // OGRE //
  ogreSurf = IMG_Load("sprites/ogre.png");
  ogreTex = SDL_CreateTextureFromSurface(render, ogreSurf);
  SDL_FreeSurface(ogreSurf);
  // EXPLOSION //
  explodirSurf = IMG_Load("sprites/explosion.png");
  explodirTex = SDL_CreateTextureFromSurface(render, explodirSurf);
  SDL_FreeSurface(explodirSurf);
  // MAGE//
  mageSurf = IMG_Load("sprites/mage.png");
  mageTex = SDL_CreateTextureFromSurface(render, mageSurf);
  SDL_FreeSurface(mageSurf);
  // cajado//
  // cajado//
  cajadoSurf = IMG_Load("sprites/cajado.png");
  cajadoTex = SDL_CreateTextureFromSurface(render, cajadoSurf);
  SDL_FreeSurface(cajadoSurf);
   // cristal //
  cristalSurf = IMG_Load("sprites/cristais.png");
  cristalTex = SDL_CreateTextureFromSurface(render, cristalSurf);
  SDL_FreeSurface(cristalSurf);
  // portao //
  portaoSurf = IMG_Load("sprites/portao.png");
  portaoTex = SDL_CreateTextureFromSurface(render, portaoSurf);
  SDL_FreeSurface(portaoSurf);
  // animais //
  dog1Surf = IMG_Load("sprites/dog1.png");
  dog1Tex = SDL_CreateTextureFromSurface(render, dog1Surf);
  SDL_FreeSurface(dog1Surf);

  cat1Surf = IMG_Load("sprites/cat1.png");
  cat1Tex = SDL_CreateTextureFromSurface(render, cat1Surf);
  SDL_FreeSurface(cat1Surf);
  // npc //
  npcSurf = IMG_Load("sprites/npc.png");
  npcTex = SDL_CreateTextureFromSurface(render, npcSurf);
  SDL_FreeSurface(npcSurf);
  // projetil
  projSurf = IMG_Load("sprites/mage.png");
  projTex = SDL_CreateTextureFromSurface(render, projSurf);
  SDL_FreeSurface(projSurf);
  // icon //
  iconSurf = IMG_Load("sprites/dialogicon.png");
  iconTex = SDL_CreateTextureFromSurface(render, iconSurf);
  SDL_FreeSurface(iconSurf);
  // book //
  bookSurf = IMG_Load("img/book.png");
  bookTex = SDL_CreateTextureFromSurface(render, bookSurf);
  SDL_FreeSurface(bookSurf);
  // portal //
  portalSurf = IMG_Load("sprites/teleport.png");
  portalTex = SDL_CreateTextureFromSurface(render, portalSurf);
  SDL_FreeSurface(portalSurf);
  // bigboss//
  bigbossSurf = IMG_Load("sprites/bigboss.png");
  bigbossTex = SDL_CreateTextureFromSurface(render, bigbossSurf);
  SDL_FreeSurface(bigbossSurf);
  // TUTORIAL //
  tutorialSurf = IMG_Load("img/tutorial.png");
  tutorialTex = SDL_CreateTextureFromSurface(render, tutorialSurf);
  SDL_FreeSurface(tutorialSurf);
}
/*
sprintf(numerodepocoes, "%d", book.potion.cura);
  fontePote = TTF_RenderText_Solid(fonte, numerodepocoes, cor);
  text[0] = SDL_CreateTextureFromSurface(render, fontePote);
  SDL_QueryTexture(text[0], NULL, NULL, &textRect.w, &textRect.h);
"Voce recebeu duas pocoes! Clique 'alt' para continuar!"

*/
void abrirDialogbox (char texto[], char texto2[], char texto3[], char texto4[], int yicon) {
  bool acabou = false;
  SDL_Rect posicaoText = {rDialogBox.x + 75, rDialogBox.y + 20, rDialogBox.w, rDialogBox.h};
  SDL_Rect posicaoText2 = {rDialogBox.x + 75, rDialogBox.y + 35, rDialogBox.w, rDialogBox.h};
  SDL_Rect posicaoText3 = {rDialogBox.x + 75, rDialogBox.y + 50, rDialogBox.w, rDialogBox.h};
  SDL_Rect posicaoText4 = {rDialogBox.x + 75, rDialogBox.y + 65, rDialogBox.w, rDialogBox.h};
  SDL_Rect posicaoText5 = {rDialogBox.x + 240, rDialogBox.y + 90, rDialogBox.w, rDialogBox.h};
  SDL_Rect iconRect = {0,0,18,25};
  iconRect.y = yicon;
  SDL_Rect iconTela = {rDialogBox.x + 10, rDialogBox.y + 20, 18 * 3, 25 * 3};



  fonteDialogo = TTF_RenderText_Solid(fonte, texto, cor);
  text[1] = SDL_CreateTextureFromSurface(render, fonteDialogo);
  SDL_QueryTexture(text[1], NULL, NULL, &posicaoText.w, &posicaoText.h);
  SDL_FreeSurface(fonteDialogo);

  fonteDialogo = TTF_RenderText_Solid(fonte, texto2, cor);
  text[2] = SDL_CreateTextureFromSurface(render, fonteDialogo);
  SDL_QueryTexture(text[2], NULL, NULL, &posicaoText2.w, &posicaoText2.h);
  SDL_FreeSurface(fonteDialogo);

  fonteDialogo = TTF_RenderText_Solid(fonte, texto3, cor);
  text[3] = SDL_CreateTextureFromSurface(render, fonteDialogo);
  SDL_QueryTexture(text[3], NULL, NULL, &posicaoText3.w, &posicaoText3.h);
  SDL_FreeSurface(fonteDialogo);

  fonteDialogo = TTF_RenderText_Solid(fonte, texto4, cor);
  text[4] = SDL_CreateTextureFromSurface(render, fonteDialogo);
  SDL_QueryTexture(text[4], NULL, NULL, &posicaoText4.w, &posicaoText4.h);
  SDL_FreeSurface(fonteDialogo);

  fonteDialogo = TTF_RenderText_Solid(fonte, "Pressione 'E' para continuar...", cor);
  text[5] = SDL_CreateTextureFromSurface(render, fonteDialogo);
  SDL_QueryTexture(text[5], NULL, NULL, &posicaoText5.w, &posicaoText5.h);
  SDL_FreeSurface(fonteDialogo);

  Mix_PlayChannel(4, talk,0);
  // mini loop//
  while(!acabou){
    emDialogo = true;
    renderizar();

    SDL_RenderCopy(render, dialogboxTex, &sDialogBox, &rDialogBox);

    SDL_RenderCopy(render, iconTex, &iconRect, &iconTela);

    SDL_RenderCopy(render, text[1], NULL, &posicaoText);
    SDL_RenderCopy(render, text[2], NULL, &posicaoText2);
    SDL_RenderCopy(render, text[3], NULL, &posicaoText3);
    SDL_RenderCopy(render, text[4], NULL, &posicaoText4);
    SDL_RenderCopy(render, text[5], NULL, &posicaoText5);
    SDL_RenderPresent(render);
    //printf("eu estive aq!\n");
    while(SDL_PollEvent(&event)){
        //X to close//
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
         acabou = true;
    }
    SDL_Delay(1000/60);
  }
  emDialogo = false;
}
/* 
bool janela (void) {
  bool success = true;
  // START //
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Ocorreu um imprevisto! :(, %s\n", SDL_GetError());
      success = false;
      // A TELA NÃO INICIOU //
  }
  else {
    printf("[Console]SDL iniciado!\n");
    SDL_Delay(100);
    //VARIAVEIS//
    gJanela = SDL_CreateWindow("Dave, The Wizard!", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, w,h, SDL_WINDOW_RESIZABLE);
      if(gJanela == NULL) {
          printf("Ocorreu um imprevisto! :(, %s\n", SDL_GetError()); 
            success = false;
        }
      else{
          render = SDL_CreateRenderer(gJanela, -1, 0);
          SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        }
  }
  //FIM//
  return success;
}
*/

bool rescalar(void){
   if(event.type ==SDL_WINDOWEVENT)
      if(event.type ==SDL_WINDOWEVENT_RESIZED)
      {
        w=event.window.data1;
        h=event.window.data2;
    }
}
                                                                                              //MOVIMENTOS E RENDER//
void movements (void) {
  // RECONHECER MOVIMENTOS //
  //event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LALT // 
  if(event.type == SDL_KEYDOWN) { // Pressionando as teclas //
    if(event.key.keysym.sym == SDLK_a) {
        xe = -1;
        sentido = 'e';
    }
    if(event.key.keysym.sym == SDLK_d) {
        xd = 1;
        sentido = 'd';
    }
    if(event.key.keysym.sym == SDLK_w) {
        yc = -1;
        sentido = 'c';
    }
    if(event.key.keysym.sym == SDLK_s) {
        yb = 1;
        sentido = 'b';
    }
    if(event.key.keysym.sym == SDLK_b) {
        book.aberto = true;
        printf("[Console] Abrindo livro\n");
    }
    //interagir//
    if(event.key.keysym.sym == SDLK_e) {
      interagir = true;
    }
    if(event.key.keysym.sym == SDLK_1){
      regeneffect=true; 
    }
    if(event.key.keysym.sym == SDLK_2){
      veleffect = true; 
    }
    if(event.key.keysym.sym == SDLK_3){
      danoeffect = true; 
    }
    if(event.key.keysym.sym == SDLK_ESCAPE){
      pause = true; 
    }
  }

  else if(event.type == SDL_KEYUP) { // Despressionando as teclas //
    if(event.key.keysym.sym == SDLK_a)
        xe = 0;
    if(event.key.keysym.sym == SDLK_d)
        xd = 0;
    if(event.key.keysym.sym == SDLK_w)
        yc = 0;
    if(event.key.keysym.sym == SDLK_s)
        yb = 0; 
    if(event.key.keysym.sym == SDLK_b)
        book.aberto = false;
    if(event.key.keysym.sym == SDLK_e) {
      interagir = false;
    }
    if(event.key.keysym.sym == SDLK_1){
        regeneffect=false;
        regeneffectkeydown=false;
    }
    if(event.key.keysym.sym == SDLK_2){
        veleffect=false;
        veleffectkeydown=false;
    }
    if(event.key.keysym.sym == SDLK_3){
        danoeffect=false;
        danoeffectkeydown=false;
    }
    if(event.key.keysym.sym == SDLK_ESCAPE){
      pause = false; 
    }
  }
}

void mousemovements(void) {
  if(event.type == SDL_MOUSEBUTTONDOWN && !projetil) {
      if(event.button.button == SDL_BUTTON_LEFT) {
        projetil = true;
      }
  }
  if(event.type == SDL_MOUSEBUTTONUP) {
      if(event.button.button == SDL_BUTTON_LEFT) {
        projetil = false;
      }


  }
}
void makemovements(void) {
  // DANDO MOVIMENTOS //
  if(!kback.emKBACK){  
    if(xd == 1) { // Direita //
      //colisao com paredes//
      for(int i = 0; i < numWall && !colisao; i++) { //COLIDINDO COM WALL//
        colisao = collision(rR, rRw[i], vel * potionvel, 0);
      }
      for(int i = 0; i < animalsmax && !colisao; i++) {
        colisao = collision(rR, animals[i].rR, vel * potionvel, 0);
        if(colisao) {
          xe = 0; xd = 0; yc = 0; yb = 0;
        }
      }

      if(!colisao)
        colisao = collision(rR, irmao.rR,vel * potionvel, 0);
      if(!colisao)
        colisao = collision(rR, anciao.rR,vel * potionvel, 0);

      for(int i = 0; i < npcmax && !colisao; i++) {
        colisao = collision(rR, npc[i].rR, vel * potionvel, 0);
      }
      //colisao com portas//
      if(!colisao)
          gX += vel * potionvel;
      colisao = false;
    }
    if(xe == -1) { // ESQUERDA //
      for(int i = 0; i < numWall && !colisao; i++) { //COLIDINDO COM WALL//
        colisao = collision(rR, rRw[i], -vel * potionvel, 0);
      }
      for(int i = 0; i < animalsmax && !colisao; i++) {
        colisao = collision(rR, animals[i].rR, -vel * potionvel, 0);
        if(colisao) {
          xe = 0; xd = 0; yc = 0; yb = 0;
        }
      }
      for(int i = 0; i < npcmax && !colisao; i++) {
        colisao = collision(rR, npc[i].rR, -vel * potionvel, 0);
      }

      if(!colisao)
        colisao = collision(rR, anciao.rR, -vel * potionvel, 0);

      if(!colisao)
        colisao = collision(rR, irmao.rR, -vel * potionvel, 0);

      if(!colisao)
          gX -= vel * potionvel;
      colisao = false;
    }

    if(yb == 1) { //  BAIXO //
      for(int i = 0; i < numWall && !colisao; i++) { //COLIDINDO COM WALL//
        colisao = collision(rR, rRw[i], 0, vel * potionvel);
      }
      for(int i = 0; i < animalsmax && !colisao; i++) {
        colisao = collision(rR, animals[i].rR, 0, vel * potionvel);
        if(colisao) {
          xe = 0; xd = 0; yc = 0; yb = 0;
        }
      }
      for(int i = 0; i < npcmax && !colisao; i++) {
        colisao = collision(rR, npc[i].rR, 0, vel * potionvel);
      }

      if(!colisao)
        colisao = collision(rR, anciao.rR, 0, vel * potionvel);

      if(!colisao)
        colisao = collision(rR, irmao.rR,0, vel * potionvel);

      if(!colisao)
          gY += vel * potionvel;

      colisao = false;
    }
    if(yc == -1) { // CIMA //
      for(int i = 0; i < numWall && !colisao; i++) { //COLIDINDO COM WALL//
        colisao = collision(rR, rRw[i], 0, -vel * potionvel);
      }
      for(int i = 0; i < animalsmax && !colisao; i++) {
        colisao = collision(rR, animals[i].rR, 0, -vel * potionvel);
        if(colisao) {
          xe = 0; xd = 0; yc = 0; yb = 0;
        }
      }
      for(int i = 0; i < npcmax && !colisao; i++) {
        colisao = collision(rR, npc[i].rR, 0, -vel * potionvel);
      }

      if(!colisao)
        colisao = collision(rR, irmao.rR,0,-vel * potionvel);

      if(!colisao)
        colisao = collision(rR, anciao.rR, 0, -vel * potionvel);


      if(!colisao)
          gY -= vel * potionvel;
      colisao = false; 
    }
  }
}
bool collision(SDL_Rect r1, SDL_Rect r2, int velocidadex, int velocidadey) {
  r1.x += velocidadex;
  r1.y += velocidadey;
  if( r1.x + r1.w > r2.x && r2.x + r2.w > r1.x &&
    r1.y + r1.h > r2.y && r2.y + r2.h > r1.y) {
    return true;
  }
  return false;
}

bool renderizar(void) {
  static SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
  static SDL_RendererFlip flipv = SDL_FLIP_VERTICAL;
  static const int framemaximumexplosion = 18;
  //RECT CAMERA//
  if(rRcam.x < 0) {
    rRcam.x = 0;
  }
  if(rRcam.y < 0){
    rRcam.y = 0;
  }
  if(rRcam.x + rRcam.w >= 6360) {
    rRcam.x = mapw - 640;
  }
  if(rRcam.y + rRcam.h >= 2880) {
    rRcam.y = maph - 400;
  } 
  // HUD configs //
      //heart//
  SDL_Rect sH = {0,11 * book.life,43,11};
  rH.x = 10; rH.y = 10; rH.w = 86 ;rH.h = 22;
  
  //RECT do Wall//
  SDL_Rect sRw = {0,0,32,32};
  renderizarparedes();
  //Renderizar mapas e acoes//
  SDL_RenderClear(render);
  //MAPA//
  SDL_RenderCopy(render, mapTex, &rRcam, NULL);
  //objetos//
  //rect dos objetos//
  //cajado//
  //RENDER DO WALL//
  for(int i = 0; i < numWall; i++)
    SDL_RenderCopy(render, wallTex, &sRw, &rRw[i]);

  for(int i = 0; i < animalsmax; i++) {
    animationAnimals(&animals[i], rRcam);
    if(animals[i].type == 1) {
      if(animals[i].sentido == 4) 
      {
        SDL_RenderCopyEx(render, dog1Tex, &animals[i].sR, &animals[i].rR, 0, NULL, flip);
      }
      else 
      {
        SDL_RenderCopy(render, dog1Tex, &animals[i].sR, &animals[i].rR);
      }
    }
    if(animals[i].type == 2) {
      if(animals[i].sentido == 4) 
      {
        SDL_RenderCopyEx(render, cat1Tex, &animals[i].sR, &animals[i].rR, 0, NULL, flip);
      }
      else 
      {
        SDL_RenderCopy(render, cat1Tex, &animals[i].sR, &animals[i].rR);
      }
    }
  }
  for(int i = 0; i < npcmax; i++) {
    NPCmechanic(&npc[i], rRcam, rR);
    if(npc[i].sentido == 2)
      SDL_RenderCopy(render, npcTex, &npc[i].sR, &npc[i].rR);
    else
      SDL_RenderCopyEx(render, npcTex, &npc[i].sR, &npc[i].rR, 0, NULL, flip);
  }

  NPCmechanic(&irmao, rRcam, rR);
    if(irmao.sentido == 2)
      SDL_RenderCopy(render, npcTex, &irmao.sR, &irmao.rR);
    else
      SDL_RenderCopyEx(render, npcTex, &irmao.sR, &irmao.rR, 0, NULL, flip);

  NPCmechanic(&anciao, rRcam, rR);
    if(anciao.sentido == 2)
      SDL_RenderCopy(render, npcTex, &anciao.sR, &anciao.rR);
    else
      SDL_RenderCopyEx(render, npcTex, &anciao.sR, &anciao.rR, 0, NULL, flip);
  
  renderizarBaus();

  // PORTAL //
  sPortal.x = 0; sPortal.y = 0; sPortal.w = 32; sPortal.h = 32;
  rPortal[0].x = 928 - rRcam.x; rPortal[0].y = 324 - rRcam.y;
  rPortal[0].w = 35; rPortal[0].h = 35;
  rPortal[1].x = 3683 - rRcam.x; rPortal[1].y = 504 - rRcam.y;
  rPortal[1].w = 51; rPortal[1].h = 70;

  SDL_RenderCopy(render, portalTex, &sPortal, &rPortal[0]);
  if(!cristal[0].ativo)
    SDL_RenderCopy(render, portalTex, &sPortal, &rPortal[1]);
  // CAJADOZADA //
  if(cajado) {
    static double angle;
    cajadoAnimated(&rR, &centerstaff, &mouse, gJanela, &angle);
    //centerstaff.x = gX;
    //centerstaff.y = gY;
    angle += 90;
    staff.rR.w = 8 * 1.2;
    staff.rR.h = 30 * 1.2;
    staff.rR.x = rR.x + rR.w/2;
    staff.rR.y = rR.y + rR.h/2;
    SDL_RenderCopyEx(render, cajadoTex, &staff.sR, &staff.rR, angle, &centerstaff, flipv);
    //SDL_RenderCopy(render, cajadoTex, &staff.sR, &staff.rR);
  }


  //MOVIMENT DO PLAYER//
  playerAnimated(&rR, &sR, &rRcam, &gX, &gY, gJanela, &mouse);

  //MOVIMENT DO PLAYER//
  if(invencible > 0) {
    playerAnimatedDamage(&invencible, playerTex);
  }
  else {
    SDL_SetTextureAlphaMod(playerTex, 255);
  }

  if(mouse.x <= rR.x + (rR.w/2)) {
      SDL_RenderCopyEx(render, playerTex, &sR, &rR, 0, NULL, flip);
  }
  else {
    SDL_RenderCopy(render, playerTex, &sR, &rR);
  }
  projsR.x = 62; projsR.y = 2; projsR.w = 14; projsR.h = 14;
  SDL_RenderCopy(render, projTex, &projsR, &rProjetil);

  //projetil de magia//
  if(!projetilstop)
    SDL_RenderCopy(render, mageTex, &mage[0].sRp, &rProjetil);
    // meat //
  for(int j = 0; j < meatboxMobs; j++) {
    // se ele ta com -1 significa que eu vou explodir ele //
    if(meatbox[j].life <= -1 && meatbox[j].morrer == 0) {
      //printf("CAIAQ\n");
      explosionMobs(&meatbox[j].x, &meatbox[j].y, &meatbox[j].rR, &explodir, &rRcam);
      explodir.sR.x = 0; explodir.sR.x = 0; 
      explodir.sR.w = 32; explodir.sR.h = 32;
      meatbox[j].morrer += meatbox[j].morrer + 1;
      SDL_RenderCopy(render, explodirTex, &explodir.sR, &explodir.rR);
      Mix_PlayChannel(6, killenemys, 0);
    }
    else if(meatbox[j].life <= -1 && meatbox[j].morrer <= framemaximumexplosion) {
      //printf("-TOAQ %i\n", meatbox[j].morrer);
      animarexplosaodeMob(&meatbox[j].morrer, &explodir, rRcam);
      explodir.rR.x = explodir.x - rRcam.x;
      explodir.rR.y = explodir.y - rRcam.y;
      SDL_RenderCopy(render, explodirTex, &explodir.sR, &explodir.rR);
    }
    if(meatbox[j].life <= -1 && meatbox[j].morrer > framemaximumexplosion)
      meatbox[j].life--;
    // isolando esse arrumbado //
    if(meatbox[j].life < 0) {
      meatbox[j].x = -800;
      meatbox[j].y = -800;
    }
    meatboxAnimated(&meatbox[j], &rRcam);
    if(meatbox[j].dir)
      SDL_RenderCopy(render, meatboxTex, &meatbox[j].sR, &meatbox[j].rR);
    else {
      SDL_RenderCopyEx(render, meatboxTex, &meatbox[j].sR, &meatbox[j].rR, 0, NULL, flip);
    }
  }




  // BIG BOSS //
  if(bigboss[0].life <= -1 && bigboss[0].morrer == 0) {
      //printf("CAIAQ\n");
      explosionMobs(&bigboss[0].x, &bigboss[0].y, &bigboss[0].rR, &explodir, &rRcam);
      explodir.sR.x = 0; explodir.sR.x = 0; 
      explodir.sR.w = 32; explodir.sR.h = 32;
      bigboss[0].morrer += bigboss[0].morrer + 1;
      SDL_RenderCopy(render, explodirTex, &explodir.sR, &explodir.rR);
      Mix_PlayChannel(6, killenemys, 0);
    }
    else if(bigboss[0].life <= -1 && bigboss[0].morrer <= framemaximumexplosion) {
      //printf("-TOAQ %i\n", meatbox[j].morrer);
      animarexplosaodeMob(&bigboss[0].morrer, &explodir, rRcam);
      explodir.rR.x = explodir.x - rRcam.x;
      explodir.rR.y = explodir.y - rRcam.y;
      SDL_RenderCopy(render, explodirTex, &explodir.sR, &explodir.rR);
    }
    if(bigboss[0].life <= -1 && bigboss[0].morrer > framemaximumexplosion)
      bigboss[0].life--;
    // isolando esse arrumbado //
    if(bigboss[0].life < 0) {
      bigboss[0].x = -800;
      bigboss[0].y = -800;
    }

    for(int i = 0; i < 8; i++) 
    {
      SDL_RenderCopy(render, mageTex, &mage[0].sRp, &bigboss[0].rRp[i]);
    }


    bigBossAnimated(&bigboss[0], &rRcam);
    if(bigboss[0].dir) {
      SDL_RenderCopy(render, bigbossTex, &bigboss[0].sR, &bigboss[0].rR);
    }
    else {
      SDL_RenderCopyEx(render, bigbossTex, &bigboss[0].sR, &bigboss[0].rR, 0, NULL, flip);
    }





  // animar o ogro //
  for(int j = 0; j < ogreMobs; j++) {
     if(ogre[j].life <= -1 && ogre[j].morrer == 0) {
      //printf("CAIAQ\n");
      explosionMobs(&ogre[j].x, &ogre[j].y, &ogre[j].rR, &explodir, &rRcam);
      explodir.sR.x = 0; explodir.sR.x = 0; 
      explodir.sR.w = 32; explodir.sR.h = 32;
      ogre[j].morrer += ogre[j].morrer + 1;
      SDL_RenderCopy(render, explodirTex, &explodir.sR, &explodir.rR);
      Mix_PlayChannel(6, killenemys, 0);
    }
    else if(ogre[j].life <= -1 && ogre[j].morrer <= framemaximumexplosion) {
      //printf("-TOAQ %i\n", meatbox[j].morrer);
      animarexplosaodeMob(&ogre[j].morrer, &explodir, rRcam);
      explodir.rR.x = explodir.x - rRcam.x;
      explodir.rR.y = explodir.y - rRcam.y;
      SDL_RenderCopy(render, explodirTex, &explodir.sR, &explodir.rR);
    }
    if(ogre[j].life <= -1 && ogre[j].morrer > framemaximumexplosion)
      ogre[j].life--;
    // isolando esse arrumbado //
    if(ogre[j].life < 0) {
      ogre[j].x = -800;
      ogre[j].y = -800;
    }
    //JOGAR PRA LONGE //
    ogreAnimated(&ogre[j], &rRcam);

    if(ogre[j].dir)
      SDL_RenderCopy(render, ogreTex, &ogre[j].sR, &ogre[j].rR);
    else {
      SDL_RenderCopyEx(render, ogreTex, &ogre[j].sR, &ogre[j].rR, 0, NULL, flip);
    }
  }
  // MAGE //
  for(int i = 0; i < mageMobs; i++) {
      if(mage[i].life <= -1 && mage[i].morrer == 0) {
      //printf("CAIAQ\n");
      explosionMobs(&mage[i].x, &mage[i].y, &mage[i].rR, &explodir, &rRcam);
      explodir.sR.x = 0; explodir.sR.x = 0; 
      explodir.sR.w = 32; explodir.sR.h = 32;
      mage[i].morrer += mage[i].morrer + 1;
      SDL_RenderCopy(render, explodirTex, &explodir.sR, &explodir.rR);
      Mix_PlayChannel(6, killenemys, 0);
    }
    else if(mage[i].life <= -1 && mage[i].morrer <= framemaximumexplosion) {
      //printf("-TOAQ %i\n", meatbox[j].morrer);
      animarexplosaodeMob(&mage[i].morrer, &explodir, rRcam);
      explodir.rR.x = explodir.x - rRcam.x;
      explodir.rR.y = explodir.y - rRcam.y;
      SDL_RenderCopy(render, explodirTex, &explodir.sR, &explodir.rR);
    }
    if(mage[i].life <= -1 && mage[i].morrer > framemaximumexplosion)
      mage[i].life--;
    // isolando esse arrumbado //
    if(mage[i].life < 0) {
      mage[i].x = -800;
      mage[i].y = -800;
    }

    mageAnimated(&mage[i], &rRcam);
    SDL_RenderCopy(render, mageTex, &mage[i].sRp, &mage[i].rRp);

    if(mage[i].dir)
       SDL_RenderCopy(render, mageTex, &mage[i].sR, &mage[i].rR);
    else {
      SDL_RenderCopyEx(render, mageTex, &mage[i].sR, &mage[i].rR, 0, NULL, flip);
    }
  }
  for(int i=0; i < cristalQuantidade; i++) {
    cristalAnimated(&cristal[i], cristalTex, rRcam);
    SDL_RenderCopy(render, cristalTex, &cristal[i].sR, &cristal[i].rR);
  }
  //iluminação e tal//
   SDL_RenderCopy(render, mapTex2, &rRcam, NULL);

  if(portao.contador < 96) {
    SDL_RenderCopy(render, portaoTex, &portao.sR, &portao.rR);
  }

            //HUD//
  SDL_RenderCopy(render, heartTex, &sH, &rH);
  //renderizarMiniBoss();
  // POTIONS //
  if(book.ativo) {
    sprintf(numerodepocoes, "%.2d", book.potion.cura);
    alterarfonte(book.potion.cura, huds.rRcura, 2);
    SDL_RenderCopy(render, text[0], NULL, &textRect);
    SDL_RenderCopy(render, HUDTex, &huds.sRcura, &huds.rRcura);

    sprintf(numerodepocoes, "%.2d", book.potion.dano);
    alterarfonte(book.potion.dano, huds.rRdano, 2);
    SDL_RenderCopy(render, text[0], NULL, &textRect);
    SDL_RenderCopy(render, HUDTex, &huds.sRdano, &huds.rRdano);

    sprintf(numerodepocoes, "%.2d", book.potion.velocidade);
    alterarfonte(book.potion.velocidade, huds.rRvel, 2);
    SDL_RenderCopy(render, text[0], NULL, &textRect);
    SDL_RenderCopy(render, HUDTex, &huds.sRvel, &huds.rRvel);

    sprintf(numerodepocoes, "%.3d", book.coins);
    huds.rRcoin.x -= 6;
    alterarfonte(book.coins, huds.rRcoin, 3);
    huds.rRcoin.x += 6;
    SDL_RenderCopy(render, text[0], NULL, &textRect);
    SDL_RenderCopy(render, HUDTex, &huds.sRcoin, &huds.rRcoin);
    
    sprintf(numerodepocoes, "%.3d", book.keys);
    huds.rRkey.x -= 6;
    alterarfonte(book.keys, huds.rRkey, 3);
    huds.rRkey.x += 6;
    SDL_RenderCopy(render, text[0], NULL, &textRect);
    SDL_RenderCopy(render, HUDTex, &huds.sRkey, &huds.rRkey);
    
    sprintf(numerodepocoes, "%.6d", book.pontos);
    huds.rRcoin.x -= 240;
    huds.rRcoin.y -= 10;
    alterarfonte(book.keys, huds.rRcoin, 3);
    huds.rRcoin.x += 240;
    huds.rRcoin.y += 10;
    SDL_RenderCopy(render, text[0], NULL, &textRect);

    sprintf(numerodepocoes, "Pontos");
    huds.rRcoin.x -= 240;
    huds.rRcoin.y -= 22;
    alterarfonte(book.keys, huds.rRcoin, 3);
    huds.rRcoin.x += 240;
    huds.rRcoin.y += 22;
    SDL_RenderCopy(render, text[0], NULL, &textRect);

    renderizarMiniBoss();

    if((!cristal[0].ativo || !cristal[1].ativo || !cristal[2].ativo || !cristal[3].ativo || !cristal[4].ativo || !cristal[5].ativo || 
    !cristal[6].ativo || !cristal[7].ativo) && (killthemall() == 2) && (sala == 3 || sala == 4)) {
      sprintf(numerodepocoes, "OS MONSTROS RENASCEM!");
      huds.rRcoin.x -= 300;
      huds.rRcoin.y += 200;
      textRect.w *= 10;
      textRect.h *= 10;
      alterarfonte(book.keys, huds.rRcoin, 3);
      huds.rRcoin.x += 300;
      huds.rRcoin.y -= 200;
      SDL_RenderCopy(render, text[0], NULL, &textRect);
      textRect.w /= 10;
      textRect.h /= 10;
    }
    //SDL_RenderCopy(render, HUDTex, &huds.sRstaff, &huds.rRstaff);
  }
}
void renderizarBaus(void) {
  for(int i = 0; i < numChest; i++) {
    // atualizando status do rect//
    chest[i].pos.x = chest[i].x - rRcam.x; chest[i].pos.y = chest[i].y - rRcam.y;
    if(chest[i].estado) {
      SDL_RenderCopy(render, chestTex, &sChestF, &chest[i].pos);
    }
    else if(!chest[i].estado)
      SDL_RenderCopy(render, chestTex, &sChestA, &chest[i].pos);
  }
}
void renderizarparedes(void) {
  rRw[0].x = 684 - rRcam.x; rRw[0].y = 297 - rRcam.y; rRw[0].w = 126; rRw[0].h = 31; // ok
  rRw[1].x = 864 - rRcam.x; rRw[1].y = 297 - rRcam.y; rRw[1].w = 106; rRw[1].h = 31; //  ok
  rRw[2].x = 685 - rRcam.x; rRw[2].y = 429 - rRcam.y; rRw[2].w = 52; rRw[2].h = 167; /// ok
  rRw[3].x = 452 - rRcam.x; rRw[3].y = 583 - rRcam.y; rRw[3].w = 195; rRw[3].h = 30; // // ok
  rRw[4].x = 468 - rRcam.x; rRw[4].y = 755 - rRcam.y; rRw[4].w = 164; rRw[4].h = 45; //  ok
  rRw[5].x = 89 - rRcam.x; rRw[5].y = 595 - rRcam.y; rRw[5].w = 145; rRw[5].h = 74; //ok
  rRw[6].x = 289 - rRcam.x; rRw[6].y = 37 - rRcam.y; rRw[6].w = 107; rRw[6].h = 58; //  ok
  rRw[7].x = 760 - rRcam.x; rRw[7].y = 0 - rRcam.y; rRw[7].w = 320; rRw[7].h = 80; //   ok
  rRw[8].x = 686 - rRcam.x; rRw[8].y = 0 - rRcam.y; rRw[8].w = 73; rRw[8].h = 95; //  ok
  rRw[9].x = 650 - rRcam.x; rRw[9].y = 0 - rRcam.y; rRw[9].w = 37; rRw[9].h = 113; //  ok
  rRw[10].x = 635 - rRcam.x; rRw[10].y = 0 - rRcam.y; rRw[10].w = 17; rRw[10].h = 128;// ok 
  rRw[11].x = 615 - rRcam.x; rRw[11].y = 0 - rRcam.y; rRw[11].w = 18; rRw[11].h = 149; //ok
  rRw[12].x = 737 - rRcam.x; rRw[12].y = 118 - rRcam.y; rRw[12].w = 110; rRw[12].h = 9; //ok
  rRw[13].x = 542 - rRcam.x; rRw[13].y = 243 - rRcam.y; rRw[13].w = 38; rRw[13].h = 114; //ok 
  rRw[14].x = 524 - rRcam.x; rRw[14].y = 357 - rRcam.y; rRw[14].w = 73; rRw[14].h = 44; // ok 
  rRw[15].x = 597 - rRcam.x; rRw[15].y = 375 - rRcam.y; rRw[15].w = 18; rRw[15].h = 26; // ok
  rRw[16].x = 505 - rRcam.x; rRw[16].y = 395 - rRcam.y; rRw[16].w = 128; rRw[16].h = 39; // ok
  rRw[17].x = 633 - rRcam.x; rRw[17].y = 411 - rRcam.y; rRw[17].w = 37; rRw[17].h = 99; // okss
  rRw[18].x = 669 - rRcam.x; rRw[18].y = 429 - rRcam.y; rRw[18].w = 69; rRw[18].h = 95; // ok
  rRw[19].x = 739 - rRcam.x; rRw[19].y = 447 - rRcam.y; rRw[19].w = 90; rRw[19].h = 77-32; //ok 
  rRw[20].x = 830 - rRcam.x; rRw[20].y = 465 - rRcam.y; rRw[20].w = 96; rRw[20].h = 27; //ok 
  rRw[21].x = 846 - rRcam.x; rRw[21].y = 465 - rRcam.y; rRw[21].w = 80; rRw[21].h = 45; //ok
  rRw[22].x = 306 - rRcam.x; rRw[22].y = 269 - rRcam.y; rRw[22].w = 197; rRw[22].h = 77; //ok
  rRw[23].x = 968 - rRcam.x; rRw[23].y = 465 - rRcam.y; rRw[23].w = 24; rRw[23].h = 95; //ok
  rRw[24].x = 988 - rRcam.x; rRw[24].y = 465 - rRcam.y; rRw[24].w = 91; rRw[24].h = 81; //ok
  rRw[25].x = 1006 - rRcam.x; rRw[25].y = 447 - rRcam.y; rRw[25].w = 73; rRw[25].h = 18; //ok
  rRw[26].x = 1025 - rRcam.x; rRw[26].y = 412 - rRcam.y; rRw[26].w = 54; rRw[26].h = 35; //ok
  rRw[27].x = 1043 - rRcam.x; rRw[27].y = 330 - rRcam.y; rRw[27].w = 36; rRw[27].h = 74; // ok
  rRw[28].x = 1060 - rRcam.x; rRw[28].y = 200 - rRcam.y; rRw[28].w = 20; rRw[28].h = 140; //ok 
  rRw[29].x = 1043 - rRcam.x; rRw[29].y = 183 - rRcam.y; rRw[29].w = 37; rRw[29].h = 17; //ok 
  rRw[30].x = 1025 - rRcam.x; rRw[30].y = 162 - rRcam.y; rRw[30].w = 55; rRw[30].h = 20; //ok
  rRw[31].x = 1007 - rRcam.x; rRw[31].y = 146 - rRcam.y; rRw[31].w = 72; rRw[31].h = 18; //ok
  rRw[32].x = 989 - rRcam.x; rRw[32].y = 127 - rRcam.y; rRw[32].w = 89; rRw[32].h = 19; //ok
  rRw[33].x = 971 - rRcam.x; rRw[33].y = 110 - rRcam.y; rRw[33].w = 111; rRw[33].h = 18; //ok
  rRw[34].x = 539 - rRcam.x; rRw[34].y =243 - rRcam.y; rRw[34].w = 115; rRw[35].h = 23; //ok
  rRw[35].x = 459 - rRcam.x; rRw[35].y = 108 - rRcam.y; rRw[35].w = 244; rRw[35].h = 56; //ok
  rRw[36].x = 468 - rRcam.x; rRw[36].y = 243 - rRcam.y; rRw[36].w = 73; rRw[36].h = 9; //ok
  rRw[37].x = 880 - rRcam.x; rRw[37].y = 154 - rRcam.y; rRw[37].w = 75; rRw[37].h = 9; //ok
  rRw[38].x = 1002 - rRcam.x; rRw[38].y = 239 - rRcam.y; rRw[38].w = 6; rRw[38].h = 30; //ok
  rRw[39].x = 467 - rRcam.x; rRw[39].y = 562 - rRcam.y; rRw[39].w = 146; rRw[39].h = 15; //ok
  rRw[40].x = 449 - rRcam.x; rRw[40].y = 541 - rRcam.y; rRw[40].w = 182; rRw[40].h = 18; //ok
  rRw[41].x = 127 - rRcam.x; rRw[41].y = 465 - rRcam.y; rRw[41].w = 541; rRw[41].h = 76-32; //ok
  rRw[42].x = 485 - rRcam.x; rRw[42].y = 719 - rRcam.y; rRw[42].w = 128; rRw[42].h = 44; //ok
  rRw[43].x = 431 - rRcam.x; rRw[43].y = 791 - rRcam.y; rRw[43].w = 362; rRw[43].h = 27; //ok
  rRw[44].x = 395 - rRcam.x; rRw[44].y = 808 - rRcam.y; rRw[44].w = 415; rRw[44].h = 26; //ok
  rRw[45].x = 377 - rRcam.x; rRw[45].y = 827 - rRcam.y; rRw[45].w = 452; rRw[45].h = 26; //ok
  rRw[46].x = 180 - rRcam.x; rRw[46].y = 847 - rRcam.y; rRw[46].w = 757; rRw[46].h = 56; //ok
  rRw[47].x = 90 - rRcam.x; rRw[47].y = 829 - rRcam.y; rRw[47].w = 90; rRw[47].h = 71; //ok
  rRw[48].x = 0 - rRcam.x; rRw[48].y = 811 - rRcam.y; rRw[48].w = 89; rRw[48].h = 25; //ok
  rRw[49].x = 0 - rRcam.x; rRw[49].y = 793 - rRcam.y; rRw[49].w = 72; rRw[49].h = 26; //ok
  rRw[50].x = 0 - rRcam.x; rRw[50].y = 775 - rRcam.y; rRw[50].w = 54; rRw[50].h = 18; //ok
  rRw[51].x = 0 - rRcam.x; rRw[51].y = 660 - rRcam.y; rRw[51].w = 36; rRw[51].h = 122; //ok
  rRw[52].x = 269 - rRcam.x; rRw[52].y = 596 - rRcam.y; rRw[52].w = 56; rRw[52].h = 3; //ok
  rRw[53].x = 324 - rRcam.x; rRw[53].y = 564 - rRcam.y; rRw[53].w = 19; rRw[53].h = 17; //ok
  rRw[54].x = 343 - rRcam.x; rRw[54].y = 527 - rRcam.y; rRw[54].w = 17; rRw[54].h = 36; //ok
  rRw[55].x = 360 - rRcam.x; rRw[55].y = 490 - rRcam.y; rRw[55].w = 19; rRw[55].h = 38; //ok
  rRw[56].x = 234 - rRcam.x; rRw[56].y = 580 - rRcam.y; rRw[56].w = 35; rRw[57].h = 20; //ok
  rRw[57].x = 918 - rRcam.x; rRw[57].y = 467 - rRcam.y; rRw[57].w = 6; rRw[58].h = 110; //ok
  rRw[58].x = 966 - rRcam.x; rRw[58].y = 467 - rRcam.y; rRw[58].w = 6; rRw[58].h = 131; //ok
  rRw[59].x = 865 - rRcam.x; rRw[59].y = 568 - rRcam.y; rRw[59].w = 59; rRw[59].h = 10; //ok
  rRw[60].x = 1026 - rRcam.x; rRw[60].y = 552 - rRcam.y; rRw[60].w = 52; rRw[60].h = 11; //ok
  rRw[61].x = 1043 - rRcam.x; rRw[61].y = 564 - rRcam.y; rRw[61].w = 37; rRw[61].h = 17; //ok
  rRw[62].x = 935 - rRcam.x; rRw[62].y = 826 - rRcam.y; rRw[62].w = 145; rRw[62].h = 27; //ok
  rRw[63].x = 971 - rRcam.x; rRw[63].y = 809 - rRcam.y; rRw[63].w = 109; rRw[63].h = 26; //ok
  rRw[64].x = 989 - rRcam.x; rRw[64].y = 791 - rRcam.y; rRw[64].w = 92; rRw[64].h = 26; //ok
  rRw[65].x = 1008 - rRcam.x; rRw[65].y = 772 - rRcam.y; rRw[65].w = 72; rRw[65].h = 26; //ok
  rRw[66].x = 1025 - rRcam.x; rRw[66].y = 754 - rRcam.y; rRw[66].w = 55; rRw[66].h = 27; //ok
  rRw[67].x = 1043 - rRcam.x; rRw[67].y = 700 - rRcam.y; rRw[67].w = 37; rRw[67].h = 63; //ok
  rRw[68].x = 1061 - rRcam.x; rRw[68].y = 614 - rRcam.y; rRw[68].w = 19; rRw[68].h = 93; //ok
  rRw[69].x = 624 - rRcam.x; rRw[69].y = 771 - rRcam.y; rRw[69].w = 42; rRw[69].h = 27; //ok
  rRw[70].x = 468 - rRcam.x; rRw[70].y = 694 - rRcam.y; rRw[70].w = 180; rRw[70].h = 9; //ok
  rRw[71].x = 413 - rRcam.x; rRw[71].y = 449 - rRcam.y; rRw[71].w = 73; rRw[71].h = 32; //ok
  rRw[72].x = 467 - rRcam.x; rRw[72].y = 431 - rRcam.y; rRw[72].w = 55; rRw[72].h = 20; //ok
  rRw[73].x = 0 - rRcam.x; rRw[73].y = 430 - rRcam.y; rRw[73].w = 91; rRw[73].h = 26; //ok
  rRw[74].x = 0 - rRcam.x; rRw[74].y = 412 - rRcam.y; rRw[74].w = 72; rRw[74].h = 26; //ok
  rRw[75].x = 0 - rRcam.x; rRw[75].y = 394 - rRcam.y; rRw[75].w = 55; rRw[75].h = 26; //ok
  rRw[76].x = 0 - rRcam.x; rRw[76].y = 340 - rRcam.y; rRw[76].w = 37; rRw[76].h = 62; //ok
  rRw[77].x = 0 - rRcam.x; rRw[77].y = 235 - rRcam.y; rRw[77].w = 19; rRw[77].h = 115; //ok
  rRw[78].x = 18 - rRcam.x; rRw[78].y = 89 - rRcam.y; rRw[78].w = 19; rRw[78].h = 115; //ok
  rRw[79].x = 35 - rRcam.x; rRw[79].y = 35 - rRcam.y; rRw[79].w = 19; rRw[79].h = 115; //ok
  rRw[80].x = 54 - rRcam.x; rRw[80].y = 63 - rRcam.y; rRw[80].w = 19; rRw[80].h = 51; //ok
  rRw[81].x = 72 - rRcam.x; rRw[81].y = 46 - rRcam.y; rRw[81].w = 19; rRw[81].h = 49; //ok
  rRw[82].x = 90 - rRcam.x; rRw[82].y = 28 - rRcam.y; rRw[82].w = 19; rRw[82].h = 51; //ok
  rRw[83].x = 108 - rRcam.x; rRw[83].y = 30 - rRcam.y; rRw[83].w = 55; rRw[83].h = 29; //ok
  rRw[84].x = 162 - rRcam.x; rRw[84].y = 20 - rRcam.y; rRw[84].w = 19; rRw[84].h = 22; //ok
  rRw[85].x = 180 - rRcam.x; rRw[85].y = 2 - rRcam.y; rRw[85].w = 108; rRw[85].h = 22; //ok
  rRw[86].x = 431 - rRcam.x; rRw[86].y = 42 - rRcam.y; rRw[86].w = 18; rRw[86].h = 17; //ok
  rRw[87].x = 450 - rRcam.x; rRw[87].y = 60- rRcam.y; rRw[87].w = 18; rRw[87].h = 17; //ok
  rRw[88].x = 485 - rRcam.x; rRw[88].y = 412 - rRcam.y; rRw[88].w = 18; rRw[88].h = 26; //ok
  rRw[89].x = 36 - rRcam.x; rRw[89].y = 572 - rRcam.y; rRw[89].w = 18; rRw[89].h = 61; //ok
  rRw[90].x = 54 - rRcam.x; rRw[90].y = 538 - rRcam.y; rRw[90].w = 18; rRw[90].h = 61; //ok
  rRw[91].x = 72 - rRcam.x; rRw[91].y = 521 - rRcam.y; rRw[91].w = 18; rRw[91].h = 61; //ok
  rRw[92].x = 90 - rRcam.x; rRw[92].y = 448 - rRcam.y; rRw[92].w = 37; rRw[92].h = 27; //ok
  rRw[93].x = 108 - rRcam.x; rRw[93].y = 195 - rRcam.y; rRw[93].w = 54; rRw[93].h = 44; //ok
  rRw[94].x = 90 - rRcam.x; rRw[94].y = 214 - rRcam.y; rRw[94].w = 18; rRw[94].h = 8; //ok
  rRw[95].x = 162 - rRcam.x; rRw[95].y = 214 - rRcam.y; rRw[95].w = 18; rRw[95].h = 8; //ok
  rRw[96].x = 41 - rRcam.x; rRw[96].y = 282 - rRcam.y; rRw[96].w = 7; rRw[96].h = 3; //ok
  rRw[97].x = 117 - rRcam.x; rRw[97].y = 135 - rRcam.y; rRw[97].w = 36; rRw[97].h = 3; //ok
  rRw[98].x = 293 - rRcam.x; rRw[98].y = 113 - rRcam.y; rRw[98].w = 38; rRw[98].h = 17; //ok
  rRw[99].x = 54 - rRcam.x; rRw[99].y = 63 - rRcam.y; rRw[99].w = 37; rRw[99].h = 1; //ok
  rRw[100].x = 365 - rRcam.x; rRw[100].y = 83 - rRcam.y; rRw[100].w = 27; rRw[100].h = 17; //ok
  rRw[101].x = 148 - rRcam.x; rRw[101].y = 432 - rRcam.y; rRw[101].w = 221; rRw[101].h = 28; //ok
  rRw[102].x = 429 - rRcam.x; rRw[102].y = 339 - rRcam.y; rRw[102].w = 28; rRw[102].h = 31; //ok
  rRw[103].x = 270 - rRcam.x; rRw[103].y = 817 - rRcam.y; rRw[103].w = 34; rRw[103].h = 43; //ok
  rRw[104].x = 357 - rRcam.x; rRw[104].y = 348 - rRcam.y; rRw[104].w = 23; rRw[104].h = 17; //ok
  rRw[105].x = 199 - rRcam.x; rRw[105].y = 671 - rRcam.y; rRw[105].w = 33; rRw[105].h = 17; //ok
  rRw[106].x = 93 - rRcam.x; rRw[106].y = 660 - rRcam.y; rRw[106].w = 30; rRw[106].h = 16; //ok
  rRw[107].x = 118 - rRcam.x; rRw[107].y = 794 - rRcam.y; rRw[107].w = 33; rRw[107].h = 10; //ok
  rRw[108].x = 209 - rRcam.x; rRw[108].y = 829 - rRcam.y; rRw[108].w = 31; rRw[108].h = 11; //ok
  rRw[109].x = 972 - rRcam.x; rRw[109].y = 330 - rRcam.y; rRw[109].w = 19; rRw[109].h = 19; //ok
  rRw[110].x = 770 - rRcam.x; rRw[110].y = 320 - rRcam.y; rRw[110].w = 27; rRw[110].h = 33; //ok
  rRw[111].x = 715 - rRcam.x; rRw[111].y = 321 - rRcam.y; rRw[111].w = 27; rRw[111].h = 30; //ok
  rRw[112].x = 742 - rRcam.x; rRw[112].y = 121 - rRcam.y; rRw[112].w = 28; rRw[112].h = 14; //ok
  rRw[113].x = 814 - rRcam.x; rRw[113].y = 121 - rRcam.y; rRw[113].w = 29; rRw[113].h = 17; //ok
  rRw[114].x = 713 - rRcam.x; rRw[114].y = 272 - rRcam.y; rRw[114].w = 32; rRw[114].h = 10; //ok
  rRw[115].x = 910 - rRcam.x; rRw[115].y = 271 - rRcam.y; rRw[115].w = 33; rRw[115].h = 10; //ok
  rRw[116].x = 911 - rRcam.x; rRw[116].y = 200 - rRcam.y; rRw[116].w = 32; rRw[116].h = 9; //ok
  rRw[117].x = 269 - rRcam.x; rRw[117].y = 315 - rRcam.y; rRw[117].w = 20; rRw[117].h = 60; //ok
  rRw[118].x = 197 - rRcam.x; rRw[118].y = 315 - rRcam.y; rRw[118].w = 20; rRw[118].h = 60; //ok
  rRw[120].x = 144 - rRcam.x; rRw[120].y = 330 - rRcam.y; rRw[120].w = 34; rRw[120].h = 44; //ok
  rRw[121].x = 107 - rRcam.x; rRw[121].y = 315 - rRcam.y; rRw[121].w = 21; rRw[121].h = 61; //ok
  rRw[122].x = 382 - rRcam.x; rRw[122].y = 160 - rRcam.y; rRw[122].w = 10; rRw[122].h = 13; //ok
  rRw[123].x = 396 - rRcam.x; rRw[123].y = 448 - rRcam.y; rRw[123].w = 14; rRw[123].h = 14; //ok
  rRw[124].x = 129 - rRcam.x; rRw[124].y = 447 - rRcam.y; rRw[124].w = 11; rRw[124].h = 15; //ok
  rRw[125].x = 472 - rRcam.x; rRw[125].y = 377 - rRcam.y; rRw[125].w = 10; rRw[125].h = 13; //ok
  rRw[126].x = 418 - rRcam.x; rRw[126].y = 72 - rRcam.y; rRw[126].w = 9; rRw[126].h = 12; //ok
  rRw[127].x = 256 - rRcam.x; rRw[127].y = 701 - rRcam.y; rRw[127].w = 9; rRw[127].h = 13; //ok
  rRw[130].x = 346 - rRcam.x; rRw[130].y = 755 - rRcam.y; rRw[130].w = 9; rRw[130].h = 13; //ok
  rRw[131].x = 401 - rRcam.x; rRw[131].y = 648 - rRcam.y; rRw[131].w = 7; rRw[131].h = 12; //ok
  rRw[132].x = 886 - rRcam.x; rRw[132].y = 413 - rRcam.y; rRw[132].w = 9; rRw[132].h = 13; //ok
  rRw[133].x = 702 - rRcam.x; rRw[133].y = 600 - rRcam.y; rRw[133].w = 18; rRw[133].h = 16; //ok

  rRw[137].x = 669 - rRcam.x; rRw[137].y = 241 - rRcam.y; rRw[137].w = 31; rRw[137].h = 43; //ok
  rRw[138].x = 957 - rRcam.x; rRw[138].y = 241 - rRcam.y; rRw[138].w = 31; rRw[138].h = 43; //ok
  rRw[135].x = 704 - rRcam.x; rRw[135].y = 147 - rRcam.y; rRw[135].w = 28; rRw[135].h = 3; //ok
  rRw[136].x = 840 - rRcam.x; rRw[136].y = 140 - rRcam.y; rRw[136].w = 52; rRw[136].h = 9; //ok

  rRw[139].x = 2442 - rRcam.x; rRw[139].y = 474 - rRcam.y; rRw[139].w = 127; rRw[139].h = 45; //ok
  rRw[140].x = 2448 - rRcam.x; rRw[140].y = 510 - rRcam.y; rRw[140].w = 47; rRw[140].h = 29; //ok
  rRw[141].x = 2615 - rRcam.x; rRw[141].y = 456 - rRcam.y; rRw[141].w = 30; rRw[141].h = 154; //ok
  rRw[142].x = 2441 - rRcam.x; rRw[142].y = 475 - rRcam.y; rRw[142].w = 5; rRw[142].h = 253; //ok
  rRw[143].x = 2225 - rRcam.x; rRw[143].y = 456 - rRcam.y; rRw[143].w = 342; rRw[143].h = 26; //ok
  rRw[144].x = 2640 - rRcam.x; rRw[144].y = 42 - rRcam.y; rRw[144].w = 5; rRw[144].h = 414; //ok
  rRw[145].x = 2224 - rRcam.x; rRw[145].y = 282 - rRcam.y; rRw[145].w = 5; rRw[145].h = 197; //ok
  rRw[146].x = 2231 - rRcam.x; rRw[146].y = 319 - rRcam.y; rRw[146].w = 24; rRw[146].h = 51; //ok
  rRw[147].x = 2226 - rRcam.x; rRw[147].y = 282 - rRcam.y; rRw[147].w = 287; rRw[147].h = 46; //ok
  rRw[148].x = 2327 - rRcam.x; rRw[148].y = 328 - rRcam.y; rRw[148].w = 143; rRw[148].h = 24; //ok
  rRw[149].x = 2614 - rRcam.x; rRw[149].y = 345 - rRcam.y; rRw[149].w = 25; rRw[149].h = 51; //ok
  rRw[150].x = 2548 - rRcam.x; rRw[150].y = 282 - rRcam.y; rRw[150].w = 92; rRw[150].h = 45; //ok
  rRw[151].x = 2441 - rRcam.x; rRw[151].y = 42 - rRcam.y; rRw[151].w = 5; rRw[151].h = 229; //ok
  rRw[152].x = 2441 - rRcam.x; rRw[152].y = 42 - rRcam.y; rRw[152].w = 199; rRw[152].h = 44; //ok
  rRw[153].x = 2618 - rRcam.x; rRw[153].y = 104 - rRcam.y; rRw[153].w = 18; rRw[153].h = 4; //ok
  rRw[154].x = 2576 - rRcam.x; rRw[154].y = 78 - rRcam.y; rRw[154].w = 23; rRw[154].h = 27; //ok
  rRw[155].x = 2447 - rRcam.x; rRw[155].y = 104 - rRcam.y; rRw[155].w = 22; rRw[155].h = 52; //ok
  rRw[156].x = 2469 - rRcam.x; rRw[156].y = 105 - rRcam.y; rRw[156].w = 27; rRw[156].h = 27; //ok
  rRw[157].x = 2496 - rRcam.x; rRw[157].y = 85 - rRcam.y; rRw[157].w = 72; rRw[157].h = 27; //ok

  rRw[158].x = 2570 - rRcam.x; rRw[158].y = 234 - rRcam.y; rRw[158].w = 73; rRw[158].h = 49; //ok
  rRw[159].x = 2442 - rRcam.x; rRw[159].y = 264 - rRcam.y; rRw[159].w = 72; rRw[159].h = 54; //ok
  rRw[160].x = 2544 - rRcam.x; rRw[160].y = 168 - rRcam.y; rRw[160].w = 92; rRw[160].h = 71; //ok
  rRw[161].x = 2548 - rRcam.x; rRw[161].y = 265 - rRcam.y; rRw[161].w = 40; rRw[161].h = 26; //ok
  rRw[162].x = 2446 - rRcam.x; rRw[162].y = 663 - rRcam.y; rRw[162].w = 68; rRw[162].h = 2; //ok
  rRw[163].x = 2548 - rRcam.x; rRw[163].y = 663 - rRcam.y; rRw[163].w = 93; rRw[163].h = 2; //ok
  rRw[164].x = 2548 - rRcam.x; rRw[164].y = 721 - rRcam.y; rRw[164].w = 102; rRw[164].h = 7; //ok
  rRw[165].x = 2441 - rRcam.x; rRw[165].y = 721 - rRcam.y; rRw[165].w = 70; rRw[165].h = 7; //ok
  rRw[166].x = 2496 - rRcam.x; rRw[166].y = 85 - rRcam.y; rRw[166].w = 72; rRw[166].h = 27; //ok
  rRw[167].x = 2512 - rRcam.x; rRw[167].y = 721 - rRcam.y; rRw[167].w = 6; rRw[167].h = 25; //ok
  rRw[168].x = 2517 - rRcam.x; rRw[168].y = 746 - rRcam.y; rRw[168].w = 72; rRw[168].h = 27; //ok
  rRw[169].x = 2517 - rRcam.x; rRw[169].y = 756 - rRcam.y; rRw[169].w = 32; rRw[169].h = 7; //ok
  rRw[170].x = 2548 - rRcam.x; rRw[170].y = 721 - rRcam.y; rRw[170].w = 5; rRw[170].h = 25; //ok
  rRw[171].x = 2496 - rRcam.x; rRw[171].y = 85 - rRcam.y; rRw[171].w = 72; rRw[171].h = 27; //ok

  rRw[172].x = 2447 - rRcam.x; rRw[172].y = 577 - rRcam.y; rRw[172].w = 48; rRw[172].h = 47; //ok
  rRw[173].x = 2525 - rRcam.x; rRw[173].y = 577 - rRcam.y; rRw[173].w = 120; rRw[173].h = 24; //ok
  rRw[174].x = 2590 - rRcam.x; rRw[174].y = 344- rRcam.y; rRw[174].w = 24; rRw[174].h = 28; //ok
  rRw[175].x = 2568 - rRcam.x; rRw[175].y = 345 - rRcam.y; rRw[175].w = 21; rRw[175].h = 3; //ok
  rRw[176].x = 1463 - rRcam.x; rRw[176].y = 489 - rRcam.y; rRw[176].w = 68; rRw[176].h = 3; //ok
  rRw[177].x = 1564 - rRcam.x; rRw[177].y = 489 - rRcam.y; rRw[177].w = 88; rRw[177].h = 3; //ok
  rRw[178].x = 1561 - rRcam.x; rRw[178].y = 554 - rRcam.y; rRw[178].w = 96; rRw[178].h = 24; //ok
  rRw[179].x = 1462 - rRcam.x; rRw[179].y = 554 - rRcam.y; rRw[179].w = 72; rRw[179].h = 24; //ok
  rRw[180].x = 1529 - rRcam.x; rRw[180].y = 578 - rRcam.y; rRw[180].w = 36; rRw[180].h = 24; //ok
  rRw[181].x = 1439 - rRcam.x; rRw[181].y = 66 - rRcam.y; rRw[181].w = 23; rRw[181].h = 488; //ok
  rRw[182].x = 1656 - rRcam.x; rRw[182].y = 66 - rRcam.y; rRw[182].w = 23; rRw[182].h = 488; //ok
  rRw[183].x = 1457 - rRcam.x; rRw[183].y = 66 - rRcam.y; rRw[183].w = 203; rRw[183].h = 45; //ok
  rRw[184].x = 1457 - rRcam.x; rRw[184].y = 288 - rRcam.y; rRw[184].w = 126; rRw[184].h = 66; //ok
  rRw[185].x = 1631 - rRcam.x; rRw[185].y = 288 - rRcam.y; rRw[185].w = 27; rRw[185].h = 188; //ok
  rRw[186].x = 1540 - rRcam.x; rRw[186].y = 407 - rRcam.y; rRw[186].w = 122; rRw[186].h = 21; //ok
  rRw[187].x = 1462 - rRcam.x; rRw[187].y = 407 - rRcam.y; rRw[187].w = 49; rRw[187].h = 66; //ok
  rRw[188].x = 1462 - rRcam.x; rRw[188].y = 355 - rRcam.y; rRw[188].w = 49; rRw[188].h = 100; //ok
  rRw[189].x = 1632 - rRcam.x; rRw[189].y = 255 - rRcam.y; rRw[189].w = 26; rRw[189].h = 49; //ok
  rRw[190].x = 1559 - rRcam.x; rRw[190].y = 192 - rRcam.y; rRw[190].w = 97; rRw[190].h = 49; //ok
  rRw[191].x = 1586 - rRcam.x; rRw[191].y = 192 - rRcam.y; rRw[191].w = 19; rRw[191].h = 53; //ok
  rRw[192].x = 1461 - rRcam.x; rRw[192].y = 129 - rRcam.y; rRw[192].w = 29; rRw[192].h = 159; //ok
  rRw[193].x = 1461 - rRcam.x; rRw[193].y = 114 - rRcam.y; rRw[193].w = 123; rRw[193].h = 24; //ok
  rRw[194].x = 1461 - rRcam.x; rRw[194].y = 114 - rRcam.y; rRw[194].w = 49; rRw[194].h = 49; //ok
  rRw[195].x = 143 - rRcam.x; rRw[195].y = 670 - rRcam.y; rRw[195].w = 20; rRw[195].h = 1; //5
  rRw[196].x = 396 - rRcam.x; rRw[196].y = 342 - rRcam.y; rRw[196].w = 18; rRw[196].h = 6; //22
  rRw[197].x = 928 - rRcam.x; rRw[197].y = 297 - rRcam.y; rRw[197].w = 35; rRw[197].h = 35; //  ok
  rRw[198].x = 3000 - 4 - rRcam.x; rRw[198].y = 2 - rRcam.y; rRw[198].w = 364; rRw[198].h = 1210; //SPACE DIREITA-- //
  rRw[199].x = 3000 + 359 - rRcam.x; rRw[199].y = 459 - rRcam.y; rRw[199].w = 96; rRw[199].h = 120; // TORRE CASTELO DIREITA CIMA //
  rRw[200].x = 3000 + 360 - rRcam.x; rRw[200].y = 572 - rRcam.y; rRw[200].w = 72; rRw[200].h = 318; // WALL //
  rRw[201].x = 3000 + 359 - rRcam.x; rRw[201].y = 886 - rRcam.y; rRw[201].w = 99; rRw[201].h = 167; // WALL BAIXO  = SALA 1//
  rRw[202].x = 3000 + 453 - rRcam.x; rRw[202].y = 909 - rRcam.y; rRw[202].w = 751; rRw[202].h = 126; // WALL // 
  rRw[203].x = 3000 + 768 - rRcam.x; rRw[203].y = 887 - rRcam.y; rRw[203].w = 96; rRw[203].h = 166; // WALL //  
  rRw[204].x = 3000 + 1199 - rRcam.x; rRw[204].y = 888 - rRcam.y; rRw[204].w = 98; rRw[204].h = 165; // WALL //  
  rRw[205].x = 3000 + 1224 - rRcam.x; rRw[205].y = 499 - rRcam.y; rRw[205].w = 49; rRw[205].h = 438; // wALL //  
  rRw[206].x = 3000 + 1201 - rRcam.x; rRw[206].y = 385 - rRcam.y; rRw[206].w = 95; rRw[206].h = 132; // WALL //  
  rRw[207].x = 3000 + 1122 - rRcam.x; rRw[207].y = 380 - rRcam.y; rRw[207].w = 80; rRw[207].h = 140; // UAU //  
  rRw[208].x = 3000 + 1057 - rRcam.x; rRw[208].y = 407 - rRcam.y; rRw[208].w = 90; rRw[208].h = 110; // WALL WALL // 
  rRw[209].x = 3000 + 815 - rRcam.x; rRw[209].y = 519 - rRcam.y; rRw[209].w = 242; rRw[209].h = 33; // UAU WALL // 
  rRw[210].x = 3000 + 733 - rRcam.x; rRw[210].y = 516 - rRcam.y; rRw[210].w = 83; rRw[210].h = 30; // TORRE //
  rRw[211].x = 3000 + 600 - rRcam.x; rRw[211].y = 519 - rRcam.y; rRw[211].w = 83; rRw[211].h = 30; // TORRE // 
  rRw[212].x = 3000 + 455 - rRcam.x; rRw[212].y = 519 - rRcam.y; rRw[212].w = 216; rRw[212].h = 33; // TORRE // 
  rRw[213].x = 3000 + 1191 - rRcam.x; rRw[213].y = 309 - rRcam.y; rRw[213].w = 104; rRw[213].h = 84; // PAREDE // 
  rRw[214].x = 3000 + 1247 - rRcam.x; rRw[214].y = 44 - rRcam.y; rRw[214].w = 109; rRw[214].h = 204; // PAREDE //
  rRw[215].x = 3000 + 1267 - rRcam.x; rRw[215].y = 234 - rRcam.y; rRw[215].w = 91; rRw[215].h = 76; // PAREDE//
  rRw[216].x = 3000 + 359 - rRcam.x; rRw[216].y = 3 - rRcam.y; rRw[216].w = 978; rRw[216].h = 45; // caixotes = sala 2//
  //intervalo//
  rRw[217].x = 3000 + 457 - rRcam.x; rRw[217].y = 3 - rRcam.y; rRw[217].w = 71; rRw[217].h = 139; //sala 2 da dg - agua//
  rRw[218].x = 3000 + 473 - rRcam.x; rRw[218].y = 280 - rRcam.y; rRw[218].w = 55; rRw[218].h = 56; //sala 2 da dg - agua//
  rRw[219].x = 3000 + 460 - rRcam.x; rRw[219].y = 330 - rRcam.y; rRw[219].w = 20; rRw[219].h = 52; //sala 2 da dg - agua//
  rRw[220].x = 3000 + 408 - rRcam.x; rRw[220].y = 215 - rRcam.y; rRw[220].w = 8; rRw[220].h = 154; //sala 2 da dg - agua//
  rRw[227].x = 3000 + 408 - rRcam.x; rRw[227].y = 215 - rRcam.y; rRw[227].w = 119; rRw[227].h = 7; //sala 2 da dg - agua//
  rRw[228].x = 3000 + 408 - rRcam.x; rRw[228].y = 215 - rRcam.y; rRw[228].w = 119; rRw[228].h = 7; //sala 2 da dg - agua// 
  rRw[229].x = 3000 + 519 - rRcam.x; rRw[229].y = 215 - rRcam.y; rRw[229].w = 8; rRw[229].h = 69; //sala 2 da dg - agua//
  rRw[221].x = 3000 + 913 - rRcam.x; rRw[221].y = 9 - rRcam.y; rRw[221].w = 71; rRw[221].h = 120; //sala 2 da dg - agua//
  rRw[222].x = 3000 + 914 - rRcam.x; rRw[222].y = 113 - rRcam.y; rRw[222].w = 332; rRw[222].h = 20; //sala 2 da dg - agua//
  rRw[223].x = 3000 + 914 - rRcam.x; rRw[223].y = 113 - rRcam.y; rRw[223].w = 101; rRw[223].h = 44; //sala 2 da dg - agua//
  rRw[224].x = 3000 + 769 - rRcam.x; rRw[224].y = 165 - rRcam.y; rRw[224].w = 10; rRw[224].h = 134; //sala 2 da dg - agua//
  rRw[225].x = 3000 + 769 -rRcam.x; rRw[225].y = 165 -rRcam.y; rRw[225].w = 114; rRw[225].h = 14; //bau da primeira parte//
  rRw[226].x = 3000 + 878 -rRcam.x; rRw[226].y = 165 -rRcam.y; rRw[226].w = 10; rRw[226].h = 138; //bau da primeira parte//

  //portao //
  if(portao.contador < 96) {
  rRw[228].x = portao.x -rRcam.x; rRw[228].y = portao.y -rRcam.y; rRw[228].w = 48 * 1.5; rRw[228].h = 48 * 1.5; //bau da primeira parte//
  }
  else {
    rRw[228].x = -500 -rRcam.x; rRw[228].y = -500 -rRcam.y; rRw[228].w = 48 * 1.5; rRw[228].h = 48 * 1.5; //bau da primeira parte//
  }
  //rRw[229].x = 765 -rRcam.x; rRw[229].y = 281 -rRcam.y; rRw[229].w = 27; rRw[229].h = 26; //bau da primeira parte//

  //printf("%d %d\n", portao.x, portao.y);
  rRw[247].x = 3000 + 456 -rRcam.x; rRw[247].y = 8 -rRcam.y; rRw[247].w = 72; rRw[247].h = 100; //bau da primeira parte//
  rRw[248].x = 3000 + 473 -rRcam.x; rRw[248].y = 279 -rRcam.y; rRw[248].w = 56; rRw[248].h = 58; //bau da primeira parte//
  rRw[249].x = 3000 + 406 -rRcam.x; rRw[249].y = 218 -rRcam.y; rRw[249].w = 12; rRw[249].h = 156; //bau da primeira parte//
  rRw[233].x = 3000 + 406 -rRcam.x; rRw[233].y = 324 -rRcam.y; rRw[233].w = 20; rRw[233].h = 60; //bau da primeira parte//
  rRw[234].x = 3000 + 1072 -rRcam.x; rRw[234].y = 209 -rRcam.y; rRw[234].w = 176; rRw[234].h = 53; //bau da primeira parte//
  rRw[235].x = 3000 + 1060 -rRcam.x; rRw[235].y = 254 -rRcam.y; rRw[235].w = 21; rRw[235].h = 53; //bau da primeira parte//
  rRw[236].x = 3000 + 1008 -rRcam.x; rRw[236].y = 254 -rRcam.y; rRw[236].w = 20; rRw[236].h = 53; //bau da primeira parte//
  rRw[237].x = 3000 + 1075 -rRcam.x; rRw[237].y = 207 -rRcam.y; rRw[237].w = 189; rRw[237].h = 30; //bau da primeira parte//
  rRw[238].x = 3000 + 1007 -rRcam.x; rRw[238].y = 157 -rRcam.y; rRw[238].w = 11; rRw[238].h = 144; //bau da primeira parte//
  rRw[239].x = 3000 + 479 -rRcam.x; rRw[239].y = 562 -rRcam.y; rRw[239].w = 10; rRw[239].h = 153; //bau da primeira parte//
  rRw[240].x = 3000 + 479 -rRcam.x; rRw[240].y = 686 -rRcam.y; rRw[240].w = 24; rRw[240].h = 29; //bau da primeira parte//
  rRw[241].x = 3000 + 532 -rRcam.x; rRw[241].y = 607 -rRcam.y; rRw[241].w = 24; rRw[241].h = 48; // CRISTAIS //
  rRw[242].x = 3000 + 1033 -rRcam.x; rRw[242].y = 173 -rRcam.y; rRw[242].w = 24; rRw[242].h = 48; // CRISTAIS//
  rRw[243].x = 3000 + 820 -rRcam.x; rRw[243].y = 183 -rRcam.y; rRw[243].w = 24; rRw[243].h = 48; // CRISTAIS//
  rRw[244].x = 3000 + 480 -rRcam.x; rRw[244].y = 202 -rRcam.y; rRw[244].w = 24; rRw[244].h = 48; // CRISTAIS//
  rRw[245].x = 3000 + 590 -rRcam.x; rRw[245].y = 574 -rRcam.y; rRw[245].w = 11; rRw[245].h = 92; // DFGGSF//
  rRw[246].x = 3000 + 684 -rRcam.x; rRw[246].y = 136 -rRcam.y; rRw[246].w = 48; rRw[246].h = 28; // DFGGSF//
  rRw[250].x = 5080 -rRcam.x; rRw[250].y = 2817 -rRcam.y; rRw[250].w = 305; rRw[250].h = 62; // DFGGSF//
  rRw[251].x = 4935 -rRcam.x; rRw[251].y = 2673 -rRcam.y; rRw[251].w = 145; rRw[251].h = 143; // DFGGSF//
  rRw[252].x = 5385 -rRcam.x; rRw[252].y = 2673 -rRcam.y; rRw[252].w = 145; rRw[252].h = 143; // DFGGSF//  
  rRw[253].x = 5529 -rRcam.x; rRw[253].y = 2601 -rRcam.y; rRw[253].w = 74; rRw[253].h = 73; // DFGGSF//
  rRw[254].x = 4856 -rRcam.x; rRw[254].y = 2268 -rRcam.y; rRw[254].w = 80; rRw[254].h = 407; // DFGGSF//
  rRw[255].x = 5600 -rRcam.x; rRw[255].y = 1938 -rRcam.y; rRw[255].w = 115; rRw[255].h = 663; // DFGGSF//
  rRw[256].x = 5576 -rRcam.x; rRw[256].y = 2072 -rRcam.y; rRw[256].w = 38; rRw[256].h = 99; // DFGGSF//  
  rRw[257].x = 5529 -rRcam.x; rRw[257].y = 2168 -rRcam.y; rRw[257].w = 75; rRw[257].h = 72; // DFGGSF//
  rRw[258].x = 5552 -rRcam.x; rRw[258].y = 2335 -rRcam.y; rRw[258].w = 58; rRw[258].h = 65-32; // DFGGSF//
  rRw[259].x = 5505 -rRcam.x; rRw[259].y = 2239 -rRcam.y; rRw[259].w = 78; rRw[259].h = 75; // DFGGSF//
  rRw[260].x = 4881 -rRcam.x; rRw[260].y = 2239 -rRcam.y; rRw[260].w = 30; rRw[260].h = 58; // DFGGSF//  
  rRw[261].x = 4847 -rRcam.x; rRw[261].y = 2038 -rRcam.y; rRw[261].w = 40; rRw[261].h = 203; // DFGGSF//
  rRw[262].x = 4848 -rRcam.x; rRw[262].y = 1990 -rRcam.y; rRw[262].w = 63; rRw[262].h = 44; // DFGGSF//
  rRw[263].x = 4790 -rRcam.x; rRw[263].y = 1830 -rRcam.y; rRw[263].w = 157; rRw[263].h = 157; // DFGGSF//
  rRw[264].x = 5121 -rRcam.x; rRw[264].y = 1832 -rRcam.y; rRw[264].w = 601; rRw[264].h = 60; // DFGGSF//  
  rRw[265].x = 5263 -rRcam.x; rRw[265].y = 1891 -rRcam.y; rRw[265].w = 121; rRw[265].h = 24; // DFGGSF//
  rRw[266].x = 5384 -rRcam.x; rRw[266].y = 1882 -rRcam.y; rRw[266].w = 330; rRw[266].h = 57; // DFGGSF//
  rRw[267].x = 4622 -rRcam.x; rRw[267].y = 1807 -rRcam.y; rRw[267].w = 171; rRw[267].h = 26; // DFGGSF//
  rRw[268].x = 4439 -rRcam.x; rRw[268].y = 1784 -rRcam.y; rRw[268].w = 184; rRw[268].h = 46; // DFGGSF//  
  rRw[269].x = 4438 -rRcam.x; rRw[269].y = 0 -rRcam.y; rRw[269].w = 2; rRw[269].h = 2880; // DFGGSF//
  rRw[270].x = 6359 -rRcam.x; rRw[270].y = 0 -rRcam.y; rRw[270].w = 1; rRw[270].h = 2880; // DFGGSF//
  rRw[271].x = 5264 -rRcam.x; rRw[271].y = 2071 -rRcam.y; rRw[271].w = 79; rRw[271].h = 372; // DFGGSF//
  rRw[272].x = 5341 -rRcam.x; rRw[272].y = 2336 -rRcam.y; rRw[272].w = 27; rRw[272].h = 83; // DFGGSF//
  rRw[273].x = 5168 -rRcam.x; rRw[273].y = 2383 -rRcam.y; rRw[273].w = 216; rRw[273].h = 30; // DFGGSF//
  rRw[274].x = 5120 -rRcam.x; rRw[274].y = 2263 -rRcam.y; rRw[274].w = 48; rRw[274].h = 132; // DFGGSF//
  rRw[275].x = 5338 -rRcam.x; rRw[275].y = 2143 -rRcam.y; rRw[275].w = 30; rRw[275].h = 84; // DFGGSF//
  rRw[276].x = 5144 -rRcam.x; rRw[276].y = 2192 -rRcam.y; rRw[276].w = 25; rRw[276].h = 72; // DFGGSF//
  rRw[277].x = 5097 -rRcam.x; rRw[277].y = 2073 -rRcam.y; rRw[277].w = 178; rRw[277].h = 34; // DFGGSF//
  rRw[278].x = 5121 -rRcam.x; rRw[278].y = 2047 -rRcam.y; rRw[278].w = 127; rRw[278].h = 30; // DFGGSF//
  rRw[279].x = 5169 -rRcam.x; rRw[279].y = 2104 -rRcam.y; rRw[279].w = 17; rRw[279].h = 89; // DFGGSF//
  rRw[280].x = 5721 -rRcam.x; rRw[280].y = 1809 -rRcam.y; rRw[280].w = 289; rRw[280].h = 45; // DFGGSF//
  rRw[281].x = 6008 -rRcam.x; rRw[281].y = 1783 -rRcam.y; rRw[281].w = 352; rRw[281].h = 44; // DFGGSF//
  rRw[282].x = 4440 -rRcam.x; rRw[282].y = 1646 -rRcam.y; rRw[282].w = 144; rRw[282].h = 22; // DFGGSF//
  rRw[283].x = 4578 -rRcam.x; rRw[283].y = 1622 -rRcam.y; rRw[283].w = 377; rRw[283].h = 21;// DFGGSF//
  rRw[284].x = 5025 -rRcam.x; rRw[284].y = 1623 -rRcam.y; rRw[284].w = 333; rRw[284].h = 20; // DFGGSF//
  rRw[285].x = 5352 -rRcam.x; rRw[285].y = 1647 -rRcam.y; rRw[285].w = 341; rRw[285].h = 20; // DFGGSF//
  rRw[286].x = 5688 -rRcam.x; rRw[286].y = 1670 -rRcam.y; rRw[286].w = 672; rRw[286].h = 20; // DFGGSF//
  rRw[287].x = 4994 -rRcam.x; rRw[287].y = 1093 -rRcam.y; rRw[287].w = 45; rRw[287].h = 20; // DFGGSF//
  rRw[288].x = 5067 -rRcam.x; rRw[288].y = 1095 -rRcam.y; rRw[288].w = 44; rRw[288].h = 20; // DFGGSF//
  rRw[289].x = 4994 -rRcam.x; rRw[289].y = 989 -rRcam.y; rRw[289].w = 6; rRw[289].h = 110; // DFGGSF//
  rRw[290].x = 4993 -rRcam.x; rRw[290].y = 984 -rRcam.y; rRw[290].w = 119; rRw[290].h = 9; // DFGGSF//
  rRw[291].x = 5104 -rRcam.x; rRw[291].y = 988 -rRcam.y; rRw[291].w = 7; rRw[291].h = 111; // DFGGSF//
  rRw[292].x = 4440 -rRcam.x; rRw[292].y = 926 -rRcam.y; rRw[292].w = 241; rRw[292].h = 22; // DFGGSF//
  rRw[293].x = 4675 -rRcam.x; rRw[293].y = 855 -rRcam.y; rRw[293].w = 232; rRw[293].h = 20; // DFGGSF//
  rRw[294].x = 4952 -rRcam.x; rRw[294].y = 855 -rRcam.y; rRw[294].w = 87; rRw[294].h = 19; // DFGGSF//
  rRw[295].x = 4969 -rRcam.x; rRw[295].y = 857 -rRcam.y; rRw[295].w = 23; rRw[295].h = 22; // DFGGSF//
  rRw[296].x = 5036 -rRcam.x; rRw[296].y = 832 -rRcam.y; rRw[296].w = 28; rRw[296].h = 17; // DFGGSF//
  rRw[297].x = 5059 -rRcam.x; rRw[297].y = 807 -rRcam.y; rRw[297].w = 26; rRw[297].h = 19; // DFGGSF//
  rRw[298].x = 5081 -rRcam.x; rRw[298].y = 687 -rRcam.y; rRw[298].w = 28; rRw[298].h = 17; // DFGGSF//
  rRw[299].x = 5084 -rRcam.x; rRw[299].y = 687 -rRcam.y; rRw[299].w = 195; rRw[299].h = 21; // DFGGSF//
  rRw[300].x = 5083 -rRcam.x; rRw[300].y = 783 -rRcam.y; rRw[300].w = 15; rRw[300].h = 28; // DFGGSF//
  rRw[301].x = 5142 -rRcam.x; rRw[301].y = 783 -rRcam.y; rRw[301].w = 207; rRw[301].h = 15; // DFGGSF//
  rRw[302].x = 5346 -rRcam.x; rRw[302].y = 713 -rRcam.y; rRw[302].w =6; rRw[302].h = 88; // DFGGSF//
  rRw[303].x = 5276 -rRcam.x; rRw[303].y = 663 -rRcam.y; rRw[303].w = 76; rRw[303].h = 21; // DFGGSF//
  rRw[304].x = 5351 -rRcam.x; rRw[304].y = 663 -rRcam.y; rRw[304].w = 216; rRw[304].h = 44; // DFGGSF//
  rRw[305].x = 5401 -rRcam.x; rRw[305].y = 691 -rRcam.y; rRw[305].w = 22; rRw[305].h = 23; // DFGGSF//
  rRw[306].x = 5568 -rRcam.x; rRw[306].y = 663 -rRcam.y; rRw[306].w = 24; rRw[306].h = 25; // DFGGSF//
  rRw[307].x = 4673 -rRcam.x; rRw[307].y = 854 -rRcam.y; rRw[307].w = 7; rRw[307].h = 77; // DFGGSF//
  rRw[308].x = 5081 -rRcam.x; rRw[308].y = 685 -rRcam.y; rRw[308].w = 6; rRw[308].h = 98; // DFGGSF//
  rRw[309].x = 5587 -rRcam.x; rRw[309].y = 589 -rRcam.y; rRw[309].w = 365; rRw[309].h = 46; // DFGGSF//
  rRw[310].x = 5569 -rRcam.x; rRw[310].y = 719 -rRcam.y; rRw[310].w = 7; rRw[310].h = 65; // DFGGSF//
  rRw[311].x = 5952 -rRcam.x; rRw[311].y = 592 -rRcam.y; rRw[311].w = 8; rRw[311].h = 96; // DFGGSF//
  rRw[312].x = 5585 -rRcam.x; rRw[312].y = 634 -rRcam.y; rRw[312].w = 28; rRw[312].h = 17; // DFGGSF//
  rRw[313].x = 5570 -rRcam.x; rRw[313].y = 783 -rRcam.y; rRw[313].w = 274; rRw[313].h = 5; // DFGGSF//
  rRw[314].x = 5811 -rRcam.x; rRw[314].y = 790 -rRcam.y; rRw[314].w = 21; rRw[314].h = 4; // DFGGSF//
  rRw[315].x = 5887 -rRcam.x; rRw[315].y = 783 -rRcam.y; rRw[315].w = 209; rRw[315].h = 6; // DFGGSF//
  rRw[316].x = 6089 -rRcam.x; rRw[316].y = 745 -rRcam.y; rRw[316].w = 8; rRw[316].h = 39; // DFGGSF//
  rRw[317].x = 5952 -rRcam.x; rRw[317].y = 685 -rRcam.y; rRw[317].w = 144; rRw[317].h = 28; // DFGGSF//
  rRw[318].x = 6096 -rRcam.x; rRw[318].y = 687 -rRcam.y; rRw[318].w = 264; rRw[318].h = 44; // DFGGSF//
  rRw[319].x = 5091 -rRcam.x; rRw[319].y = 566 -rRcam.y; rRw[319].w = 104; rRw[319].h = 22; // DFGGSF//
  rRw[320].x = 5242 -rRcam.x; rRw[320].y = 567 -rRcam.y; rRw[320].w = 69; rRw[320].h = 20; // DFGGSF//
  rRw[321].x = 5488 -rRcam.x; rRw[321].y = 518 -rRcam.y; rRw[321].w = 9; rRw[321].h = 76; // DFGGSF//
  rRw[322].x = 5306 -rRcam.x; rRw[322].y = 591 -rRcam.y; rRw[322].w = 191; rRw[322].h = 20; // DFGGSF//
  rRw[323].x = 5491 -rRcam.x; rRw[323].y = 519 -rRcam.y; rRw[323].w = 539; rRw[323].h = 19; // DFGGSF//
  rRw[324].x = 6028 -rRcam.x; rRw[324].y = 613 -rRcam.y; rRw[324].w = 332; rRw[324].h = 20; // DFGGSF//
  rRw[325].x = 6023 -rRcam.x; rRw[325].y = 526 -rRcam.y; rRw[325].w = 10; rRw[325].h = 18; // DFGGSF//
  rRw[326].x = 5490 -rRcam.x; rRw[326].y = 527 -rRcam.y; rRw[326].w = 5; rRw[326].h = 64; // DFGGSF//
  rRw[327].x = 5091 -rRcam.x; rRw[327].y = 484 -rRcam.y; rRw[327].w = 8; rRw[327].h = 80; // DFGGSF//
  rRw[328].x = 5115 -rRcam.x; rRw[328].y = 413 -rRcam.y; rRw[328].w = 8; rRw[328].h = 74; // DFGGSF//
  rRw[329].x = 5135 -rRcam.x; rRw[329].y = 255 -rRcam.y; rRw[329].w = 10; rRw[329].h = 137; // DFGGSF//
  rRw[330].x = 5113 -rRcam.x; rRw[330].y = 136 -rRcam.y; rRw[330].w = 8; rRw[330].h = 121; // DFGGSF//
  rRw[331].x = 5091 -rRcam.x; rRw[331].y = 0 -rRcam.y; rRw[331].w = 7; rRw[331].h = 136; // DFGGSF//
  rRw[332].x = 6021 -rRcam.x; rRw[332].y = 519 -rRcam.y; rRw[332].w = 12; rRw[332].h = 96; // DFGGSF//
  rRw[333].x = 5159 -rRcam.x; rRw[333].y = 571 -rRcam.y; rRw[333].w = 26; rRw[333].h = 23; // DFGGSF//
  rRw[334].x = 5018 -rRcam.x; rRw[334].y = 1099 -rRcam.y; rRw[334].w = 20; rRw[334].h = 20; // DFGGSF//
  rRw[335].x = 4922 -rRcam.x; rRw[335].y = 1623 -rRcam.y; rRw[335].w = 21; rRw[335].h = 22; // DFGGSF//
  rRw[336].x = 5090 -rRcam.x; rRw[336].y = 2112 -rRcam.y; rRw[336].w = 23; rRw[336].h = 5; // DFGGSF//
  rRw[337].x = 4459 -rRcam.x; rRw[337].y = 1433 -rRcam.y; rRw[337].w = 59; rRw[337].h = 29; // DFGGSF//
  rRw[338].x = 4675 -rRcam.x; rRw[338].y = 1505 -rRcam.y; rRw[338].w = 59; rRw[338].h = 29; // DFGGSF//
  rRw[339].x = 5203 -rRcam.x; rRw[339].y = 1145 -rRcam.y; rRw[339].w = 59; rRw[339].h = 29; // DFGGSF//
  rRw[340].x = 5396 -rRcam.x; rRw[340].y = 952 -rRcam.y; rRw[340].w = 59; rRw[340].h = 29; // DFGGSF//
  rRw[341].x = 5563 -rRcam.x; rRw[341].y = 809 -rRcam.y; rRw[341].w = 59; rRw[341].h = 29; // DFGGSF//
  rRw[342 ].x = 5827 -rRcam.x; rRw[342].y = 1289 -rRcam.y; rRw[342].w = 59; rRw[342].h = 29; // DFGGSF//
  rRw[343].x = 5633 -rRcam.x; rRw[343].y = 1505 -rRcam.y; rRw[343].w = 59; rRw[343].h = 29; // DFGGSF//
  rRw[344].x = 6212 -rRcam.x; rRw[344].y = 1529 -rRcam.y; rRw[344].w = 59; rRw[344].h = 29; // DFGGSF//
  rRw[345].x = 6118 -rRcam.x; rRw[345].y = 1265 -rRcam.y; rRw[345].w = 59; rRw[345].h = 29; // DFGGSF//
  rRw[346].x = 6236 -rRcam.x; rRw[346].y = 1240 -rRcam.y; rRw[346].w = 59; rRw[346].h = 29; // DFGGSF//
  rRw[347].x = 5012 -rRcam.x; rRw[347].y = 640 -rRcam.y; rRw[347].w = 59; rRw[347].h = 29; // DFGGSF//
  rRw[348].x = 4483 -rRcam.x; rRw[348].y = 259 -rRcam.y; rRw[348].w = 59; rRw[348].h = 29; // DFGGSF//
  rRw[349].x = 5429 -rRcam.x; rRw[349].y = 1177 -rRcam.y; rRw[349].w = 40; rRw[349].h = 18; // DFGGSF//
  rRw[350].x = 5863 -rRcam.x; rRw[350].y = 1056 -rRcam.y; rRw[350].w = 40; rRw[350].h = 18; // DFGGSF//
  rRw[351].x = 5935 -rRcam.x; rRw[351].y = 817 -rRcam.y; rRw[351].w = 40; rRw[351].h = 18; // DFGGSF//
  rRw[352].x = 4664 -rRcam.x; rRw[352].y = 1106 -rRcam.y; rRw[352].w = 40; rRw[352].h = 18; // DFGGSF//
  rRw[353].x = 4493 -rRcam.x; rRw[353].y = 888 -rRcam.y; rRw[353].w = 40; rRw[353].h = 18; // DFGGSF//
  rRw[354].x = 4781 -rRcam.x; rRw[354].y = 914 -rRcam.y; rRw[354].w = 40; rRw[354].h = 18; // DFGGSF//
  rRw[355].x = 4997 -rRcam.x; rRw[355].y = 145 -rRcam.y; rRw[355].w = 40; rRw[355].h = 18; // DFGGSF//
  rRw[356].x = 6198 -rRcam.x; rRw[356].y = 1034 -rRcam.y; rRw[356].w = 40; rRw[356].h = 18; // DFGGSF//
  rRw[357].x = 4434 -rRcam.x; rRw[357].y = -36 -rRcam.y; rRw[357].w = 1940; rRw[357].h = 36; // DFGGSF//
}
void invencibleF (void) {
  //INVENCIBILIDADE DO JOGADOR APOS A COLISAO COM MOB//
  if(invencible == 1) {
    Mix_PlayChannel(4, damage, 0);
    printf("[Console]Tempo de Invencibilidade Iniciado! %i Vidas!\n",book.life);
    invencible++;
  }
  else if(invencible > 1 && invencible <= 40) {
    invencible++;
  }
  else if(invencible > 40) {
    invencible = 0; 
    printf("[Console]Tempo de Invencibilidade Finalizado!\n");
  }
}
                                                                                                  //CAMERA E IDENTIFICACAO DE SALAS//

void salaAtual()
{
  if(gX >= 0 && gX+rR.w <= 1080 && gY >= 0 && gY+rR.h <= 900) {
    sala = 1;//primeira sala
    if(checkSala != sala) {
      renderizar();
      teladeAnimacaoOUT();
      salaCamera();
      teladeAnimacaoIN();
    }
    checkSala = sala;
  }
  else if(gX >= 1244 && gX+rR.w <= 1244 + 1919 && gY >= 0 && gY+rR.h <= 900) {
    if(!firsttimeoverworld) {
      firsttimeoverworld = true;
      Mix_PlayMusic(overworld, -1);
    }
    sala = 2;//primeira sala
    if(checkSala != sala) {
      renderizar();
      teladeAnimacaoOUT();
      salaCamera();
      teladeAnimacaoIN();
    }
    checkSala = sala;
  }
  else if(gX >= 3000 && gX+rR.w <= 3000+1440 && gY >= 0 && gY+rR.h <= 1200) {
    if(!firsttimeunderworld) {
      Mix_HaltMusic();
      firsttimeunderworld = true;
      Mix_PlayMusic(underworld, -1);
    }
    sala = 3;//primeira sala
    if(checkSala != sala) {
      renderizar();
      teladeAnimacaoOUT();
      salaCamera();
      teladeAnimacaoIN();
    }
    checkSala = sala;
  }
  else if(gX >= 4440 && gX+rR.w <= 6360 && gY >= 0 && gY+rR.h <= 2880) {
    sala = 4;//primeira sala
    if(checkSala != sala) {
      cajado = true;
      projetil = false;
      projetilstop = false;
      renderizar();
      teladeAnimacaoOUT();
      salaCamera();
      teladeAnimacaoIN();
    }
    checkSala = sala;
  }
}
void salaCamera()
{
  if(sala==2)
  {
    rRcam.x = gX - 320;
    rRcam.y = gY - 200;
    if(gX > 3000 - 320)
    {
      rRcam.x = 3000 - 640;
    }
    if(gY > 900 - 200)
    {
      rRcam.y = 900 - 400;
    }
  }
  else if(sala==1)
  {
    rRcam.x = gX - 320;
    rRcam.y = gY - 200;
    if(gX > 1080 - 320)
    {
      rRcam.x = 1080 - 640;
    }
    if(gY > 900 - 200)
    {
      rRcam.y = 900 - 400;
    }
  }
  else if(sala==3)
  {
    rRcam.x = gX - 320;
    rRcam.y = gY - 200;
    if(gX > 4440 - 320)
    {
      rRcam.x = 4440- 640;
    }
    if(gY > 1200 - 200)
    {
      rRcam.y = 1200 - 400;
    }
  }
   else if(sala==4)
  {
    rRcam.x = gX - 320;
    rRcam.y = gY - 200;
    if(gX <= 4440 + 320) {
      rRcam.x = 4440;
    }
    if(gX > 6360 - 320)
    {
      rRcam.x = 6360- 640;
    }
    if(gY > 2880 - 200)
    {
      rRcam.y = 2880 - 400;
    }
  }
  
}
void teladeAnimacaoOUT (void) {
  for(fadeAlpha = 0; fadeAlpha <= 255; fadeAlpha+=5) {
    renderizar();
    SDL_SetTextureAlphaMod(fadeTex, fadeAlpha);
    SDL_RenderCopy(render, fadeTex, NULL, NULL);
    SDL_RenderPresent(render);
    SDL_Delay(7);
  }
}
void teladeAnimacaoIN (void) {
  for(fadeAlpha = 255; fadeAlpha >= 0; fadeAlpha-=5) {
    renderizar();
    SDL_SetTextureAlphaMod(fadeTex, fadeAlpha);
    SDL_RenderCopy(render, fadeTex, NULL, NULL);
    SDL_RenderPresent(render);
    SDL_Delay(7);
  }
  fadeAlpha=0;
}
void projetilF (void) {
  static int contador = 0;
  static bool colisao = false;
  static bool stop = false;
  static int velprojetil;
  static char sentidop = 'n';
  
  projetilstop = stop;
  wizard_Magic(&projetil, &cajado, &mouse, &rR, &rProjetil, &rRcam, gJanela, &projetilstop, contador);
  if(projetil && contador == 0 && !stop) {
    contador = 1;
  }
  if(contador == 1 && !stop && projetil && cajado) { //som do projetil//
    Mix_PlayChannel(3, projetilstart, 0);
  }
  if(contador > 0 && contador <= 45 && !colisao && !stop) {
      contador++;
  }
  if(contador > 45) {
    stop = true;
  }
  if(contador > 0 && contador <= DELAY_PROJETIL && stop) {
    contador++;
    rProjetil.x = -2000 - rRcam.x;
    rProjetil.y = -2000 - rRcam.y;
  }
  else if(contador > DELAY_PROJETIL) {
    stop = false;
    contador = 0;
  }
  colisao = false;
  //COLISAO DE PROJETIL COM PAREDE//
  for(int i = 0; i < numWall; i++) { 
    colisao = collision(rProjetil, rRw[i], 0, 0);
    if(colisao) {
      printf("[Console]O projetil colidiu com a parede %i\n", i); 
      stop = true;        
    }
  }
  // COLISAO DE PROJETIL COM MOBS //
  colisao = false;
  for(int i = 0; i < meatboxMobs; i++) { 
      if(meatbox[i].life >= 0) { 
          colisao = collision(rProjetil, meatbox[i].rR, 0, 0);
          MAGIC_MEATBOX(rProjetil, meatbox[i].rR, &meatbox[i], &book.coins,&book.pontos, &danofx);
        if(colisao) {
          Mix_PlayChannel(3, projetilhit, 0);
          stop = true;
        }
      }
  }
  colisao = false; 
  for(int i = 0; i < ogreMobs; i++) { 
    if(ogre[i].life >= 0) { 
        colisao = collision(rProjetil, ogre[i].rR, 0, 0);
        MAGIC_OGRE(rProjetil, ogre[i].rR, &ogre[i], &book.coins,&book.pontos, &danofx);
      if(colisao) {
        Mix_PlayChannel(3, projetilhit, 0);
        stop = true;
      }
    }
  } 
  colisao = false; 
  for(int i = 0; i < mageMobs && !colisao && !stop; i++) { 
    if(mage[i].life >= 0) { 
        colisao = collision(rProjetil, mage[i].rR, 0, 0);
        MAGIC_MAGE(rProjetil, mage[i].rR, &mage[i], &book.coins,&book.pontos, &danofx, &book.keys);
      if(colisao) {
        Mix_PlayChannel(3, projetilhit, 0);
        stop = true;
      }
    }
  }
  colisao = false;
  if(bigboss[0].life >= 0) { 
    colisao = collision(rProjetil, bigboss[0].rR, 0, 0);
    MAGIC_BIGBOSS(rProjetil, bigboss[0].rR, &bigboss[0], &book.coins,&book.pontos, &danofx, &book.keys); 
    if(colisao) {
      Mix_PlayChannel(3, projetilhit, 0);
      stop = true;
    }
  }
}
void plaquinhas (void)
  {
    if(!wakeup)
    {
      abrirDialogbox("JOHN: Oii, vem falar comigo! :D",
                       "","","",irmao.icon);
      wakeup = true;

    }


    if(interagir)
    {

      if(colisor_verificator(rR,rRw[336],0,-3)) //ashlands
      {
         abrirDialogbox("ASHLANDS, nao ouse se aproximar!.", "", "", "", 125);
         interagir = false;
      }
       if(colisor_verificator(rR,rRw[335],0,-3)) //ashlands
      {
         abrirDialogbox("Aqueles que ousarem desafiar o mestre Klyn", "PAGARAO O PRECO", "", "", 125);
         interagir = false;
      }
       if(colisor_verificator(rR,rRw[334],0,-3)) //ashlands
      {
         abrirDialogbox("Desative os cristais e proiba os monstros de", "ranascerem", "", "", 125);
         interagir = false;
      }
       if(colisor_verificator(rR,rRw[295],0,-3)) //ashlands
      {
         abrirDialogbox("Mestre Klyn a frente entre por conta e risco.", "", "", "", 125);
         interagir = false;
      }
       if(colisor_verificator(rR,rRw[305],0,-3)) //ashlands
      {
         abrirDialogbox("mina em construcao.", "", "", "", 125);
         interagir = false;
      }
       if(colisor_verificator(rR,rRw[314],0,-3)) //ashlands
      {
         abrirDialogbox("e o fim dos tempos.", "", "", "", 125);
         interagir = false;
      }
      if(colisor_verificator(rR,rRw[333],0,-3)) //
      {
         abrirDialogbox("tesouros a frente?.", "", "", "", 125);
         interagir = false;
      }

      if(colisor_verificator(rR,rRw[104],0,-3)) //CASA DO ANCIAO
      {
         abrirDialogbox("Casa do Anciao Aratus, Heroi da cidade de Zephyr.", "", "", "", 125);
         interagir = false;
      }
      if(colisor_verificator(rR,rRw[105],0,-3)) 
      {
         abrirDialogbox("Casa de Dave Ildor, aprendiz do Anciao e John Ildors", "", "", "", 125);
         interagir = false;
      }
      if(colisor_verificator(rR,rRw[109],0,-3))
      {
         abrirDialogbox("Portal de teletransporte!", "", "", "APENAS PESSOAS AUTORIZADAS!!", 125);
         interagir = false;
      }
       if(colisor_verificator(rR,rRw[98],0,-3))
      {
         abrirDialogbox("Casa da Familia Nimbus.", "", "", "", 125);
         interagir = false;
      }
      if(colisor_verificator(rR,rRw[133],0,-3)) 
      {
         abrirDialogbox("Torre memorial a vitoria de Aratus na guerra", "contra a dimensao sombria", "", "", 125);
         interagir = false;
      }
      for(int i=0;i<npcmax;i++)
      {
         if(colisor_verificator(rR,npc[i].rR,0,vel) || colisor_verificator(rR,npc[i].rR,0,-vel) || colisor_verificator(rR,npc[i].rR, vel, 0) || colisor_verificator(rR,npc[i].rR, -vel,0))
        {
          if(!cajado)
            abrirDialogbox(npc[i].texto, "", "", "", npc[i].icon);
          else
            abrirDialogbox(npc[i].texto2, "", "", "", npc[i].icon);
          interagir = false;

        }
      }
      for(int i=0;i<animalsmax;i++)
      {
          if(colisor_verificator(rR,animals[i].rR,0,vel) || colisor_verificator(rR,animals[i].rR,0,-vel) || colisor_verificator(rR,animals[i].rR, vel, 0) || colisor_verificator(rR,animals[i].rR,-vel,0))
          {
            abrirDialogbox(animals[i].texto, "", "", "", animals[i].icon);
            interagir = false;
          }
      }
      if((colisor_verificator(rR,irmao.rR,0,vel) || colisor_verificator(rR,irmao.rR,0,-vel) || colisor_verificator(rR,irmao.rR, vel, 0) 
      || colisor_verificator(rR,irmao.rR,-vel,0)) && !cajado)
      {
        abrirDialogbox("JOHN: Acordou tarde hein.",
                       "Logo agora que voce devia estar mais responsavel.","","",irmao.icon);
        abrirDialogbox("JOHN: soube o anciao te promoveu a assistente.",
                       "Enfim, parabens pela promocao irmao, voce merece","","",irmao.icon);

        abrirDialogbox("JOHN: Ah, acho que o anciao quer falar com voce.",
                       "Se eu fosse voce iria logo.","","",irmao.icon);
        interagir=false;
        irmao.talk = true;
      }
      else if((colisor_verificator(rR,irmao.rR,0,vel) || colisor_verificator(rR,irmao.rR,0,-vel) || colisor_verificator(rR,irmao.rR, vel, 0) 
      || colisor_verificator(rR,irmao.rR,-vel,0)) && cajado) 
      {
        abrirDialogbox("JOHN: Boa sorte na sua jornada, mano!",
                       "A casa vai ficar vazia sem voce.. :(","",
                       "     Toma um pouco de dinheiro...",irmao.icon);
        interagir=false;
        if(!irmao.talk2)
          book.coins += 10;
        irmao.talk2 = true;
      }

      if(colisor_verificator(rR,anciao.rR,0,vel) || colisor_verificator(rR,anciao.rR,0,-vel) || colisor_verificator(rR,anciao.rR, vel, 0) || colisor_verificator(rR,anciao.rR,-vel,0))
      {
        if(!cajado) {
          abrirDialogbox("ANCIAO: Ola Dave... Finalmente chegou!",
                        "Estava te esperando para discutirmos",
                        "","",anciao.icon);

          abrirDialogbox("ANCIAO: Acho que voce ja percebeu que estou velho...",
                        "Essa cidade precisa de um novo protetor para as ","proximas batalhas","",anciao.icon);

          abrirDialogbox("ANCIAO: Ha uma profecia que diz que a cada 100 anos",
                        "a dimensao sombria atacara a cidade de Zephyr","","",anciao.icon);

          abrirDialogbox("ANCIAO: Fazem 100 anos desde que protegi Zephyr",
                        "pela primeira vez...","","",anciao.icon);

          abrirDialogbox("ANCIAO: Agora nao sou capaz de lutar...",
                        "estou lento e cansado...",
                        "preciso passar meu posto a frente...","",anciao.icon);
          
          abrirDialogbox("ANCIAO: Voce, Dave, sempre se mostrou muito....",
                        "talentoso em tudo o que fazia...",
                        "e tem se empenhado bastante para aprender","comigo.",anciao.icon);

          abrirDialogbox("ANCIAO: Voce herdara o cargo de protetor de Zephyr.",
                        "Estou lhe passando meu cajado...",
                        "Pegue-o no meu bau de ouro.","e volte ate mim",anciao.icon);
        }
        else if(cajado) {
          abrirDialogbox("ANCIAO: Entao Dave...",
                        "Preciso que voce acabe com essa guerra",
                        "antes que ela comece...","",anciao.icon);

          abrirDialogbox("ANCIAO: Use o portal de teletransporte para",
                        "entrar na dimensao sombria ",
                        "la voce sera capaz de provar seu valor",
                        "lutando contra todos os monstros...",anciao.icon);

          abrirDialogbox("ANCIAO: La existem cristais invocadores que",
                        "sao capazes de reviver os monstros","","",anciao.icon);

          abrirDialogbox("ANCIAO: Lembre de desativa-los sempre que",
                        "achar algum....","","Alguns sao capazes de abrir portas!!",anciao.icon);

          abrirDialogbox("ANCIAO: Leve meu livro de Alquimia. Ele sera",
                        "capaz de ajuda-lo a criar",
                        "pocoes para te fortalecer durante as lutas...",
                        "",anciao.icon);

          abrirDialogbox("ANCIAO: Para ativa-lo basta clicar na letra 'b'",
                        "Cada pocao e ativada com um numero do teclado",
                        "A vermelha e ativada com o 1, a azul com o 2",
                        "e a verde com o 3", anciao.icon);

          abrirDialogbox("ANCIAO: A pocao vermelha cura um coracao",
                        "A pocao azul dobra sua velocidade por 5 segundos",
                        "A pocao verde dobra seu dano por 5 segundos",
                        "",anciao.icon);

          abrirDialogbox("ANCIAO: Boa sorte, meu jovem...",
                        "A vila conta com voce!!",
                        "","",anciao.icon);
            if(!anciao.talk2)
              book.coins += 20;
            anciao.talk2 = true;
            book.ativo = true;
            
              
        }

        interagir=false;
        anciao.talk = true;
      }
      

      xe=0; xd=0; yc=0; yc=0;
    
    }

  }
  void teleporte(void)
  {
    if(colisor_verificator(rR,rRw[168],0,2) && anciao.talk2)
    {
      gX=398; gY=355;
    }
    else if(colisor_verificator(rR,rRw[168],0,2) && !anciao.talk2) {
      abrirDialogbox("Vai sair sem falar comigo?", "", "", "                 Doido...", anciao.icon);
      interagir = false;
      xe = 0; xd = 0; yc = 0; yb = 0;
      gY -= 10;
    }

    if(colisor_verificator(rR,rRw[196],0,-2))
    {
      gX=2518; gY=712;
    }

    if(colisor_verificator(rR,rRw[180],0,2) && irmao.talk)
    {
      gX=144; gY=703;
    }
    else if(colisor_verificator(rR,rRw[180],0,2) && !irmao.talk)
    {
      abrirDialogbox("VEM FALAR COMIGO IRMAOZINHO!!", "", "", "          :) :)", irmao.icon);
      interagir = false;
      xe = 0; xd = 0; yc = 0; yb = 0;
      gY -= 10;
    }
    if(colisor_verificator(rR,rRw[195],0,-2))
    {
      gX=1536; gY=544;
    }

    if(colisor_verificator(rR, rRw[197], 0, -2)) {
      if(anciao.talk2) {
        abrirDialogbox("SENTINELA: BOA SORTE AMIGO!!", "", "", "", 0);
        gX=3701;gY=94;
        xe = 0; xd = 0; yc = 0; yb = 0;
      }
      else {
        abrirDialogbox("SENTINELA: VOCE NAO TEM AUTORIZACAO!", "NAO PERTUBE MEU TRABALHO!!", "", "", 0);
        interagir = false;
        xe = 0; xd = 0; yc = 0; yb = 0;
        gY += 10;
      }
    }
    if(!cristal[0].ativo) {
      rPortal[1].h -= 32;
      if(colisor_verificator(rR, rPortal[1], 0, -2)) {
        xe = 0; xd = 0; yc = 0; yb = 0;
        gX = 5209; gY = 2575;
      }
      rPortal[1].h += 32;
    }

  }
  void interactioncristais(CRISTAL* cristal)
  {
    //desativar cristais
    if(interagir)
    { 
      for(int i = 0; i < cristalQuantidade; i++)
      {
          if(sqrt(pow(rR.x + rR.w - cristal->rR.x,2) +pow(rR.y + rR.h - cristal->rR.y,2)) <= 100)
        {
            Mix_PlayChannel(1, cristalsounds, 0);
            cristal->ativo=false;
        }
      }
    }  
  }
  void interaction(void) {
  colisao = false;
  // interacao com os baus//
  //bau 1//
  if(chest[1].estado) {
    // if para verificar se houve interacao! //
    if(colisor_verificator(rR,chest[1].pos,0,vel) 
    || colisor_verificator(rR,chest[1].pos,0,-vel) || colisor_verificator(rR,chest[1].pos, vel, 0) || colisor_verificator(rR,chest[1].pos,-vel,0) && book.keys > 0) 
    {
      book.potion.cura+=2;
      book.keys -= 1;
      chest[1].estado = false;
      Mix_PlayChannel(1, openchest, 0);
      // se houve interacao //
      abrirDialogbox("voce pegou duas pocoes de cura!", "", "", "",100);
      interagir = false;

      xd = 0; xe = 0; yc = 0 ;yb = 0;
    }
    else {
      Mix_PlayChannel(4, error, 0);
    }
  }
  if(chest[2].estado) {
    // if para verificar se houve interacao! //
    if(colisor_verificator(rR,chest[2].pos,0,vel) 
    || colisor_verificator(rR,chest[2].pos,0,-vel) || colisor_verificator(rR,chest[2].pos, vel, 0) || colisor_verificator(rR,chest[2].pos,-vel,0) && book.keys > 0) 
    {
      book.potion.velocidade +=1;
      book.potion.cura += 1;
      book.keys -= 1;
      chest[2].estado = false;
      Mix_PlayChannel(1, openchest, 0);
      // se houve interacao //
      abrirDialogbox("voce pegou uma pocao de velocidade", "e uma de cura!", "", "",100);
      interagir = false;

      xd = 0; xe = 0; yc = 0 ;yb = 0;
    }
    else if(book.keys <= 0){
      Mix_PlayChannel(4, error, 0);
    }
  }
  if(chest[3].estado) {
    // if para verificar se houve interacao! //
    if(colisor_verificator(rR,chest[3].pos,0,vel) 
    || colisor_verificator(rR,chest[3].pos,0,-vel) || colisor_verificator(rR,chest[3].pos, vel, 0) || colisor_verificator(rR,chest[3].pos,-vel,0) && book.keys > 0) 
    {
      book.potion.dano +=2;
      book.keys -= 1;
      chest[3].estado = false;
      Mix_PlayChannel(1, openchest, 0);
      // se houve interacao //
      abrirDialogbox("voce pegou duas pocoes de dano!", "", "", "",100);
      interagir = false;

      xd = 0; xe = 0; yc = 0 ;yb = 0;
    }
    else if(book.keys <= 0) {
      Mix_PlayChannel(4, error, 0);
    }
  }
  if(chest[4].estado) {
    // if para verificar se houve interacao! //
    if(colisor_verificator(rR,chest[4].pos,0,vel) 
    || colisor_verificator(rR,chest[4].pos,0,-vel) || colisor_verificator(rR,chest[4].pos, vel, 0) || colisor_verificator(rR,chest[4].pos,-vel,0) && book.keys > 0) 
    {
      book.potion.dano +=2;
      book.keys -= 1;
      chest[4].estado = false;
      Mix_PlayChannel(1, openchest, 0);
      // se houve interacao //
      abrirDialogbox("voce pegou duas pocoes de dano!", "", "", "",100);
      interagir = false;

      xd = 0; xe = 0; yc = 0 ;yb = 0;
    }
    else if(book.keys <= 0) {
      Mix_PlayChannel(4, error, 0);
    }
  }
   if(chest[0].estado && anciao.talk) {
    // if para verificar se houve interacao! //
    if(colisor_verificator(rR,chest[0].pos,0,vel) || colisor_verificator(rR,chest[0].pos,0,-vel) || colisor_verificator(rR,chest[0].pos, vel, 0) || colisor_verificator(rR,chest[0].pos,-vel,0)) 
    {
      cajado = true;
      chest[0].estado = false;
      printf("[Console]Parabens, voce pegou o cajado!\n");
      Mix_PlayChannel(1, openchest, 0);
      // se houve interacao //
      abrirDialogbox("Voce pegou o cajado!", "", "", "Use o botao esquerdo do mouse para atacar", 100);
      interagir = false;

      xd = 0; xe = 0; yc = 0 ;yb = 0;
    }
  }
  else if(chest[0].estado && !anciao.talk) {
    if(colisor_verificator(rR,chest[0].pos,0,vel) || colisor_verificator(rR,chest[0].pos,0,-vel) || colisor_verificator(rR,chest[0].pos, vel, 0) || colisor_verificator(rR,chest[0].pos,-vel,0)) 
    {
    abrirDialogbox("CHEST: Nao mexa nas coisas do anciao >:[!", "", "", "", 100);

    interagir = false;
    xd = 0; xe = 0; yc = 0 ;yb = 0;
    }
  }
}
void pauseGame (void) {
  bool pausemenu = true;
  while(pausemenu) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_KEYDOWN) { // Pressionando as teclas //
        if(event.key.keysym.sym == SDLK_ESCAPE) {
          pause = false;
          pausemenu = false;
        }
        if(event.type == SDL_QUIT) {
          gaming = false;
          pausemenu = false;
          pause = false;
        }
      }
    }
    renderizar();
    SDL_SetTextureAlphaMod(fadeTex, 180);
    SDL_RenderCopy(render, fadeTex, NULL, NULL);

    sprintf(numerodepocoes, "PAUSE");
    huds.rRcoin.x -= 240;
    huds.rRcoin.y += 170;
    alterarfonte(book.keys, huds.rRcoin, 3);
    huds.rRcoin.x += 240;
    huds.rRcoin.y -= 170;
    SDL_RenderCopy(render, text[0], NULL, &textRect);


    SDL_RenderPresent(render);

    SDL_Delay(1000/60);
  }

}

                                                                                                                      // MAIN // 
void gameloop (SDL_Renderer * renderer, SDL_Window * Janelona) {
  gaming=true;
    render = renderer;
    gJanela = Janelona;
  //test//
  fadeSurf = SDL_CreateRGBSurface(0, 640, 400, 32, 0, 0, 0, fadeAlpha);
  //INICIANDO SDL//
  //SDL_Init(SDL_INIT_EVERYTHING);
  //TTF_Init();
  //Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
  Mix_Volume(1, 50);
  //START PLAYER//
  rR.x = gX; rR.y = gY; rR.w = 64; rR.h = 120;
  //FRAMETIME//
  const int FPS = 60;
  const int frameDelay = 1000/ FPS;
  int frameStart;
  int frameTime;
  //Start em Window//
    //GAME HERE//
    fontes();
    printf("[Console] fontes carregadas!\n");
    printf("[Console]tela iniciada\n");
    surfaces();
    printf("[Console]surfaces carregadas\n");
    audio();
    printf("[Console]audio iniciado\n");
    printf("[Console]o Jogo ira iniciar...\n");
    printf(". ");
    printf(". ");
    printf(".\n");
    printf("[Console]iniciando!\n");
    Mix_PlayChannel(1, welcome, 0);
    Mix_Volume(6,0);
    Mix_VolumeMusic(15);
    //TIRANDO O ALPHA DO WALL//
    // E88E0C
    //SDL_SetTextureColorMod( playerTex, 50, 50, 50 );
    SDL_SetTextureAlphaMod(wallTex, 0);
    //préiniciados//
    cristalStart();
    iniciarChests();
    meatboxStart();
    ogreStart();
    mageStart();
    playerStart();
    iniciarNPC();
    bigbossStart();

    //definindo o inicio da tela//
    salaAtual();
    salaCamera();
    //reescalando//
    rescalar();
    SDL_RenderSetLogicalSize(render, 640, 400);

    srand(time(NULL));

    if(!houvetutorial) {
      SDL_RenderClear(render);
      SDL_RenderCopy(render, tutorialTex, NULL, NULL);
      SDL_RenderPresent(render);
      SDL_Delay(10000);
      houvetutorial = true;
    }

    //renderizar();
    teladeAnimacaoIN();
    while(gaming) {                                                                                                             //GAME LOOP//
      //FRAMES//
        frameStart = SDL_GetTicks();
      //Eventos//
      while(SDL_PollEvent(&event)){
        //X to close//
        if (event.type == SDL_QUIT)
          gaming = false;
        //reconhecendo movimentos//
        mousemovements();
        movements();
      }
      // RESCALAR JANELA E SPRITES //
      rescalar();
      SDL_RenderSetLogicalSize(render, 640, 400);

      if(kback.mobTYPE == 'M')
      {
        takeKnockback (&kback, rR, meatbox[kback.mobNUMERO].rR, &gX, &gY, vel, rRw, numWall);
      }
      else if(kback.mobTYPE == 'O')
      {
        takeKnockback (&kback, rR, ogre[kback.mobNUMERO].rR, &gX, &gY, vel, rRw, numWall);
      }
      else if(kback.mobTYPE == 'B')
      {
        takeKnockback (&kback, rR, bigboss[0].rR, &gX, &gY, vel, rRw, numWall);
      }

      // dando movimentos & ações//
      makemovements();
      projetilF();
      if(interagir) {
        //printf("[Console]Vamos tentar achar um objeto para voce!\n");
        interaction();
      }
            // POCAO DE CURA //
      if(regeneffect && !regeneffectkeydown) {
        regenerar(&book, &book.life,&regeneffect,&regeneffectkeydown, regen, error);
      }
      else if(!regeneffect)
        regeneffectkeydown = false;

      // POCAO DE VELOCIDADE //
      if((veleffect && !veleffectkeydown) || velffectcounter > 0) {
        velocidadeextra(&book, &potionvel, &veleffect, &veleffectkeydown, &velffectcounter, regen, error);
      }
      else if(!veleffect)
        veleffectkeydown = false;

      // POCAO DE DANO //
      if((danoeffect && !danoeffectkeydown) || danocounter > 0) {
        danoextra(&book, &danofx, &danoeffect, &danoeffectkeydown, &danocounter, regen, error);
      }
      else if(!danoeffect)
        danoeffectkeydown = false;

        // movimentos dos mobs //
      for(int i = 0; i < meatboxMobs; i++) {
        kback.mobNUMEROtemp = i;
        meatboxEngine(&meatbox[i], &rR, rRw, numWall, &book.life, &invencible, &kback);
      }
      for(int i = 0; i < ogreMobs; i++) {
        kback.mobNUMEROtemp = i;
        ogreEngine (&ogre[i], &rR, rRw, numWall, &book.life, &invencible, &kback);
      }
      for(int i = 0; i < mageMobs; i++) {
        mageEngine (&mage[i], &rRcam, &rR, &book.life, &invencible, rRw, numWall);
      }
      bigBossEngine (&bigboss[0], &rR, rRw, numWall, &book.life, &invencible, &kback, rRcam);
      for(int i=0; i < cristalQuantidade ;i++)
      {
        interactioncristais(&cristal[i]);
      }
       if(!cristal[0].ativo && !cristal[1].ativo && !cristal[2].ativo && !cristal[3].ativo) {
      }
      else if((!cristal[0].ativo || !cristal[1].ativo || !cristal[2].ativo || !cristal[3].ativo || !cristal[4].ativo || !cristal[5].ativo 
      || !cristal[6].ativo || !cristal[7].ativo) && killthemall() == 1) 
      {
          missao.desafiomatarportempo = true;
          // REwIND //
          ogreStart();
          mageStart();
          meatboxStart();
          Mix_PlayChannel(1, error, 0);
      }
      if(!cristal[1].ativo && !cristal[2].ativo && !cristal[3].ativo) {
        if(portao.contador == 10) 
          Mix_PlayChannel(1, opendoor, 0);
        animarPortao(&portao, rRcam);
      }
      else {
        portao.rR.x = portao.x - rRcam.x;
        portao.rR.y = portao.y - rRcam.y;
        portao.rR.w = 48 * 1.5;
        portao.rR.h = 48 * 1.5; 

        portao.sR.y = 0; portao.sR.x = 0;
        portao.sR.w = 48; portao.sR.h = 48;
      }
      
      //alterarfonte(0);
      //camera//
        //camera e sala//s
      salaAtual();
      salaCamera();
      teleporte();
      for(int i = 0; i < animalsmax; i++) {
        AnimalMechanic(&animals[i]);
      }
      invencibleF();
  
      // book magico //
      if(book.aberto && book.ativo) {
        teladeAnimacaoOUT();
        bookOpen (&book,render,numerodepocoes,cor ,fontePote,&event,bookTex,fonte2,text,gJanela,&mouse);
        teladeAnimacaoIN();
        xe = 0; xd = 0; yc = 0; yb = 0;
      }
      if(pause) {
        pauseGame();
      }
      // GOD MODE //
      
     /*if(life < 2)
        life = LIFE;*/
      //printf("%i\n", coins);
      plaquinhas();

      // APRESENTANDO AO USUARIO //
      renderizar();
      //SDL_RenderCopy(render, bookTex, NULL, NULL);      
      SDL_RenderPresent(render);
      //morte//
      dialogoMiniboss();
      Mix_Volume(6, 15);
      if(book.life < 0 && invencible == 0) 
      {
            gaming = false;
            Mix_PlayChannel(1, death, 0);
            SDL_Delay(1000);
            printf("\n\n\n[Console]Voce Perdeu, Meu Consagrado! \n\n\n");
      }
      //FRAME DELAY//
      frameTime = SDL_GetTicks() - frameStart;
      if(frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
      }
    }
    teladeAnimacaoOUT();

    textoInput(render, gJanela, book.pontos);
  //Destroy//
  //SDL_DestroyWindow(gJanela);
  SDL_DestroyTexture(playerTex);
  SDL_DestroyTexture(wallTex);
  SDL_DestroyTexture(mapTex);
  SDL_DestroyTexture(heartTex);
  SDL_DestroyTexture(mapTex2);
  SDL_DestroyTexture(objectTex);
  SDL_DestroyTexture(HUDTex);
  SDL_DestroyTexture(chestTex);
  SDL_DestroyTexture(minibossTex);
  SDL_DestroyTexture(cajadoTex);
  SDL_DestroyTexture(meatboxTex);
  SDL_DestroyTexture(ogreTex);
  SDL_DestroyTexture(explodirTex);
  SDL_DestroyTexture(mageTex);
  SDL_DestroyTexture(projTex);
  SDL_DestroyTexture(cristalTex);
  SDL_DestroyTexture(iconTex);
  SDL_DestroyTexture(bookTex);
  SDL_DestroyTexture(portalTex);
  SDL_DestroyTexture(bigbossTex);
  SDL_DestroyTexture(tutorialTex);
  TTF_CloseFont(fonte);
  SDL_FreeCursor(cursor);
  Mix_HaltMusic();
  //FIM//
  //Mix_Quit();
  //SDL_Quit();
  //TTF_Quit();  
  //printf("[Dev's] Adeus caro amigo! Foi bom te conhecer ;')\n");
  
}
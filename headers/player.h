#include "SDL2/SDL.h"
#include <math.h>
#define PROJETILVEL 5

typedef struct {
    int x;
    int y;
} PONTEIROMOUSE;

typedef struct {
    bool desafiomatarportempo;
}DESAFIOS;

typedef struct {
    SDL_Rect rR;
    SDL_Rect sR;
}CAJADO;

typedef struct {
    int x;
    int y;
    int contador;
    SDL_Rect rR;
    SDL_Rect sR;

}PORTAO;
void playerAnimated(SDL_Rect * rR, SDL_Rect * sR, SDL_Rect * rRcam, float * gX, float * gY, SDL_Window * gJanela, PONTEIROMOUSE * mouse) {
  //RECT do Player//
  static int move = 0;
  static int contador = 1;
    if(move >= 42) {
        move = 0;
    }
    else if(move >= 0 && move < 7) {
        sR->x = 0; sR->y = 4; sR->w = 15; sR->h = 20;
    }
    else if(move >= 7 && move < 14) {
        sR->x = 16; sR->y = 4; sR->w = 15; sR->h = 20;
    }
    else if(move >= 14 && move < 21) {
        sR->x = 31; sR->y = 4; sR->w = 15; sR->h = 20;
    }
    else if(move >= 21 && move < 28) {
        sR->x = 48; sR->y = 4; sR->w = 15; sR->h = 20;
    } 
    else if(move >= 28 && move < 35) {
        sR->x = 63; sR->y = 4; sR->w = 15; sR->h = 20;
    }  
    else if(move >= 35 && move < 42) {
        sR->x = 80; sR->y = 4; sR->w = 15; sR->h = 20;
    }
    move++;
    rR->x = *gX - rRcam->x; rR->y = *gY - rRcam->y;
    rR->w = sR->w * 1.6; rR->h = sR->h * 1.6;

    static float wf, hf;
    static int width, height;
    SDL_GetMouseState( &mouse->x, &mouse->y); // pegando a pos do mouse //
    SDL_GetWindowSize(gJanela, &width, &height);
    wf = (float)width / 640;
    hf = (float)height / 400;
    mouse->x /= wf;
    mouse->y = (mouse->y / hf);
    if(mouse->y <= rR->y + (rR->h/2)) {
        sR->y = 28;
    }

}
void playerAnimatedDamage (int * invencible, SDL_Texture * playerTex) {
    if(*invencible % 4 == 0) {
        SDL_SetTextureAlphaMod(playerTex, 100);
    }
    else if(*invencible % 2 == 0) {
        SDL_SetTextureAlphaMod(playerTex, 50);
    }
    else {
        SDL_SetTextureAlphaMod(playerTex, 200);
    }
}

void wizard_Magic (bool * projetil, bool * cajado, PONTEIROMOUSE * mouse, SDL_Rect * rR, SDL_Rect * rProj, SDL_Rect * rRcam, SDL_Window * gJanela, bool * stop, int contador) {
    static float distx;
    static float disty;
    static float temp;
    static float velx;
    static float vely;
    static int x;
    static int y;
    static float posx;
    static float posy;
    static int fixx;
    static int fixy;
    float hf;
    float wf;
    static int width;
    static int height;
    static bool colisao;
    if(*projetil && *cajado && contador == 0) {
        SDL_GetMouseState( &mouse->x, &mouse->y); // pegando a pos do mouse //
        SDL_GetWindowSize(gJanela, &width, &height);
        wf = (float)width / 640;
        hf = (float)height / 400;
        mouse->x /= wf;
        mouse->y = (mouse->y / hf);

        //printf("%i %i\n", mouse->x, mouse->y);

        distx = abs(rR->x + rR->w/2 - mouse->x);
        disty = abs(rR->y + rR->h/4 - mouse->y);
        temp = sqrt(pow(distx, 2) + pow(disty, 2));
        temp = PROJETILVEL / temp;
        velx = distx * temp;
        vely = disty * temp;
        posx = 0;
        posy = 0;
        contador = 1;
        fixx = rR->x + rRcam->x;
        fixy = rR->y + rRcam->y;

        if(mouse->x <= rR->x) {// esquerda //
            x = -1;
            fixx -= 6.5*velx;
        }
        else {
            x = 1;
            fixx += 6.5*velx;
        }
        if(mouse->y <= rR->y) {// cima // 
            y = -1;
            fixy -= 6.5*vely;
        }
        else {
            y = 1;
            fixy += 6.5*vely;
        }

    }
    if(contador < 45 && contador > 0 && !*stop) {
        if(x == 1 && y == 1)  // direita e baixo //
        { 
            //printf("ATIRANDO D B\n"); 
            // direita //
            posx += velx;
            rProj->x = fixx + posx - rRcam->x;
            //baixo //
            posy += vely;
            rProj->y = fixy + posy - rRcam->y;
        }
        else if(x == -1 && y == 1)  // esquerda e baixo //
        { 
            // esquerda //
            //printf("ATIRANDO E B\n");
            posx -= velx;
            rProj->x = fixx + posx - rRcam->x;
            //baixo //
            posy += vely;
            rProj->y = fixy + posy - rRcam->y;
        }
        else if(x == -1 && y == -1)  // esquerda e cima //
        { 
            //printf("ATIRANDO E C\n");
            // esquerda //
            posx -= velx;
            rProj->x = fixx + posx - rRcam->x;
            //cima //
            posy -= vely;
            rProj->y = fixy + posy - rRcam->y;
        }
        else if(x == 1 && y == -1)  // DIREITA e cima //
        { 
            //printf("ATIRANDO D C\n");
            // esquerda //
            posx += velx;
            rProj->x = fixx + posx - rRcam->x;
            //cima //
            posy -= vely;
            rProj->y = fixy + posy - rRcam->y;
        }
        rProj->w = 14;
        rProj->h = 14;
    }
    if(contador >= 60) { // 60 == DELAYPROJETIL //
        contador = 0;
        *stop = false;
    }
}

int killthemall (void) {
    static int contador = 0;
    static int maximo = 3600; // 1 minuto //
    //printf("%i\n", contador);
    if(contador < maximo-90) {
        contador++;
        return 0;
    }
    else if(contador >= maximo-90 && contador < maximo) {
        contador++;
        return 2;
    }
    else if(contador >= maximo) {
        contador = 0;
        return 1;
    }
}

void cajadoAnimated(SDL_Rect * playerRect, SDL_Point * cajadoCenter, PONTEIROMOUSE * mouse, SDL_Window * gJanela, double * angle) {
    //definindo ponto centro //

    cajadoCenter->x = 4;
    cajadoCenter->y = 0;

    // definindo angulo //

    static double hf;
    static double wf;
    static int width;
    static int height;
    static double temp;
    SDL_GetMouseState( &mouse->x, &mouse->y); // pegando a pos do mouse //
    SDL_GetWindowSize(gJanela, &width, &height);
    wf = (float)width / 640;
    hf = (float)height / 400;
    mouse->x /= wf;
    mouse->y = (mouse->y / hf);
    // pegando a distancia nos eixos //
    wf = ((playerRect->x + playerRect->w)- mouse->x);
    hf = ((playerRect->y + playerRect->h) - mouse->y);
    *angle = (atan2(hf, wf) * 180.00000)/ 3.1416;

    //printf("%lf\n", *angle);
}

void animarPortao(PORTAO * portao, SDL_Rect rRcam) {
    portao->rR.x = portao->x - rRcam.x;
    portao->rR.y = portao->y - rRcam.y;
    portao->rR.w = 48 * 1.5;
    portao->rR.h = 48 * 1.5; 

    portao->sR.y = 0;
    portao->sR.w = 48; portao->sR.h = 48;
    if(portao->contador >= 0 && portao->contador < 24) {
        portao->sR.x = 0;
    }
    else if(portao->contador >= 24 && portao->contador < 48) {
        portao->sR.x = 48;
    }
    else if(portao->contador >= 48 && portao->contador < 72) {
        portao->sR.x = 72;
    }
    else if(portao->contador >= 72 && portao->contador < 96) {
        portao->sR.x = 96;
    }



    if(portao->contador < 96)
        portao->contador++;
    else if(portao->contador >= 96) {
        portao->contador = 96;
    }
    
}





/* 
void changeBookValor(int i){
  sprintf(numerodepocoes, "%d", book.potion.cura);
  fontePote = TTF_RenderText_Solid(fonte, numerodepocoes, cor);
  text[i] = SDL_CreateTextureFromSurface(render, fontePote);
  SDL_QueryTexture(text[i], NULL, NULL, &textRect.w, &textRect.h);
}
*/


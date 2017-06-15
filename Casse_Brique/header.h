#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

#define COUT_JAUNE 10
#define COUT_ROUGE 25
#define COUT_BLEU 50
#define COUT_VERT 100


//Option de build dans les linker setting mettre les libSDL2main.a libSDL2.dll.a
//Dans search directory
//Option de build compiler mettre les include
//Option de build linker mettre les lib

//mettre dans build linker -lmingw32

typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_texture[5];
     SDL_Surface *g_surface;


}game;

typedef struct gameState{

    int g_bRunning;
    int left;
    int right;


}gameState;

typedef struct font{

    TTF_Font *g_font;

}font;

typedef struct coordonnees{

    double x;
    double y;



}coordonnees;

typedef struct raquette{

    coordonnees pos;
    int h;
    int w;
    int vitesse;
    int score;
    int vie;

}raquette;

typedef struct briques{

    coordonnees pos;
    int h;
    int w;
    int destoy;
    int cou;

}briques;

typedef struct cercle{

    coordonnees pos;
    int h;
    int w;
    coordonnees centre;
    float vitesse;
    float modif;
    int HautBas;
    int GaucheDroite;

}cercle;

enum VerifEcran { Haut,Bas,Gauche,Droite,GaucheHaut,GaucheBas,DroiteHaut,DroiteBas };

void initJoueur(raquette *joueur);
void reInitJoueur(raquette *joueur);
void dessineRaquette(raquette *joueur,game *myGame);
int verifCollRaquette(raquette *joueur);
void handleEvents(cercle *balle,raquette *joueur,int key[],gameState *state);
void UpdateEvents(gameState *state,int key[]);
int verifRenvoiBalle(cercle *balle,raquette *joueur);

void initBalle(cercle *balle);
void dessineBalle(cercle *balle,game *myGame,gameState *state);
void DeplaceBalle(cercle *balle,raquette *joueur);
void DirectionBalle(cercle *balle,raquette *joueur,int key[]);
int VerifCollEcran(cercle *balle);
int verifCollBalle(cercle *balle,raquette *joueur);

void dessineBordure(game *myGame, gameState *state);

void dessineBrique(briques brique[16][15],game *myGame, gameState *state);
void initBrique(briques brique[16][15]);
int verifCollBrique(cercle *balle,briques brique);
void destroyBrique(cercle *balle,briques brique[16][15]);
void gestScore(raquette *joueur,briques brique[16][15]);

void initTexture(game *myGame,briques brique[16][15],cercle *balle,raquette *joueur);

int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame,font *mFont);
void writeSDL(game *myGame,font mFont,raquette *joueur);
void delay(unsigned int frameLimit);
void destroyTexture(game *myGame);
void destroy(game *myGame);

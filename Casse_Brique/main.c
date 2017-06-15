
#include "header.h"

int main(int argc, char *argv[])
{

     game myGame;
     gameState state;
     font mFont;

    //Pour les 60 fps
    unsigned int frameLimit = SDL_GetTicks() + 16;

    raquette joueur;
    cercle balle;
    briques brique[16][15];
    int key[4]={0,0,0,0};

    if(init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame,&mFont)){

                state.g_bRunning=1;
    }else{

            return 1;//something's wrong

    }

    initJoueur(&joueur);
    initBalle(&balle);
    initBrique(brique);

    //initTexture(&myGame,brique,&balle,&joueur);

    while(state.g_bRunning){

        UpdateEvents(&state,key);
        handleEvents(&balle,&joueur,key,&state);

        if(key[3]==1){


            DeplaceBalle(&balle,&joueur);
            DirectionBalle(&balle,&joueur,key);
            destroyBrique(&balle,brique);
        }

        dessineRaquette(&joueur,&myGame);

        gestScore(&joueur,brique);
        writeSDL(&myGame,mFont,&joueur);

        dessineBalle(&balle,&myGame,&state);

        dessineBordure(&myGame,&state);
        dessineBrique(brique,&myGame,&state);

        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;

        SDL_RenderPresent(myGame.g_pRenderer); // Affichage
        SDL_RenderClear(myGame.g_pRenderer);
        destroyTexture(&myGame);

        if(joueur.vie<=0){
            state.g_bRunning=0;
        }
    }
    //destroyTexture(&myGame);
    destroy(&myGame);
    SDL_Quit();
  return 0;
}



















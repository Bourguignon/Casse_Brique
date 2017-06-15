#include "header.h"

/*************************************************************************************************
BUT : Initialise la fenetre SDL
ENTREE :
SORTIE :
*************************************************************************************************/

int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame,font *mFont){


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);
                SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 0, 0, 255);
                SDL_RenderClear(myGame->g_pRenderer);

            }
    }else{
        return 0;
    }if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    mFont->g_font=TTF_OpenFont("./assets/fonts/American/American Captain.ttf",65);

    return 1;
}

/*************************************************************************************************
BUT : Ecrit dans la surface
ENTREE : La fenetre et la police
SORTIE : Affiche le texte dans la fenetre
*************************************************************************************************/

void writeSDL(game *myGame,font mFont,raquette *joueur) {

char score[15] ="";

        sprintf(score,"score %i",joueur->score);

        SDL_Color fontColor={255,255,255};

        myGame->g_surface=TTF_RenderText_Blended(mFont.g_font, score, fontColor);//Charge la police

        if(myGame->g_surface){


                //Définition du rectangle dest pour blitter la chaine
                SDL_Rect rectangle;
                rectangle.x=100;//debut x
                rectangle.y=(SCREEN_HEIGHT)-350;//debut y
                rectangle.w=60; //Largeur
                rectangle.h=25; //Hauteur


                 myGame->g_texture[4] = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation de la texture pour la chaine
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                 if(myGame->g_texture[4]){

                        SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture[4],NULL,&rectangle); // Copie du sprite grâce au SDL_Renderer
                 }
                 else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }

        }else{
            fprintf(stdout,"Échec de creation surface pour chaine (%s)\n",SDL_GetError());
        }
}

/*************************************************************************************************
BUT : Dessine les bordure
ENTREE :
SORTIE :
*************************************************************************************************/

void dessineBordure(game *myGame, gameState *state){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load("./assets/side.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture[3] = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture[3]){

                    rectangleSource.x=0;//128*(int)((SDL_GetTicks()/100)%6);
                    rectangleSource.y=0;
                    rectangleSource.w=16;//1 image = w:128 et h:82
                    rectangleSource.h=SCREEN_HEIGHT;

                    SDL_QueryTexture(myGame->g_texture[3],NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=0;//debut x
                    rectangleDest.y=0;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture[3],&rectangleSource,&rectangleDest);

                    rectangleSource.x=0;//128*(int)((SDL_GetTicks()/100)%6);
                    rectangleSource.y=0;
                    rectangleSource.w=16;//1 image = w:128 et h:82
                    rectangleSource.h=SCREEN_HEIGHT;

                    SDL_QueryTexture(myGame->g_texture[3],NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=SCREEN_WIDTH-16;//debut x
                    rectangleDest.y=0;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture[3],&rectangleSource,&rectangleDest);
                }
                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }
        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }
        //destroyTexture(myGame);
}

/*************************************************************************************************
BUT : Bloque le jeu a 60fps
ENTREE :
SORTIE :
*************************************************************************************************/

void delay(unsigned int frameLimit){
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}

/*************************************************************************************************
BUT : Detruit la fenetre
ENTREE :
SORTIE :
*************************************************************************************************/

void destroy(game *myGame){

    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}

/*************************************************************************************************
BUT : detruit la texture
ENTREE :
SORTIE :
*************************************************************************************************/

void destroyTexture(game *myGame){

int i;
    //Destroy texture
    for(i=0;i<5;i++){
        if(myGame->g_texture[i]!=NULL)
            SDL_DestroyTexture(myGame->g_texture[i]);
    }

}



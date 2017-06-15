#include "header.h"

/*************************************************************************************************
BUT : Init le joueur
ENTREE : le joueur
SORTIE :
*************************************************************************************************/

void initJoueur(raquette *joueur){

    joueur->h=32;
    joueur->w=128;
    joueur->pos.x=SCREEN_WIDTH/2-joueur->w/2;
    joueur->pos.y=SCREEN_HEIGHT-joueur->h;
    joueur->vitesse=10;
    joueur->score=0;
    joueur->vie=3;
}

/*************************************************************************************************
BUT : Init le joueur
ENTREE : le joueur
SORTIE :
*************************************************************************************************/

void reInitJoueur(raquette *joueur){

    joueur->h=32;
    joueur->w=128;
    joueur->pos.x=SCREEN_WIDTH/2-joueur->w/2;
    joueur->pos.y=SCREEN_HEIGHT-joueur->h;
    joueur->vitesse=10;
}

/*************************************************************************************************
BUT : Dessine la raquette
ENTREE : la raquette
SORTIE : La raquette se dessine
*************************************************************************************************/

void dessineRaquette(raquette *joueur, game *myGame){


        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load("./assets/paddle.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                myGame->g_texture[0] = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture[0]){

                    rectangleSource.x=0;//128*(int)((SDL_GetTicks()/100)%6);
                    rectangleSource.y=0;
                    rectangleSource.w=joueur->w;//1 image = w:128 et h:82
                    rectangleSource.h=joueur->h;

                    SDL_QueryTexture(myGame->g_texture[0],NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=joueur->pos.x;//debut x
                    rectangleDest.y=joueur->pos.y;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture[0],&rectangleSource,&rectangleDest);
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
BUT : Affecte les entres clavier a un tableau
ENTREE : le tableau d'entier
SORTIE : le tableau d'entier affecter
*************************************************************************************************/

void UpdateEvents(gameState *state,int key[]){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_SPACE:key[3]=1;break;
                                case SDLK_LEFT:key[1]=1;break;
                                case SDLK_RIGHT:key[2]=1;break;
                                case SDLK_ESCAPE:key[0]=1;break;
                            }
                            break;

        case SDL_KEYUP:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:key[1]=0;break;
                                case SDLK_RIGHT:key[2]=0;break;
                            }
                            break;
        default:break;

        }
    }
}

/*************************************************************************************************
BUT : Deplace la raquette
ENTREE : la raquette et un tableau d'entier
SORTIE : La raquette se deplace
*************************************************************************************************/

void handleEvents(cercle *balle,raquette *joueur,int key[],gameState *state){

    if(key[3]==1){
        if((key[1]==1)&&(verifCollRaquette(joueur)!=Gauche)){

            joueur->pos.x-=joueur->vitesse;
        }else if((key[2]==1)&&(verifCollRaquette(joueur)!=Droite)){

            joueur->pos.x+=joueur->vitesse;
        }
        if((balle->GaucheDroite==2)&&(balle->HautBas==2)){

            verifRenvoiBalle(balle,joueur);
            balle->HautBas=1;
        }

    }else if(key[3]==0){
        if((key[1]==1)&&(verifCollBalle(balle,joueur)!=Gauche)){

            balle->pos.x-=balle->vitesse;
            balle->centre.x-=balle->vitesse;
        }else if((key[2]==1)&&(verifCollBalle(balle,joueur)!=Droite)){

            balle->pos.x+=balle->vitesse;
            balle->centre.x+=balle->vitesse;
        }

    }


        if(key[0]==1){

        state->g_bRunning=0;
    }
}

/*************************************************************************************************
BUT : verifie si la raquette est au bord de l'ecran
ENTREE : la raquette
SORTIE : le cote de l'ecran ou la raquette est
*************************************************************************************************/

int verifCollRaquette(raquette *joueur){

    if(joueur->pos.x<=16){

        return Gauche;
    }else if(joueur->pos.x+joueur->w>=SCREEN_WIDTH-16){

        return Droite;
    }
    return 0;
}

/*************************************************************************************************
BUT : verifie si la balle entre en colision avec la raquette
ENTREE : la balle et le joueur
SORTIE :
*************************************************************************************************/

int verifRenvoiBalle(cercle *balle,raquette *joueur){

int i;

    if(balle->GaucheDroite==2){
        if(balle->pos.x+balle->w<=joueur->pos.x+joueur->w/2){

            balle->GaucheDroite=1;
        }else if(balle->pos.x>=joueur->pos.x+joueur->w/2){

            balle->GaucheDroite=0;
        }else{

            balle->GaucheDroite=rand()%2;
        }
    }else{

        if((balle->pos.x>=joueur->pos.x)&&(balle->pos.x+balle->w<=joueur->pos.x+joueur->w)
        &&(balle->pos.y+balle->h>=joueur->pos.y)){

            for(i=0;i<joueur->w;i++){

                if(balle->pos.x==joueur->pos.x+i){
                    balle->modif=(i*0.1);
                }
            }

            return Bas;
        }
    }
    return 5;
}

/*************************************************************************************************
BUT : gere le score
ENTREE : la raquette et les briques
SORTIE : le score est incrementer
*************************************************************************************************/

void gestScore(raquette *joueur,briques brique[16][15]){

int i,j;

    for(i=0;i<16;i++){
        for(j=0;j<15;j++){
            if((brique[i][j].destoy==1)&&(brique[i][j].cou!=0)){

                joueur->score+=brique[i][j].cou;
                brique[i][j].cou=0;
            }
        }
    }
}

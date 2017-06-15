#include "header.h"

/*************************************************************************************************
BUT : Init la balle
ENTREE : la balle
SORTIE :
*************************************************************************************************/

void initBalle(cercle *balle){

    balle->h=24;
    balle->w=24;
    balle->pos.y=SCREEN_HEIGHT-32-balle->h;
    balle->pos.x=SCREEN_WIDTH/2-balle->w/2;
    balle->centre.x=balle->pos.x+balle->w/2;
    balle->centre.y=balle->pos.y+balle->h/2;
    balle->HautBas=2;
    balle->GaucheDroite=2;
    balle->vitesse=5;
    balle->modif=0;
}

/*************************************************************************************************
BUT : Dessine la balle
ENTREE : la balle
SORTIE : La balle se dessine
*************************************************************************************************/

void dessineBalle(cercle *balle,game *myGame,gameState *state){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;

        myGame->g_surface = IMG_Load("./assets/ball.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture[1] = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture[1]){

                    rectangleSource.x=0;//128*(int)((SDL_GetTicks()/100)%6);
                    rectangleSource.y=0;
                    rectangleSource.w=balle->w;//1 image = w:128 et h:82
                    rectangleSource.h=balle->h;

                    SDL_QueryTexture(myGame->g_texture[1],NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=balle->pos.x;//debut x
                    rectangleDest.y=balle->pos.y;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture[1],&rectangleSource,&rectangleDest);

                    //SDL_RenderClear(myGame->g_pRenderer);
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
BUT : Deplace la balle
ENTREE : la balle
SORTIE : La balle se deplace
*************************************************************************************************/

void DeplaceBalle(cercle *balle,raquette *joueur){

//int i;
    if(balle->HautBas==0){

        balle->pos.y+=balle->vitesse;
        balle->centre.y+=balle->vitesse;
    }else if(balle->HautBas==1){

        balle->pos.y-=balle->vitesse;
        balle->centre.y-=balle->vitesse;
    }

    if(balle->GaucheDroite==0){

        balle->pos.x+=balle->vitesse+balle->modif;
        balle->centre.x+=balle->vitesse+balle->modif;
    }else if(balle->GaucheDroite==1){

        balle->pos.x-=balle->vitesse+balle->modif;
        balle->centre.x-=balle->vitesse+balle->modif;
    }
}

/*************************************************************************************************
BUT : Gere la direction de la balle
ENTREE : la balle et les raquette
SORTIE : La balle change de direction si elle touche les raquette ou le bord de l'ecran
*************************************************************************************************/

void DirectionBalle(cercle *balle,raquette *joueur,int key[]){

    if(VerifCollEcran(balle)==Droite){

        balle->GaucheDroite=1;
    }else if(VerifCollEcran(balle)==Gauche){

        balle->GaucheDroite=0;
    }else if(verifRenvoiBalle(balle,joueur)==Bas){

        balle->HautBas=1;
    }else if(VerifCollEcran(balle)==Haut){

        balle->HautBas=0;
    }else if(VerifCollEcran(balle)==Bas){

        initBalle(balle);
        reInitJoueur(joueur);
        joueur->vie-=1;
        key[3]==0;
    }
}

/*************************************************************************************************
BUT : Verifie la sortie de l'ecran
ENTREE : Des coordonne
SORTIE : Le coté de l'ecran ou l'objet est sortie
*************************************************************************************************/

int VerifCollEcran(cercle *balle){

    if(balle->pos.y<=0){

        return Haut;
    }else if(balle->pos.y>=SCREEN_HEIGHT+balle->h){

        return Bas;
    }else if(balle->pos.x<=16){

        return Gauche;
    }else if(balle->pos.x>=SCREEN_WIDTH-balle->w-16){

        return Droite;
    }
    return 4;
}

int verifCollBalle(cercle *balle,raquette *joueur){

    if(balle->pos.x<=joueur->pos.x){

        return Gauche;
    }else if(balle->pos.x+balle->w>=joueur->pos.x+joueur->w){

        return Droite;
    }
    return 0;
}


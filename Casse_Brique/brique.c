#include "header.h"

/*************************************************************************************************
BUT : init le briques
ENTREE :
SORTIE :
*************************************************************************************************/

void initBrique(briques brique[16][15]){

int i,j;

    for(i=0;i<16;i++){
        for(j=0;j<15;j++){
            brique[i][j].h=50/2;
            brique[i][j].w=130/2;
            brique[i][j].pos.x=24+(j*brique[i][j].w);
            brique[i][j].pos.y=(i*brique[i][j].h);
            brique[i][j].destoy=0;

            if(rand()%4==0){

            brique[i][j].cou=COUT_ROUGE;
            }else if(rand()%4==1){

            brique[i][j].cou=COUT_BLEU;
            }else if(rand()%4==2){

            brique[i][j].cou=COUT_VERT;
            }else{

            brique[i][j].cou=COUT_JAUNE;
            }
        }
    }
}

/*************************************************************************************************
BUT : Dessine les briques
ENTREE :
SORTIE :
*************************************************************************************************/

void dessineBrique(briques brique[16][15],game *myGame, gameState *state){

int i,j;

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;

        srand(time(NULL));
        myGame->g_surface = IMG_Load("./assets/bricks.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture[2] = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture[2]){

                    for(i=0;i<16;i++){
                        for(j=0;j<15;j++){
                            if(brique[i][j].destoy==0){
                                if(brique[i][j].cou==COUT_ROUGE){
                                rectangleSource.x=0;//128*(int)((SDL_GetTicks()/100)%6);
                                rectangleSource.y=0;
                                }else if(brique[i][j].cou==COUT_JAUNE){
                                rectangleSource.x=brique[i][j].w;//128*(int)((SDL_GetTicks()/100)%6);
                                rectangleSource.y=0;
                                }else if(brique[i][j].cou==COUT_VERT){
                                rectangleSource.x=0;//128*(int)((SDL_GetTicks()/100)%6);
                                rectangleSource.y=brique[i][j].h;
                                }else if(brique[i][j].cou==COUT_BLEU){
                                rectangleSource.x=brique[i][j].w;//128*(int)((SDL_GetTicks()/100)%6);
                                rectangleSource.y=brique[i][j].h;
                                }

                                rectangleSource.w=brique[i][j].w;//1 image = w:128 et h:82
                                rectangleSource.h=brique[i][j].h;

                                SDL_QueryTexture(myGame->g_texture[2],NULL,NULL,NULL,NULL);

                                //Définition du rectangle dest pour dessiner Bitmap
                                rectangleDest.x=brique[i][j].pos.x;//debut x
                                rectangleDest.y=brique[i][j].pos.y;//debut y
                                rectangleDest.w=rectangleSource.w; //Largeur
                                rectangleDest.h=rectangleSource.h; //Hauteur

                                SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture[2],&rectangleSource,&rectangleDest);
                            }
                        }
                    }

                    //SDL_RenderClear(myGame->g_pRenderer);
                }
                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }
        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }
    destroyTexture(myGame);
}

/*************************************************************************************************
BUT : Detruit les briques si colision
ENTREE : balle briques
SORTIE : les briques detruite si collision
*************************************************************************************************/

void destroyBrique(cercle *balle,briques brique[16][15]){

int i,j;

    for(i=0;i<16;i++){
        for(j=0;j<15;j++){
            if(brique[i][j].destoy==0){
                if(verifCollBrique(balle,brique[i][j])==Haut){

                    brique[i][j].destoy=1;
                    balle->HautBas=1;
                }else if(verifCollBrique(balle,brique[i][j])==Bas){

                    brique[i][j].destoy=1;
                    balle->HautBas=0;
                }else if(verifCollBrique(balle,brique[i][j])==Gauche){

                    brique[i][j].destoy=1;
                    balle->GaucheDroite=0;
                }else if(verifCollBrique(balle,brique[i][j])==Droite){

                    brique[i][j].destoy=1;
                    balle->GaucheDroite=1;
                }
            }
        }
    }
}

/*************************************************************************************************
BUT : verifie si les brique son en collision avec la balle et de quel coté
ENTREE : la balle brique
SORTIE : enum HBGD
*************************************************************************************************/

int verifCollBrique(cercle *balle,briques brique){


        if((balle->centre.x+balle->w/2>=brique.pos.x)&&(balle->centre.x-balle->w/2<=brique.pos.x+brique.w)
        &&(balle->centre.y+balle->h/2>=brique.pos.y)&&(balle->centre.y-balle->h/2<=brique.pos.y+brique.h)){
            if((balle->centre.x+balle->w/2>=brique.pos.x)&&(balle->centre.x+balle->w/2<=brique.pos.x+10)){

                return Droite;
            }else if((balle->centre.x-balle->w/2<=brique.pos.x+brique.w)&&(balle->centre.x-balle->w/2>=brique.pos.x+brique.w-10)){

                return Gauche;
            }else if((balle->centre.y+balle->h/2>=brique.pos.y)&&(balle->centre.y+balle->h/2<=brique.pos.y+10)){

                return Haut;
            }else if((balle->centre.y-balle->h/2<=brique.pos.y+brique.h)&&(balle->centre.y-balle->h/2>=brique.pos.y+brique.h-10)){

                return Bas;
            }
        }
    return 5;
}
void initTexture(game *myGame,briques brique[16][15],cercle *balle,raquette *joueur){

        myGame->g_surface = IMG_Load("./assets/paddle.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture[0] = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface);

                 dessineRaquette(joueur,myGame);

        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

}

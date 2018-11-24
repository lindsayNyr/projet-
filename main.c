//
//  main.c
//  towerDefense
//
//  Created by Lindsay Noyer on 21/10/2018.
//  Copyright © 2018 Lindsay Noyer. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <unistd.h>
#include <SDL/SDL_ttf.h>
#include <math.h>

#include "event.h"
#include "structure.h"
#include "attaque.h"
#include "define.h"
#include "menuevent.h"
#include "fonctions.h"


int main(int argc,char** argv){
   
    // init variables 
    int i,j, colorkey, colorkey2, colorkey3;
    int k = 1;
    int towerPositionning = 0;
    int gameover = 0;
    FILE* fichier = NULL;
    int currentDirection = 0;  /* Information about the current situation of the sprite: */
    int animationFlip = 0;   /* Information about the animationFlip of the sprite: */
    int l =0;
    int m = 0;
    int estVivant = 1;
    int cpt=0;
    
    

    
        SDL_Rect positiontexte;

    


    TTF_Font *police = NULL;

    SDL_Color couleurNoire = {0, 0, 0};



    int  argent = 50;

    char tableauargent[20] = ""; /* Tableau de char suffisamment grand */


    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();
    
    
    
    
    
    
    

    //init tableau 
    int map[WIDTH_MAP][HEIGHT_MAP];
    int towerArray[WIDTH_MAP][HEIGHT_MAP];

    //init SDL
    SDL_Surface *screen, *tileset, *towerblack, *sprite, *temp, *explosion, *HB, *missile, *texte ;
    SDL_Surface *menu = NULL; ///Initialise la surface qui servira de menu
    SDL_Event event;
    
SDL_Event touche; ///Initialise un évnènement qui servira à récupérer la saisie au clavier de la touche entrée



SDL_Rect MENU;
MENU.x = 0;
MENU.y = 0;

    
    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO); 

    /* set the title bar */
    SDL_WM_SetCaption("🏦 TOWER DEFENSE 🏦", NULL);

    /* create window */
    screen = SDL_SetVideoMode(TAILLE*WIDTH_MAP, TAILLE*HEIGHT_MAP, TAILLE, SDL_HWSURFACE|SDL_DOUBLEBUF);
    

    
    temp = SDL_LoadBMP("images/menu.bmp");
    menu = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    
    
    
    
    SDL_BlitSurface(menu, NULL, screen, &MENU); ///Colle le menu sur l'écran
    SDL_UpdateRect(screen,0,0,0,0);
  
    
    
    
    
    
    
    
    int compteur = 1;
    
    
    while(compteur == 1 && gameover == 0){
        if (SDL_PollEvent(&touche)) {
            MenuEvent(touche, &compteur, &gameover);
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    //load towers
    temp = SDL_LoadBMP("images/tower_3.bmp");
    towerblack = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    
    //load sprite
    temp = SDL_LoadBMP("images/sprite.bmp");
    sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    //load sprite
    temp = SDL_LoadBMP("images/tiles.bmp");
    tileset = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    //load exposion
    temp = SDL_LoadBMP("images/boum.bmp");
    explosion = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    // load HealthBar
    temp = SDL_LoadBMP("images/HB.bmp");
    HB = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    
    temp = SDL_LoadBMP("images/missile.bmp");
    missile = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);  
    
    /* setup launcher colorkey and turn on RLE */
    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    colorkey2 = SDL_MapRGB(screen->format, 0, 0, 0);
    colorkey3 = SDL_MapRGB(screen->format, 255,255, 255);

    SDL_SetColorKey(towerblack, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(explosion, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(HB, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey3);
    SDL_SetColorKey(missile, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey3);

    //déclaration d'un ennemi
    struct Enemy mechant;
    mechant.HP = 100;
    mechant.vitesse = 1;
    mechant.Position.x = 0;
    mechant.Position.y = 0;
    
    //declaration d'une tour
    struct Tower tower1;
    tower1.distAttaque = 3;
    tower1.degats = 10;   //par tile
    tower1.cout = 10;
    tower1.Position.x = 10*32;
    tower1.Position.y = 17*32; 
    

    
    
    
   
    if (!tileset){
       
        printf("Echec de chargement tileset.bmp\n");
        SDL_Quit();
        system("pause");
        exit(-1);
    }

    fichier = fopen("level.txt", "r");
        
    if (fichier != NULL){
    
        for(i=0; i<HEIGHT_MAP; i++){
            for(j=0; j<WIDTH_MAP; j++){
                   
                fscanf(fichier,"%d", &map[j][i]);
            }
        }
    }

    else {
         
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier level.txt");
        
    }

    
    /*init tab */
         
    for(j=0; j<WIDTH_MAP; j++){
        for(i=0; i<HEIGHT_MAP; i++){
    		  
            towerArray[j][i] = 0 ;    
            if ( j == 0  && i == HEIGHT_MAP-1 ){
    		   
                towerArray[j][i] = 1;     
    		}
	   }  
	}
    
//     AfficherMap(screen,tileset,map);
 
    /* Define the source rectangle for the BlitSurface tower */
    SDL_Rect towerImage;
    towerImage.x = 0;
    towerImage.y = 0;
    towerImage.w = TAILLE+8;
    towerImage.h = TAILLE+8;

    /* Define the source rectangle for the BlitSurface sprite */
    SDL_Rect spriteImage;
    spriteImage.y = 0;
    spriteImage.w = TAILLE;
    spriteImage.h = TAILLE;

    /* Define the source rectangle for the BlitSurface HB */
    SDL_Rect HBImage;
    HBImage.y = 0;
    HBImage.x = 0;
    HBImage.w = TAILLE;
    HBImage.h = TAILLE;   

//     /* Define the source rectangle for the BlitSurface missile */
//     SDL_Rect missileImage;
//     missileImage.y = 0;
//     missileImage.x = 0;
//     missileImage.w = TAILLE;
//     missileImage.h = TAILLE;
    
    
    /* Define the source rectangle for the BlitSurface explosion */
    SDL_Rect explosionImage;
    explosionImage.y = 0;
    explosionImage.x = 0;
    explosionImage.w = TAILLE;
    explosionImage.h = TAILLE; 

    SDL_Rect HBPosition;

    
    int copie_map[WIDTH_MAP][HEIGHT_MAP];
    for (i=0;i<=HEIGHT_MAP+1;i++){
        for (j=0;j<=HEIGHT_MAP+1;j++){
           
            copie_map[i][j] = map[i][j];

        }
    }
    
    

    //i = 0;
   // j = 0;
    


    
    
            /* Chargement de la police */

    police = TTF_OpenFont("arial.ttf", 30);


    /* Initialisation du texte */



    sprintf(tableauargent, "Temps : %d", argent);

    texte = TTF_RenderText_Blended(police, tableauargent, couleurNoire);
    
    
    positiontexte.x = 15*TAILLE;

    positiontexte.y = 0;
    
    
    while (mechant.Position.x < 20*30 && gameover == 0){

        HBPosition.y = mechant.Position.y - 22;
        HBPosition.x = mechant.Position.x;
        
        if (SDL_PollEvent(&event)) {
           
            HandleEvent(event, &gameover, &tower1.Position, &towerPositionning, &argent, &tower1.cout);
        }
        
        Deplacement(&mechant, copie_map, &currentDirection,&animationFlip, &l, &m, &k);
        AfficherMap(screen,tileset,map);
        
        spriteImage.x = TAILLE*(2*currentDirection + animationFlip);
        
        if (mechant.HP>0){
           
            SDL_BlitSurface(sprite, &spriteImage, screen, &mechant.Position);
        }
        
        if (towerPositionning == 1){
            towerArray[tower1.Position.x/TAILLE][tower1.Position.y/TAILLE] = 1;
            towerPositionning = 0;
        }
       
     
 		for (j=0;j< WIDTH_MAP;j++){
            for (i=0;i<HEIGHT_MAP-1;i++){
                if ( map[j][i] != 1){
                    towerArray[j][i] = 0;
                }
            }
        }
              
        for (j=0;j< WIDTH_MAP;j++){
            for (i=0;i<HEIGHT_MAP;i++){
                if ( towerArray[j][i] == 1){
			     
                    tower1.Position.x = j*TAILLE;
                    tower1.Position.y = i*TAILLE;
                    SDL_BlitSurface(towerblack, &towerImage, screen, &tower1.Position);  
			    }
			}
		}
		
		
		
            sprintf(tableauargent, "argent : %d", argent); /* On écrit dans la chaîne "temps" le nouveau temps */

            SDL_FreeSurface(texte); /* On supprime la surface précédente */

            texte = TTF_RenderText_Blended(police, tableauargent, couleurNoire); /* On écrit la chaîne temps dans la SDL_Surface */
            SDL_BlitSurface(texte, NULL, screen, &positiontexte); /* Blit du texte */
		
		
		
		
		
        
        SDL_BlitSurface(HB, &HBImage, screen, &HBPosition);
        
        if (mechant.HP<=0 && estVivant == 1){       //quand un ennemi meurt
//             for (i=0; i<4; i++){
                for (j=0; j<4; j++){
                    
                    explosionImage.x = j*TAILLE ;
//                     explosionImage.y = i*TAILLE ;
                    SDL_BlitSurface(explosion, &explosionImage, screen, &mechant.Position);
                    SDL_Delay(150);
                    SDL_BlitSurface(towerblack, &towerImage, screen, &tower1.Position);
                    SDL_UpdateRect(screen,0,0,0,0);
                    SDL_BlitSurface(texte, NULL, screen, &positiontexte); /* Blit du texte */
                    estVivant = 0;
                }
//             }   
            argent += 10;
        }
        SDL_BlitSurface(towerblack, &towerImage, screen, &tower1.Position);
        for (j=0;j< WIDTH_MAP;j++){
            for (i=0;i<HEIGHT_MAP-1;i++){
                if ( towerArray[j][i] == 1){
			      
                    tower1.Position.x = j*TAILLE;
                    tower1.Position.y = i*TAILLE;
                      
                    if (estAPortee(&tower1, &mechant)&& (mechant.HP >0)){
                        DrawLine(screen, tower1.Position.x,tower1.Position.y, mechant.Position.x, mechant.Position.y, 3000);
                        Attack(&tower1, &mechant, &HBImage, &cpt);
                    }
                }
            }
        }
        SDL_UpdateRect(screen,0,0,0,0);
    }

    
    printf("GAMEOVER\n");

    /* clean up */
    SDL_FreeSurface(tileset);
    SDL_FreeSurface(HB);
    SDL_FreeSurface(sprite);
    SDL_FreeSurface(towerblack);
    SDL_FreeSurface(screen);

    SDL_Quit();

    return EXIT_SUCCESS;

    
 }




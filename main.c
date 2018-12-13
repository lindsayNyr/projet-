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

#include "move.h"

#include "map.h"
#include "score.h"
#include "tower.h"
#include "enemy.h"



int main(int argc,char** argv){
   
    // init variables 
    FILE *fichierScore = NULL;
    
    int y, colorkey, colorkey2, colorkey3;
    
    int towerFlagBlack = 0 , towerFlagBlue = 0, gameover = 0, click = 0, recordActuel = 0, 
        nbEnnemisTues = 0, p = 0, finVague = 0, prem = 0 ; 
    
    int argent = 50, compteurMenu = 1, cptEnemy = 2, nbVie = 3, nbVagues = 10;
    


 
    recordActuel = recupScore(fichierScore, recordActuel);

    //init tableaux 
    int towerAttack[WIDTH_MAP][HEIGHT_MAP];
    int map[WIDTH_MAP][HEIGHT_MAP];
    int towerArray[WIDTH_MAP][HEIGHT_MAP];
    char ArgentArray[20] = ""; /* Tableau de char suffisamment grand */
    char ScoreArray[20] = "";
    struct Enemy *EnemyTab = malloc(sizeof(Enemy) * cptEnemy);
   
    //init SDL
    SDL_Surface *screen, *tileset, *towerblack, *towerblue, *sprite, *temp,
    		    *explosion, *HB, *missile , *texteArgent, *textePlay, *texteQuit,
                *menu, *texteScore;
    
    SDL_Event event;
    SDL_Event eventMenu; //Initialise un évnènement qui servira à récupérer la saisie au clavier de la touche entrée

    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurBlanc = {250, 250,250};


    //init TTF
   SDL_Init(SDL_INIT_VIDEO);
   TTF_Init();
 
   /*	if(TTF_Init() == -1)
	{
	    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    exit(EXIT_FAILURE);
	}*/

	/* Chargement de la police */
    TTF_Font *policeArgent = NULL;
    TTF_Font *policeMenu = NULL;
    policeArgent = TTF_OpenFont("arial.ttf", 50);
    policeMenu = TTF_OpenFont("arial.ttf", 50);


    // init texte ttf
    sprintf(ArgentArray, "Argent : %d", argent);
    texteArgent = TTF_RenderText_Blended(policeArgent, ArgentArray, couleurNoire);
    sprintf(ScoreArray, "Score : %d", recordActuel);
    

    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO); 

    /* set the title bar */
    SDL_WM_SetCaption(" TOWER DEFENSE ", NULL);

    /* create window */
    screen = SDL_SetVideoMode(TAILLE*WIDTH_MAP, TAILLE*HEIGHT_MAP, TAILLE, SDL_HWSURFACE|SDL_DOUBLEBUF);


    //load menu 
    temp = SDL_LoadBMP("images/menu.bmp");
    menu = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    //position menu 
    SDL_Rect MENU;
    MENU.x = 0;
    MENU.y = 0;

    //position texte menu
    SDL_Rect positionTextePlay;
    positionTextePlay.x = 9*TAILLE;
    positionTextePlay.y = 2*TAILLE;
    
    SDL_Rect positionTexteQuit;
    positionTexteQuit.x = 9*TAILLE;
    positionTexteQuit.y = 5*TAILLE;

    //initialisation du texte pour le menu 
    textePlay = TTF_RenderText_Blended(policeMenu, "JOUER", couleurBlanc);  
    texteQuit = TTF_RenderText_Blended(policeMenu, "QUITTER", couleurBlanc);  
    
    SDL_BlitSurface(menu, NULL, screen, &MENU); //Colle le menu sur l'écran
    //blit 
    SDL_BlitSurface(textePlay, NULL, screen, &positionTextePlay); /* Blit du texte */
    SDL_BlitSurface(texteQuit, NULL, screen, &positionTexteQuit); /* Blit du texte */

    SDL_Rect positionTexteScore;
    positionTexteScore.x = (WIDTH_MAP-15)*TAILLE;
    positionTexteScore.y = (HEIGHT_MAP-2)*TAILLE;
    
    sprintf(ScoreArray, "record actuel : %d", recordActuel); /* On écrit dans la chaîne "argent" la nouvelle somme */
    texteScore = TTF_RenderText_Blended(policeArgent, ScoreArray, couleurNoire); /* On écrit la chaîne argent dans la SDL_Surface */
    SDL_BlitSurface(texteScore, NULL, screen, &positionTexteScore); /* Blit du texte */    
    
    
    SDL_UpdateRect(screen,0,0,0,0);

  
    

    while(compteurMenu == 1 && gameover == 0){
       if (SDL_PollEvent(&eventMenu)) {
          MenuEvent(eventMenu, &compteurMenu, &gameover);
       }
    }
    
    SDL_FreeSurface(texteScore);
    
    //clean up menu
    TTF_CloseFont(policeMenu);
    SDL_FreeSurface(textePlay);
    SDL_FreeSurface(texteQuit);
    SDL_FreeSurface(menu);

    
    //load towers
    temp = SDL_LoadBMP("images/tower_red.bmp");
    towerblack = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    temp = SDL_LoadBMP("images/tower_blue.bmp");
    towerblue = SDL_DisplayFormat(temp);
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
    SDL_SetColorKey(towerblue, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(explosion, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(HB, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey3);
    SDL_SetColorKey(missile, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey3);

  
    
      
  
    struct Tower towerBlack;
    struct Tower towerBlue;
    initTower(&towerBlack, &towerBlue);
    ChargerMap(map, tileset);

   /*int tab*/
    initTabTower(towerArray);
    initTabAttack(towerAttack);
    
  
            
    	

    SDL_Rect positionDebut;
    SDL_Rect positionFin;
       

    searchPremTermTile( map, &prem,  &positionDebut,  &positionFin);
    	

    SDL_Rect positionTexteArgent;
	positionTexteArgent.x = (WIDTH_MAP-8)*TAILLE;
    positionTexteArgent.y = (HEIGHT_MAP-2)*TAILLE;

    /* Define the source rectangle for the BlitSurface tower */
    SDL_Rect towerImage;
    towerImage.x = 0;
    towerImage.y = 0;
    towerImage.w = TAILLE_TOWER;
    towerImage.h = TAILLE_TOWER;

    /* Define the source rectangle for the BlitSurface sprite */
    SDL_Rect spriteImage;
    spriteImage.y = 0;
    spriteImage.w = TAILLE;
    spriteImage.h = TAILLE;

    /* Define the source rectangle for the BlitSurface explosion */
    SDL_Rect explosionImage;
    explosionImage.y = 0;
    explosionImage.x = 0;
    explosionImage.w = TAILLE;
    explosionImage.h = TAILLE; 

          
    for (y=0; y < nbVagues; y++){
            
            finVague = 0;
            cptEnemy = cptEnemy+2;
            EnemyTab = realloc(EnemyTab, sizeof(Enemy) * cptEnemy);
           /* if(tmp != NULL){
               
               EnemyTab = tmp;
               free(tmp);
            }*/


        //déclaration d'un ennemi
        initEnemy(EnemyTab, cptEnemy, map, positionDebut, y);

    	while (gameover == 0 && finVague == 0){


            initHBPosition(EnemyTab, cptEnemy);
    	    
            if (SDL_PollEvent(&event)) {
                HandleEvent(event, &gameover, &towerBlack.Position, &towerBlue.Position, &towerBlack.cout, &towerBlue.cout, &argent, &towerFlagBlack, &towerFlagBlue, &click, map);
    		}
    	  
            SDL_Delay(5);
    	
    	   deplacer(EnemyTab, positionFin, 	positionDebut, cptEnemy);
    	   afficherMap(screen,tileset,map);

    	   afficherEnemy(EnemyTab,cptEnemy, sprite,  spriteImage,screen);
    	  
    	   positionTower(&towerFlagBlack, &towerFlagBlue, towerArray,  towerBlack,towerBlue); 
      
    	   afficherTower(towerArray, towerBlack, towerBlue,  screen , towerblue,  towerblack, towerImage );
    	    
    	   sprintf(ArgentArray, "argent : %d", argent); /* On écrit dans la chaîne "argent" la nouvelle somme */
    	   texteArgent = TTF_RenderText_Blended(policeArgent, ArgentArray, couleurNoire); /* On écrit la chaîne argent dans la SDL_Surface */
    	   SDL_BlitSurface(texteArgent, NULL, screen, &positionTexteArgent); /* Blit du texte */ 
    	    
    	  
    	   afficherHB(EnemyTab, cptEnemy, HB, screen);
    	    
    	   
    	    estMort(cptEnemy, EnemyTab,screen,  explosion, explosionImage, &nbEnnemisTues, &argent);
    	    attaquer(cptEnemy, EnemyTab, towerBlue, towerBlack, towerAttack, towerArray, screen, y);

    	    vie(EnemyTab,cptEnemy, &nbVie, &gameover,positionFin);
        

    	    SDL_UpdateRect(screen,0,0,0,0);
     
        	finVague = 1;
        	
            for (p=0; p < cptEnemy; p++){
        	    if (EnemyTab[p].HP > 0){
        		  
                  finVague = 0;
        	    }
        	    
        	}
        	    
        	SDL_Delay(5);
        	initTabAttack(towerAttack);
    	}
    }

    
    newScore(nbEnnemisTues, fichierScore, recordActuel); 
    

    
    printf("GAMEOVER\n");

    /* clean up */
    TTF_CloseFont(policeArgent);
    TTF_Quit();

    free(EnemyTab);
    
    SDL_FreeSurface(texteArgent);
    SDL_FreeSurface(tileset);
    SDL_FreeSurface(HB);
    SDL_FreeSurface(sprite);
    SDL_FreeSurface(towerblack);
    SDL_FreeSurface(towerblue);
    SDL_FreeSurface(explosion);
    SDL_FreeSurface(screen);

    SDL_Quit();

    return EXIT_SUCCESS;
  
}




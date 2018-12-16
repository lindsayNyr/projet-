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

#include <time.h>



int main(int argc,char** argv){

    srand(time(NULL));

   
    
  
  
    // init variables 
    FILE *fichierScore = NULL;
    
    int y ,z ,  colorkey, colorkey2, colorkey3;
    
    int gameover = 0, click = 0, recordActuel = 0, 
        nbEnnemisTues = 0, p = 0, finVague = 0, prem = 0 ; 
    
    int argent = 30, compteurMenu = 1, cptEnemy = 2, nbVie = 10, nbVagues = 10;
    


 
    recordActuel = recupScore(fichierScore, recordActuel);

    //init tableaux 
    int towerAttack[WIDTH_MAP][HEIGHT_MAP];
    int map[WIDTH_MAP][HEIGHT_MAP];
    int towerArray[WIDTH_MAP][HEIGHT_MAP];
    char ArgentArray[20] = ""; /* Tableau de char suffisamment grand */
    char VieArray[20] = "";
    char ScoreArray[20] = "";
    char vagueArray[20] = "";
    struct Enemy *EnemyTab = malloc(sizeof(Enemy) * cptEnemy);
   
    //init SDL
    SDL_Surface *screen, *tileset, *towerblack, *towerblue, *towerblackE, *towerblueE, *sprite, *sprite2, *temp,
    		    *explosion, *HB, *texteArgent, *textePlay, *texteQuit,
                *menu, *texteScore, *texteVie, *texteVague ,*coeur, *piece, *texteDegat1, *texteDegat2, *texteCout1, *texteCout2 ;
    
    SDL_Event event;
    SDL_Event eventMenu; 

    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurBlanc = {250, 250,250};


    //init TTF
   SDL_Init(SDL_INIT_VIDEO);
   TTF_Init();
 

	/* Chargement de la police */
    TTF_Font *police50, *police20 = NULL;

    police50 = TTF_OpenFont("arial.ttf", 50);
    police20 = TTF_OpenFont("arial.ttf", 20);


    // init texte ttf
    sprintf(ArgentArray, "Argent : %d", argent);
    texteArgent = TTF_RenderText_Blended(police50, ArgentArray, couleurNoire);
    sprintf(ScoreArray, "Score : %d", recordActuel);
    
    texteCout1 = TTF_RenderText_Blended(police20, "cout:10", couleurNoire);
    texteCout2 = TTF_RenderText_Blended(police20, "cout:40", couleurNoire);
    texteDegat1 = TTF_RenderText_Blended(police20, "degats:5", couleurNoire);
    texteDegat2 = TTF_RenderText_Blended(police20, "degats:20", couleurNoire);


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
    
    SDL_Rect posDegat1, posDegat2, posCout1, posCout2;
    posDegat1.x = 1*TAILLE;
    posDegat1.y = 21*TAILLE;
    posDegat2.x = 5*TAILLE;
    posDegat2.y = 21*TAILLE;
    posCout1.x = 1*TAILLE;
    posCout1.y = 20*TAILLE;
    posCout2.x = 5*TAILLE;
    posCout2.y = 20*TAILLE;
    

    //position texte menu
    SDL_Rect positionTextePlay;
    positionTextePlay.x = 9*TAILLE;
    positionTextePlay.y = 2*TAILLE;
    
    SDL_Rect positionTexteQuit;
    positionTexteQuit.x = 9*TAILLE;
    positionTexteQuit.y = 5*TAILLE;

    //initialisation du texte pour le menu 
    textePlay = TTF_RenderText_Blended(police50, "JOUER", couleurBlanc);  
    texteQuit = TTF_RenderText_Blended(police50, "QUITTER", couleurBlanc);  
    
    SDL_BlitSurface(menu, NULL, screen, &MENU); //Colle le menu sur l'écran
    //blit 
    SDL_BlitSurface(textePlay, NULL, screen, &positionTextePlay); /* Blit du texte */
    SDL_BlitSurface(texteQuit, NULL, screen, &positionTexteQuit); /* Blit du texte */

    SDL_Rect positionTexteScore;
    positionTexteScore.x = (WIDTH_MAP-15)*TAILLE;
    positionTexteScore.y = (HEIGHT_MAP-2)*TAILLE;
    
    sprintf(ScoreArray, "record actuel : %d", recordActuel); 
    texteScore = TTF_RenderText_Blended(police50, ScoreArray, couleurNoire); 
    SDL_BlitSurface(texteScore, NULL, screen, &positionTexteScore);    
    
    
    SDL_UpdateRect(screen,0,0,0,0);

  
    

    while(compteurMenu == 1 && gameover == 0){
       if (SDL_PollEvent(&eventMenu)) {
          MenuEvent(eventMenu, &compteurMenu, &gameover);
       }
    }
    
    SDL_FreeSurface(textePlay);
    SDL_FreeSurface(texteQuit);
    SDL_FreeSurface(texteScore);
    SDL_FreeSurface(menu);
    
    //clean up menu


    
    //load towers
    temp = SDL_LoadBMP("images/tower_red.bmp");
    towerblack = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    temp = SDL_LoadBMP("images/tower_blue.bmp");
    towerblue = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    temp = SDL_LoadBMP("images/tower_violet.bmp");
    towerblackE = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    
    
    temp = SDL_LoadBMP("images/tower_green.bmp");
    towerblueE = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    
    //load sprite
    temp = SDL_LoadBMP("images/sprite.bmp");
    sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    temp = SDL_LoadBMP("images/sprite2.bmp");
    sprite2 = SDL_DisplayFormat(temp);
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


    temp = SDL_LoadBMP("images/coeur.bmp");
    coeur = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    
    
    temp = SDL_LoadBMP("images/piece.bmp");
    piece = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    
    /* setup launcher colorkey and turn on RLE */
    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    colorkey2 = SDL_MapRGB(screen->format, 0, 0, 0);
    colorkey3 = SDL_MapRGB(screen->format, 255,255, 255);


    SDL_SetColorKey(towerblack, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(towerblue, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(towerblackE, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(towerblueE, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(sprite2, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey3);
    SDL_SetColorKey(explosion, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(HB, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey3);
    SDL_SetColorKey(coeur, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(piece, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
   
  	struct Tower towerBlack;
    struct Tower towerBlue;
    struct Tower towerBlackE;
    struct Tower towerBlueE;

    initTower(&towerBlack, &towerBlue, &towerBlackE, &towerBlueE);


   /*int tab*/

    initTabAttack(towerAttack);
    

    SDL_Rect positionDebut;
    SDL_Rect positionFin;
    SDL_Rect posPiece;       
    SDL_Rect posCoeur;

    posPiece.x = 19*TAILLE;
    posPiece.y = 20*TAILLE;	
    posCoeur.x = 13*TAILLE;
    posCoeur.y = 20*TAILLE;   
    
    SDL_Rect positionTexteArgent;
	positionTexteArgent.x = (WIDTH_MAP-8)*TAILLE;
    positionTexteArgent.y = (HEIGHT_MAP-2)*TAILLE;
    
    SDL_Rect posVie;
    posVie.x = 11*TAILLE;
    posVie.y =20*TAILLE;    
    SDL_Rect posVague;
    posVague.x = (WIDTH_MAP-7)*TAILLE;
    posVague.y = 0;
    
    
    
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

    
   for (z=1; z<=2; z++){
    
    ChargerMap(map, tileset, z);
	searchPremTermTile( map, &prem,  &positionDebut,  &positionFin);
	initTabTower(towerArray);
	if (z == 2){
		cptEnemy = 6;
	}
	      
	for (y=1; y <= nbVagues; y++){
            
		finVague = 0;
		cptEnemy = cptEnemy+2;
		EnemyTab = realloc(EnemyTab, sizeof(Enemy) * cptEnemy);

		initEnemy(EnemyTab, cptEnemy, map, positionDebut, y);

		while (gameover == 0 && finVague == 0 && nbVie > 0){


			  initHBPosition(EnemyTab, cptEnemy);
			  
			  if (SDL_PollEvent(&event)) {
			      HandleEvent(event, &gameover, &towerBlack.Position, &towerBlue.Position,&towerBlackE.Position, &towerBlueE.Position,
                             &towerBlack.cout, &towerBlue.cout,&towerBlackE.cout, &towerBlueE.cout,
                              &argent, &towerBlack.flag, &towerBlue.flag, &towerBlackE.flag, &towerBlueE.flag,
                               &click, map, towerArray);
			    }
			
			  SDL_Delay(5);
		      
			deplacer(EnemyTab, positionFin, 	positionDebut, cptEnemy);
			afficherMap(screen,tileset,map);

			afficherEnemy(EnemyTab,cptEnemy, sprite, sprite2,  spriteImage,screen);
			
			positionTower(towerArray,  &towerBlack, &towerBlue, &towerBlackE, &towerBlueE); 
		    
			afficherTower(towerArray, towerBlack, towerBlue, towerBlackE, towerBlueE,  screen , 
                        towerblue,  towerblack, towerblueE,  towerblackE, towerImage );
			  
			sprintf(ArgentArray, "%d", argent); 
			texteArgent = TTF_RenderText_Blended(police50, ArgentArray, couleurNoire); 
			SDL_BlitSurface(texteArgent, NULL, screen, &positionTexteArgent); 

			sprintf(VieArray, "%d", nbVie); 
			texteVie = TTF_RenderText_Blended(police50, VieArray, couleurNoire); 
			SDL_BlitSurface(texteVie, NULL, screen, &posVie); 	   
			
			sprintf(vagueArray, "vague : %d", y); 
			texteVague = TTF_RenderText_Blended(police50, vagueArray, couleurNoire); 
			SDL_BlitSurface(texteVague, NULL, screen, &posVague); 			
			SDL_BlitSurface(coeur, NULL, screen, &posCoeur);
            SDL_BlitSurface(piece, NULL, screen, &posPiece);
            SDL_BlitSurface(texteDegat1, NULL, screen, &posDegat1);
            SDL_BlitSurface(texteDegat2, NULL, screen, &posDegat2);
            SDL_BlitSurface(texteCout1, NULL, screen, &posCout1);
            SDL_BlitSurface(texteCout2, NULL, screen, &posCout2);
            
			afficherHB(EnemyTab, cptEnemy, HB, screen);
			  
			
			  estMort(cptEnemy, EnemyTab,screen,  explosion, explosionImage, &nbEnnemisTues, &argent, y);
			  attaquer(cptEnemy, EnemyTab, towerBlue, towerBlack,towerBlueE, towerBlackE, towerAttack, towerArray, screen, y);

			  vie(EnemyTab,cptEnemy, &nbVie, &gameover,positionFin);
		      SDL_Delay(5);
                if (SDL_PollEvent(&event)) {
			      HandleEvent(event, &gameover, &towerBlack.Position, &towerBlue.Position,&towerBlackE.Position, &towerBlueE.Position,
                             &towerBlack.cout, &towerBlue.cout,&towerBlackE.cout, &towerBlueE.cout,
                              &argent, &towerBlack.flag, &towerBlue.flag, &towerBlackE.flag, &towerBlueE.flag,
                               &click, map, towerArray);
			     }
			  SDL_UpdateRect(screen,0,0,0,0);
		  
			      finVague = 1;
			      
			   for (p=0; p < cptEnemy; p++){
				    if (EnemyTab[p].estVivant == 1){
					
				        finVague = 0;
				    }
				  
			     }
				  
			    initTabAttack(towerAttack);    
		    }
		}
    }
		  
    newScore(nbEnnemisTues, fichierScore, recordActuel); 
    

    
    printf("GAMEOVER\n");

    /* clean up */

    free(EnemyTab);

    TTF_CloseFont(police50);
    TTF_CloseFont(police20);

  

    TTF_Quit();

   
    
    SDL_FreeSurface(texteArgent);
    SDL_FreeSurface(texteVie);
    SDL_FreeSurface(texteVague);
    SDL_FreeSurface(coeur);
    SDL_FreeSurface(piece);
    SDL_FreeSurface(texteDegat1);
    SDL_FreeSurface(texteDegat2);
    SDL_FreeSurface(texteCout1);
    SDL_FreeSurface(texteCout2);
    SDL_FreeSurface(tileset);
    SDL_FreeSurface(HB);
    SDL_FreeSurface(sprite);
    SDL_FreeSurface(sprite2);

    SDL_FreeSurface(towerblack);
    SDL_FreeSurface(towerblue);
    SDL_FreeSurface(towerblackE);
    SDL_FreeSurface(towerblueE);
    SDL_FreeSurface(explosion);
    SDL_FreeSurface(screen);

    SDL_Quit();

    return EXIT_SUCCESS;
  
}




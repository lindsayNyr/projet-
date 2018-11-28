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
    int towerFlagBlack = 0;
    int towerFlagBlue = 0;
    int gameover = 0;
    FILE* fichier = NULL, *fichierScore = NULL;
    int currentDirection = 0;  /* Information about the current situation of the sprite: */
    int animationFlip = 0;   /* Information about the animationFlip of the sprite: */
    int l =0;
    int m = 0;
    int estVivant = 1;
    int cpt=0;
    int click = 0;
    int argent = 50;
    int nbEnnemisTues = 0;
    int compteurMenu = 1;
    int recordActuel;
    
    
    //recuperation du record actuel
    fichierScore = fopen("score.txt", "r");
    if (fichierScore == NULL){
      perror("Error opening file");
    }
    else{
       fscanf(fichierScore, "%d", &recordActuel);
        if (ferror (fichierScore)){     
            printf("erreur ecriture score.txt\n");
        }
        fclose(fichierScore);
    }
    
    
   
    //init tableaux 
    int map[WIDTH_MAP][HEIGHT_MAP];
    int towerArray[WIDTH_MAP][HEIGHT_MAP];
    char ArgentArray[20] = ""; /* Tableau de char suffisamment grand */
    char ScoreArray[20] = "";

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
    SDL_WM_SetCaption("🏦 TOWER DEFENSE 🏦", NULL);

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
    positionTexteScore.x = (WIDTH_MAP-12)*TAILLE;
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

    //déclaration d'un ennemi
    struct Enemy mechant;
    mechant.HP = 100;
    mechant.vitesse = 1;
    mechant.Position.x = 0;
    mechant.Position.y = 0;
    
    //declaration d'une tour
    struct Tower towerBlack;
    towerBlack.distAttaque = 3;
    towerBlack.degats = 15;   //par tile
    towerBlack.cout = 10;
    towerBlack.Position.x = 10*32;
    towerBlack.Position.y = 17*32; 
    

    //declaration d'une tour
    struct Tower towerBlue;
    towerBlue.distAttaque = 2;
    towerBlue.degats = 20;   //par tile
    towerBlue.cout = 20;
    towerBlue.Position.x = 10*32;
    towerBlue.Position.y = 17*32; 
    

    
   
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
            if ( j == 2  && i == HEIGHT_MAP-1 ){
               
                towerArray[j][i] = 2;     
            }

	   }  
	}
    
    AfficherMap(screen,tileset,map);

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
    for (i=0;i<WIDTH_MAP;i++){
        for (j=0;j<HEIGHT_MAP;j++){
           
            copie_map[i][j] = map[i][j];

        }
    }
    
    

    //i = 0;
   // j = 0;
    


    while (mechant.Position.x < 20*30 && gameover == 0){

        HBPosition.y = mechant.Position.y - 22;
        HBPosition.x = mechant.Position.x;
        
        if (SDL_PollEvent(&event)) {
           
            HandleEvent(event, &gameover, &towerBlack.Position, &towerBlue.Position, &towerBlack.cout, &towerBlue.cout, &argent, &towerFlagBlack, &towerFlagBlue, &click);
        }
        
        Deplacement(&mechant, copie_map, &currentDirection,&animationFlip, &l, &m, &k);

        AfficherMap(screen,tileset,map);
        
        spriteImage.x = TAILLE*(2*currentDirection + animationFlip);
        
        if (mechant.HP>0){
           
            SDL_BlitSurface(sprite, &spriteImage, screen, &mechant.Position);
        }
        
        if (towerFlagBlack == 1){

            towerArray[towerBlack.Position.x/TAILLE][towerBlack.Position.y/TAILLE] = 1;
            towerFlagBlack = 0;
        }

        if (towerFlagBlue == 1){

            towerArray[towerBlue.Position.x/TAILLE][towerBlue.Position.y/TAILLE] = 2;

            towerFlagBlue = 0;
        }
       
     
 		for (j=0;j< WIDTH_MAP;j++){
            for (i=0;i<HEIGHT_MAP;i++){
                if ( map[j][i] != 1){

                    towerArray[j][i] = 0;
                }
                  ;    
            	if ( j == 0  && i == HEIGHT_MAP-1 ){
    		   
               	 	towerArray[j][i] = 1;     
    			}
    			
            	if ( j == 2  && i == HEIGHT_MAP-1 ){
               
               	 	towerArray[j][i] = 2;     
           		}
            }
        }
              

        for (j=0;j< WIDTH_MAP;j++){
            for (i=0;i<HEIGHT_MAP;i++){
                if ( towerArray[j][i] == 1){
			     
                    towerBlack.Position.x = j*TAILLE;
                    towerBlack.Position.y = i*TAILLE-8;
                    SDL_BlitSurface(towerblack, &towerImage, screen, &towerBlack.Position);  
			    }

                 if ( towerArray[j][i] == 2){
                 
                    towerBlue.Position.x = j*TAILLE;
                    towerBlue.Position.y = i*TAILLE-8;
                    SDL_BlitSurface(towerblue, &towerImage, screen, &towerBlue.Position);  
                }


			}
		}

	    
        sprintf(ArgentArray, "argent : %d", argent); /* On écrit dans la chaîne "argent" la nouvelle somme */

        texteArgent = TTF_RenderText_Blended(policeArgent, ArgentArray, couleurNoire); /* On écrit la chaîne argent dans la SDL_Surface */
        SDL_BlitSurface(texteArgent, NULL, screen, &positionTexteArgent); /* Blit du texte */
        
        SDL_BlitSurface(HB, &HBImage, screen, &HBPosition);
        
        if (mechant.HP<=0 && estVivant == 1){       //quand un ennemi meurt
//             for (i=0; i<4; i++){
                for (j=0; j<4; j++){
                    
                    explosionImage.x = j*TAILLE ;
//                     explosionImage.y = i*TAILLE ;
                    SDL_BlitSurface(explosion, &explosionImage, screen, &mechant.Position);
                    SDL_Delay(100);
                    //SDL_BlitSurface(towerblack, &towerImage, screen, &tower1.Position);
                    SDL_UpdateRect(screen,0,0,0,0);
                    estVivant = 0;
                    

                }
                nbEnnemisTues +=1;
//             }

            argent += 10;
        }

        //SDL_BlitSurface(towerblack, &towerImage, screen, &tower1.Position);

        for (j=0;j< WIDTH_MAP;j++){
            for (i=0;i<HEIGHT_MAP-1;i++){
                if ( towerArray[j][i] == 1){
			      

                    towerBlack.Position.x = j*TAILLE;
                    towerBlack.Position.y = i*TAILLE;
                      
                    if (estAPortee(&towerBlack, &mechant)&& (mechant.HP >0)){
                    
                        DrawLine(screen, towerBlack.Position.x,towerBlack.Position.y, mechant.Position.x, mechant.Position.y, 3000);
                        Attack(&towerBlack, &mechant, &HBImage, &cpt);
                    }
                }


                if ( towerArray[j][i] == 2){
                  
                    towerBlue.Position.x = j*TAILLE;
                    towerBlue.Position.y = i*TAILLE;
                      
                    if (estAPortee(&towerBlue, &mechant)&& (mechant.HP >0)){
                    
                        DrawLine(screen, towerBlue.Position.x,towerBlue.Position.y, mechant.Position.x, mechant.Position.y, 3000);
                        Attack(&towerBlue, &mechant, &HBImage, &cpt);
                    }
            	}
            }
        }
 
        SDL_UpdateRect(screen,0,0,0,0);
    }

    //score
    
    fichierScore = fopen("score.txt", "w+");
    
    if (fichierScore == NULL){
     
      perror("Error opening file");
    }

    else{
       fscanf(fichierScore, "%d", &recordActuel);
      if (nbEnnemisTues >= recordActuel){
        fprintf (fichierScore , "%d" ,nbEnnemisTues);
      }
      else{
	fprintf (fichierScore, "%d", recordActuel);
      }
        if (ferror (fichierScore)){
        
            printf("erreur ecriture score.txt\n");
        }

        fclose(fichierScore);
    }
    

    
    printf("GAMEOVER\n");

    /* clean up */
    TTF_CloseFont(policeArgent);
    TTF_Quit();
    
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




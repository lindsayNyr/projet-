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
    //int k = 1;
    int towerFlagBlack = 0;
    int towerFlagBlue = 0;
    int gameover = 0;
    FILE* fichier = NULL, *fichierScore = NULL;
    int currentDirection = 0;  /* Information about the current situation of the sprite: */
    int animationFlip = 0;   /* Information about the animationFlip of the sprite: */
    //int l =0;
    //int m = 0;
    int estVivant = 1;
    int cpt=0;
    int click = 0;
    int argent = 50;
    int nbEnnemisTues = 0;
    int compteurMenu = 1;
    int nbVie = 3;
    int p =0;
    int cptEnemy = 5;



    //init tableau 
    int map[WIDTH_MAP][HEIGHT_MAP];
    int towerArray[WIDTH_MAP][HEIGHT_MAP];
    char ArgentArray[20] = ""; /* Tableau de char suffisamment grand */
    struct Enemy *EnemyTab = malloc(sizeof(Enemy) * cptEnemy);



    //init SDL
    SDL_Surface *screen, *tileset, *towerblack, *towerblue, *sprite, *temp,
    		    *explosion, *HB, *missile , *texteArgent, *textePlay, *texteQuit,
                *menu;
    
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
    MENU.x = 2.5*TAILLE;
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

    //blit 
    SDL_BlitSurface(textePlay, NULL, screen, &positionTextePlay); /* Blit du texte */
    SDL_BlitSurface(texteQuit, NULL, screen, &positionTexteQuit); /* Blit du texte */

    SDL_UpdateRect(screen,0,0,0,0);

     while(compteurMenu == 1 && gameover == 0){
        if (SDL_PollEvent(&eventMenu)) {
            MenuEvent(eventMenu, &compteurMenu, &gameover);
        }
    }
    
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
    temp = SDL_LoadBMP("images/explosion.bmp");
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

   
    
    //declaration d'une tour
    struct Tower towerBlack;
    towerBlack.distAttaque = 3;
    towerBlack.degats = 15;   //par tile
    towerBlack.cout = 0;
    towerBlack.Position.x = 10*32;
    towerBlack.Position.y = 17*32; 
    

    //declaration d'une tour
    struct Tower towerBlue;
    towerBlue.distAttaque = 3;
    towerBlue.degats = 15;   //par tile
    towerBlue.cout = 0;
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


     //déclaration d'un ennemi
    for (i=0; i < cptEnemy; i++){
	    
	    EnemyTab[i].HP = 100;
	    EnemyTab[i].vitesse = 1;
	    EnemyTab[i].indiceX = 0;
	    EnemyTab[i].indiceY = 0;
	    EnemyTab[i].pixel = 1;
	   	
	    EnemyTab[i].Position.x = 0;
	    EnemyTab[i].Position.y = 0;	
	    for (p=0;p<HEIGHT_MAP;p++){
        	for(j=0; j<WIDTH_MAP; j++){

           
            	 EnemyTab[i].copieMap[j][p] = map[j][p];
            	 //printf("%d", EnemyTab[i].copieMap[j][p]);
        	}
   	    }	    
	}
			

		      //  printf("%d %d\n", EnemyTab[0].Position.x, cptEnemy);
		  


    SDL_Rect positionTexteArgent;
    positionTexteArgent.x = (WIDTH_MAP-8)*TAILLE;
    positionTexteArgent.y = (HEIGHT_MAP-2)*TAILLE;

    /* Define the source rectangle for the BlitSurface tower */
    SDL_Rect towerImage;
    towerImage.x = 0;
    towerImage.y = 0;
    towerImage.w = TAILLE;
    towerImage.h = TAILLE;

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
    for (i=0;i< WIDTH_MAP ;i++){
        for (j=0;j<HEIGHT_MAP;j++){
           
            copie_map[i][j] = map[i][j];

        }
    }
    
    

    //i = 0;
   // j = 0;
    


    while (/*nbVie > 0 &&*/ gameover == 0){


    	   

    	/*for (p=0;p<HEIGHT_MAP;p++){
        	for(j=0; j<WIDTH_MAP; j++){

           
            	// EnemyTab[0].copieMap[j][p] = map[j][p];
            	 printf("%d ", EnemyTab[0].copieMap[j][p]);
            	 
        	
   	    }
   	}*/

        /*HBPosition.y = EnemyTab[p].Position.y - 22;
        HBPosition.x = EnemyTab[p].Position.x;*/
        
        if (SDL_PollEvent(&event)) {
           
            HandleEvent(event, &gameover, &towerBlack.Position, &towerBlue.Position, &towerBlack.cout, &towerBlue.cout, &argent, &towerFlagBlack, &towerFlagBlue, &click);
        }

       

        for( p = 0 ; p < cptEnemy; p++){
	  if(p == 0)
       		Deplacement(EnemyTab, &p,  &currentDirection,&animationFlip);
		printf("%d\n",  Distance(EnemyTab[p-1].Position.x,  EnemyTab[p-1].Position.y, EnemyTab[p].Position.x,  EnemyTab[p].Position.y));
	   if( Distance(EnemyTab[p-1].Position.x,  EnemyTab[p-1].Position.y, EnemyTab[p].Position.x,  EnemyTab[p].Position.y) == 32)
			printf("ok\n");
	      		Deplacement(EnemyTab, &p,  &currentDirection,&animationFlip);
	      		

	      	
	      	
	    }
	    AfficherMap(screen,tileset,map);


	    
	  for( p = 0 ; p < cptEnemy; p++){
		    if (EnemyTab[p].HP>0){
	   
	    		SDL_BlitSurface(sprite, &spriteImage, screen, &EnemyTab[p].Position);
		    }


	    }







    /*   for( p = 0 ; p < cptEnemy; p++){
	        
	        Deplacement(&EnemyTab[p], &p,  &currentDirection,&animationFlip);
	       // printf("%d\n", EnemyTab[0].Position.x);

	        AfficherMap(screen,tileset,map);
	        
	        spriteImage.x = TAILLE*(2*currentDirection + animationFlip);
	        

	       //	SDL_BlitSurface(sprite, &spriteImage, screen, &EnemyTab[p].Position);
	       }
	        
	        if (EnemyTab[p].HP>0){

	        	//if(p == 0){
	         
		            SDL_BlitSurface(sprite, &spriteImage, screen, &EnemyTab[p].Position);
		            EnemyTab[p].Position.x =+32;
		            EnemyTab[p].Position.x =+32;

		            SDL_BlitSurface(sprite, &spriteImage, screen, &EnemyTab[p].Position);*/
		        //}
		       // else{

		        	//if(EnemyTab[p].indiceX == EnemyTab[p+1].indiceX - TAILLE || EnemyTab[p].indiceX == EnemyTab[p+1].indiceY - TAILLE ){

		        		//SDL_BlitSurface(sprite, &spriteImage, screen, &EnemyTab[p].Position);
		        	//}
		       // }
		   // }
	    //}*/

        
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
                    towerBlack.Position.y = i*TAILLE;
                    SDL_BlitSurface(towerblack, &towerImage, screen, &towerBlack.Position);  
			    }

                 if ( towerArray[j][i] == 2){
                 
                    towerBlue.Position.x = j*TAILLE;
                    towerBlue.Position.y = i*TAILLE;
                    SDL_BlitSurface(towerblue, &towerImage, screen, &towerBlue.Position);  
                }


			}
		}

	    
        sprintf(ArgentArray, "argent : %d", argent); /* On écrit dans la chaîne "argent" la nouvelle somme */
        SDL_FreeSurface(texteArgent); /* On supprime la surface précédente */
        texteArgent = TTF_RenderText_Blended(policeArgent, ArgentArray, couleurNoire); /* On écrit la chaîne argent dans la SDL_Surface */
        SDL_BlitSurface(texteArgent, NULL, screen, &positionTexteArgent); /* Blit du texte */
        
        //SDL_BlitSurface(HB, &HBImage, screen, &HBPosition);
       for( p = 0 ; p < cptEnemy; p++){

        if (EnemyTab[p].HP<=0 ){       //quand un ennemi meurt
            for (i=0; i<4; i++){
                for (j=0; j<5; j++){
                    
                    explosionImage.x = j*TAILLE ;
                    explosionImage.y = i*TAILLE ;
                    SDL_BlitSurface(explosion, &explosionImage, screen, &EnemyTab[p].position);
                    SDL_Delay(100);
                    //SDL_BlitSurface(towerblack, &towerImage, screen, &tower1.Position);
                    SDL_UpdateRect(screen,0,0,0,0);
                  
                    nbEnnemisTues +=1;

                }
            }

            argent += 10;
        }
       }
        //SDL_BlitSurface(towerblack, &towerImage, screen, &tower1.Position);

      	  for( p = 0 ; p < cptEnemy; p++){

       for (j=0;j< WIDTH_MAP;j++){
            for (i=0;i<HEIGHT_MAP-1;i++){
                if ( towerArray[j][i] == 1){
			      

                    towerBlack.Position.x = j*TAILLE;
                    towerBlack.Position.y = i*TAILLE;
                      
                    if (estAPortee(&towerBlack, &EnemyTab[p])&& (EnemyTab[p].HP >0)){
                    
                        DrawLine(screen, towerBlack.Position.x,towerBlack.Position.y, EnemyTab[p].Position.x, EnemyTab[p].Position.y, 3000);
                        Attack(&towerBlack, &EnemyTab[p], &HBImage, &cpt);
                    }
                }


                if ( towerArray[j][i] == 2){
                  
                    towerBlue.Position.x = j*TAILLE;
                    towerBlue.Position.y = i*TAILLE;
                      
                    if (estAPortee(&towerBlue, &EnemyTab[p])&& (EnemyTab[p].HP >0)){
                    
                        DrawLine(screen, towerBlue.Position.x,towerBlue.Position.y, EnemyTab[p].Position.x, EnemyTab[p].Position.y, 3000);
                        Attack(&towerBlue, &EnemyTab[p], &HBImage, &cpt);
                    }
            	}
            }
        }
      }

      for( p = 0 ; p < cptEnemy; p++){

        if (EnemyTab[p].Position.x == 20*30){

 			nbVie = nbVie - 1;

 		}
      }
 
        SDL_UpdateRect(screen,0,0,0,0);
    }
    

    //score
    
    fichierScore = fopen("score.txt", "w");
    
    if (fichierScore == NULL){
     
      perror("Error opening file");
    }

    else{
      
        fprintf (fichierScore , "%d" ,nbEnnemisTues);
        if (ferror (fichierScore)){
        
            printf("erreur ecriture score.txt\n");
        }

        fclose(fichierScore);
    }
    
    printf("GAMEOVER\n");



    /* clean up */
    free(EnemyTab);

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




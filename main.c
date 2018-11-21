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
#include "event.h"
#include "personnages.h"
#include <math.h>
#include "attaque.h"




#define TAILLE 32  // HEIGHT et WIDTH des tiles.


#define WIDTH_MAP 20  // nombre a afficher en x et y
#define HEIGHT_MAP 18


//Fonction 








void Deplacement(struct Enemy* mechant, int copie_map[WIDTH_MAP][HEIGHT_MAP], int* currentDirection,int* animFlip, int* x, int* y, int* k){
    int i = *x;
    int j = *y;
  SDL_Delay(5);
  
      if (mechant->HP > 0){
	if (copie_map[i+1][j]==2){
	    mechant->Position.x +=1;
	    *currentDirection = 1;
	    copie_map[i][j]=0;
	    if (*k == 32){
            *x+=1; 
            *animFlip = 1 - *animFlip;
	    }
	}
	else{
	    if (copie_map[i][j+1]==2){
		mechant->Position.y +=1;
		*currentDirection = 2;         
		copie_map[i][j]=0;
		if (*k == 32){
		    *y+=1;
		    *animFlip = 1 - *animFlip;
		}
	    }
	    else{
		if (copie_map[i-1][j]==2){
		    mechant->Position.x -=1;
		    *currentDirection = 3;             
		    copie_map[i][j]=0;
		    if (*k == 32){
                *x-=1;
                *animFlip = 1 - *animFlip;
		    }
		}
		else{
		    if (copie_map[i][j-1]==2){
                mechant->Position.y -=1;
                *currentDirection = 0;
                copie_map[i][j]=0;
			if (*k == 32){
			    *y-=1;
			    *animFlip = 1 - *animFlip;
			}
		    }           
		}
	    }   
	}
	*k = *k+1;
	if (*k == 33){
	    *k = 1;
	}
    }
}






void AfficherMap(SDL_Surface* screen, SDL_Surface* tileset, int table[WIDTH_MAP][HEIGHT_MAP]){
   
    int i,j;

    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    Rect_source.w = TAILLE;
    Rect_source.h = TAILLE;
   
    for(i=0;i<WIDTH_MAP;i++){
        
        for(j=0;j<HEIGHT_MAP;j++){
    
            Rect_dest.x = i*TAILLE;
            Rect_dest.y = j*TAILLE;
           
            if (table[i][j] < 10){
                Rect_source.x = table[i][j]*TAILLE;
                Rect_source.y = 0;
            }
            
            if (table[i][j] > 10 && table[i][j] < 20){
                Rect_source.x = (table[i][j]-10)*TAILLE;
                Rect_source.y = TAILLE;
            }
            
	    if (table[i][j] > 20 && table[i][j] < 30){
                Rect_source.x = (table[i][j]-20)*TAILLE;
                Rect_source.y = TAILLE*2;
             }
             
	    if (table[i][j] > 30 && table[i][j] < 40){
                Rect_source.x = (table[i][j]-30)*TAILLE;
                Rect_source.y = TAILLE*3;
            }
            SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest);
        }
    }

}



    
    int main(int argc,char** argv)
{
    // init variables 
    int map[WIDTH_MAP][HEIGHT_MAP];
    int i,j, colorkey, colorkey2, colorkey3;
    int k = 1;
    int towerPositionning = 0;

    int gameover = 0;
    FILE* fichier = NULL;
    SDL_Surface *screen, *tileset, *towerblack, *sprite, *temp, *explosion, *HB, *missile ;
//     SDL_Rect * ;
    SDL_Event event;
    
    int towerArray[WIDTH_MAP][HEIGHT_MAP];

int PosX, PosY;
    
    
    


	

    
    
    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO); 

    /* set the title bar */
    SDL_WM_SetCaption("🏦 TOWER DEFENSE 🏦", NULL);

    /* create window */
    screen = SDL_SetVideoMode(TAILLE*WIDTH_MAP, TAILLE*HEIGHT_MAP, TAILLE, SDL_HWSURFACE|SDL_DOUBLEBUF);
    
        
    



    /* Information about the current situation of the sprite: */
    int currentDirection = 0;

    /* Information about the animationFlip of the sprite: */
    int animationFlip = 0;


    //load towers
    
    temp = SDL_LoadBMP("images/tower_black.bmp");
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

    SDL_SetColorKey(towerblack, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(explosion, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey2);
    SDL_SetColorKey(HB, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey3);
    SDL_SetColorKey(missile, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey3);

    
    
    
    
    
     /* Rectangle to store the position of the launcher in the window.
     * Only the x and y coordinates are used. */
//     SDL_Rect spritePosition;
//     SDL_Rect towerPosition;
  
    //set tower position
//     towerPosition.x = 0;
//     towerPosition.y = 0;

//     //set sprite position
//     spritePosition.x = 0;
//     spritePosition.y = 0;

    
    
    //déclaration d'un ennemi
    struct Enemy mechant;
    mechant.HP = 100;
    mechant.vitesse = 1;
    mechant.Position.x = 0;
    mechant.Position.y = 0;
    
    //declaration d'une tour
    struct Tower tower1;
    tower1.distAttaque = 3;
    tower1.degats = 15;   //par tile
    tower1.cout = 0;
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
      printf("Impossible d'ouvrir le fichier test.txt");
    }
    
    
    
          /*init tab */
     
         for(j=0; j<WIDTH_MAP; j++){

          for(i=0; i<HEIGHT_MAP; i++){
		  towerArray[j][i] = 0 ;
		  
	    
		  if ( i == 0  && j == HEIGHT_MAP-1 ){
		    towerArray[j][i] = 1;
		    
		  
		}
	 }
	  
	  }
    
    AfficherMap(screen,tileset,map);
 


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
    
    
    
//     int copie_map2[WIDTH_MAP][HEIGHT_MAP];
    int copie_map[WIDTH_MAP][HEIGHT_MAP];
    for (i=0;i<=HEIGHT_MAP+1;i++){
        for (j=0;j<=HEIGHT_MAP+1;j++){
            copie_map[i][j]=map[i][j];
//             copie_map2[i][j]=map[i][j];
        }
    }
    
    
SDL_Rect HBPosition;


    
    

    //tentative de deplacement d'un ennemi
    i = 0;
    j = 0;
    int l =0;
    int m = 0;


    int estVivant = 1;
    int cpt=0;



    while (mechant.Position.x < 20*30 && gameover == 0){

        HBPosition.y = mechant.Position.y - 22;
        HBPosition.x = mechant.Position.x;
        if (SDL_PollEvent(&event)) {
            HandleEvent(event, &gameover, &tower1.Position, &towerPositionning, &PosX, &PosY);
        }
        
        Deplacement(&mechant, copie_map, &currentDirection,&animationFlip, &l, &m, &k);

        AfficherMap(screen,tileset,map);
        spriteImage.x = TAILLE*(2*currentDirection + animationFlip);
        if (mechant.HP>0){
            SDL_BlitSurface(sprite, &spriteImage, screen, &mechant.Position);
        }
        
        
        
        
        
        if (towerPositionning == 1){
            towerArray[tower1.Position.y/TAILLE][tower1.Position.x/TAILLE] = 1;
            towerPositionning = 0;
        }
              for (j=0;j< WIDTH_MAP;j++){
                    for (i=0;i<HEIGHT_MAP;i++){
                    if ( towerArray[j][i] == 1){
			      

                        tower1.Position.x = i*TAILLE;
                        tower1.Position.y = j*TAILLE;
                        SDL_BlitSurface(towerblack, &towerImage, screen, &tower1.Position);  
			  }
			}
		}
        
        
        
        SDL_BlitSurface(HB, &HBImage, screen, &HBPosition);
        
        if (mechant.HP<=0 && estVivant == 1){       //quand un ennemi meurt
            for (i=0; i<4; i++){
                for (j=0; j<5; j++){
                    explosionImage.x = j*TAILLE ;
                    explosionImage.y = i*TAILLE ;
                    SDL_BlitSurface(explosion, &explosionImage, screen, &mechant.Position);
                    SDL_Delay(100);
                    SDL_BlitSurface(towerblack, &towerImage, screen, &tower1.Position);

                    SDL_UpdateRect(screen,0,0,0,0);
                    estVivant = 0;
                }
            }
            
        }
        SDL_BlitSurface(towerblack, &towerImage, screen, &tower1.Position);

        for (j=0;j< WIDTH_MAP;j++){
                    for (i=0;i<HEIGHT_MAP;i++){
                    if ( towerArray[j][i] == 1){
			      

                        tower1.Position.x = i*TAILLE;
                        tower1.Position.y = j*TAILLE;
                      
			
		
        
        if (estAPortee(&tower1, &mechant)&& (mechant.HP >0)){
            DrawLine(screen, tower1.Position.x,tower1.Position.y, mechant.Position.x, mechant.Position.y, 3000);
            Attack(&tower1, &mechant, &HBImage, &cpt);
        }
       }
     }
 }

        
//         SDL_Flip(screen);
        SDL_UpdateRect(screen,0,0,0,0);
    }

    


 /* clean up */
    SDL_FreeSurface(tileset);
    SDL_FreeSurface(HB);

    SDL_FreeSurface(sprite);
    SDL_FreeSurface(towerblack);
    //SDL_FreeSurface(Rect_source);
    //SDL_FreeSurface(Rect_dest);
    SDL_FreeSurface(screen);

    printf("GAMEOVER\n");
    SDL_Quit();

 return EXIT_SUCCESS;

    
 }




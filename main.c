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



#define TAILLE 32  // HEIGHT et WIDTH des tiles.


#define WIDTH_MAP 20  // nombre a afficher en x et y
#define HEIGHT_MAP 18


//Fonction 

void Deplacement(SDL_Rect* spritePosition, int copie_map[WIDTH_MAP][HEIGHT_MAP], int* currentDirection,int* animFlip, int* x, int* y, int* k){
    int i = *x;
    int j = *y;

    if (copie_map[i+1][j]==2){
        spritePosition->x +=1;
        *currentDirection = 1;
        
        copie_map[i][j]=0;
        if (*k == 32){
            *x+=1; 

            *animFlip = 1 - *animFlip;
        }
    }
    else{
        if (copie_map[i][j+1]==2){
            spritePosition->y +=1;
            *currentDirection = 2;
            
            copie_map[i][j]=0;
            if (*k == 32){
                *y+=1;
                *animFlip = 1 - *animFlip;
            }
        }
        else{
            if (copie_map[i-1][j]==2){
                spritePosition->x -=1;
                *currentDirection = 3;
                
                copie_map[i][j]=0;
                if (*k == 32){
                    *x-=1;
                    *animFlip = 1 - *animFlip;
                }
            }
            else{
                if (copie_map[i][j-1]==2){
                    spritePosition->y -=1;
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
    int i,j, colorkey;
    int k = 1;
    int towerPositionning = 0;
    int PosX, PosY;
    int towerArray[WIDTH_MAP][HEIGHT_MAP];

    int gameover = 0;
    FILE* fichier = NULL;
    SDL_Surface *screen, *tileset, *tower, *sprite, *temp ;
    SDL_Event event;
    


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


    //load tower
    
    temp = SDL_LoadBMP("tower_black.bmp");
    tower = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    //load sprite
    temp = SDL_LoadBMP("sprite.bmp");
    sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    //load sprite
    temp = SDL_LoadBMP("tiles.bmp");
    tileset = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);



    /* setup launcher colorkey and turn on RLE */
    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(tower, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    
     /* Rectangle to store the position of the launcher in the window.
     * Only the x and y coordinates are used. */
    SDL_Rect spritePosition;
    SDL_Rect towerPosition;
  
    //set tower position
   /* towerPosition.x = 0;
    towerPosition.y = 17*TAILLE;*/

    //set sprite position
    spritePosition.x = 0;
    spritePosition.y = 0;




   
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
      printf("Impossible d'ouvrir le fichier map.txt");
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
    // SDL_BlitSurface(tower, &towerImage, screen, &towerPosition);

     
    
//     int copie_map2[WIDTH_MAP][HEIGHT_MAP];
    int copie_map[WIDTH_MAP][HEIGHT_MAP];
    for (i=0;i<WIDTH_MAP;i++){
        for (j=0;j<HEIGHT_MAP;j++){
            copie_map[i][j]=map[i][j];
//             copie_map2[i][j]=map[i][j];
        }
    }
    
    



    
    

    //tentative de deplacement d'un ennemi
    i = 0;
    j = 0;
   

    while (/*pritePosition.x < 20*30 &&*/ gameover == 0){

    	

        
        if (SDL_PollEvent(&event)) {
            HandleEvent(event, &gameover, &towerPosition, &towerPositionning, &PosX, &PosY);
        }


        AfficherMap(screen,tileset,map);
        Deplacement(&spritePosition, copie_map, &currentDirection,&animationFlip, &i, &j, &k);


        spriteImage.x = TAILLE*(2*currentDirection + animationFlip);
        SDL_BlitSurface(sprite, &spriteImage, screen, &spritePosition);




       
        if (towerPositionning == 1){
		towerArray[towerPosition.y/TAILLE][towerPosition.x/TAILLE] = 1;
		towerPositionning = 0;
        }
        
        
        
              for (j=0;j< WIDTH_MAP;j++){
        	for (i=0;i<HEIGHT_MAP;i++){
			  if ( towerArray[j][i] == 1){
			      
			     /* SDL_BlitSurface(tower, &towerImage, screen, &towerPosition);*/
			     	printf("i = %d j = %d array = %d\n" , i , j , towerArray[j][i]);
			       towerPosition.x = i*TAILLE;
			       towerPosition.y = j*TAILLE;
			      
			      
			      SDL_BlitSurface(tower, &towerImage, screen, &towerPosition);


			    
			  }
			}
		}
		
		
		
		
		

        //SDL_Flip(screen);
        SDL_UpdateRect(screen,0,0,0,0);


    }

    


 /* clean up */
 SDL_FreeSurface(tileset);
 SDL_FreeSurface(sprite);
 SDL_FreeSurface(tower);
 //SDL_FreeSurface(Rect_source);
 //SDL_FreeSurface(Rect_dest);
 SDL_FreeSurface(screen);


 SDL_Quit();
 return 0;

    
 }




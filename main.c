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




#define TAILLE_TILE 32  // hauteur et largeur des tiles.


#define LARGEUR_MAP 20  // nombre a afficher en x et y
#define HAUTEUR_MAP 17




void Deplacement(SDL_Rect* spritePosition, int copie_map[LARGEUR_MAP][HAUTEUR_MAP], int* currentDirection,int* animFlip, int* x, int* y, int* k){
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
















void AfficherMap(SDL_Surface* screen,SDL_Surface* tileset,int table[LARGEUR_MAP][HAUTEUR_MAP]){
   
    int i,j;
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    Rect_source.w = TAILLE_TILE;
    Rect_source.h = TAILLE_TILE;
   
    for(i=0;i<LARGEUR_MAP;i++){
        
        for(j=0;j<HAUTEUR_MAP;j++){
    
            Rect_dest.x = i*TAILLE_TILE;
            Rect_dest.y = j*TAILLE_TILE;
           
            if (table[i][j] < 10){
	            Rect_source.x = table[i][j]*TAILLE_TILE;
	            Rect_source.y = 0;
         	}
         	
            if (table[i][j] > 10 && table[i][j] < 20){
		        Rect_source.x = (table[i][j]-10)*TAILLE_TILE;
		        Rect_source.y = TAILLE_TILE;
        	}
	        
	    if (table[i][j] > 20 && table[i][j] < 30){
		        Rect_source.x = (table[i][j]-20)*TAILLE_TILE;
		        Rect_source.y = TAILLE_TILE*2;
	     	 }
		     
	    if (table[i][j] > 30 && table[i][j] < 40){
			    Rect_source.x = (table[i][j]-30)*TAILLE_TILE;
			    Rect_source.y = TAILLE_TILE*3;
		    }
            

            SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest);
        }
    }
    SDL_Flip(screen);
}




    
    
    
    
    
    
    
    

    
    
    
    
    
    
    
    
    
    int main(int argc,char** argv)
{
    
    
    
    
    
    
    
    
    
    
    
    
    
    
	int map[LARGEUR_MAP][HAUTEUR_MAP];
	int i,j;
	FILE* fichier = NULL;
  	SDL_Surface* screen,*tileset;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);        // prepare SDL
    screen = SDL_SetVideoMode(TAILLE_TILE*LARGEUR_MAP, TAILLE_TILE*HAUTEUR_MAP, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    tileset = SDL_LoadBMP("tiles.bmp");
   
    if (!tileset){
       
        printf("Echec de chargement tileset.bmp\n");
        SDL_Quit();
        system("pause");
        exit(-1);
    }

  	fichier = fopen("level.txt", "r");

 	 	if (fichier != NULL){
    
	     	for(i=0; i<HAUTEUR_MAP; i++){
	      		for(j=0; j<LARGEUR_MAP; j++){

	 				 fscanf(fichier,"%d", &map[j][i]);
				}
			}
  		}

    else {
     
      // On affiche un message d'erreur si on veut
      printf("Impossible d'ouvrir le fichier test.txt");
  	}
  	
  	
    SDL_WM_SetCaption("🏦 TOWER DEFENSE 🏦", NULL);
    AfficherMap(screen,tileset,map);
    int gameover = 0;
    int colorkey;
     
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
     

    //tentative de chargement d'un ennemi

    SDL_Rect spritePosition;

    spritePosition.x = 0;
    spritePosition.y = 0;

    SDL_Surface *temp, *sprite;

    temp   = SDL_LoadBMP("sprite.bmp");
    sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);


    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    
    //tentative de chargement d'un autre ennemi
//     SDL_Rect sprite2Position;

//     sprite2Position.x = 0;
//     sprite2Position.y = 0;

//     SDL_Surface *sprite2;

//     temp   = SDL_LoadBMP("sprite.bmp");
//     sprite2 = SDL_DisplayFormat(temp);
//     SDL_FreeSurface(temp);


//     colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
//     SDL_SetColorKey(sprite2, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    
    
//     int copie_map2[LARGEUR_MAP][HAUTEUR_MAP];
    int copie_map[LARGEUR_MAP][HAUTEUR_MAP];
    for (i=0;i<=HAUTEUR_MAP+2;i++){
        for (j=0;j<=HAUTEUR_MAP+1;j++){
            copie_map[i][j]=map[i][j];
//             copie_map2[i][j]=map[i][j];
        }
    }
    
    
        int animationFlip = 0;

    
        int currentDirection = 0;


    
    
    
    
    
    
    


    
    

    //tentative de deplacement d'un ennemi
    i=0;
    j=0;
    int k=1;
//     int l = 0;
//     int m = 0;
//     int n = 0;
    int cpt = 0;
    while (spritePosition.x < 20*30){
        AfficherMap(screen,tileset,map);
        Deplacement(&spritePosition, copie_map, &currentDirection,&animationFlip, &i, &j, &k);
        
        
        /*if (cpt > 200){
            Deplacement(&sprite2Position, copie_map2,  &l, &m, &n);          
            SDL_BlitSurface(sprite2, &spriteImage, screen, &sprite2Position);
            SDL_UpdateRect(screen,0,0,0,0);
        }*/
     cpt += 1; 
     


         
   
            SDL_Rect spriteImage;
            spriteImage.y = 0;
            spriteImage.w = 32;
            spriteImage.h = 32;
            /* choose image according to direction and animation flip: */
            spriteImage.x = 32*(2*currentDirection + animationFlip);

            SDL_BlitSurface(sprite, &spriteImage, screen, &spritePosition);

            SDL_UpdateRect(screen,0,0,0,0);
            
            

            
            
    }
    


    
 
    
    
    
    
    
  
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    while (!gameover)
    {
        /* look for an event */
        if (SDL_PollEvent(&event)) {
            /* an event was found */
            switch (event.type) {
                /* close button clicked */
                case SDL_QUIT:
                    gameover = 1;
                    break;

                /* handle the keyboard */
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            gameover = 1;
                            break;
                        /* do nothing for other keys */
                        case SDLK_LEFT:
                            printf("ouiiii ");
                        default:
                            break;
                    }
                    break;
            }
        }
    }
    
}


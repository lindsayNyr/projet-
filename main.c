//
//  main.c
//  towerDefense
//
//  Created by Lindsay Noyer on 21/10/2018.
//  Copyright © 2018 Lindsay Noyer. All rights reserved.
//

#include <stdio.h>
#include <SDL/SDL.h>
#include <unistd.h>




#define TAILLE_TILE 32  // hauteur et largeur des tiles.


#define LARGEUR_MAP 15  // nombre a afficher en x et y
#define HAUTEUR_MAP 13


	






void Afficher(SDL_Surface* screen,SDL_Surface* tileset,int table[LARGEUR_MAP][HAUTEUR_MAP]){
   
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
	 SDL_WM_SetCaption("TOWER DEFENSE", NULL);
	 Afficher(screen,tileset,map);







  do { // attend qu'on appuie sur une touche.
    
    SDL_WaitEvent(&event);
   
    } while (event.type!=SDL_KEYDOWN);

    SDL_FreeSurface(tileset);
    SDL_Quit();
    return 0;

}

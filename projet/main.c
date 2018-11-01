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




#define TAILLE_TILE 32  // hauteur et largeur des tiles.


#define LARGEUR_MAP 20  // nombre a afficher en x et y
#define HAUTEUR_MAP 17




void Deplacement(SDL_Rect position, int table[LARGEUR_MAP][HAUTEUR_MAP]){

//while (table[i][j] != 2){

//}
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









//tentative de chargement d'un ennemi
int gameover = 0;
    SDL_Rect spritePosition;

    spritePosition.x = 0;
    spritePosition.y = 0;
int colorkey;
    SDL_Surface *temp, *sprite;

    temp   = SDL_LoadBMP("sprite.bmp");
    sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);






int copie_map[LARGEUR_MAP][HAUTEUR_MAP];
for (i=0;i<=HAUTEUR_MAP+2;i++){
	for (j=0;j<=HAUTEUR_MAP+1;j++){
		copie_map[i][j]=map[i][j];
	}
}






//tentative de deplacement d'un ennemi
i=0;
j=0;
int k;
while (spritePosition.x < 20*30){

	if (copie_map[i+1][j]==2){
		for (k=0;k<32;k++){
			spritePosition.x += 1;
			AfficherMap(screen,tileset,map);
			SDL_BlitSurface(sprite, NULL, screen, &spritePosition);
            SDL_UpdateRect(screen,0,0,0,0);
		}
		copie_map[i][j]=0;
		i=i+1; 
	}
	else{
	
		if (copie_map[i][j+1]==2){
			for (k=0;k<32;k++){
				spritePosition.y += 1; 
                AfficherMap(screen,tileset,map);
				SDL_BlitSurface(sprite, NULL, screen, &spritePosition);
                SDL_UpdateRect(screen,0,0,0,0);
			}
			copie_map[i][j]=0;
			j=j+1;
		}
		else{
			if (copie_map[i-1][j]==2){
				for (k=0;k<32;k++){
					spritePosition.x -= 1; 
					AfficherMap(screen,tileset,map);
					SDL_BlitSurface(sprite, NULL, screen, &spritePosition);
                    SDL_UpdateRect(screen,0,0,0,0);
				}
				copie_map[i][j]=0;
				i=i-1;
			}

			else{
				if (copie_map[i][j-1]==2){
					for (k=0;k<32;k++){
						spritePosition.y -= 1; 
						AfficherMap(screen,tileset,map);	
						SDL_BlitSurface(sprite, NULL, screen, &spritePosition);
                        SDL_UpdateRect(screen,0,0,0,0);
					}
				copie_map[i][j]=0;
				j=j-1;
				}
			
		}
}	

}
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
                        default:
                            break;
                    }
                    break;
            }
        }

}

}


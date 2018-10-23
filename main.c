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



#include <SDL/SDL.h> 



#define LARGEUR_TILE 32  // hauteur et largeur des tiles. 
#define HAUTEUR_TILE 32 

#define NOMBRE_BLOCS_LARGEUR 15  // nombre a afficher en x et y 
#define NOMBRE_BLOCS_HAUTEUR 13 

char* table[] = { 
"222222222222222", 
"0000013000000000", 
"000000000000000", 
"000000000000000", 
"100000000111110", 
"000000000000000", 
"000000000000000", 
"000000000000000", 
"003400022220022", 
"005600000000000", 
"005600000000000", 
"005600000000000", 
"777777777777777"}; 


void Afficher(SDL_Surface* screen,SDL_Surface* tileset,char** table,int nombre_blocs_largeur,int nombre_blocs_hauteur) 
{ 
    int i,j; 
    SDL_Rect Rect_dest; 
    SDL_Rect Rect_source; 
    Rect_source.w = LARGEUR_TILE; 
    Rect_source.h = HAUTEUR_TILE; 
    for(i=0;i<nombre_blocs_largeur;i++) 
    { 
        for(j=0;j<nombre_blocs_hauteur;j++) 
        { 
            Rect_dest.x = i*LARGEUR_TILE; 
            Rect_dest.y = j*HAUTEUR_TILE; 
            Rect_source.x = (table[j][i]-'0')*LARGEUR_TILE; 
            Rect_source.y = 0; 
            SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest); 
        } 
    } 
    SDL_Flip(screen); 
} 

int main(int argc,char** argv) 
{ 
    SDL_Surface* screen,*tileset; 
    SDL_Event event; 
    SDL_Init(SDL_INIT_VIDEO);        // prepare SDL 
    screen = SDL_SetVideoMode(LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR, HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR, 32,SDL_HWSURFACE|SDL_DOUBLEBUF); 
    tileset = SDL_LoadBMP("tiles.bmp"); 
    if (!tileset) 
    { 
        printf("Echec de chargement tileset1.bmp\n"); 
        SDL_Quit(); 
        system("pause"); 
        exit(-1); 
    } 
    Afficher(screen,tileset,table,NOMBRE_BLOCS_LARGEUR,NOMBRE_BLOCS_HAUTEUR); 

    do  // attend qu'on appuie sur une touche. 
    { 
        SDL_WaitEvent(&event); 
    } while (event.type!=SDL_KEYDOWN); 
     
    SDL_FreeSurface(tileset); 
    SDL_Quit(); 
    return 0; 
}

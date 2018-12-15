#include "define.h"
 
void ChargerMap(int  map[WIDTH_MAP][HEIGHT_MAP],  SDL_Surface *tileset, int z){
  
    FILE* fichier = NULL;
     
    if (!tileset){
       
        printf("Echec de chargement tileset.bmp\n");
        SDL_Quit();
        system("pause");
        exit(-1);
    }
    if (z==1){
    fichier = fopen("level1.txt", "r");
    }
    if (z==2){
    fichier = fopen("level2.txt", "r");
    }    
        
    if (fichier != NULL){
    
        for(int i=0; i<HEIGHT_MAP; i++){
            for(int j=0; j<WIDTH_MAP; j++){
                   
                fscanf(fichier,"%d", &map[j][i]);
            }
        }
    }

    else {
         
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier level.txt");   
    } 
}




void afficherMap(SDL_Surface* screen, SDL_Surface* tileset, int table[WIDTH_MAP][HEIGHT_MAP]){
   
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

void searchPremTermTile(int map[WIDTH_MAP][HEIGHT_MAP], int *prem, SDL_Rect *positionDebut, SDL_Rect *positionFin){

        for(int i=0; i<HEIGHT_MAP; i++){
            for(int j=0; j<WIDTH_MAP; j++){
                if(map[j][i] == 2 && *prem == 0){
                    positionDebut->x = j*TAILLE;
                    positionDebut->y = i*TAILLE;
                    *prem = 1;
                }

                if(map[j][i] == 2 ){
                    positionFin->x = j*TAILLE;
                    positionFin->y = i*TAILLE;
                }
            }
        }



}


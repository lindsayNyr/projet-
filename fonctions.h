//Fonctions 
#include "math.h"

int Distance(int x1, int y1, int x2, int y2) {
    return sqrt((y2 - y1)*(y - y1) + (x2 - x1)*(y - y1));
} 

void Deplacement(struct Enemy* EnemyTab, int *p, int* currentDirection,int* animFlip){
    
    int i = EnemyTab[*p].indiceX;
    int j = EnemyTab[*p].indiceY;

    SDL_Delay(10);
  
    if (EnemyTab[*p].HP > 0){
        if (EnemyTab[*p].copieMap[i+1][j] == 2){
           
            EnemyTab[*p].Position.x += 1;
            *currentDirection = 1;
            EnemyTab[*p].copieMap[i][j] = 0;
            if (EnemyTab[*p].pixel == 32){
               
                EnemyTab[*p].indiceX+=1; 
                *animFlip = 1 - *animFlip;
            }
        }
    
        else{

            if (EnemyTab[*p].copieMap[i][j+1] == 2){
                
                EnemyTab[*p].Position.y += 1;
                *currentDirection = 2;         
                EnemyTab[*p].copieMap[i][j] = 0;
                if (EnemyTab[*p].pixel == 32){
                  
                    EnemyTab[*p].indiceY+=1;
                    *animFlip = 1 - *animFlip;
                }
            }
            else{
                
                if (EnemyTab[*p].copieMap[i-1][j] == 2){
                   
                    EnemyTab[*p].Position.x -= 1;
                    *currentDirection = 3;             
                    EnemyTab[*p].copieMap[i][j] = 0;
                    if (EnemyTab[*p].pixel == 32){
                      
                        EnemyTab[*p].indiceX-=1;
                        *animFlip = 1 - *animFlip;
                    }
                }
            
                else{
                    
                    if (EnemyTab[*p].copieMap[i][j-1] == 2){
                       
                        EnemyTab[*p].Position.y -= 1;
                        *currentDirection = 0;
                        EnemyTab[*p].copieMap[i][j] = 0;
                        if (EnemyTab[*p].pixel == 32){
                       
                            EnemyTab[*p].indiceY-=1;
                            *animFlip = 1 - *animFlip;
                        }
                    }           
                }
            }   
        }
    
        EnemyTab[*p].pixel = EnemyTab[*p].pixel+1;
    
        if (EnemyTab[*p].pixel == 33){
       
            EnemyTab[*p].pixel = 1;
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


//Fonctions 

void Deplacement(struct Enemy* mechant, int copie_map[WIDTH_MAP][HEIGHT_MAP], int* currentDirection,int* animFlip, int* x, int* y, int* k){
    
    int i = *x;
    int j = *y;

    SDL_Delay(10);
  
    if (mechant->HP > 0){
        if (copie_map[i+1][j] == 2){
           
            mechant->Position.x += 1;
            *currentDirection = 1;
            copie_map[i][j] = 0;
            if (*k == 32){
               
                *x+=1; 
                *animFlip = 1 - *animFlip;
            }
        }
    
        else{

            if (copie_map[i][j+1] == 2){
                
                mechant->Position.y += 1;
                *currentDirection = 2;         
                copie_map[i][j] = 0;
                if (*k == 32){
                  
                    *y+=1;
                    *animFlip = 1 - *animFlip;
                }
            }
            else{
                
                if (copie_map[i-1][j] == 2){
                   
                    mechant->Position.x -= 1;
                    *currentDirection = 3;             
                    copie_map[i][j] = 0;
                    if (*k == 32){
                      
                        *x-=1;
                        *animFlip = 1 - *animFlip;
                    }
                }
            
                else{
                    
                    if (copie_map[i][j-1] == 2){
                       
                        mechant->Position.y -= 1;
                        *currentDirection = 0;
                        copie_map[i][j] = 0;
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


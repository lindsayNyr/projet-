//Fonctions 
 

void Deplacement(struct Enemy* mechent){
    
    int i = mechent->indiceX;
    int j = mechent->indiceY;

    SDL_Delay(5);
  
    if (mechent->HP > 0){
        if (mechent->copieMap[i+1][j] == 2){
           
            mechent->Position.x += 1;
            mechent->currentDirection = 1;
            mechent->copieMap[i][j] = 0;
            if (mechent->pixel == 32){
               
                mechent->indiceX+=1; 
                mechent->animFlip = 1 - mechent->animFlip;
            }
        }
    
        else{

            if (mechent->copieMap[i][j+1] == 2){
                
                mechent->Position.y += 1;
                mechent->currentDirection = 2;         
                mechent->copieMap[i][j] = 0;
                if (mechent->pixel == 32){
                  
                    mechent->indiceY+=1;
                    mechent->animFlip = 1 - mechent->animFlip;
                }
            }
            else{
                
                if (mechent->copieMap[i-1][j] == 2){
                   
                    mechent->Position.x -= 1;
                    mechent->currentDirection = 3;             
                    mechent->copieMap[i][j] = 0;
                    if (mechent->pixel == 32){
                      
                        mechent->indiceX-=1;
                        mechent->animFlip = 1 - mechent->animFlip;
                    }
                }
            
                else{
                    
                    if (mechent->copieMap[i][j-1] == 2){
                       
                        mechent->Position.y -= 1;
                        mechent->currentDirection = 0;
                        mechent->copieMap[i][j] = 0;
                        if (mechent->pixel == 32){
                       
                            mechent->indiceY-=1;
                            mechent->animFlip = 1 - mechent->animFlip;
                        }
                    }           
                }
            }   
        }
    
        mechent->pixel = mechent->pixel+1;
    
        if (mechent->pixel == 33){
       
            mechent->pixel = 1;
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


//Fonctions 
 

void Deplacement(struct Enemy* mechent){
    
    int i = mechent->indiceX;
    int j = mechent->indiceY;


  
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

void deplacer(struct Enemy* EnemyTab, SDL_Rect positionFin,  SDL_Rect positionDebut, int cptEnemy){
    
    
    for( int p = 0 ; p < cptEnemy; p++){
		if((EnemyTab[p].Position.x != positionFin.x) || (EnemyTab[p].Position.y != positionFin.y)){
			if(p == 0){
                
                Deplacement(&EnemyTab[p]);
                if (EnemyTab[p].Position.x == positionDebut.x + 1){
                       
                        EnemyTab[p].estVivant = 1;
                    }
            }
					    
			else{
                    
                if( EnemyTab[p-1].Position.x >=32  ){
                        
                    Deplacement(&EnemyTab[p]);
                    if (EnemyTab[p].Position.x == positionDebut.x + 1){
                            
                        EnemyTab[p].estVivant = 1;
                    }
                }
            }
		}
    }    
}









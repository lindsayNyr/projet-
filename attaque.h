#define abs_max(x, y) ((abs(x)>abs(y))?abs(x):abs(y)) 
#define TAILLE 32
#include "define.h"


//fonction qui retourne 1 si la tour est assez proche pour attaquer
int estAPortee(struct Tower* tour, struct Enemy* mechant, int* towerAttack){
    
    if (((tour->Position.x -tour->distAttaque*TAILLE) <= (mechant->Position.x) &&(mechant->Position.x)  <= (tour->Position.x+tour->distAttaque*TAILLE)  && (tour->Position.y - tour->distAttaque*TAILLE) <= (mechant->Position.y) && (mechant->Position.y)<= ( tour->Position.y+tour->distAttaque*TAILLE))&&(mechant->HP >0)){

       *towerAttack = 1;
       
        return 1;
	
    }
    
    else{
        
        return 0;
    }
}



//fonction d'attaque
void Attack(struct Tower* tour , struct Enemy* mechant, int y){

    if (((tour->Position.x -tour->distAttaque*TAILLE) <= (mechant->Position.x) &&(mechant->Position.x)  <= (tour->Position.x+tour->distAttaque*TAILLE)  && (tour->Position.y - tour->distAttaque*TAILLE) <= (mechant->Position.y) && (mechant->Position.y)<= ( tour->Position.y+tour->distAttaque*TAILLE))&&(mechant->HP >0)){
       
        mechant->HP -= tour->degats;
       
        if (mechant->HBImage.w >0){
         
            mechant->HBImage.w = 32-(32-( (32*mechant->HP)/(1000*y)));
        }
    }

    if (mechant->HP < 0){
      
      mechant->HBImage.w = 0;
    }

   
    
}


typedef struct {

    float x, y;

} f_vecteur2D;



void dot(SDL_Surface * surf,int x,int y,Uint32 color) {
    SDL_Rect rect;
    rect.x=x+16;
    rect.y=y+16;
    rect.w=1;
    rect.h=1;

    SDL_FillRect(surf,&rect,color);
}


void DrawLine(SDL_Surface * surf,int x1,int y1,int x2,int y2,Uint32 color){

    int div,i;

    // Pos contient la position actuelle sur la ligne
    // Move contient le vecteur qui est ajouté à pos pour passer au pixel suivant
    f_vecteur2D pos,move;

    // Position de départ
    pos.x=x1;
    pos.y=y1;

    // Déplacement maxi
    move.x=x2-x1;
    move.y=y2-y1;

    // On divise ce déplacement par la plus grande différence de coordonnées
    div = abs_max(x2-x1,y2-y1);
    move.x=move.x/div;
    move.y=move.y/div;

    // Maintenant, on boucle DIV fois
    for(i=0;i<div;i+=1){
        // Point
        dot(surf,(int)pos.x,(int)pos.y,color);

        // On avance
        pos.x+=move.x;
        pos.y+=move.y;
    }
}



void attaquer(int cptEnemy, struct Enemy* EnemyTab, struct Tower towerBlue, struct Tower towerBlackE, struct Tower towerBlueE, 
                struct Tower towerBlack, int towerAttack[WIDTH_MAP][HEIGHT_MAP], 
                int towerArray[WIDTH_MAP][HEIGHT_MAP], SDL_Surface* screen, int y ){
  
     
    for(int p=0; p<cptEnemy; p++){      
    	for (int j=0;j< WIDTH_MAP;j++){
            for (int i=0;i<HEIGHT_MAP-1;i++){      
               
                if ( towerArray[j][i] == 1){
                    
                    towerBlack.Position.x = j*TAILLE;
                    towerBlack.Position.y = i*TAILLE;
                                    
                    if (towerAttack[j][i] == 0){
                        if (estAPortee(&towerBlack, &EnemyTab[p], &towerAttack[j][i])){
                               
                            DrawLine(screen, towerBlack.Position.x,towerBlack.Position.y, EnemyTab[p].Position.x, EnemyTab[p].Position.y, 3000);
                            Attack(&towerBlack, &EnemyTab[p], y);
                        }
                    }			 
                }
                        
                if ( towerArray[j][i] == 2){
                            
                    towerBlue.Position.x = j*TAILLE;
                    towerBlue.Position.y = i*TAILLE;
                            
                    if (towerAttack[j][i] == 0){
                        if (estAPortee(&towerBlue, &EnemyTab[p], &towerAttack[j][i]) ){
                                   
                            DrawLine(screen, towerBlue.Position.x,towerBlue.Position.y, EnemyTab[p].Position.x, EnemyTab[p].Position.y, 3000);
                            Attack(&towerBlue, &EnemyTab[p], y);
                                
                        }
                    }
                }

                if ( towerArray[j][i] == 3){
                    
                    towerBlackE.Position.x = j*TAILLE;
                    towerBlackE.Position.y = i*TAILLE;
                                    
                    if (towerAttack[j][i] == 0){
                        if (estAPortee(&towerBlackE, &EnemyTab[p], &towerAttack[j][i])){
                               
                            DrawLine(screen, towerBlackE.Position.x,towerBlackE.Position.y, EnemyTab[p].Position.x, EnemyTab[p].Position.y, 3000);
                            Attack(&towerBlackE, &EnemyTab[p], y);
                        }
                    }            
                }

                if ( towerArray[j][i] == 4){
                            
                    towerBlueE.Position.x = j*TAILLE;
                    towerBlueE.Position.y = i*TAILLE;
                            
                    if (towerAttack[j][i] == 0){
                        if (estAPortee(&towerBlueE, &EnemyTab[p], &towerAttack[j][i]) ){
                                   
                            DrawLine(screen, towerBlueE.Position.x, towerBlueE.Position.y, EnemyTab[p].Position.x, EnemyTab[p].Position.y, 3000);
                            Attack(&towerBlueE, &EnemyTab[p], y);
                                
                        }
                    }
                }
            }
    	}	    
    }
  
}

void estMort(int cptEnemy, struct Enemy* EnemyTab, SDL_Surface* screen,SDL_Surface* explosion, SDL_Rect explosionImage, int *nbEnnemisTues, int *argent ){
  
    for( int p = 0 ; p < cptEnemy; p++){
		if (EnemyTab[p].HP <= 0 && EnemyTab[p].estVivant == 1){       //quand un ennemi meurt
		    for (int j=0; j<4; j++){ // 4 nb image sprite explosion 
			    
    			explosionImage.x = j*TAILLE ;
    			SDL_BlitSurface(explosion, &explosionImage, screen, &EnemyTab[p].Position);
                SDL_Delay(5);
    			SDL_UpdateRect(screen,0,0,0,0);
    			EnemyTab[p].estVivant = 0;
    			    
    		}
    		*nbEnnemisTues +=1;
    		*argent += 10;
    	}
	}  
}




void initTabAttack(int towerAttack[WIDTH_MAP][HEIGHT_MAP]){

    for(int j=0; j<WIDTH_MAP; j++){
        for(int i=0; i<HEIGHT_MAP; i++){
   
            towerAttack[j][i] = 0 ;
        }
    }

}
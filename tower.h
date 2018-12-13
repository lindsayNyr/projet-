
#include "define.h"

void positionTower(int *towerFlagBlack, int *towerFlagBlue, int towerArray[WIDTH_MAP][HEIGHT_MAP], struct Tower towerBlack,struct Tower towerBlue){
  
    if (*towerFlagBlack == 1){
        
        towerArray[towerBlack.Position.x/TAILLE][towerBlack.Position.y/TAILLE] = 1;
        *towerFlagBlack = 0;
	}

	if (*towerFlagBlue == 1){
        
        towerArray[towerBlue.Position.x/TAILLE][towerBlue.Position.y/TAILLE] = 2;
        *towerFlagBlue = 0;
	}	  
}

void afficherTower(int towerArray[WIDTH_MAP][HEIGHT_MAP], struct Tower towerBlack,struct Tower towerBlue, SDL_Surface *screen , SDL_Surface *towerblue, SDL_Surface *towerblack, SDL_Rect towerImage ){
  
  
  
    for (int j=0;j< WIDTH_MAP;j++){
        for (int i=0;i<HEIGHT_MAP;i++){
            if ( towerArray[j][i] == 1){
                    
                towerBlack.Position.x = j*TAILLE;
                towerBlack.Position.y = i*TAILLE-8;
                SDL_BlitSurface(towerblack, &towerImage, screen, &towerBlack.Position);  
            }
                
            if ( towerArray[j][i] == 2){
                
                towerBlue.Position.x = j*TAILLE;
                towerBlue.Position.y = i*TAILLE-8;
                SDL_BlitSurface(towerblue, &towerImage, screen, &towerBlue.Position);  
            }
        }
    }			      
}

void initTabTower(int towerArray[WIDTH_MAP][HEIGHT_MAP]){

    for(int j=0; j<WIDTH_MAP; j++){
        for(int i=0; i<HEIGHT_MAP; i++){
              
            
            towerArray[j][i] = 0 ;    
            
            if ( j == 0  && i == HEIGHT_MAP-1 ){
               
                towerArray[j][i] = 1;     
            }
            
            if ( j == 2  && i == HEIGHT_MAP-1 ){
               
                towerArray[j][i] = 2;     
            }
        }  
    }   
}

void initTower(struct Tower* towerBlack,struct Tower* towerBlue){

    towerBlack->distAttaque = 3;
    towerBlack->degats = 5;   //par pixel
    towerBlack->cout = 10;
    towerBlack->Position.x = 0;
    towerBlack->Position.y = 0; 
    
    
    //declaration d'une tour
    
    towerBlue->distAttaque = 2;
    towerBlue->degats = 10;   //par pixel
    towerBlue->cout = 20;
    towerBlue->Position.x = 0;
    towerBlue->Position.y = 0; 



}
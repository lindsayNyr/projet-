
#include "define.h"

void positionTower( int towerArray[WIDTH_MAP][HEIGHT_MAP], struct Tower *towerBlack,struct Tower *towerBlue, struct Tower *towerBlackE ,struct Tower *towerBlueE){
  
    if (towerBlack->flag == 1){
        
        towerArray[towerBlack->Position.x/TAILLE][towerBlack->Position.y/TAILLE] = 1;
        towerBlack->flag = 0;
	}

	if (towerBlue->flag == 1){
        
        towerArray[towerBlue->Position.x/TAILLE][towerBlue->Position.y/TAILLE] = 2;
        towerBlue->flag = 0;
	}

    if (towerBlackE->flag == 1){
        
        towerArray[towerBlackE->Position.x/TAILLE][towerBlackE->Position.y/TAILLE] = 3;
        towerBlackE->flag = 0;
    }

    if (towerBlueE->flag == 1){
        
        towerArray[towerBlueE->Position.x/TAILLE][towerBlueE->Position.y/TAILLE] = 4;
        towerBlueE->flag = 0;
    }   	  
}

void afficherTower(int towerArray[WIDTH_MAP][HEIGHT_MAP], struct Tower towerBlack, struct Tower towerBlue, 
                    struct Tower towerBlackE, struct Tower towerBlueE, SDL_Surface *screen , SDL_Surface *towerblue, 
                    SDL_Surface *towerblack, SDL_Surface *towerblueE, SDL_Surface *towerblackE,  SDL_Rect towerImage ){
  
  
  
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

            if ( towerArray[j][i] == 3){
                    
                towerBlackE.Position.x = j*TAILLE;
                towerBlackE.Position.y = i*TAILLE-8;
                SDL_BlitSurface(towerblackE, &towerImage, screen, &towerBlackE.Position);  
            }
                
            if ( towerArray[j][i] == 4){
                
                towerBlueE.Position.x = j*TAILLE;
                towerBlueE.Position.y = i*TAILLE-8;
                SDL_BlitSurface(towerblueE, &towerImage, screen, &towerBlueE.Position);  
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
            
            if ( j == 5  && i == HEIGHT_MAP-1 ){
               
                towerArray[j][i] = 2;     
            }
        }  
    }   
}

void initTower(struct Tower* towerBlack,struct Tower* towerBlue,struct Tower* towerBlackE ,struct Tower* towerBlueE ){


    towerBlack->distAttaque = 3;
    towerBlack->degats = 20;   
    towerBlack->cout = 20;
    towerBlack->Position.x = 0;
    towerBlack->flag= 0; 
    
    towerBlue->distAttaque = 2;
    towerBlue->degats = 70;   
    towerBlue->cout = 100;
    towerBlue->Position.x = 0;
    towerBlue->Position.y = 0; 
    towerBlue->flag= 0; 
    
    towerBlackE->distAttaque = 3;
    towerBlackE->degats = 40;   
    towerBlackE->cout = 10;
    towerBlackE->Position.x = 0;
    towerBlackE->Position.y = 0; 
    towerBlackE->flag = 0; 
    
    towerBlueE->distAttaque = 2;
    towerBlueE->degats = 100;   
    towerBlueE->cout = 50;
    towerBlueE->Position.x = 0;
    towerBlueE->flag = 0; 
}

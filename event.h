#include "define.h"


void HandleEvent(SDL_Event event, int* gameover, SDL_Rect* towerPositionBlack, SDL_Rect* towerPositionBlue,SDL_Rect* towerPositionBlackE, SDL_Rect* towerPositionBlueE,
    int *towerCoutBlack, int *towerCoutBlue,int *towerCoutBlackE, int *towerCoutBlueE, int *argent, int *towerFlagBlack, 
    int *towerFlagBlue,int *towerFlagBlackE, 
    int *towerFlagBlueE , int *click, int map[WIDTH_MAP][HEIGHT_MAP],int towerArray[WIDTH_MAP][HEIGHT_MAP] )
{
	int i, j;
    switch (event.type) {
        
        /* close button clicked */
        case SDL_QUIT:
           
            *gameover = 1;
        break;

        /* handle the keyboard */
        case SDL_KEYDOWN:
            
            switch (event.key.keysym.sym) {
              
                case SDLK_q:
                    
                    *gameover = 1;
                break;
                
                default:
                break;    
            }
            
            //break;

        case SDL_MOUSEBUTTONDOWN:
		   
		    if ( event.motion.x < 32 &&  event.motion.x > 0 && event.motion.y < 704 &&  event.motion.y > 672 && *click == 0 && *argent >= *towerCoutBlack ){ //tour noir
                if(event.button.button == SDL_BUTTON_LEFT){
                         
                    *click = 1;    
                }
            }     

            else{
                    
                if (*click== 1){ //la tour noire est selectionnée
			
        			i = event.motion.x / 32;
        			j = event.motion.y / 32;

        			if (map[i][j]==1){
        		           
                        towerPositionBlack->y = event.motion.y;
        		        towerPositionBlack->x = event.motion.x;
        		        *towerFlagBlack = 1;
        		        *argent -= *towerCoutBlack;
        		        *click = 0;
         			}  
                }

                else{

                    if ( event.motion.x < 3*32 &&  event.motion.x > 2*32 && event.motion.y < 704 &&  event.motion.y > 672 && *click == 0 && *argent >= *towerCoutBlue ){
                        if(event.button.button == SDL_BUTTON_LEFT){                   
                                
                            *click = 2;      
                        }
                    }
                    
                    else{

                        if (*click == 2){
    		               
                           	i = event.motion.x / 32;
    				        j = event.motion.y / 32;  
				            if (map[i][j]==1){                        
		                    
                                towerPositionBlue->y = event.motion.y;
    		                    towerPositionBlue->x = event.motion.x;
    		                    *towerFlagBlue = 1;
    		                    *click = 0; 
    		                    *argent -= *towerCoutBlue;  
                            }     
                        }
                    } 
                }
           

                if(event.button.button == SDL_BUTTON_RIGHT){
                    
                        i = event.motion.x / 32;
                        j = event.motion.y / 32; 

                    if (towerArray[i][j]==1){   
                        if(*argent >= *towerCoutBlackE){
         
                            towerPositionBlackE->y = event.motion.y;
                            towerPositionBlackE->x = event.motion.x;
                            *towerFlagBlackE = 1;
                            *argent -= *towerCoutBlackE;
                            //*click = 0;
                        }
                    }
                
                   // else{
                        if (towerArray[i][j]==2){ 

                           

                            if(*argent >= *towerCoutBlueE){
             
                               towerPositionBlueE->y = event.motion.y;
                               towerPositionBlueE->x = event.motion.x;
                               *towerFlagBlueE = 1;
                               *argent -= *towerCoutBlueE;  
                            }
                        }
                  //  }
                }
            }
        break;               
    }
}

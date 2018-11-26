#include "define.h"

void HandleEvent(SDL_Event event, int* gameover, SDL_Rect* towerPositionBlack, SDL_Rect* towerPositionBlue , int *towerFlagBlack, int *towerFlagBlue, int cout1, int cout2, int  *click, int* argent)
{

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





	   
		if ( event.motion.x < 32 &&  event.motion.x > 0 && event.motion.y < 640 &&  event.motion.y > 608 && *click == 0 && *argent >= cout1 ){ //tour bleue
               		if(event.button.button == SDL_BUTTON_LEFT){
                    		*click = 1;    
		        }
		  }     

			else{
                		if (*click== 1){ //la tour bleue est selectionnée
		            		towerPositionBlack->y = event.motion.y;
		            		towerPositionBlack->x = event.motion.x;
		            		*towerFlagBlack = 1;
					*argent -= cout1;
		            		*click = 0;   
                		}
			else{


		            	if ( event.motion.x < 3*32 &&  event.motion.x > 2*32 && event.motion.y < 640 &&  event.motion.y > 608 && *click == 0 && *argent >= cout2 ){
                			if(event.button.button == SDL_BUTTON_LEFT){                   
                    				*click = 2;    
                			}
            			}
				else{
            			if (*click == 2){
		        		towerPositionBlue->y = event.motion.y;
		        		towerPositionBlue->x = event.motion.x;
		        		*towerFlagBlue = 1;
		        		*click = 0; 
			 		*argent -= cout2;  
				}
           		 } 
}
}		      
        	break;
               
        
    }
}

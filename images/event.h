#include "define.h"


void HandleEvent(SDL_Event event, int* gameover, SDL_Rect* towerPositionBlack, SDL_Rect* towerPositionBlue,SDL_Rect* towerPositionBlackE, SDL_Rect* towerPositionBlueE,
    int *towerCoutBlack, int *towerCoutBlue,int *towerCoutBlackE, int *towerCoutBlueE, int *argent, int *towerFlagBlack, 
    int *towerFlagBlue,int *towerFlagBlackE, 
    int *towerFlagBlueE , int *click, int map[WIDTH_MAP][HEIGHT_MAP],int towerArray[WIDTH_MAP][HEIGHT_MAP] )
{
	int i = 0, j = 0;
	int mousex = 0, mousey = 0 ;
	
	
	
	
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
            
            break;

        case SDL_MOUSEBUTTONDOWN:
	  
		   
		       
		    	
		     switch(event.button.button){
		       
		
		       
		       case SDL_BUTTON_LEFT:
			
			mousex = event.button.x/32 ;
			mousey = event.button.y/32 ;


		   
			 if ( mousex == 0 && mousey == 21 && *click == 0 && *argent >= *towerCoutBlack ){ //tour noir
              
                         
                    *click = 1;    
                }
                 

            else{
                    
                if (*click== 1){ //la tour noire est selectionnée
			
        			i = event.button.x / 32;
        			j = event.button.y / 32;

        			if (map[i][j]==1 && towerArray[i][j] != 1 && towerArray[i][j] != 3){
        		           
                        towerPositionBlack->y = event.button.y;
        		        towerPositionBlack->x = event.button.x;
        		        *towerFlagBlack = 1;
        		        *argent -= *towerCoutBlack;
        		        *click = 0;
         			}  
                }

                else{

                    if ( mousex == 5 && mousey == 21 && *click == 0 && *argent >= *towerCoutBlue ){
                     //   if(event.button.button == SDL_BUTTON_LEFT){                   
                                
                            *click = 2;      
                        }
                   // }
                    
                    else{

                        if (*click == 2){
    		               
                           	i = event.button.x / 32;
    				        j = event.button.y / 32;  
				            if (map[i][j]==1 && towerArray[i][j] != 2 && towerArray[i][j] != 5){                        
		                    
                               towerPositionBlue->y = event.button.y;
    		                    towerPositionBlue->x = event.button.x;
    		                    *towerFlagBlue = 1;
    		                    *click = 0; 
    		                    *argent -= *towerCoutBlue;  
                            }     
                        }
                    } 
                }
	    }
	    break;
	    

              case SDL_BUTTON_RIGHT : 
                    
                    i = event.button.x / 32;
                    j = event.button.y / 32; 

                    if ((towerArray[i][j] == 1) && ((i != 0 && j != 21) ||  (i != 5 && j != 21))&& (*click == 0)){   
                        if(*argent >= *towerCoutBlackE){
         
                            towerPositionBlackE->y = event.button.y;
                            towerPositionBlackE->x = event.button.x;
                            *towerFlagBlackE = 1;
                            *argent -= *towerCoutBlackE;
                            
                        }
                    }
                
                 
                    if ((towerArray[i][j]==2) && ((i != 0 && j != 21) ||  (i != 5 && j != 21))&&(*click == 0)){ 

                        if(*argent >= *towerCoutBlueE){
             
                            towerPositionBlueE->y = event.button.y;
                            towerPositionBlueE->x = event.button.x;
                            *towerFlagBlueE = 1;
                            *argent -= *towerCoutBlueE;  
                        }
                    }
                  
                }
            
	      default:
	    break;
        break;               
    }
}

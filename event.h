

void HandleEvent(SDL_Event event, int* gameover, SDL_Rect* towerPositionBlack, SDL_Rect* towerPositionBlue,int *towerCoutBlack, int *towerCoutBlue, int *argent, int *towerFlagBlack, int *towerFlagBlue,int  *click)
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
		   
		    if ( event.motion.x < 32 &&  event.motion.x > 0 && event.motion.y < 640 &&  event.motion.y > 608 && *click == 0 && *argent >= *towerCoutBlack ){ //tour noir
                if(event.button.button == SDL_BUTTON_LEFT){
                         
                    *click = 1;    
                }
            }     

            else{
                    
                if (*click== 1){ //la tour noire est selectionnée
                        towerPositionBlack->y = event.motion.y;
                        towerPositionBlack->x = event.motion.x;
                        *towerFlagBlack = 1;
                        *argent -= *towerCoutBlack;
                        *click = 0;   
                }
                else{

                    if ( event.motion.x < 3*32 &&  event.motion.x > 2*32 && event.motion.y < 640 &&  event.motion.y > 608 && *click == 0 && *argent >= *towerCoutBlue ){
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
                            *argent -= *towerCoutBlue;  
                        }
                    } 
                }
            }
        break;               
    }
}

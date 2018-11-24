


void HandleEvent(SDL_Event event, int* gameover, SDL_Rect* towerPosition, int *towerPositionning, int* argent, int* cout)
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
            
            break;

        	case SDL_MOUSEBUTTONDOWN:

		   if (*argent >= *cout){
			 /* if ( event.motion.x < 32 &&  event.motion.x > 0 && event.motion.y < 576 &&  event.motion.y > 544 ){*/
		        *towerPositionning = 1;
	                towerPosition->y = event.motion.y;
	                towerPosition->x = event.motion.x;
			*argent -= *cout;
		}
		   // printf("ok\n");
			
		    
		/*  }*/
	        break;
               
        
	    }
}


void MenuEvent(SDL_Event eventMenu ,int* compteurMenu , int* gameover)
{

    switch (eventMenu.type) {
        
        /* close button clicked */
        case SDL_QUIT:
          
            
            *gameover = 1;
        break;

        /* handle the keyboard */
        case SDL_KEYDOWN:
            
            switch (eventMenu.key.keysym.sym) {
              
                case SDLK_q:
                    
                    *gameover = 1;
                break;
		
                case SDLK_SPACE:
			     
                    *compteurMenu = 0; 
                default:
                break;    
            }
            
            //break;
            case SDL_MOUSEBUTTONDOWN:
        		if (eventMenu.motion.x > 9*32 && eventMenu.motion.x < 15*32 && eventMenu.motion.y > 2*32 && eventMenu.motion.y < 4*32){
        		 
                    *compteurMenu = 0;
        		}
		
        		if (eventMenu.motion.x > 9*32 && eventMenu.motion.x < 15*32 && eventMenu.motion.y > 5*32 && eventMenu.motion.y < 7*32){
        		  
                    *gameover = 1;
        		}
	        break;
    }
    
}

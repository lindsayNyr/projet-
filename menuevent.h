
void MenuEvent(SDL_Event touche ,int* compteur, int* gameover)
{

    switch (touche.type) {
        
        /* close button clicked */
        case SDL_QUIT:
           printf("evenement !!\n");
            *gameover = 1;
        break;

        /* handle the keyboard */
        case SDL_KEYDOWN:
            
            switch (touche.key.keysym.sym) {
              
                case SDLK_q:
                    
                    *gameover = 1;
                break;
		case SDLK_SPACE:
			*compteur = 0;
                
                default:
                break;    
            }
            
            //break;
            case SDL_MOUSEBUTTONDOWN:
		if (touche.motion.x > 9*32 && touche.motion.x < 15*32 && touche.motion.y > 2*32 && touche.motion.y < 4*32){
		  *compteur = 0;
		}
		
		if (touche.motion.x > 9*32 && touche.motion.x < 15*32 && touche.motion.y > 5*32 && touche.motion.y < 7*32){
		  *gameover = 1;
		}
		
	      
	    break;

    }
}

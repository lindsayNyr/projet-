
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


               
        
    }
}

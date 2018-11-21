


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
		  printf("argent = %d cout = %d \n", *argent, *cout);
		  if (*argent >= *cout){
                    towerPosition->x = event.motion.x-20;
                    towerPosition->y = event.motion.y-20;
                    *towerPositionning = 1;
		    *argent -= *cout;
		  }
                break;
               

            
            
        }
    }

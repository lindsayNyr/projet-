


void HandleEvent(SDL_Event event, int* gameover, SDL_Rect* towerPosition, int *towerPositionning, int *PosX, int *PosY)
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
		   
		 /* if ( event.motion.x < 32 &&  event.motion.x > 0 && event.motion.y < 576 &&  event.motion.y > 544 ){*/
                    towerPosition->x = event.motion.x;
                    towerPosition->y = event.motion.y;
                    *towerPositionning = 1;
		    printf("ok\n");
		    
		/*  }*/
                break;
               

            
            
        }
    }

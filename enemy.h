

//#include <stdlib.h>



void initHBPosition(struct Enemy* EnemyTab, int cptEnemy){
   

    for(int p = 0; p < cptEnemy; p++){
                
        EnemyTab[p].HBPosition.y = EnemyTab[p].Position.y - 22;
        EnemyTab[p].HBPosition.x = EnemyTab[p].Position.x;
    }



}

void initEnemy(struct Enemy* EnemyTab,int cptEnemy, int map[WIDTH_MAP][HEIGHT_MAP], SDL_Rect positionDebut, int y){

    for (int i = 0; i < cptEnemy; i++){

        
        if( y >= 5){

            int nbAlea = (rand() % 2) + 1; 
            if(nbAlea == 1){
                
                EnemyTab[i].HP = 1000*y;
                EnemyTab[i].numEnemy = 1;

            }

            if(nbAlea == 2){

                EnemyTab[i].HP = 2000*y;
                EnemyTab[i].numEnemy = 2;

            }
        }

        else{

            EnemyTab[i].HP = 1000*y;
            EnemyTab[i].numEnemy = 1;

        }

        
        



        EnemyTab[i].indiceX = 0;
        EnemyTab[i].indiceY = 0;
        EnemyTab[i].pixel = 1;
        EnemyTab[i].estVivant = 0;
        EnemyTab[i].currentDirection = 0;
        EnemyTab[i].animFlip = 0;



        EnemyTab[i].Position.x = positionDebut.x ;
        EnemyTab[i].Position.y = positionDebut.y ;

        EnemyTab[i].HBPosition.x = 0;
        EnemyTab[i].HBPosition.y = 0;

            /* Define the source rectangle for the BlitSurface HB */
        EnemyTab[i].HBImage.y = positionDebut.y;
        EnemyTab[i].HBImage.x = positionDebut.x ;
        EnemyTab[i].HBImage.w = TAILLE;
        EnemyTab[i].HBImage.h = TAILLE; 

        for (int p = 0;p < HEIGHT_MAP; p++){
            for(int j = 0; j < WIDTH_MAP; j++){

              
                EnemyTab[i].copieMap[j][p] = map[j][p];
            }
        }       
    }
}

void afficherEnemy(struct Enemy* EnemyTab, int cptEnemy, SDL_Surface *sprite, SDL_Surface *sprite2,  SDL_Rect spriteImage, SDL_Surface *screen){

    for( int p = 0 ; p < cptEnemy; p++){
        if (EnemyTab[p].HP>0 && EnemyTab[p].estVivant== 1){

              
            spriteImage.x = TAILLE*(2*EnemyTab[p].currentDirection + EnemyTab[p].animFlip);

            if(EnemyTab[p].numEnemy == 1){
                SDL_BlitSurface(sprite, &spriteImage, screen, &EnemyTab[p].Position);
            }

            if(EnemyTab[p].numEnemy == 2){

               SDL_BlitSurface(sprite2 , &spriteImage, screen, &EnemyTab[p].Position);
            }
        }
    }
}

void afficherHB(struct Enemy* EnemyTab, int cptEnemy, SDL_Surface *HB, SDL_Surface *screen){

    for(int p = 0; p < cptEnemy; p++){

        if(EnemyTab[p].estVivant == 1){
                 
            SDL_BlitSurface(HB, &EnemyTab[p].HBImage, screen, &EnemyTab[p].HBPosition);  
        }
    }
}

void vie(struct Enemy* EnemyTab, int cptEnemy, int *nbVie, int *gameover, SDL_Rect positionFin){


    for(int p = 0; p < cptEnemy; p++){

        if((EnemyTab[p].Position.x == positionFin.x) && (EnemyTab[p].Position.y == positionFin.y)&&(EnemyTab[p].estVivant == 1)){

            *nbVie = *nbVie - 1;
            EnemyTab[p].estVivant = 0;
           printf("%d vies \n", *nbVie);
        }
    }
            
    if(*nbVie == 0){

        *gameover = 1;
    }
}
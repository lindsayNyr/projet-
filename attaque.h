#define abs_max(x, y) ((abs(x)>abs(y))?abs(x):abs(y)) 
#define TAILLE 32


//fonction qui retourne 1 si la tour est assez proche pour attaquer
int estAPortee(struct Tower* tour, struct Enemy* mechant){
    
    if (((tour->Position.x -tour->distAttaque*TAILLE) <= (mechant->Position.x) &&(mechant->Position.x)  <= (tour->Position.x+tour->distAttaque*TAILLE)  && (tour->Position.y - tour->distAttaque*TAILLE) <= (mechant->Position.y) && (mechant->Position.y)<= ( tour->Position.y+tour->distAttaque*TAILLE))&&(mechant->HP >0)){
       
        return 1;
    }
    
    else{
        
        return 0;
    }
}



//fonction d'attaque
void Attack(struct Tower* tour , struct Enemy* mechant, SDL_Rect* HBImage, int* cpt){

    if (((tour->Position.x -tour->distAttaque*TAILLE) <= (mechant->Position.x) &&(mechant->Position.x)  <= (tour->Position.x+tour->distAttaque*TAILLE)  && (tour->Position.y - tour->distAttaque*TAILLE) <= (mechant->Position.y) && (mechant->Position.y)<= ( tour->Position.y+tour->distAttaque*TAILLE))&&(mechant->HP >0)&&(*cpt ==32)){
       
        mechant->HP -= tour->degats;
        if (HBImage->w >0){
         
            HBImage->w = 32-(32-( (32*mechant->HP)/100));
        }
    }

    if (mechant->HP < 0){
      
      HBImage->w = 0;
    }

    *cpt +=1;
    
    if (*cpt == 33){
      
      *cpt = 1;
    }
 
    
}


typedef struct {

    float x, y;

} f_vecteur2D;



void dot(SDL_Surface * surf,int x,int y,Uint32 color) {
    SDL_Rect rect;
    rect.x=x+16;
    rect.y=y+16;
    rect.w=1;
    rect.h=1;

    SDL_FillRect(surf,&rect,color);
}


void DrawLine(SDL_Surface * surf,int x1,int y1,int x2,int y2,Uint32 color){

    int div,i;

    // Pos contient la position actuelle sur la ligne
    // Move contient le vecteur qui est ajouté à pos pour passer au pixel suivant
    f_vecteur2D pos,move;

    // Position de départ
    pos.x=x1;
    pos.y=y1;

    // Déplacement maxi
    move.x=x2-x1;
    move.y=y2-y1;

    // On divise ce déplacement par la plus grande différence de coordonnées
    div = abs_max(x2-x1,y2-y1);
    move.x=move.x/div;
    move.y=move.y/div;

    // Maintenant, on boucle DIV fois
    for(i=0;i<div;i+=1){
        // Point
        dot(surf,(int)pos.x,(int)pos.y,color);

        // On avance
        pos.x+=move.x;
        pos.y+=move.y;
    }
}

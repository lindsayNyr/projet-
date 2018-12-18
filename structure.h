
#include "define.h"

struct Enemy
{
  int HP;
  int indiceX; //indice map x
  int indiceY; //indice map y 
  int pixel ;
  int numEnemy;
  int estVivant;
  int currentDirection ; /* Information about the current situation of the sprite: */
  int animFlip; /* Information about the animationFlip of the sprite: */
  SDL_Rect HBImage;
  int copieMap[WIDTH_MAP][HEIGHT_MAP];
  SDL_Rect Position;
  SDL_Rect HBPosition;
 
} Enemy;




struct Tower
{
  int distAttaque;
  int degats;
  int cout;
  int flag;
  SDL_Rect Position;
};

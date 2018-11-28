
#include "define.h"

struct Enemy
{
  int HP;
  int vitesse;
  int indiceX; //indice map x
  int indiceY; //indice map y 
  int pixel ;
  int copieMap[WIDTH_MAP][HEIGHT_MAP];
  SDL_Rect Position;
 
} Enemy;




struct Tower
{
  int distAttaque;
  int degats;
  int cout;
  SDL_Rect Position;
};

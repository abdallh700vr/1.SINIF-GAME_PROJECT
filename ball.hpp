#include "raylib.h"

class Ball {
public:
Texture2D color;
float x,y;

Ball(Texture2D color)
{
    this->color = color;
}
void draw(float x,float y){
   DrawTexture(color,x,y,WHITE);
}

};

#include <raylib.h>
#include <math.h>
#include "ball.hpp"
#include <iostream>
#include <time.h>

#define  Y 100
#define X 100

using namespace std;
// Get our angle between two points.
static float getangle(float x1,float y1,float x2,float y2);
// Our rectsoverlap function. Returns true/false.
static bool rectsoverlap(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2);

//*************************************************************************************
//class shutter

class shutter{

public:

int x=385;
int y=420;
int speed_x=7;
int speed_y=7;
Ball ball;



void draw(int x,int y){
   ball.draw(x,y);
}



void control(int color_random,Ball ball,Ball ball2,Ball ball3)
{
  if(color_random==1)
  {
    this->ball = ball;
  }
  else if (color_random==2)
  {
    this->ball=ball2;
  }
  else{
    this->ball=ball3;
  }
}

void handleinput(){
int key_pressed = GetKeyPressed();

switch (key_pressed)
{
case KEY_A:
if(x>0)
{
 x -=speed_x;
}
ball.draw(x,y);
    break;

case KEY_D:
if(x<800)
{
 x +=speed_x;
}
ball.draw(x,y);
break;
default:
    break;
}
}


};


int main(void)
{
  srand(time(NULL));
    //here we initialized the varibels
 //*******************************************************************************
    Color grey = {29,29,27,255};
    int color_random = (rand()%3)+1;
    int windowWidth = 800;
    int windowHeight = 490;
    int balls_matrix [Y][X]={0};
 //*******************************************************************************
for(int j = 0 ; j<5 ; j++)
{
for(int i = 0 ; i<20; i++)
{
    balls_matrix[j][i]=(rand()%3)+1;
}
}
balls_matrix[11][10]=1;
 //*******************************************************************************
 //here we started the window (box) 1100x720 and name it as "kafa patlat"
    InitWindow(windowWidth,windowHeight,"bubble booming");

 //*******************************************************************************
 //NOT:focus that you need to load the image after initwindow if you dont you will get errors
    Texture2D t1 = LoadTexture("t1.png");
     Texture2D t2 = LoadTexture("t2.png");
      Texture2D t3 = LoadTexture("t3.png");
    Texture2D Background = LoadTexture("Background.png");
 //*******************************************************************************     
  //here we difeind the objects
    Ball ball;
    Ball ball2;
    Ball ball3;
    ball.renk(t1);
    ball2.renk(t2);
    ball3.renk(t3);
    shutter s1;
    s1.control(color_random,ball,ball2,ball3);
    


 //********************************************************************
//ball object 
ball.x = 400;
ball.y = 225;
ball2.x = 400;
ball2.y = 225;
ball3.x = 400;
ball3.y = 225;
 //*******************************************************************************     
  //here we difeind how much fbs we need in the game
    SetTargetFPS(60);
 //*******************************************************************************
     float posx = 400;
     float posy = 400;

 //*******************************************************************************
 //GAME LOOP
    while (WindowShouldClose() ==  false)
    {
 
       s1.handleinput();
       if(IsMouseButtonPressed(0))
       {
        int mousex =GetMouseX();
        int mousey =GetMouseY();
        cout<<"hiiiiiiiiii:"<<mousex<<endl;
        cout<<"hiiiiiiiiii:"<<mousey<<endl;
       }




      //DRAWİNG BEGİNS
        BeginDrawing();
       //updating 
       
    
    
      
        ClearBackground(grey);
 //*******************************************************************************
       DrawTexture(Background,0,0,WHITE);
      
        //getting where is cursor standing to calculete the angle for the line
        float x = GetMouseX()/40*40;
        float y = GetMouseY()/40*40;
        float an = getangle(posx,posy,x,y);
        DrawRectangle(x,y,40,40,grey);

 //*******************************************************************************
        //here drawing the line for aiming 
        DrawLine(posx,posy+50,posx+cos(an)*40,posy+sin(an)*40,BLACK);
        
        for(int y = 0 ; y<Y ; y++)
        {
          for(int x = 0 ; x<X ; x++)
          {
             if(balls_matrix[y][x] == 1)
            {
                 ball.draw(x*40,y*40); 
            }
            else if(balls_matrix[y][x] == 2)
            {
              ball2.draw(x*40,y*40);
            } else if(balls_matrix[y][x] == 3)
            {
              ball3.draw(x*40,y*40);
            }
            
          }
        }
 
       
       //s1.draw(s1.x,s1.y);
        
        
        EndDrawing();
        
    }
     UnloadTexture(t1);
      UnloadTexture(t2);
       UnloadTexture(t3);

     UnloadTexture(Background);
    //close window 
    CloseWindow();
}

// Return the angle from - to in float
float getangle(float x1,float y1,float x2,float y2){
    return (float)atan2(y2-y1, x2-x1);
}
// Rectangles overlap
bool rectsoverlap(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2){
    if(x1 >= (x2 + w2) || (x1 + w1) <= x2) return false;
    if(y1 >= (y2 + h2) || (y1 + h1) <= y2) return false;
    return true;
}
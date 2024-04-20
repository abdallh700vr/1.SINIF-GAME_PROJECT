#include "raylib.h"
#include <math.h>
#define  Y 5
#define X 25


static float getangle(float x1 , float y1 , float x2 , float y2 );

int main(void)
{
    //here we initialized the varibels
 //*******************************************************************************
    Color grey = {29,29,27,255};
    int windowWidth = 1100;
    int windowHeight = 720;
    int balls_matrix [Y][X];
    Vector2 Ballpoition = { -100.0f , -100.0f};
 //*******************************************************************************
for(int j = 0 ; j<Y ; j++)
{
for(int i = 0 ; i<X; i++)
{
    balls_matrix[j][i]=1;
}
}
 //*******************************************************************************
 //here we started the window (box) 1100x720 and name it as "kafa patlat"
    InitWindow(windowWidth,windowHeight,"bubble booming");
 //*******************************************************************************
 //NOT:focus that you need to load the image after initwindow if you dont you will get errors
    Texture2D t1 = LoadTexture("t1.png");
    Texture2D Background = LoadTexture("Background.png");
 //*******************************************************************************     
  //here we difeind how much fbs we need in the game
    SetTargetFPS(60);
 //*******************************************************************************
     float posx = windowWidth/2;
     float posy = 620;

 //*******************************************************************************
 //GAME LOOP
    while (WindowShouldClose() ==  false)
    {
      //here Getting mouse position to set where the circle should be 
      Ballpoition = GetMousePosition();
      //DRAWİNG BEGİNS
        BeginDrawing();

      
        ClearBackground(grey);
 //*******************************************************************************
       DrawTexture(Background,0,0,WHITE);
      
        //getting where is cursor standing to calculete the angle for the line
        float x = GetMouseX()/32*32;
        float y = GetMouseY()/32*32;
        float an = getangle(posx,posy,x,y);
 //*******************************************************************************
        //here drawing the line for aiming 
        DrawLine(posx,posy,posx+cos(an)*32,posy+sin(an)*32,BLACK);
        
        for(int y = 0 ; y<Y ; y++)
        {
          for(int x = 0 ; x<X ; x++)
          {
            if( y%2 ==0 )
            {
              if(balls_matrix[y][x] == 1)
            {
                 DrawTexture(t1,x*42+50,y*42+20,WHITE);
            }
            }
            else{
              if(balls_matrix[y][x] == 1)
            {
                DrawTexture(t1,x*42+30,y*42+20,WHITE);
            }
            }
            
          }
        }
       

       //drawing the circle for the cursor
        DrawCircleV(Ballpoition,10,WHITE);
        
        
        EndDrawing();
    }
     UnloadTexture(t1);
     UnloadTexture(Background);
    //close window 
    CloseWindow();
}

float getangle(float x1 , float y1 , float x2 , float y2 ){
return (float)atan2(y2-y1 , x2-x1);
}
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




int main(void)
{
   //*******************************************************************************
 //here we started the window (box) 800x450 and name it as "kafa patlat"
   int windowWidth = 800;
    int windowHeight = 490;
    InitWindow(windowWidth,windowHeight,"bubble booming");

   //******************************************************************************* 

  //here we difeind how much fbs we need in the game
    SetTargetFPS(60);
   //******************************************************************************* 
  srand(time(NULL));
    //here we initialized the variables
 //*******************************************************************************
    Color grey = {29,29,27,255};
    int color_random = (rand()%3)+1;
    int balls_matrix [X][Y]={0};
    float animx;
    float animy;
    float animtargetx;
    float animtargety;
    bool startanim = false;
 //*******************************************************************************
for(int j = 0 ; j<5 ; j++)
{
for(int i = 0 ; i<20; i++)
{
    balls_matrix[i][j]=(rand()%3)+1;
}
}
 balls_matrix[10][11]=(rand()%3)+1;

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
 //********************************************************************


 //*******************************************************************************
     float posx = 400;
     float posy = 440;

 //*******************************************************************************
 //GAME LOOP
    while (WindowShouldClose() ==  false)
    {
     // Update
        //----------------------------------------------------------------------------------
        if(startanim==false){
            if(IsMouseButtonDown(0)){
                
                float x = GetMouseX()/40;
                float y = GetMouseY()/40;
                
                    if(balls_matrix[(int)x][(int)y]==0){
                    if( balls_matrix[(int)x][(int)y-1]>0 || balls_matrix[(int)x-1][(int)y]>0 || balls_matrix[(int)x+1][(int)y]>0){
                        startanim=true;
                         cout<<"x index control:"<<x<<endl;
                        animtargetx = x*40;
                        animtargety = y*40;
                        animx = posx;
                        animy = posy;
                    }}
                        // cout<<"x index control1:"<<(rand()%3)+1<<endl;
                    
                    
                }
        }
        if(startanim){
            float an = getangle(animx,animy,animtargetx,animtargety);
            animx += cos(an)*8;
            animy += sin(an)*8;
            if(rectsoverlap(animx-1,animy-1,32+2,32+2,animtargetx-1,animtargety-1,32+2,32+2)){
                startanim=false;
                balls_matrix[(int)animtargetx/40][(int)animtargety/40]=balls_matrix[10][11];
            }
            
        }
     
      //  if(IsMouseButtonPressed(0))
      //  {
      //   int mousex =GetMouseX();
      //   int mousey =GetMouseY();
      //   cout<<"hiiiiiiiiii:"<<mousex<<endl;
      //   cout<<"hiiiiiiiiii:"<<mousey<<endl;
      //  }




      //DRAWİNG BEGİNS
        BeginDrawing();
       //updating 
       
    
    
      
        ClearBackground(grey);
 //*******************************************************************************
 //here we defined the background
       DrawTexture(Background,0,0,WHITE);
      
        //getting where is cursor standing to calculete the angle for the line
        float x = GetMouseX()/40*40;
        float y = GetMouseY()/40*40;
        float an = getangle(posx,posy,x,y); 

 //*******************************************************************************
        //here drawing the line for aiming 
        DrawLine(posx,posy,posx+cos(an)*40,posy+sin(an)*40,BLACK);
        
        for(int y = 0 ; y<Y/5 ; y++)
        {
          for(int x = 0 ; x<X/5 ; x++)
          {
             if(balls_matrix[x][y] == 1)
            {
                 ball.draw(x*40,y*40); 
            }
            else if(balls_matrix[x][y] == 2)
            {
              ball2.draw(x*40,y*40);
            } else if(balls_matrix[x][y] == 3)
            {
              ball3.draw(x*40,y*40);
            }
            
          }
        }
        if(startanim){
             if(balls_matrix[10][11] == 1)
            {
                 ball.draw(animx,animy); 
            }
            else if(balls_matrix[10][11] == 2)
            {
              ball2.draw(animx,animy); 
            } else if(balls_matrix[10][11] == 3)
            {
             ball3.draw(animx,animy); 
            }
            }



 //*************************************************************************************************
        //here im drawing a box if the player can shoot
              float x_controlBox = GetMouseX()/40;
              float y_controlBox= GetMouseY()/40;
              
         if(balls_matrix[(int)x_controlBox][(int)y_controlBox]==0)
        {
          if(balls_matrix[(int)x_controlBox][(int)y_controlBox-1]>0 || balls_matrix[(int)x_controlBox-1][(int)y_controlBox]>0 || balls_matrix[(int)x_controlBox+1][(int)y_controlBox]>0)
          {
           DrawRectangle( x_controlBox*40 ,y_controlBox*40,40,40,DARKGRAY);
          } }
 //*************************************************************************************************
//here is the  end of everthing BYE ;)
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

#include <raylib.h>
#include <math.h>
#include "ball.hpp"
#include <iostream>
#include <time.h>
using namespace std;

//global variables
#define  Y 20
#define X 20
int balls_matrix [X][Y]={{1, 2, 3, 3, 3},
                         {3, 1, 3, 1, 2},
                         {2, 2, 3, 1, 1},
                         {3, 1, 2, 1, 1},
                         {3, 3, 3, 1, 1},
                         {1, 2, 1, 3, 2},
                         {2, 3, 2, 1, 3},
                         {3, 1, 3, 2, 2},
                         {1, 3, 1, 3, 2},
                         {3, 2, 3, 3, 3},
                         {2, 2, 2, 2, 1},
                         {2, 2, 2, 3, 1},
                         {3, 3, 3, 2, 3},
                         {3, 3, 3, 2, 1},
                         {2, 1, 2, 2, 1},
                         {1, 2, 1, 1, 2},
                         {2, 3, 2, 2, 1},
                         {3, 3, 3, 3, 2},
                         {1, 1, 1, 2, 3},
                         {3, 3, 3, 1, 1}};

int points=0;
int windowWidth = 800;
int windowHeight = 480;
bool startanim = false;
//*************************************************************************************
//close window button 
void close_window(Texture2D exit,int  x_exit , int32_t  y_exit);
//admin mode
void admin();
//drawing the balls
void draw_balls(Ball ball,Ball ball2 , Ball ball3,int x , int y);
// Get our angle between two points.
static float getangle(float x1,float y1,float x2,float y2);
// Our rectsoverlap function. Returns true/false.
static bool rectsoverlap(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2);
//we check if the player scored
void score(int x,int y);
//we here scroll down the matrix
void Scroll_down(int y_scroll);
//we here create end function
void EndScreen(int points,int x,int y);
//RESET the game
void Reset();

//*************************************************************************************


int main(void)
{
   //*******************************************************************************
 //here we started the window (box) 800x480 and name it as "kafa patlat"
    InitWindow(windowWidth,windowHeight,"bubble booming");
 // Initializing audio device
    InitAudioDevice();
   //******************************************************************************* 

  //here we difeind how much fbs we need in the game
    SetTargetFPS(60);
   //******************************************************************************* 
   //1970 :)
  srand(time(NULL));
    //here we initialize the variables
 //*******************************************************************************
    Color grey = {29,29,27,255};
    int color_random = (rand()%3)+1;
    float animx;
    float animy;
    float animtargetx;
    float animtargety;
    
    bool flag = false;
    int lastScrollDownScore = 0;
 //*******************************************************************************
 //random balls
// for(int j = 0 ; j<5 ; j++)
// {
// for(int i = 0 ; i<20; i++)
// {
//     balls_matrix[i][j]=(rand()%3)+1;
// }
// }
//***********************************************************************************
 balls_matrix[10][11]=(rand()%3)+1;

 //*******************************************************************************
 //NOT:focus that you need to load the image after initwindow if you dont you will get errors
    Texture2D t1 = LoadTexture("t1.png");
    Texture2D exit = LoadTexture("EXİT.png");
    Texture2D t2 = LoadTexture("t2.png");
    Texture2D t3 = LoadTexture("t3.png");
    Texture2D Background = LoadTexture("Background.png");
    Sound babu = LoadSound("babu.wav"); 
 //*******************************************************************************     
  //here we difeind the objects
    Ball ball(t1);
    Ball ball2(t2);
    Ball ball3(t3);
 
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
                        PlaySound(babu);
                    }}
                        // cout<<"x index control1:"<<(rand()%3)+1<<endl;
                    }}





        if(startanim){
            float an = getangle(animx,animy,animtargetx,animtargety);
            animx += cos(an)*8;
            animy += sin(an)*8;
            if(rectsoverlap(animx-1,animy-1,40+2,40+2,animtargetx-1,animtargety-1,40+2,40+2)){
                startanim=false;
                balls_matrix[(int)animtargetx/40][(int)animtargety/40]=balls_matrix[10][11];
                //here am checking if the player scored
                score((int)animtargetx/40,(int)animtargety/40);
               balls_matrix[10][11]=(rand()%3)+1;

            }}
     

      //DRAWİNG BEGİNS
        BeginDrawing();
      

    
        ClearBackground(grey);
 //*******************************************************************************
 //here we defined the background
       DrawTexture(Background,0,0,WHITE);
  //printing score
   DrawText(TextFormat("Score: %.3i", points),80,460, 20, BEIGE);
 //----------------------------------------------------------------------------------
 //scroll down 

      if(points%10==0 && points!=0 )
      { 
        if(lastScrollDownScore != points )
        {
         Scroll_down(points);
         lastScrollDownScore = points;
        }
      }


 //----------------------------------------------------------------------------------
      
      //getting where is cursor standing to calculete the angle for the line
        float x = GetMouseX()/40*40;
        float y = GetMouseY()/40*40;
        float an = getangle(posx,posy,x,y); 

 //*******************************************************************************
        //here drawing the line for aiming 
        DrawLine(posx,posy,posx+cos(an)*40,posy+sin(an)*40,BLACK);
        
       draw_balls(ball,ball2,ball3,animx,animy);

        DrawLine(0,400,800,400,SKYBLUE);


 //*************************************************************************************************
        //devloper mode 
        // admin();

  //**************************************************************************
   //close window  button 
   float x_exit = GetMouseX()/40;
   float y_exit = GetMouseY()/40;

    close_window(exit,x_exit,y_exit);
      
  EndScreen(points,x_exit,y_exit);
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





void close_window(Texture2D exit,int  x_exit, int  y_exit)
{


      DrawTexture(exit,720,410,WHITE);
      if(IsMouseButtonDown(0)){
              
         if((int)x_exit==18 && (int)y_exit==10 || (int)x_exit==18 && (int)y_exit==11 || (int)x_exit==19 && (int)y_exit==10 || (int)x_exit==19 && (int)y_exit==11)
          {
             CloseWindow();
          }}

}





void admin()
{
           float x_controlBox = GetMouseX()/40;
              float y_controlBox= GetMouseY()/40;
              
         if(balls_matrix[(int)x_controlBox][(int)y_controlBox]==0)
        {
          if(balls_matrix[(int)x_controlBox][(int)y_controlBox-1]>0 || balls_matrix[(int)x_controlBox-1][(int)y_controlBox]>0 || balls_matrix[(int)x_controlBox+1][(int)y_controlBox]>0)
          {
           DrawRectangle( x_controlBox*40 ,y_controlBox*40,40,40,DARKGRAY);
          } }
}



void draw_balls(Ball ball,Ball ball2 , Ball ball3,int x , int y)
{
         for(int y = 0 ; y<Y ; y++)
        {
          for(int x = 0 ; x<X ; x++)
          
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
            
          }}




        if(startanim){
             if(balls_matrix[10][11] == 1)
            {
                 ball.draw(x,y); 
            }
            else if(balls_matrix[10][11] == 2)
            {
              ball2.draw(x,y); 
            } else if(balls_matrix[10][11] == 3)
            {
             ball3.draw(x,y); 
            }}

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
//checking score
void score(int x,int y){

bool scored = false;
int temp1=balls_matrix[x][y];
  if(balls_matrix[x][y]>0)
  {


    if(balls_matrix[x][y]==balls_matrix[x][y] && balls_matrix[x-1][y]==balls_matrix[x][y] && balls_matrix[x+1][y]==balls_matrix[x][y])
    {                        
           scored=true;
             for(int i =x+1 ; i<20 ; i++)
             {
            
              if(balls_matrix[i][y]==temp1)
              {
                 balls_matrix[i][y]=0;
              }
              else{break;} 
             }  
             for(int i =x-1 ; i>=0 ; i--)
             {
            
              if(balls_matrix[i][y]==temp1)
              {
                 balls_matrix[i][y]=0;
              }
              else
              {break;}
             }

             points++;  

    }
         
           

            //checking right
            if(balls_matrix[x][y]==balls_matrix[x][y] && balls_matrix[x+1][y]==balls_matrix[x][y] && balls_matrix[x+2][y]==balls_matrix[x][y])
              {
                 scored = true;
             for(int i =x+1 ; i<20 ; i++)
             {
            
              if(balls_matrix[i][y]==temp1)
              {
                 for(int j =y-1 ; j>=0 ; j--)
             {
            
              if(balls_matrix[i][j]==temp1)
              {
                 balls_matrix[i][j]=0;
              }
              else{  
              break;
              }
              
             }

                 balls_matrix[i][y]=0;
              }
              else{ 
                 points++;
              break;
              }
              
             }
               }

              //checking left
                          
                 if(balls_matrix[x][y]==balls_matrix[x][y] && balls_matrix[x-1][y]==balls_matrix[x][y] && balls_matrix[x-2][y]==balls_matrix[x][y])
                 {
                   scored = true;
                for(int i =x-1 ; i>=0 ; i--)
                {
               
                 if(balls_matrix[i][y]==temp1)
                 {

                     if(balls_matrix[i][y]==temp1)
                    {
                       for(int j =y-1 ; j>=0 ; j--)
                   {
                  
                    if(balls_matrix[i][j]==temp1)
                    {
                       balls_matrix[i][j]=0;
                    }
                    else{  
                    break;
                    }
                    
                   }
                    }

                    balls_matrix[i][y]=0;
                 }
                 else{ 
                    points++;
                 break;
                 }
                 
                }
                  }
   
               //checking top 

               if(balls_matrix[x][y]==balls_matrix[x][y] && balls_matrix[x][y-1]==balls_matrix[x][y] && balls_matrix[x][y-2]==balls_matrix[x][y])
              {
                 scored = true;
             for(int i =y-1 ; i>=0 ; i--)
             {
            
              if(balls_matrix[x][i]==temp1)
              {



                for(int j =x-1 ; j>=0 ; j--)
                {
               
                 if(balls_matrix[j][i]==temp1)
                 {
                    balls_matrix[j][i]=0;
                 }
                 else{ 
                 break;
                 }
                }



               for(int j =x+1 ; j<20 ; j++)
             {
            
              if(balls_matrix[j][i]==temp1)
              {
                 balls_matrix[j][i]=0;
              }
              else{ 
              break;
              }
              
             }


                 balls_matrix[x][i]=0;
              }
              else{  
                points++;
              break;
              }
              
             }
               }
           
  }
              if(scored )
              balls_matrix[x][y]=0;
}

void Scroll_down(int y_scroll)
{
 
            int to_row= 5+(y_scroll/5);
           
            for(int j = y_scroll/5; j<to_row ; j++)
           {
           for(int i = 0 ; i<20; i++)
           {
               balls_matrix[i][j]=GetRandomValue(1,3);
           }
           }
           
            for(int j = 0 ; j<y_scroll/5 ; j++)
           {
           for(int i = 0 ; i<20; i++)
           {
               balls_matrix[i][j]=(rand()%3)+1;
           }
           }
}



void EndScreen(int points,int x,int y)
{
           bool control = false;
         for(int i = 0; i<=20 ; i++)
         {
           if(balls_matrix[i][10]>0)
           {
               balls_matrix[10][11]=0;
              DrawRectangle(240,120,300,300,SKYBLUE);
            DrawText(TextFormat("Score: %.3i", points),260,290, 20, BEIGE);
           DrawText(TextFormat("thx for support", points),260,160, 20, RED);
           DrawText(TextFormat("SEFA,SELiM", points),260,200, 20, RED);
            DrawText(TextFormat("SELÇUK,TURAN", points),260,240, 20, RED);
            DrawText(TextFormat("TRY AGAiN", points),260,320, 20, RED);
            DrawText(TextFormat("QUiT", points),400,320, 20, RED);
            control=true;
         }
         if(control)
         {
          if(IsMouseButtonDown(0))
            {
             if(x==6 || x==7 || x==8)
             {
               Reset();
             }
             else if(x==10)
             {
               CloseWindow();
             }
            }
         }
          
         
           }

}

//RESET the game
void Reset()
{
 
             points=0;
             for(int j = 0 ; j<11; j++)
             {
             for(int i = 0 ; i<20; i++)
             {
                 balls_matrix[i][j]=0;
             }
             }
             for(int j = 0 ; j<5 ; j++)
             {
             for(int i = 0 ; i<20; i++)
             {
                 balls_matrix[i][j]=(rand()%3)+1;
             }
             }
             
             
             balls_matrix[10][11]=(rand()%3)+1;
}

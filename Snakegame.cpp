#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver ;
const int width = 20;
const int height = 20;
int x,y;
int fruitX,fruitY;
int score = 0;
int nTails = 0;
int tailX[100],tailY[100];

enum eDirection{STOP = 0,UP,DOWN,LEFT,RIGHT};
eDirection dir;
void Setup(){
    dir = STOP;
    x = width/2,y = height/2;
    srand(time(nullptr));
    fruitX = rand() % width,fruitY = rand() % height;
    gameOver = false;
    score = 0;    
    return;
}

void Draw(){
    system("cls");
    for(int i=0;i<width;i++)
        cout << "#" ;
    cout << endl;
    for(int i=0;i<height-2;i++){
        for(int j=0;j<width;j++){
            if(j==0||j==width-1)
                cout << "#";
            else if(j==x&&i==y){
                cout << "0";
            }
            else if(j==fruitX&&i==fruitY){
                cout << "F";
            }
            else{
                bool print = false;
                for(int k=0;k<nTails;k++){
                    if(i==tailY[k]&&j==tailX[k]){
                        print = true;
                        cout << "o";
                    }
                }
                if(!print)
                    cout << " ";
                
            }
        }
        cout << endl;
    }
    for(int i=0;i<width;i++)
        cout << "#" ;
    cout << endl;
    cout << "Score: " << score << endl ;
    cout << "fruitX:" << fruitX << " " <<"fruitY:" << fruitY << endl;
    return;
}

void Input(){
    if(_kbhit()){
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'q':
            gameOver = true;
            break;
        }
    }
    return;
}

void Logic(){
    int prevX = tailX[0],prevY = tailY[0];
    int prevX2,prevY2;
    tailX[0] = x,tailY[0] = y;
    for(int i=1;i<nTails;i++){
        prevX2 = prevX,prevY2 = prevY;
        prevX = tailX[i],prevY = tailY[i];
        tailX[i] = prevX2;
        tailY[i] = prevY2;
    }
    switch (dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    }
    if(x<0||x>=width||y<0||y>=height)
        gameOver = true;
    for(int i=0;i<nTails;i++){
        if(tailX[i]==x&&tailY[i]==y)
            gameOver = true;
    }
    
    if(x==fruitX&&y==fruitY){
        srand(time(nullptr));
        fruitX = rand() % (width-5)+1,fruitY = rand() % (height-5)+1;
        score += 10;
        nTails++;

    }
    return;
}


int main(){
    Setup();
    while(!gameOver){
        Draw();  
        Input();
        Logic();
        Sleep(100);
    }
    system("pause");
    return 0;
}
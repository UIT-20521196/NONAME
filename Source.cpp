#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include <io.h>
#include <direct.h>
using namespace std;
const int heigh = 30, width = 30;
int x, y, fruitx, fruity, score;
map<int,string>name;

set<int,greater<int>>scorebroad;
bool choosing,in_instruction,showscore,nhap;
enum direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    CHOOSE

};
direction dir;
direction di;
string ten;
map<string, int> ce;
map<int, string> ec;

vector<char> game{'g', 'a', 'm', 'e', 'o', 'v', 'e', 'r'};
vector<char> play{'p', 'l', 'a', 'y'};
vector<char> quit{'q', 'u', 'i', 't'};
vector<char>instr{'i','n','s','t','r','u','c','t','i','o','n',' '};
string hs="hight score";
bool gameover, start,st,change,on=true;
int snakex[361];
int snakey[361];
int snake ,temp;
void SetColor(int ForgC);
void gotoxy(int column, int line);
void input()
{
    if (_kbhit())
    {    change=true;
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'c':
            dir = CHOOSE;
            break;

        case 's':
            dir = DOWN;
            break;
        case 'w':
            dir = UP;
            break;
        }
    }
}
void logic1()
{
    switch (dir)
    {
    case UP:
        if(change&&temp!=1)
        {
            temp-=1;
            change=false;
        }
        ce[ec[temp]]=1;
        ce[ec[temp+1]]=0;
        break;

    case DOWN:
        if(change&&temp!=4)
        {
            temp+=1;
            change=false;
        }
        ce[ec[temp]]=1;
        ce[ec[temp-1]]=0;

        break;

    case CHOOSE:
        choosing = true;
        st=true;
        break;
    default:
        break;
    }
}
void logic()
{
    if(!st){
    int prevx = snakex[0] = x;
    int prevy = snakey[0] = y;
    int prev2x;
    int prev2y;
    for (int i = 1; i < snake; i++)
    {
        prev2x = snakex[i];
        prev2y = snakey[i];
        snakex[i] = prevx;
        snakey[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    }
    switch (dir)
    {
    case STOP:
        st = true;
        break;
    case UP:
        x--;st=false;
        break;

    case DOWN:
        x++;st=false;
        break;

    case RIGHT:
        y++;st=false;
        break;
    case LEFT:
        y--;st=false;
        break;


    default:
        break;
    }
    if (!st)
    {
        if (x <= 0 || x > width - 2 || y <= 0 || y > heigh - 2)
            {gameover = true;
              name[score]=ten;
                scorebroad.insert(score);

            }
        for (int i = 1; i < snake; i++)
        {
            if (snakex[i] == x && snakey[i] == y)
                {gameover = true;

                scorebroad.insert(temp);



                }
        }

        if (x == fruitx && y == fruity)
        {
            score += 10;
            fruitx = (rand() % (heigh - 3)) + 1;
            fruity = (rand() & (width - 3)) + 1;
            snake++;
        }
    }
}
void setup()
{  st=false;
    start = false;
    temp=1;
    snake=3;
    change=false;
    di=STOP;
    ce["play"] = 1;
    ce["quit"] = 0;
    ce["instruction"]=0;
    ce["hight score"]=0;
    ec[1]="play";
    ec[2]="quit";
    ec[4]="instruction";
    ec[3]="hight score";
    SetColor(25);
    gameover = false;
    in_instruction=false;
    choosing = false;

    dir = STOP;
    x = width /2;
    y = heigh /2;
    snakex[0] = x;
    snakey[0] = y;
    for (int i = 1; i < snake; i++)
    {
        snakex[i] = x - i;
        snakey[i] = y;
    }

    fruitx = rand() % (width - 1);
    fruity = rand() % (heigh - 1);
    score = 0;
}
void draw()
{
    system("cls");

    for (int i = 0; i < width; i++)
    {
        gotoxy(i + 15, 0 + 5);
        cout << "+";
    }

    if (gameover)
    {
        int index = 0;
        for (int i = 1; i < heigh - 1; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0 || j == width - 1)
                {
                    gotoxy(j + 15, i + 5);
                    cout << "+";
                }

                if (j >= (width / 2 - 4) && (j < width / 2 + 4) && i == heigh / 2)
                {
                    gotoxy(j + 15, i + 5);
                    cout << game[index];
                    index++;
                }
            }
        }
    }
    else
    {
        SetColor(10);
        for (int k = 1; k < snake; k++)
        {

            gotoxy(snakey[k] + 15, snakex[k] + 5);
            cout << "0";
        }
        SetColor(25);
        for (int i = 1; i < heigh - 1; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0 || j == width - 1)
                {
                    gotoxy(j + 15, i + 5);
                    cout << "+";
                }
                if (i == fruitx && j == fruity)
                {
                    gotoxy(j + 15, i + 5);
                    cout << "F";
                }
                else if (i == x && j == y)
                {
                    gotoxy(j + 15, i + 5);
                    SetColor(10);
                    cout << "$";
                    SetColor(25);
                }
            }
        }
    }

    for (int i = 0; i < width; i++)
    {
        gotoxy(i + 15, heigh - 1 + 5);
        cout << "+";
    }
    gotoxy(0 + 15, heigh + 5);
    cout << "SCORE:" << score << endl;
    Sleep(100);
}
void start_game()
{
    SetColor(25);
    while (!choosing)
    {

        system("cls");
        gotoxy(18, 8);
        cout << "press key c to choose";

        gotoxy(18, 9);
        cout << "press w to up";

        gotoxy(18, 10);
        cout << "press s to down";
           gotoxy(18,13);
           cout<<"SCORE:"<<score;
        for (int i = 0; i < width; i++)
        {
            gotoxy(i + 15, 0 + 5);
            cout << "+";
        }
        int index = 0, index1 = 0,index2=0,index3=0;
        for (int i = 1; i < heigh - 1; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0 || j == width - 1)
                {
                    gotoxy(j + 15, i + 5);
                    cout << "+";
                }
                if (j >= (width / 2 - 2) && (j < width / 2 + 2) && i == heigh / 2)
                {
                    if (ce["play"])
                    {
                        SetColor(11);
                        gotoxy(j + 15, i + 5);
                        cout << play[index];
                        index++;
                        SetColor(25);
                    }
                    else
                    {
                        gotoxy(j + 15, i + 5);
                        cout << play[index];
                        index++;
                    }
                }
                if (j >= (width / 2 - 2) && (j < width / 2 + 2) && i == (heigh / 2) + 1 )
                {
                    if (ce["quit"])
                    {
                        SetColor(11);
                        gotoxy(j + 15, i + 5);
                        cout << quit[index1];
                        index1++;
                        SetColor(25);
                    }
                    else
                    {
                        gotoxy(j + 15, i + 5);
                        cout << quit[index1];
                        index1++;
                    }
                }
                 if (j >= (width / 2 - 6) && (j < width / 2 + 6) && i == (heigh / 2) + 2 )
                {
                    if (ce["hight score"])
                    {
                        SetColor(11);
                        gotoxy(j + 15, i + 5);
                        cout << hs[index2];
                        index2++;
                        SetColor(25);
                    }
                    else
                    {
                        gotoxy(j + 15, i + 5);
                        cout << hs[index2];
                        index2++;
                    }
                }
                 if (j >= (width / 2 - 6) && (j < width / 2 + 6) && i == (heigh / 2) + 3 )
                {
                    if (ce["instruction"])
                    {
                        SetColor(11);
                        gotoxy(j + 15, i + 5);
                        cout << instr[index3];
                        index3++;
                        SetColor(25);
                    }
                    else
                    {
                        gotoxy(j + 15, i + 5);
                        cout << instr[index3];
                        index3++;
                    }
                }
            }
        }
        for (int i = 0; i < width; i++)
        {
            gotoxy(i + 15, heigh - 1 + 5);
            cout << "+";
        }

        input();
        logic1();
        Sleep(300);
    }
}
void instruction()
{   in_instruction=true;
    while(in_instruction)
    {   system("cls");
        SetColor(11);
       gotoxy(18,8);
       cout<<"w:up";
       gotoxy(18,9);
       cout<<"s:down";
       gotoxy(18,10);
       cout<<"a:left";
       gotoxy(18,11);
       cout<<"d:right";
       gotoxy(18,12);
       cout<<"space: pause";
       gotoxy(18,13);
       cout<<"fress b to back";

        for (int i = 0; i < width; i++)
        {
            gotoxy(i + 15, 0 + 5);
            cout << "+";
        }
         for (int i = 1; i < heigh - 1; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0 || j == width - 1)
                {
                    gotoxy(j + 15, i + 5);
                    cout << "+";
                }
            }
        }
        for (int i = 0; i < width; i++)
        {
            gotoxy(i + 15, heigh - 1 + 5);
            cout << "+";
        }
        Sleep(300);
        if (_kbhit())
    {    change=true;
        switch (_getch())
        {
        case 'b':
            in_instruction=false;
            choosing=false;
            break;
        }
    }


}
}
void nhapten(){
 ten=" ";
 int longg =0;
nhap=true;
    while(nhap)
    {   system("cls");
       gotoxy(18,6);
            cout<<"fress . to save";
            gotoxy(18,9);
       cout<<"moi ban nhap ten:";
       cout<<ten;


        for (int i = 0; i < width; i++)
        {
            gotoxy(i + 15, 0 + 5);
            cout << "+";
        }
         for (int i = 1; i < heigh - 1; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0 || j == width - 1)
                {
                    gotoxy(j + 15, i + 5);
                    cout << "+";
                }
            }
        }
        for (int i = 0; i < width; i++)
        {
            gotoxy(i + 15, heigh - 1 + 5);
            cout << "+";
        }
        Sleep(300);
        if (_kbhit())
    {    change=true;
     ten+=_getch();
     longg++;
        switch ( ten[longg])
        {
        case '.':
            nhap=false;
            choosing=false;
            break;
        }


    }


}
}

void show_hightscore()
{
    showscore=true;
    while(showscore)
    {   system("cls");
    SetColor(11);
    int index=1;
    gotoxy(18,8);
    cout<<"press  b to back menu";
    for(auto x:scorebroad)
    {   if(index==6)
          break;
        gotoxy(18,10+index);
        cout<<name[x]<<"     "<<x;
        index++;
    }
           SetColor(25);
        for (int i = 0; i < width; i++)
        {
            gotoxy(i + 15, 0 + 5);
            cout << "+";
        }
         for (int i = 1; i < heigh - 1; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0 || j == width - 1)
                {
                    gotoxy(j + 15, i + 5);
                    cout << "+";
                }
            }
        }
        for (int i = 0; i < width; i++)
        {
            gotoxy(i + 15, heigh - 1 + 5);
            cout << "+";
        }
        Sleep(300);
        if (_kbhit())
    {

        switch (_getch())
        {
        case 'b':
            showscore=false;
            choosing=false;
            break;
        }
    }


}

}
void play1()
{

     nhapten();

          draw();
                while (!gameover )
    {

        input();
        logic();
        draw();
}
show_hightscore();



}
int main()
{

   while(on)
{    setup();
      start_game();
      if(ce["quit"])
      {
          on=false;
      }
        if(ce["play"])
            {

       play1();
    }
     if(ce["instruction"])
    {
        instruction();
    }
    if(ce["hight score"])
    {
        show_hightscore();
    }
}

}
void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord);
}

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include<cmath>
#include<cstdlib>
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib, "Winmm.lib")


#include"mmsystem.h"
char waitGetch(size_t ms);
#define PI 3.14159
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
    HDC dstDC = GetImageHDC(dstimg);
    HDC srcDC = GetImageHDC(srcimg);
    int w = srcimg->getwidth();
    int h = srcimg->getheight();

    // 使用 Windows GDI 函数实现透明位图
    TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}
using namespace std;

const int amount_of_food = 500;
const int timelimit = 30000;
int xiaojay = 50;

struct Form_Dog
{
    float x;
    float y;
    int radius = 8; //半徑
};
Form_Dog left_dog, right_dog;

float speed = 0.8;

struct Form_Food
{
    int x = 0;
    float y = 0;
    int radius = 15;
    float value = 1.35769809;
    bool visiable = true;

    void drop(int t)
    {
        if (value != -1)
            y += (float)t / 5 * speed;
        else
            y += (float)t / 4 * speed;
    };

    IMAGE pic;
};
Form_Food food[amount_of_food];

float score = 0;
float per = 0;
bool run = true;

struct Randomizer
{
    void chihuahuaFood(int, Form_Food*);
    int cur =clock() ;
    int rand(int);
};

void Randomizer::chihuahuaFood(int level, Form_Food* ptr)
{
    int r = 0;
    for (int i = 0; i < amount_of_food ; i++)
    {
        r = rand(i+1);
        ptr[i].x = 380 + r;
        ptr[i].y = 50 * (i - amount_of_food);
        if (i %xiaojay == 0)
        {
            food[i].value = -1; //小傑
            food[i].radius = 35;
        }
        else if (i % 10 == 0)
        {
            food[i].value = -10; //巧克力
        }
        /*else if (i % 5 == 0)
        {
            food[i].value = 2;  //布丁
        }*/

    }
};

int Randomizer::rand(int leel)
{
    cur = (101 * cur + 10001 ) % 32767;
    return cur % 200 ;
};


//for every rotation

int count_distance(int k, Form_Dog item)
{
    return pow(item.y - food[k].y, 2) + pow(item.x - food[k].x, 2);
}

bool collision(int k, Form_Dog item)
{
    if (count_distance(k, item) <= pow((item.radius + food[k].radius), 2))
    {
        food[k].x = food[k].y = 10000;
        return 1;
    }
    return 0;
}

void gainpoint(int i)
{
    bool leftc = collision(i, left_dog);
    bool rightc = collision(i, right_dog);
   /* if ((food[i].value == -1) && (leftc || rightc))
    {
        //run = false;
    }*/
    //else 
    if (food[i].visiable)
    {
        score += leftc * food[i].value;
        score += rightc * food[i].value;
        if (score < 0)
            score = 0;
    }
}

int main()
{
    clock_t aclock, bclock, cclock;
    int cx = 480, cy = 420, r = 80, temp = 0;
    TCHAR s[100] = { 0 };
    TCHAR s1[100] = { 0 };
    TCHAR s2[100] = { 0 };
    COLORREF coo;
    char c;
    IMAGE img1, img2, rrro, start, chh, pii, wawa1, wawa2, bk[4] = { 0 }, comp[4] = { 0 }, levelP[4] = { 0 }, fail[8] = { 0 }, comp3[8] = { 0 };
    initgraph(960, 540);
      
    setfillcolor(GREEN);
    cleardevice();
    fillrectangle(300, 540, 660, 0);
    loadimage(&img1, _T("C:\\Users\\jojo\\Downloads\\135855556_260193168775955_7235500536502646435_n (1).jpg"), 24, 24);
    loadimage(&bk[1], _T("C:\\Users\\jojo\\Downloads\\135575011_948283739040898_1684736028132865031_n.jpg"), 360, 540);
    loadimage(&bk[2], _T("C:\\Users\\jojo\\Downloads\\137300732_1956676131157564_8142269444296796218_n.jpg"), 360, 540);
    loadimage(&bk[3], _T("C:\\Users\\jojo\\Downloads\\136984160_3407055996083226_2213100634149689654_n.jpg"), 360, 540);
    loadimage(&rrro, _T("C:\\Users\\jojo\\Downloads\\137233245_252668669579158_2365437835483472275_n.png"), 70, 70);
    loadimage(&chh, _T("C:\\Users\\jojo\\Downloads\\128344986_905032620034241_8617594174002966522_n.jpg"), 20, 20);
    loadimage(&wawa1, _T("C:\\Users\\jojo\\Downloads\\138156865_886324935462406_3030486264489818977_n.png"), 30, 30);
    loadimage(&wawa2, _T("C:\\Users\\jojo\\Downloads\\137235249_313442973389995_846110596046820384_n.png"), 30, 30);
    loadimage(&start, _T("C:\\Users\\jojo\\Downloads\\136173468_2834837410095306_2024302247440590521_n.jpg"), 960, 540);
    loadimage(&comp[1], _T("C:\\Users\\jojo\\Downloads\\L1complish.jpg"), 960, 540);
    loadimage(&comp[2], _T("C:\\Users\\jojo\\Downloads\\L2complish.jpg"), 960, 540);
    loadimage(&comp3[7], _T("C:\\Users\\jojo\\Downloads\\L3complish.jpg"), 960, 540);
    loadimage(&levelP[1], _T("C:\\Users\\jojo\\Downloads\\level1.jpg"), 960, 540);
    loadimage(&levelP[2], _T("C:\\Users\\jojo\\Downloads\\level2.jpg"), 960, 540);
    loadimage(&levelP[3], _T("C:\\Users\\jojo\\Downloads\\level3.jpg"), 960, 540);
    loadimage(&fail[7], _T("C:\\Users\\jojo\\Downloads\\fail.jpg"), 960, 540);
    loadimage(&fail[1], _T("C:\\Users\\jojo\\Downloads\\fail_1.jpg"), 960, 540);
    loadimage(&fail[2], _T("C:\\Users\\jojo\\Downloads\\fail_2jpg"), 960, 540);
    loadimage(&fail[3], _T("C:\\Users\\jojo\\Downloads\\fail_3.jpg"), 960, 540);
    loadimage(&fail[4], _T("C:\\Users\\jojo\\Downloads\\fail_4.jpg"), 960, 540);
    loadimage(&fail[5], _T("C:\\Users\\jojo\\Downloads\\fail_5.jpg"), 960, 540);
    loadimage(&fail[6], _T("C:\\Users\\jojo\\Downloads\\fail_6.jpg"), 960, 540);
    loadimage(&comp3[1], _T("C:\\Users\\jojo\\Downloads\\w_1.jpg"), 960, 540);
    loadimage(&comp3[2], _T("C:\\Users\\jojo\\Downloads\\w_2jpg"), 960, 540);
    loadimage(&comp3[3], _T("C:\\Users\\jojo\\Downloads\\w_3.jpg"), 960, 540);
    loadimage(&comp3[4], _T("C:\\Users\\jojo\\Downloads\\w_4.jpg"), 960, 540);
    loadimage(&comp3[5], _T("C:\\Users\\jojo\\Downloads\\w_5.jpg"), 960, 540);
    loadimage(&comp3[6], _T("C:\\Users\\jojo\\Downloads\\w_6.jpg"), 960, 540);
    

    
    Randomizer foodSituation;
    //Form_food food[60];
    float droppedFood = 1;

   

    TCHAR h[] = _T("- TAP TO START -");
    char u = 0;
    int a = 0;
    for (int j = 0; j >= -1; j++)
    {
        putimage(0, 0, &start);
        setbkmode(TRANSPARENT);
        settextcolor(WHITE);
        if ((j % 2) != 1)
        {
            settextstyle(20,10, _T("American Typewriter"));
            outtextxy(402, 453, h);//xy再
        }
        u = waitGetch(500);
        if (u != 0)
        {
            putimage(0, 0, &levelP[1]);
            break;
        }
    }
    Sleep(1500);
    

   
   

     for (int level = 1; level <= 3; level++)
     {  
         TCHAR h1[] = _T("- NEXT LEVEL -");
         per = 0;
         score = 0;
         droppedFood = 1;
         if (level == 2 && run)
         {
             speed = 1.5;
             xiaojay = 40;
             char u1 = 0;
             setbkmode(TRANSPARENT);
             settextcolor(WHITE);
             settextstyle(20, 10, _T("American Typewriter"));
             
             putimage(0, 0, &comp[1]);
             outtextxy(417, 453, h1);//xy再
             Sleep(3000);
             putimage(0,0,&levelP[2]);
             Sleep(1500);
             putimage(300, 0, &bk[2]);
         }
         else if (level == 3 && run)
         {
             speed = 2;
             xiaojay = 1;
             putimage(0, 0, &comp[2]);
             outtextxy(417, 453, h1);//xy再
             Sleep(3000);
             putimage(0, 0, &levelP[3]);
             Sleep(1500);
             putimage(300, 0, &bk[3]);
         }
         foodSituation.chihuahuaFood(level, food);
         aclock = clock();
         cclock = aclock;
         for (int i = 0; i < amount_of_food; i++)
         {
             food[i].visiable = true;
         }
         foodSituation.chihuahuaFood(level, food);
             per = 0;
             score = 0;
              BeginBatchDraw();
             while (run)
             {  
                 const float f = 30;
                 bclock = clock();
                 setfillcolor(BLACK);
                 cleardevice();
                 putimage(300, 0, &bk[level]);
                 setbkmode(TRANSPARENT);
                 settextstyle(22,11, _T("American Typewriter"));
                 per =( score -529.8)/ droppedFood;
                 if (score == 0)
                 {
                     _stprintf_s(s, _T("RATE : %d "), 0);
                     outtextxy(680, 20, s);
                 }
                 else {
                     _stprintf_s(s, _T("SCORE : %.2f "), score);
                     outtextxy(680, 20, s);
                 }
                 _stprintf_s(s1, _T("LEVEL : %d"), level);
                 outtextxy(680, 50, s1);
                 _stprintf_s(s2, _T("TIME : %.2f"),f-(float(bclock -aclock)/1000));
                 outtextxy(20, 20, s2);
                
                 
               

                 
                 if (bclock - aclock >= timelimit)
                 {
                    if (score < 40)  //記得加上晉級條件
                     {
                         //被當
                        run = false;
                     
                     }
                    break;
                 }
                 for (int i = 0; i < amount_of_food; i++)
                 {
                     food[i].drop(bclock - cclock);
                     gainpoint(i);
                     if (!run)
                     {
                         break;
                     }
                     if (food[i].visiable)
                     {
                         if(food[i].value == -1)
                             transparentimage(NULL, food[i].x-35, food[i].y-35, &rrro, WHITE);
                         else if(food[i].value == -10)
                             transparentimage(NULL, food[i].x - 10, food[i].y - 10, &chh, WHITE);
                         else
                             transparentimage(NULL, food[i].x-12, food[i].y-12, &img1, WHITE);
                     }
                     if (food[i].y > 500)
                         droppedFood ++;//max(i ,droppedFood);
                 }
                 cclock = bclock;

                 c = waitGetch(1);
                 if (c == 75)
                     temp--;
                 if (c == 77)
                     temp++;

                 transparentimage(NULL, cx + r * cos(temp * PI / 25)-15, cy + r * sin(temp * PI / 25)-15, &wawa1, WHITE);
                 transparentimage(NULL, cx + r * cos(PI + temp * PI / 25)-15, cy + r * sin(PI + temp * PI / 25)-15, &wawa2, WHITE);
                 left_dog.x = cx + r * cos(temp * PI / 25);
                 right_dog.x = cx + r * cos(PI + temp * PI / 25);
                 left_dog.y = cy + r * sin(temp * PI / 25);
                 right_dog.y = cy + r * sin(PI + temp * PI / 25);
                 FlushBatchDraw();

                 //Sleep(20);

             }
             EndBatchDraw();
}

    if (run == true)
    {
        for (int g = 1; g <= 6; g++)
        {
            putimage(0, 0, &comp3[g]);
            Sleep(500);
        }
        putimage(0, 0, &comp[7]);
        Sleep(50000);
    }

     if (run == false)
     {
         for (int g = 1; g <= 6; g++)
         {
             putimage(0, 0, &fail[g]);
             Sleep(500);
         }
         putimage(0, 0, &fail[7]);
         Sleep(50000);
     }
       
        _getch();
        closegraph();

    
    return 0;
}



char waitGetch(size_t ms)

{

    int k = 0, t = -clock();

    do

    {

        if (_kbhit()) {

            k = _getch();  break;

        }

    } while (clock() + t < ms);

    return k;

}
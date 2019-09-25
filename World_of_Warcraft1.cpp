//
//  first.cpp
//  World_of_Warcraft
//
//  Created by xiaomeizhuang on 19/9/4.
//  Copyright © 2019年 xiaomeizhuang. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
const int  WARRIOR_NUM = 5;
/*
 string Warrior::names[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };
 红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。
 蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。
 */

class Headquarter;
class Warrior
{
private:
    Headquarter * pHeadquarter;
    int kindNo;
    int no;
public:
    static string names[WARRIOR_NUM];
    static int initialLifeValue [WARRIOR_NUM];
    Warrior( Headquarter * p,int no_,int kindNo_ );
    void PrintResult(int nTime);
};

class Headquarter
{
private:
    int totalLifeValue;
    bool stopped;
    int totalWarriorNum;
    int color;
    int curMakingSeqIdx;
    int warriorNum[WARRIOR_NUM];
    Warrior * pWarriors[1000];
public:
    friend class Warrior;
    static int makingSeq[2][WARRIOR_NUM];
    void Init(int color_, int lv);
    ~Headquarter () ;
    int Produce(int nTime);
    string GetColor();
};


Warrior::Warrior( Headquarter * p,int no_,int kindNo_ ) {
    no = no_;
    kindNo = kindNo_;
    pHeadquarter = p;
}

void Warrior::PrintResult(int nTime)
{
    string color =  pHeadquarter->GetColor();
    printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n"	,
           nTime, color.c_str(), names[kindNo].c_str(), no, initialLifeValue[kindNo],
           pHeadquarter->warriorNum[kindNo],names[kindNo].c_str(),color.c_str());
}

void Headquarter::Init(int color_, int lv)
{
    color = color_;
    totalLifeValue = lv;
    totalWarriorNum = 0;
    stopped = false;
    curMakingSeqIdx = 0;
    for( int i = 0;i < WARRIOR_NUM;i++ )
        warriorNum[i] = 0;
}

Headquarter::~Headquarter () {
    for( int i = 0;i < totalWarriorNum;i++ )
        delete pWarriors[i];
}

int Headquarter::Produce(int nTime)
{
    
    if( stopped )
        return 0;
    int searchingTimes = 0;
    while( Warrior::initialLifeValue[makingSeq[color][curMakingSeqIdx]] > totalLifeValue &&
          searchingTimes < WARRIOR_NUM  ) {
        curMakingSeqIdx = ( curMakingSeqIdx + 1 ) % WARRIOR_NUM;
        searchingTimes++;
    }
    int kindNo = makingSeq[color][curMakingSeqIdx];
    if( Warrior::initialLifeValue[kindNo] > totalLifeValue ) {
        stopped = true;
        if( color == 0 )
            printf("%03d red headquarter stops making warriors\n",nTime);
        else
            printf("%03d blue headquarter stops making warriors\n",nTime);
        return 0;
    }
    //制作士兵：
    totalLifeValue -= Warrior::initialLifeValue[kindNo];
    curMakingSeqIdx = ( curMakingSeqIdx + 1 ) % WARRIOR_NUM;
    pWarriors[totalWarriorNum] = new Warrior( this,totalWarriorNum+1,kindNo);
    warriorNum[kindNo]++;
    pWarriors[totalWarriorNum]->PrintResult(nTime);
    totalWarriorNum++;
    return 1;
}

string Headquarter::GetColor()
{
    if( color == 0)
        return "red";
    else
        return "blue";
}

string Warrior::names[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };
int Warrior::initialLifeValue [WARRIOR_NUM];
int Headquarter::makingSeq[2][WARRIOR_NUM] = { { 2,3,4,1,0 },{3,0,1,2,4} };

int main()
{
    int t; //测试数据组数
    int m; //司令部的生命元
    Headquarter RedHead,BlueHead;
    scanf("%d",&t);
    int nCaseNo = 1; //组数从1开始，到t为止
    while ( t-- ) {
        printf("Case:%d\n",nCaseNo++);
        scanf("%d",&m);
        for( int i = 0;i < WARRIOR_NUM;i++ )
            scanf("%d", & Warrior::initialLifeValue[i]); //输入生命值
        RedHead.Init(0,m); //0代表红司令部，m生命元，初始化红司令部
        BlueHead.Init(1,m);//1代表蓝司令部，m生命元，初始化蓝司令部
        int nTime = 0;
        while(true) {
            int tmp1 = RedHead.Produce(nTime);
            int tmp2 = BlueHead.Produce(nTime);
            if( tmp1 == 0 && tmp2 == 0 )
                break;
            nTime++;
        }
    }
    return 0;
}

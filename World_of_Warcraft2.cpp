//
//  main.cpp
//  World_of_Warcraft2
//
//  Created by xiaomeizhuang on 19/9/4.
//  Copyright © 2019年 xiaomeizhuang. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <string>

const int WARRIOR_NUM = 5;
const int WEAPON_NUM = 3;

class Headquarter;
class Warrior
{
private:
    Headquarter *pHeadquarter;//为了使用Headquarter中成员
    int no;
    int kindNo;//用这个数字代号来代表武士种类
public:
    static std::string names[WARRIOR_NUM];
    static int initialLifeValue[WARRIOR_NUM];
    static std::string weapon[WEAPON_NUM];
    Warrior(Headquarter *p, int no_, int kindNo_):pHeadquarter(p), no(no_), kindNo(kindNo_){}
    void PrintResult(int nTime);
    virtual void PrintMore() = 0;//各自不同的打印
    virtual ~Warrior(){}
    int getNo() {return no;}
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
    Warrior *pWarriors[1000];
public:
    friend class Warrior;
    friend class dragon;
    friend class ninja;
    friend class iceman;
    friend class lion;
    friend class wolf;
    static int makingSeq[2][WARRIOR_NUM];
    void Init(int color_, int lv);
    ~Headquarter();//要自己写析构函数
    int Produce(int nTime);
    std::string GetColor();
};

void Warrior::PrintResult(int nTime)
{
    std::string color=pHeadquarter->GetColor();//实例化
    printf("%03d %s %s %d born with strength %d, %d %s in %s headquarter\n", nTime, color.c_str(), names[kindNo].c_str(), no, initialLifeValue[kindNo], pHeadquarter->warriorNum[kindNo], names[kindNo].c_str(), color.c_str());
    //004 blue lion 5 born with strength 5,2 lion in red headquarter
    
    PrintMore();
}

//dragon类
class dragon:public Warrior{
private:
    int weaponNo;
    float morale;
public:
    virtual void PrintMore()
    {
        printf("It has a %s, and it's morale is %.2f\n", weapon[weaponNo].c_str(), morale);
    }
    dragon(Headquarter *p, int no_, int kindNo_):Warrior(p, no_, kindNo_)
    {
        weaponNo = getNo()%3;
        morale = (float)p->totalLifeValue/(float)initialLifeValue[kindNo_];
    }
    ~dragon(){};
};

//ninja类
class ninja:public Warrior{
private:
    int weaponNo1;
    int weaponNo2;
public:
    virtual void PrintMore()
    {
        printf("It has a %s and a %s\n", weapon[weaponNo1].c_str(), weapon[weaponNo2].c_str());
        //It has a bomb and a arrow
    }
    ninja(Headquarter *p, int no_, int kindNo_):Warrior(p, no_, kindNo_), weaponNo1(no_%3), weaponNo2((no_+1)%3){};
    ~ninja(){};
};

//iceman类
class iceman:public Warrior{
private:
    int weaponNo;
public:
    virtual void PrintMore()
    {
        printf("It has a %s\n", weapon[weaponNo].c_str());
        //It has a sword
    }
    iceman(Headquarter *p, int no_, int kindNo_):Warrior(p, no_, kindNo_), weaponNo(no_%3){};
    ~iceman(){};
};

//lion类
class lion:public Warrior
{
private:
    int loyalty;
public:
    virtual void PrintMore()
    {
        printf("It's loyalty is %d\n", loyalty);
        //It's loyalty is 24
    }
    lion(Headquarter *p, int no_, int kindNo_):Warrior(p, no_, kindNo_),loyalty(p->totalLifeValue){};
    ~lion(){};
};


//wolf类
class wolf:public Warrior{
public:
    virtual void PrintMore(){}
    wolf(Headquarter *p, int no_, int kindNo_):Warrior(p, no_, kindNo_){}
    ~wolf(){};
};


void Headquarter::Init(int color_, int lv)
{
    color=color_;
    totalLifeValue=lv;
    totalWarriorNum=0;
    stopped=false;
    curMakingSeqIdx=0;
    for(int i=0; i< WARRIOR_NUM; ++i)
        warriorNum[i]=0;
}

Headquarter::~Headquarter()
{
    for(int i=0; i<totalWarriorNum; ++i)
        delete pWarriors[i];
}

int Headquarter::Produce(int nTime)
{
    if(stopped) return 0; //直接停止生产
    
    int searchingTimes=0;
    while(Warrior::initialLifeValue[makingSeq[color][curMakingSeqIdx]] > totalLifeValue && searchingTimes < WARRIOR_NUM)
    {
        curMakingSeqIdx=(curMakingSeqIdx + 1 )%WARRIOR_NUM;
        searchingTimes++;
    }
    
    int kindNo=makingSeq[color][curMakingSeqIdx];
    if(Warrior::initialLifeValue[kindNo]>totalLifeValue)
    {
        stopped=true;
        printf("%03d %s headquarter stops making warriors\n", nTime, GetColor().c_str());
        return 0;
    }
    
    totalLifeValue -= Warrior::initialLifeValue[kindNo];
    curMakingSeqIdx = (curMakingSeqIdx + 1)%WARRIOR_NUM;
    switch(kindNo)
    {
        case 0: pWarriors[totalWarriorNum]=new dragon(this, totalWarriorNum+1, kindNo);break;
        case 1: pWarriors[totalWarriorNum]=new ninja(this, totalWarriorNum+1, kindNo);break;
        case 2: pWarriors[totalWarriorNum]=new iceman(this, totalWarriorNum+1, kindNo);break;
        case 3: pWarriors[totalWarriorNum]=new lion(this, totalWarriorNum+1, kindNo);break;
        case 4: pWarriors[totalWarriorNum]=new wolf(this, totalWarriorNum+1, kindNo);break;
        default:;
    }
    warriorNum[kindNo]++;
    pWarriors[totalWarriorNum]->PrintResult(nTime);
    //pWarriors[totalWarriorNum]->PrintMore();
    totalWarriorNum++;
    return 1;
}

std::string Headquarter::GetColor()
{
    if(color==0) return "red";
    return "blue";
}

std::string Warrior::names[WARRIOR_NUM] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int Warrior::initialLifeValue[WARRIOR_NUM];
int Headquarter::makingSeq[2][WARRIOR_NUM]={{2,3,4,1,0},{3,0,1,2,4}};
std::string Warrior::weapon[WEAPON_NUM] = {"sword", "bomb", "arrow"};


int main() {
    int t;
    int m;
    //调用默认构造函数；初始化，再赋值；//
    Headquarter RedHead, BlueHead;
    scanf("%d", &t);
    int nCaseNo = 1;
    while(t--)
    {
        printf("Case:%d\n", nCaseNo++);//先提示Case:1时才会读入司令部生命元和武士生命值
        scanf("%d", &m);
        for( int i = 0; i<WARRIOR_NUM; ++i) scanf("%d", &Warrior::initialLifeValue[i]);
        
        RedHead.Init(0,m);
        BlueHead.Init(1,m);
        int nTime = 0;
        while(true)
        {
            int tmp1 = RedHead.Produce(nTime);
            int tmp2 = BlueHead.Produce(nTime);
            if(tmp1 ==0 && tmp2 == 0)
                break;
            nTime++;
        }
    }
    return 0;
}

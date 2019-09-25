### 简介

魔兽世界这个系列的题一共三道，是coursera上北大的专项课程《程序设计与算法》的第三部分课程《c++程序设计》中第3、5、6周课程的练习题，针对类和对象、继承与派生、多态和虚拟这个几个部分的练习。

![](/Users/xiaomeizhuang/OOP_Practice/png/courseratask.png)

据说这也是北大的C++程序设计实习课的大作业，一般给1~2周让同学完成。这个题是北大信院的带ACM的郭炜老师的书《新标准C++程序设计教程》的最后实践内容：

![](/Users/xiaomeizhuang/OOP_Practice/png/question.png)

这三题真的挺难的，对我来说比leetcode的hard题要难，Open Judge上有88.5%的人打出最高难度五星的评价，上完C++这几部分的课程，以为听懂了就能完成这几道题了，事实证明并不是🙃。做这道题时，我又跑去把《C++ Primer 5th》的第7章类，第15章面向对象程序设计认真温习了，还用思维导图mindnode做了读书笔记，由于身边也没有学C++的人，也没有人讨论，所以花了不少时间😅。这几个题给我最大的感受就是继承和多态，尤其第二题，用继承和多态的方式，代码就会简洁很多；封装这方面，原本我以为这样小项目不用也行，设为public还方便访问，但还是不放心所以看了一下《Effective C++》，Item:22说到最好要把数据成员设为private，因为设为public意味着假如这个类被广泛使用的话那么后期就很难修改了，只有private才能保证封装对类的控制权才可以掌握在自己手里。所以数据成员就都设为private啦，需要哪个数据再单独写个访问的成员函数即可。在每题附上代码之前我都写了自己的分析。



[TOC]



### [魔兽世界一：备战](http://cxsjsxmooc.openjudge.cn/test/B/)

#### 题目

总时间限制: 1000ms    内存限制: 65536kB

##### 描述

魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市。 
红司令部，City 1，City 2，……，City n，蓝司令部

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。 

双方的武士编号都是从1开始计算。红方制造出来的第n个武士，编号就是n。同样，蓝方制造出来的第n个武士，编号也是n。 

武士在刚降生的时候有一个生命值。 

在每个整点，双方的司令部中各有一个武士降生。 

红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。 

蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。 

制造武士需要生命元。 

制造一个初始生命值为m的武士，司令部中的生命元就要减少m个。 

如果司令部中的生命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个。如果所有武士都不能制造了，则司令部停止制造武士。

给定一个时间，和双方司令部的初始生命元数目，要求你将从0点0分开始到双方司令部停止制造武士为止的所有事件按顺序输出。
一共有两种事件，其对应的输出样例如下： 

1) 武士降生 
输出样例： 004 blue lion 5 born with strength 5,2 lion in red headquarter
表示在4点整，编号为5的蓝魔lion武士降生，它降生时生命值为5，降生后蓝魔司令部里共有2个lion武士。（为简单起见，不考虑单词的复数形式）注意，每制造出一个新的武士，都要输出此时司令部里共有多少个该种武士。

2) 司令部停止制造武士
输出样例： 010 red headquarter stops making warriors
表示在10点整，红方司令部停止制造武士

输出事件时： 

首先按时间顺序输出； 

同一时间发生的事件，先输出红司令部的，再输出蓝司令部的。

##### 输入

第一行是一个整数，代表测试数据组数。

每组测试数据共两行。 

第一行：一个整数M。其含义为， 每个司令部一开始都有M个生命元( 1 <= M <= 10000)。

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000。

##### 输出

对每组测试数据，要求输出从0时0分开始，到双方司令部都停止制造武士为止的所有事件。
对每组测试数据，首先输出"Case:n" n是测试数据的编号，从1开始 。
接下来按恰当的顺序和格式输出所有事件。每个事件都以事件发生的时间开头，时间以小时为单位，有三位。

##### 样例输入

```c++
1
20
3 4 5 6 7
```

##### 样例输出

```c++
Case:1
000 red iceman 1 born with strength 5,1 iceman in red headquarter
000 blue lion 1 born with strength 6,1 lion in blue headquarter
001 red lion 2 born with strength 6,1 lion in red headquarter
001 blue dragon 2 born with strength 3,1 dragon in blue headquarter
002 red wolf 3 born with strength 7,1 wolf in red headquarter
002 blue ninja 3 born with strength 4,1 ninja in blue headquarter
003 red headquarter stops making warriors
003 blue iceman 4 born with strength 5,1 iceman in blue headquarter
004 blue headquarter stops making warriors
```



#### 分析🤔

class Headquarter代表司令部类，class Warrior代表武士类。









##### class Headquarter

class Headquarter除了显而易见的int totalLifeValue和int color的成员变量之外，还需要生产武士的成员函数Produce(){ }，这个函数负责生产武士，直到剩余生命元小于任何武士的生命值时停止。

每次生产武士，前提是生命元要足够，即当前生产武士所需的生命值要小于生命元，那么直接进行生产武士；而当司令部的生命元开始拮据，即生产某个武士时出现生命元不足的状况，那么就需要while循环来遍历武士种类，直到查找可以生产的武士时，就退出循环；或者遍历所有的武士种类后但仍未找到，这种情况也会退出循环。因为while循环结束条件有两种，因此还需要判断是哪一种情况，如果退出循环时的武士的生命值还是大于司令部的生命元，那就说明是因为后者而退出循环。为了表示因为后者而退出的循环，用一个标志变量bool stopped来说明，如果因为后者，这个stopped变量值就为true，意味着无论如何都停止了无法再生产武士了。因此每次司令部调用Produce生产武士时得首先判断stopped变量，如果stopped仍然为false，说明还没有确定停止生产，经过这步判断才又可能需要进入前面所说的while循环。

生产武士的时候，每生产一个武士就需要new一个武士对象，调用武士类构造函数。因为这些武士对象都属于这个司令部，所以这两个类是composition关系，因此在Headqaurter中增加一个Warrior类的指针数组，类指针依次指向新new出来的武士对象，方便司令部操作武士对象（还有部分原因是因为后面的扩展题，需要用到基类指针指向派生类这种多态的情况），这个方法上课时老师有明显叮嘱过。

同时，生产武士还有其它结果：该司令部的生命元要相应地减去生命值；统计该种武士的数量，因此用int warriorNum[WARRIOR_NUM]数组来存放每种武士的数量；以及该司令部生产的武士总数量，用int totalWarriorNum统计。

生产武士顺序由curMakingSeqIdx迭代，相当于for循环里的临时变量i，但是这个变量后面还会用到，所以放在类的私有成员里。

武士的制作顺序用一个整数数组表示，数组中存放的数字就代表了武士，这其实是一个全局变量，但是和Headquarter这个类紧密相关，便把它写到类里，不需要每个对象都拥有一份，因此声明为static。

尽可能把Headquarter拥有的成员变量声明为私有，这样封装性更好，如果需要访问某一个变量，那么设置一个public函数，比如int GetColor( )函数来访问司令部的颜色int color。

析构函数~Headquarter( )需要依次销毁动态分配的武士类对象，内置类型不需要在析构函数中提到。

void Init( )用来给Headquarter对象赋值，main函数里创建Headquarter对象是用默认构造函数，不同的case中可以进行重新赋值。



##### class Warrior

class Warrior的成员变量除了表示武士种类的代号int kindNo，还有一个指向司令部的指针Headquarter *pHeadquarter，可以通过这个指针访问司令部的成员，比如通过pHeadquarter调用司令部的Getcolor( )函数和访问int warriorNum[kindNo]等成员变量。既然已经声明为友元，为何不直接访问变量，而需要通过指针❓

剩下的int no是司令部生产武士时的序号，因为后面的题中Warrior的派生类需要用它给成员变量赋值，因此提前考虑在此算作成员变量一员。

虽然武士有很多种，但是这里并没有用到派生类，因为这些武士的特点都相同，对他们的操作也是相同的，也就是成员变量和成员函数都是相同的，因此不需要用派生类，而不同的生命值等这种特点其实是体现在不同的实例化。

##### main函数

按照要求需要输入数据测试组数Case，在屏幕输出Case:1的提示之后，输入司令部的生命元int m，以及各个武士的生命值。

构造两个Headquarter对象，一个实例对象为RedHead，另一个实例对象为BlueHead，在每个case中，用Init()函数对这两个对象重新赋值。



#### 代码😉

```c++
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
		Headquarter * pHeadquarter; //每个武士都有指向司令部的指针
		int kindNo; //相当于武士的代号 0 dragon 1 ninja 2 iceman 3 lion 4 wolf
		int no; //Headquarter生产武士时产生的序号
	public:
		static string names[WARRIOR_NUM]; //存储武士名字
		static int initialLifeValue [WARRIOR_NUM]; //存储武士生命值
		Warrior( Headquarter * p,int no_,int kindNo_ );
		void PrintResult(int nTime);//打印结果的函数
};

class Headquarter
{
	private:
		int totalLifeValue; //司令部总的生命值
		bool stopped;
		int totalWarriorNum;
		int color;
		int curMakingSeqIdx; //当前要制造的武士是制造序列中的第几个
		int warriorNum[WARRIOR_NUM]; //存放每种武士的数量
		Warrior * pWarriors[1000];
	public:
		friend class Warrior; //便于Warrior类操作Headquarter类里的私有成员；
		static int makingSeq[2][WARRIOR_NUM]; //武士的制作顺序序列
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
    printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n", nTime, color.c_str(), names[kindNo].c_str(), no, initialLifeValue[kindNo], pHeadquarter->warriorNum[kindNo], names[kindNo].c_str(), color.c_str());
}//通过类的指针访问成员和声明为友元直接访问有什么区别❓❓

void Headquarter::Init(int color_, int lv)  //产生一个司令部
{
	color = color_;
	totalLifeValue = lv;
	totalWarriorNum = 0;
	stopped = false;
	curMakingSeqIdx = 0; //当前要制造的武士是制造序列中的第几个
	for( int i = 0;i < WARRIOR_NUM;i++ )
		warriorNum[i] = 0;
}

Headquarter::~Headquarter () {
	for( int i = 0;i < totalWarriorNum;i++ )
		delete pWarriors[i];
}

int Headquarter::Produce(int nTime)  //制造武士
{
	if( stopped )
		return 0;
	int searchingTimes = 0;
	while( Warrior::initialLifeValue[makingSeq[color][curMakingSeqIdx]] > totalLifeValue &&searchingTimes < WARRIOR_NUM )
    {
		curMakingSeqIdx = ( curMakingSeqIdx + 1 ) % WARRIOR_NUM; 
		searchingTimes++;
	}
	int kindNo = makingSeq[color][curMakingSeqIdx]; //某个武士的编号，说明他是哪种武士
	if( Warrior::initialLifeValue[kindNo] > totalLifeValue )
    {
		stopped = true;
		if( color == 0 ) //判断该停的是哪个司令部
			printf("%03d red headquarter stops making warriors\n",nTime);
		else
			printf("%03d blue headquarter stops making warriors\n",nTime);
		return 0;
	}
	//制作士兵：
	totalLifeValue -= Warrior::initialLifeValue[kindNo];
	curMakingSeqIdx = ( curMakingSeqIdx + 1 ) % WARRIOR_NUM;
	pWarriors[totalWarriorNum] = new Warrior( this,totalWarriorNum+1,kindNo); //指向武士的指针数组，new出武士对象的空间
	warriorNum[kindNo]++; //统计有几个该种武士
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
int Warrior::initialLifeValue [WARRIOR_NUM]; //这是让我们输入的
int Headquarter::makingSeq[2][WARRIOR_NUM] = { { 2,3,4,1,0 },{3,0,1,2,4} }; //两个司令部武士的制作顺序序列

int main()
{
	int t; //测试数据组数
	int m; //司令部的生命元
	Headquarter RedHead,BlueHead; //红蓝司令部两个Headquarter对象
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

```





### [魔兽世界：装备二](http://cxsjsxmooc.openjudge.cn/test/E/)

#### 题目

总时间限制: 1000ms    内存限制: 65536kB

##### 描述

魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市。 

红司令部，City 1，City 2，……，City n，蓝司令部

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值这两种属性。 
有的武士可以拥有武器。武器有三种，sword, bomb,和arrow，编号分别为0,1,2。
双方的武士编号都是从1开始计算。红方制造出来的第 n 个武士，编号就是n。同样，蓝方制造出来的第 n 个武士，编号也是n。 

不同的武士有不同的特点。
dragon 可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器。dragon还有“士气”这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造dragon所需的生命元数量。
ninja可以拥有两件武器。编号为n的ninja降生时即获得编号为 n%3 和 (n+1)%3的武器。
iceman有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器。
lion 有“忠诚度”这个属性，其值等于它降生后其司令部剩余生命元的数目。
wolf没特点。
请注意，在以后的题目里，武士的士气，生命值，忠诚度在其生存期间都可能发生变化，都有作用，武士手中的武器随着使用攻击力也会发生变化。

武士在刚降生的时候有一个生命值。 

在每个整点，双方的司令部中各有一个武士降生。 

红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序循环制造武士。 

蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序循环制造武士。 

制造武士需要生命元。 

制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。 

如果司令部中的生命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个。如果所有武士都不能制造了，则司令部停止制造武士。
给定一个时间，和双方司令部的初始生命元数目，要求你将从0点0分开始到双方司令部停止制造武士为止的所有事件按顺序输出。
一共有两种事件，其对应的输出样例如下： 

1) 武士降生 
输出样例： 004 blue lion 5 born with strength 5,2 lion in red headquarter
表示在 4点整，编号为5的蓝魔lion武士降生，它降生时生命值为5,降生后蓝魔司令部里共有2个lion武士。(为简单起见，不考虑单词的复数形式)注意，每制造出一个新的武士，都要输出此时司令部里共有多少个该种武士。
如果造出的是dragon，那么还要输出一行，例：
It has a arrow,and it's morale is 23.34
表示该dragon降生时得到了arrow,其士气是23.34（为简单起见，本题中arrow前面的冠词用a,不用an，士气精确到小数点后面2位，四舍五入）
如果造出的是ninja，那么还要输出一行，例：
It has a bomb and a arrow
表示该ninja降生时得到了bomb和arrow。
如果造出的是iceman，那么还要输出一行，例：
It has a sword
表示该iceman降生时得到了sword。
如果造出的是lion，那么还要输出一行，例：
It's loyalty is 24
表示该lion降生时的忠诚度是24。
2) 司令部停止制造武士
输出样例： 010 red headquarter stops making warriors
表示在 10点整，红方司令部停止制造武士

输出事件时： 

首先按时间顺序输出； 

同一时间发生的事件，先输出红司令部的，再输出蓝司令部的。

##### 输入

第一行是一个整数,代表测试数据组数。

每组测试数据共两行。 

第一行，一个整数M。其含义为： 每个司令部一开始都有M个生命元( 1 <= M <= 10000) 

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000

##### 输出

对每组测试数据，要求输出从0时0分开始，到双方司令部都停止制造武士为止的所有事件。
对每组测试数据，首先输出“Case:n" n是测试数据的编号，从1开始 
接下来按恰当的顺序和格式输出所有事件。每个事件都以事件发生的时间开头，时间以小时为单位，有三位。

##### 样例输入

```c++
1
20
3 4 5 6 7
```

##### 样例输出

```c++
Case:1
000 red iceman 1 born with strength 5,1 iceman in red headquarter
It has a bomb
000 blue lion 1 born with strength 6,1 lion in blue headquarter
It's loyalty is 14
001 red lion 2 born with strength 6,1 lion in red headquarter
It's loyalty is 9
001 blue dragon 2 born with strength 3,1 dragon in blue headquarter
It has a arrow,and it's morale is 3.67
002 red wolf 3 born with strength 7,1 wolf in red headquarter
002 blue ninja 3 born with strength 4,1 ninja in blue headquarter
It has a sword and a bomb
003 red headquarter stops making warriors
003 blue iceman 4 born with strength 5,1 iceman in blue headquarter
It has a bomb
004 blue headquarter stops making warriors
```



#### 分析🤔

之前的武士特点相同，司令部对它们的操作也相同，因此不用写派生类，但是这次需要武士有了各自的特点，所以必须写。

##### derived class

有了之前的结构，这一步能非常明显地体现c++面向对象程序设计的可扩展性。

不同的武士有相同的特点和各自仅有的特点，因此把Warrior当作基类，派生出不同的武士类，相同的特点通过继承得到，不同的特点作为每种武士自己拥有的成员。比如对于dragon这个类，dragon类拥有从Warrior继承得到的Headquarter *pHeadquarter、int no和int kindNo等等，但也拥有自己的成员int weaponNo和float morale等等。

##### polymorphism

生产武士的时候，每生产一个武士就需要new一个派生类武士对象， 司令部类中的Warrior *pWarrior[1000]的基类指针分别指向这些产生的派生类武士，因此有些函数需要声明为virtual：

class Warrior的析构函数需要声明为virtual，派生类的析构函数可以省略不写，当Headquarter的析构函数在执行的时候，才能通过基类指针删除派生类对象。

void PrintMore()也要声明为虚函数，负责输出和每种武士特点相关的语句，需要每个武士类都自己定义函数体，通过指向派生类的pWarrior指针调用。

总之，代码并没有做多少改动，只是添加了几个派生类和虚函数。



#### 代码😉👏

```c++
/*
1、释构没大括号
2、PrintMore 换行
3、morale = (float)(p->totalLifeValue/initialLifeValue[kindNo_]); == > morale = (float)p->totalLifeValue/(float)initialLifeValue[kindNo_];
4、PrintMore(); 放在了PrintResult里面输出
5、结束输出修改，合并成了一个
*/

#include <iostream>
#include <cstdio>
#include <string>

const int WARRIOR_NUM = 5;
const int WEAPON_NUM = 3;

class Headquarter;
class Warrior
{
private:
    Headquarter *pHeadquarter;//为了使用Headquater中成员
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
    ~Headquarter();
    int Produce(int nTime);
    std::string GetColor();
};

void Warrior::PrintResult(int nTime)
{
    std::string color=pHeadquarter->GetColor();
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
```



### [魔兽世界：终极版](http://cxsjsxmooc.openjudge.cn/test/R/)

#### 题目🙄🙄

总时间限制: 6000ms    内存限制: 65536kB

##### 描述

魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市，城市从西向东依次编号为1,2,3 .... N ( N <= 20 )。红魔军的司令部算作编号为0的城市，蓝魔军的司令部算作编号为N+1的城市。司令部有生命元，用于制造武士。

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。

双方的武士编号都是从1开始计算。红方制造出来的第 n 个武士，编号就是n。同样，蓝方制造出来的第 n 个武士，编号也是n。

武士在刚降生的时候有一个初始的生命值，生命值在战斗中会发生变化，如果生命值减少到0（生命值变为负数时应当做变为0处理），则武士死亡（消失）。

有的武士可以拥有武器。武器有三种，sword, bomb,和arrow，编号分别为0,1,2。

武士降生后就朝对方司令部走，在经过的城市如果遇到敌人（同一时刻每个城市最多只可能有1个蓝武士和一个红武士），就会发生战斗。每次战斗只有一方发起主动进攻一次。被攻击者生命值会减去进攻者的攻击力值和进攻者手中sword的攻击力值。被进攻者若没死，就会发起反击，被反击者的生命值要减去反击者攻击力值的一半(去尾取整)和反击者手中sword的攻击力值。反击可能致敌人于死地。

如果武士在战斗中杀死敌人（不论是主动进攻杀死还是反击杀死），则其司令部会立即向其发送8个生命元作为奖励，使其生命值增加8。当然前提是司令部得有8个生命元。如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士。

如果某武士在某城市的战斗中杀死了敌人，则该武士的司令部立即取得该城市中所有的生命元。注意，司令部总是先完成全部奖励工作，然后才开始从各个打了胜仗的城市回收生命元。对于因司令部生命元不足而领不到奖励的武士，司令部也不会在取得战利品生命元后为其补发奖励。

如果一次战斗的结果是双方都幸存(平局)，则双方都不能拿走发生战斗的城市的生命元。

城市可以插旗子，一开始所有城市都没有旗子。在插红旗的城市，以及编号为奇数的无旗城市，由红武士主动发起进攻。在插蓝旗的城市，以及编号为偶数的无旗城市，由蓝武士主动发起进攻。

当某个城市有连续两场战斗都是同一方的武士杀死敌人(两场战斗之间如果有若干个战斗时刻并没有发生战斗，则这两场战斗仍然算是连续的；但如果中间有平局的战斗，就不算连续了) ，那么该城市就会插上胜方的旗帜，若原来插着败方的旗帜，则败方旗帜落下。旗帜一旦插上，就一直插着，直到被敌人更换。一个城市最多只能插一面旗帜，旗帜没被敌人更换前，也不会再次插同颜色的旗。

各种武器有其特点：

sword武器的初始攻击力为拥有它的武士的攻击力的20%（去尾取整）。但是sword每经过一次战斗(不论是主动攻击还是反击)，就会变钝，攻击力变为本次战斗前的80% (去尾取整)。sword攻击力变为0时，视为武士失去了sword。如果武士降生时得到了一个初始攻击力为0的sword，则视为武士没有sword.

arrow有一个攻击力值R。如果下一步要走到的城市有敌人，那么拥有arrow的武士就会放箭攻击下一个城市的敌人（不能攻击对方司令部里的敌人）而不被还击。arrow使敌人的生命值减少R，若减至小于等于0，则敌人被杀死。arrow使用3次后即被耗尽，武士失去arrow。两个相邻的武士可能同时放箭把对方射死。

拥有bomb的武士，在战斗开始前如果判断自己将被杀死（不论主动攻击敌人，或者被敌人主动攻击都可能导致自己被杀死，而且假设武士可以知道敌人的攻击力和生命值），那么就会使用bomb和敌人同归于尽。武士不预测对方是否会使用bomb。

武士使用bomb和敌人同归于尽的情况下，不算是一场战斗，双方都不能拿走城市的生命元，也不影响城市的旗帜。

不同的武士有不同的特点。

dragon可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器。dragon还有“士气”这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造dragon所需的生命元数量。dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，而且士气值大于0.8，就会欢呼。dragon每取得一次战斗的胜利(敌人被杀死)，士气就会增加0.2，每经历一次未能获胜的战斗，士气值就会减少0.2。士气增减发生在欢呼之前。

ninja可以拥有两件武器。编号为n的ninja降生时即获得编号为 n%3 和 (n+1)%3的武器。ninja 挨打了也从不反击敌人。

iceman有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器。iceman 每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20。但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了而死。

lion 有“忠诚度”这个属性，其初始值等于它降生之后其司令部剩余生命元的数目。每经过一场未能杀死敌人的战斗，忠诚度就降低K。忠诚度降至0或0以下，则该lion逃离战场,永远消失。但是已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑。lion 若是战死，则其战斗前的生命值就会转移到对手身上。所谓“战斗前”，就是每个小时的40分前的一瞬间。

wolf降生时没有武器，但是在战斗中如果获胜（杀死敌人），就会缴获敌人的武器，但自己已有的武器就不缴获了。被缴获的武器当然不能算新的，已经被用到什么样了，就是什么样的。

以下是不同时间会发生的不同事件：

在每个整点，即每个小时的第0分， 双方的司令部中各有一个武士降生。

红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。

蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。

制造武士需要生命元。

制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。

如果司令部中的生命元不足以制造某武士，那么司令部就等待，直到获得足够生命元后的第一个整点，才制造该武士。例如，在2:00，红方司令部本该制造一个 wolf ，如果此时生命元不足，那么就会等待，直到生命元足够后的下一个整点，才制造一个 wolf。

在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了。

在每个小时的第10分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。或从和敌军司令部相邻的城市到达敌军司令部。

在每个小时的第20分：每个城市产出10个生命元。生命元留在城市，直到被武士取走。

在每个小时的第30分：如果某个城市中只有一个武士，那么该武士取走该城市中的所有生命元，并立即将这些生命元传送到其所属的司令部。

在每个小时的第35分，拥有arrow的武士放箭，对敌人造成伤害。放箭事件应算发生在箭发出的城市。注意，放箭不算是战斗，因此放箭的武士不会得到任何好处。武士在没有敌人的城市被箭射死也不影响其所在城市的旗帜更换情况。

在每个小时的第38分，拥有bomb的武士评估是否应该使用bomb。如果是，就用bomb和敌人同归于尽。

在每个小时的第40分：在有两个武士的城市，会发生战斗。 如果敌人在5分钟前已经被飞来的arrow射死，那么仍然视为发生了一场战斗，而且存活者视为获得了战斗的胜利。此情况下不会有“武士主动攻击”，“武士反击”，“武士战死”的事件发生，但战斗胜利后应该发生的事情都会发生。如Wolf一样能缴获武器，旗帜也可能更换，等等。在此情况下,Dragon同样会通过判断是否应该轮到自己主动攻击来决定是否欢呼。

在每个小时的第50分，司令部报告它拥有的生命元数量。

在每个小时的第55分，每个武士报告其拥有的武器情况。

武士到达对方司令部后就算完成任务了，从此就呆在那里无所事事。

任何一方的司令部里若是出现了2个敌人，则认为该司令部已被敌人占领。

任何一方的司令部被敌人占领，则战争结束。战争结束之后就不会发生任何事情了。

给定一个时间，要求你将从0点0分开始到此时间为止的所有事件按顺序输出。事件及其对应的输出样例如下：



1) 武士降生

输出样例： 000:00 blue lion 1 born表示在 0点0分，编号为1的蓝魔lion武士降生 如果造出的是dragon，那么还要多输出一行，例：000:00 blue dragon 1 born Its morale is 23.34  表示该该dragon降生时士气是23. 34(四舍五入到小数点后两位)如果造出的是lion，那么还要多输出一行，例: 000:00 blue lion 1 born Its loyalty is 24  表示该lion降生时的忠诚度是24

2) lion逃跑

输出样例： 000:05 blue lion 1 ran away  表示在 0点5分，编号为1的蓝魔lion武士逃走

3) 武士前进到某一城市

输出样例： 000:10 red iceman 1 marched to city 1 with 20 elements and force 30 表示在 0点10分，红魔1号武士iceman前进到1号城市，此时他生命值为20,攻击力为30 对于iceman,输出的生命值和攻击力应该是变化后的数值

4)武士放箭

输出样例： 000:35 blue dragon 1 shot 表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭。如果射出的箭杀死了敌人，则应如下输出： 000:35 blue dragon 1 shot and killed red lion 4 表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭，杀死了编号为4的红魔lion。

5)武士使用bomb

输出样例： 000:38 blue dragon 1 used a bomb and killed red lion 7 表示在 0点38分，编号为1的蓝魔dragon武士用炸弹和编号为7的红魔lion同归于尽。

6) 武士主动进攻

输出样例：000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30 表示在0点40分，1号城市中，红魔1号武士iceman 进攻蓝魔1号武士lion,在发起进攻前，红魔1号武士iceman生命值为20，攻击力为 30

7) 武士反击

输出样例：001:40 blue dragon 2 fought back against red lion 2 in city 1  表示在1点40分，1号城市中，蓝魔2号武士dragon反击红魔2号武士lion

8) 武士战死

输出样例：001:40 red lion 2 was killed in city 1 被箭射死的武士就不会有这一条输出。

9) 武士欢呼

输出样例：003:40 blue dragon 2 yelled in city 4

10) 武士获取生命元( elements )

输出样例：001:40 blue dragon 2 earned 10 elements for his headquarter

输出不包括在30分不是通过战斗获取的elements

11) 旗帜升起

输出样例：004:40 blue flag raised in city 4

12) 武士抵达敌军司令部

输出样例：001:10 red iceman 1 reached blue headquarter with 20 elements and force 30 (此时他生命值为20,攻击力为30）对于iceman,输出的生命值和攻击力应该是变化后的数值

13) 司令部被占领

输出样例：003:10 blue headquarter was taken

14)司令部报告生命元数量

000:50 100 elements in red headquarter  000:50 120 elements in blue headquarter 表示在0点50分，红方司令部有100个生命元，蓝方有120个

15)武士报告武器情况

000:55 blue wolf 2 has arrow(2),bomb,sword(23) 000:55 blue wolf 4 has no weapon 000:55 blue wolf 5 has sword(20) 表示在0点55分，蓝魔2号武士wolf有一支arrow（这支arrow还可以用2次），一个bomb，还有一支攻击力为23的sword。 蓝魔4号武士wolf没武器。 蓝魔5号武士wolf有一支攻击力为20的sword。 交代武器情况时，次序依次是：arrow,bomb,sword。如果没有某种武器，某种武器就不用提。报告时，先按从西向东的顺序所有的红武士报告，然后再从西向东所有的蓝武士报告。

输出事件时：

首先按时间顺序输出；

同一时间发生的事件，按发生地点从西向东依次输出. 武士前进的事件, 算是发生在目的地。

在一次战斗中有可能发生上面的 6 至 11 号事件。这些事件都算同时发生，其时间就是战斗开始时间。一次战斗中的这些事件，序号小的应该先输出。

两个武士同时抵达同一城市，则先输出红武士的前进事件，后输出蓝武士的。

显然，13号事件发生之前的一瞬间一定发生了12号事件。输出时，这两件事算同一时间发生，但是应先输出12号事件

虽然任何一方的司令部被占领之后，就不会有任何事情发生了。但和司令部被占领同时发生的事件，全都要输出。

##### 输入

第一行是t,代表测试数据组数
每组样例共三行。
第一行，五个整数 M,N,R,K, T。其含义为：

每个司令部一开始都有M个生命元( 1 <= M <= 10000)
两个司令部之间一共有N个城市( 1 <= N <= 20 )
arrow的攻击力是R
lion每经过一场未能杀死敌人的战斗，忠诚度就降低K。
要求输出从0时0分开始，到时间T为止(包括T) 的所有事件。T以分钟为单位，0 <= T <= 5000

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000

第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于10000

##### 输出

对每组数据，先输出一行：
Case n:
如对第一组数据就输出 Case1:
然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是“时: 分”，“时”有三位，“分”有两位。

##### 样例输入

```c++
1
20 1 10 10 1000
20 20 30 10 20
5 5 5 5 5
```

##### 样例输出

```c++
Case 1:
000:00 blue lion 1 born
Its loyalty is 10
000:10 blue lion 1 marched to city 1 with 10 elements and force 5
000:30 blue lion 1 earned 10 elements for his headquarter
000:50 20 elements in red headquarter
000:50 20 elements in blue headquarter
000:55 blue lion 1 has no weapon
001:00 blue dragon 2 born
Its morale is 0.00
001:10 blue lion 1 reached red headquarter with 10 elements and force 5
001:10 blue dragon 2 marched to city 1 with 20 elements and force 5
001:30 blue dragon 2 earned 10 elements for his headquarter
001:50 20 elements in red headquarter
001:50 10 elements in blue headquarter
001:55 blue lion 1 has no weapon
001:55 blue dragon 2 has arrow(3)
002:10 blue dragon 2 reached red headquarter with 20 elements and force 5
002:10 red headquarter was taken
```



#### 分析😣😫



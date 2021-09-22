#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>


#define WALLS   "*" // 1  墙
#define BEANS   "." // 0  豆子
#define ROAD    " " // 2  吃完豆子的空路
#define BOSS    "O" // 3  怪物
#define MINE    "@" // 4  玩家

#define HIGH    20//行
#define WIDTH   30//列
#define STATE   int

char szMazeMap[HIGH][WIDTH] = { 0 };//迷宫地图
char szBossMap[HIGH][WIDTH] = { 0 };//怪物地图
int nScore = 0;    //总得分
long lLevel = 1000;//难度，每次boss移动的时间间隔
int xPlayer = 1;   //玩家坐标  行
int yPlayer = 1;   //玩家坐标  列

void _init_map()//初始化玩家地图
{
    int i = 0;
    char szMapPlayer[][WIDTH] = {
        "11111111111111111111111111111",
        "14000000000110000000000000001",
        "10101110110000011010100100101",
        "10100000000100000000110101101",
        "10001101101101010110000100101",
        "10100001001001010000101101001",
        "10101100100001010110000000001",
        "10000010100011000001011000101",
        "11010000001000010101010101101",
        "10000101100011010000000000001",
        "10101000001001000110110101101",
        "10101010100101010000010101001",
        "10000000101100011011000001011",
        "10101010001101010000101100001",
        "10000001000101011010101101101",
        "10110101010001000000101000001",
        "10000100010100011010000010001",
        "10010011000000101010101010101",
        "10000000010100000000000000001",
        "11111111111111111111111111111" };
    char szMapBoss[][WIDTH] = {
        "00000000000000000000000000000",
        "00000000000000000000000000030",
        "00000000000000000000000000000",
        "00000000000000000000000000000",
        "00000000000000000000000000000", 
        "00000000000000000000000000000", 
        "00000000000000000000000000000", 
        "00000000000000000000000000000", 
        "00000000000000000000000000000", 
        "00000000000000000000000000000", 
        "00000000000000030000000000000", 
        "00000000000000000000000000000", 
        "00000000000000000000000000000", 
        "00000000000000000000000000000",
        "00000000000000000000000000000",
        "00000000000000000000000000000",
        "00000000000000000000000000000",
        "00000000000000000000000000000",
        "03000000000000000000000000030",
        "00000000000000000000000000000"};

    for (i = 0; i < HIGH; i++)
    {
        strcpy_s(szMazeMap[i], WIDTH * sizeof(char), szMapPlayer[i]);
    }  
    for (i = 0; i < HIGH; i++)
    {
        strcpy_s(szBossMap[i], WIDTH * sizeof(char), szMapBoss[i]);
    }
}
void __copy_map(char szTempMap[][WIDTH])//将Boss地图复制给参数
{
    int i = 0;

    for (i = 0; i < HIGH; i++)
    {
        strcpy_s(szTempMap[i], WIDTH * sizeof(char), szBossMap[i]);
    }
}
void _print_map()//打印地图
{
    int i = 0;
    int j = 0;

    system("cls");
    for (i = 0; i < HIGH; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            if (szMazeMap[i][j] == '0')
            {
                if (szBossMap[i][j] == '3')
                {
                    printf(BOSS);
                }
                else
                {
                    printf(BEANS);
                }                
            }
            if (szMazeMap[i][j] == '1')
            {
                printf(WALLS);
            }
            if (szMazeMap[i][j] == '2')
            {
                if (szBossMap[i][j] == '3')
                {
                    printf(BOSS);
                }
                else
                {
                    printf(ROAD);
                }               
            }
            if (szMazeMap[i][j] == '4')
            {
                printf_s(MINE);
            }
        }
        if (i == 5)
        {
            printf("      提示：您的目标出现在左上角，通过w/a/s/d来控制目标移动");
        }
        if (i == 7)
        {
            printf("      难度设置：2个小Boss，2个大Boss，每10秒唤醒一个");
        }
        if (i == 9)
        {
            printf("      您当前的得分是：%d", nScore);
        }
        if (i == 11)
        {
            printf("      您当前的难度是：%d", 10 - lLevel/100);
        }   
        printf("\r\n");
    }
}

//////////////////////////////////////////////////////////////////////////
/*                        玩家移动控制函数                              */
//////////////////////////////////////////////////////////////////////////

STATE __player_move_up()//玩家向上移动
{
    if (szBossMap[xPlayer - 1][yPlayer] == '3')//先判断是否有Boss
    {
        return 0;
    }
    if (szMazeMap[xPlayer - 1][yPlayer] == '0')
    {
        szMazeMap[xPlayer - 1][yPlayer] = '4';//移动到现在位置
        szMazeMap[xPlayer][yPlayer] = '2';    //之前位置变为空格
        xPlayer = xPlayer - 1;                 //坐标变换
        nScore++;                              //加分
    }
    else if (szMazeMap[xPlayer - 1][yPlayer] == '2')
    {
        szMazeMap[xPlayer - 1][yPlayer] = '4';//移动到现在位置
        szMazeMap[xPlayer][yPlayer] = '2';    //之前位置变为空格
        xPlayer = xPlayer - 1;
    }
    else
    {
        return 1;
    }
    _print_map();
    return 1;
}
STATE __player_move_down()//玩家向下移动
{
    if (szBossMap[xPlayer + 1][yPlayer] == '3')//先判断是否有Boss
    {
        return 0;
    }
    if (szMazeMap[xPlayer + 1][yPlayer] == '0')
    {
        szMazeMap[xPlayer + 1][yPlayer] = '4'; //移动到现在位置
        szMazeMap[xPlayer][yPlayer] = '2';     //之前位置变为空格
        xPlayer = xPlayer + 1;                 //坐标变换
        nScore++;                              //加分
    }
    else if (szMazeMap[xPlayer + 1][yPlayer] == '2')
    {
        szMazeMap[xPlayer + 1][yPlayer] = '4';//移动到现在位置
        szMazeMap[xPlayer][yPlayer] = '2';    //之前位置变为空格
        xPlayer = xPlayer + 1;
    }
    else
    {
        return 1;
    }
    _print_map();
    return 1;
}
STATE __player_move_left()//玩家向左移动
{
    if (szBossMap[xPlayer][yPlayer - 1] == '3')//先判断是否有Boss
    {
        return 0;
    }
    if (szMazeMap[xPlayer][yPlayer - 1] == '0')
    {
        szMazeMap[xPlayer][yPlayer - 1] = '4'; //移动到现在位置
        szMazeMap[xPlayer][yPlayer] = '2';     //之前位置变为空格
        yPlayer = yPlayer - 1;                 //坐标变换
        nScore++;                              //加分
    }
    else if (szMazeMap[xPlayer][yPlayer - 1] == '2')
    {
        szMazeMap[xPlayer][yPlayer - 1] = '4';//移动到现在位置
        szMazeMap[xPlayer][yPlayer] = '2';    //之前位置变为空格
        yPlayer = yPlayer - 1;
    }
    else
    {
        return 1;
    }
    _print_map();
    return 1;
}
STATE __player_move_right()//玩家向右移动
{
    if (szBossMap[xPlayer][yPlayer + 1] == '3')//先判断是否有Boss
    {
        return 0;
    }
    if (szMazeMap[xPlayer][yPlayer + 1] == '0')
    {
        szMazeMap[xPlayer][yPlayer + 1] = '4'; //移动到现在位置
        szMazeMap[xPlayer][yPlayer] = '2';     //之前位置变为空格
        yPlayer = yPlayer + 1;                 //坐标变换
        nScore++;                              //加分
    }
    else if (szMazeMap[xPlayer][yPlayer + 1] == '2')
    {
        szMazeMap[xPlayer][yPlayer + 1] = '4';//移动到现在位置
        szMazeMap[xPlayer][yPlayer] = '2';    //之前位置变为空格
        yPlayer = yPlayer + 1;
    }
    else
    {
        return 1;
    }
    _print_map();
    return 1;
}

STATE _move_player()//玩家移动控制
{
    char cMove = 0;

    if (_kbhit() == 0)
    {
        return 2;//2表示没有移动
    }
    cMove = _getch();
    rewind(stdin);

    switch (cMove)
    {
        case 'w':
            if (__player_move_up() == 0)  //0结束游戏
            {
                return 0;
            }
            break;
        case 's':
            if (__player_move_down() == 0)//0结束游戏
            {
                return 0;
            }
            break;
        case 'a':
            if (__player_move_left() == 0)//0结束游戏
            {
                return 0;
            }
            break;
        case 'd':
            if (__player_move_right() == 0)//0结束游戏
            {
                return 0;
            }
            break;
        default:break;
    }
    return 1;//1表示正常移动
}

///////////////////////////////////////////////////////////////////////////////////////
/*                            Boss上下左右移动控制函数                               */
///////////////////////////////////////////////////////////////////////////////////////

STATE __boss_move_up(int *x, int *y)    //Boss向上移动，传参数是为了确定是哪一个怪物调用这个函数
{
    if (szMazeMap[*x - 1][*y] == '4')   //先判断是否吃掉玩家
    {
        return 0;
    }
    if (szBossMap[*x - 1][*y] == '3')   //碰到其他Boss
    {
        return 2;   
    }
    if (szMazeMap[*x - 1][*y] == '0' || szMazeMap[*x - 1][*y] == '2')//碰到豆子或者空格可以走一步
    {
        szBossMap[*x - 1][*y] = '3'; //移动到现在位置
        szBossMap[*x][*y] = '0';     //之前位置变为0
        *x = *x - 1;                 //坐标变换
    }
    else             //碰到墙
    {
        return 2;    //2表示碰到墙
    }
    return 1;        //正常结束
}
STATE __boss_move_down(int *x, int *y)  //Boss向下移动，传参数是为了确定是哪一个怪物调用这个函数
{
    if (szMazeMap[*x + 1][*y] == '4')   //先判断是否吃掉玩家
    {
        return 0;
    }
    if (szBossMap[*x + 1][*y] == '3')   //碰到其他Boss
    {
        return 2;   
    }
    if (szMazeMap[*x + 1][*y] == '0' || szMazeMap[*x + 1][*y] == '2')//碰到豆子或者空格可以走一步
    {
        szBossMap[*x + 1][*y] = '3'; //移动到现在位置
        szBossMap[*x][*y] = '0';     //之前位置变为0
        *x = *x + 1;                 //坐标变换
    }
    else           //碰到墙就跳过
    {
        return 2;  //2表示碰到墙
    }
    return 1;      //正常结束
}
STATE __boss_move_left(int *x, int *y)  //Boss向左移动，传参数是为了确定是哪一个怪物调用这个函数
{
    if (szMazeMap[*x][*y - 1] == '4')   //先判断是否吃掉玩家
    {
        return 0;
    }
    if (szBossMap[*x][*y - 1] == '3')   //碰到其他Boss
    {
        return 2;   
    }
    if (szMazeMap[*x][*y - 1] == '0' || szMazeMap[*x][*y - 1] == '2')//碰到豆子或者空格可以走一步
    {
        szBossMap[*x][*y - 1] = '3'; //移动到现在位置
        szBossMap[*x][*y] = '0';     //之前位置变为0
        *y = *y - 1;                 //坐标变换
    }
    else          //碰到墙就跳过
    {
        return 2; //2表示碰到墙
    }
    return 1;     //正常结束
}
STATE __boss_move_right(int *x, int *y)  //Boss向右移动，传参数是为了确定是哪一个怪物调用这个函数
{
    if (szMazeMap[*x][*y + 1] == '4')   //先判断是否吃掉玩家
    {
        return 0;
    }
    if (szBossMap[*x][*y + 1] == '3')   //碰到其他Boss
    {
        return 2;   //碰到其他Boss
    }
    if (szMazeMap[*x][*y + 1] == '0' || szMazeMap[*x][*y + 1] == '2')//碰到豆子或者空格可以走一步
    {
        szBossMap[*x][*y + 1] = '3'; //移动到现在位置
        szBossMap[*x][*y] = '0';     //之前位置变为0
        *y = *y + 1;                 //坐标变换
    }
    else           //碰到墙就跳过
    {
        return 2;  //2表示碰到墙
    }
    return 1;      //正常结束
}

//////////////////////////////////////////////////////////////////////////////////
/*                            简单Boss移动方法函数                              */
//////////////////////////////////////////////////////////////////////////////////

STATE _move_boss_easy(int *x, int *y)//随机移动
{
    int nMove = 0;  //1上， 2下， 3左， 4右
    int nState = 0; //记录移动的返回状态

    while (1)
    {
        nMove = rand() % 4 + 1;
        switch (nMove)//1上， 2下， 3左， 4右
        {
            case 1:
                nState = __boss_move_up(x, y);
                if (nState == 0)//0结束
                {
                    return 0;
                }              
                if (nState == 1)//1走了一步
                {
                    return 1;
                }
                if (nState == 2)//2遇到墙或其他boss，重新循环一次，直到可以走动为止
                {
                    break;
                }
            case 2:
                nState = __boss_move_down(x, y);
                if (nState == 0)//0结束
                {
                    return 0;
                }
                if (nState == 1)//1走了一步
                {
                    return 1;
                }
                if (nState == 2)//2遇到墙或其他boss，重新循环一次，直到可以走动为止
                {
                    break;
                }
            case 3:
                nState = __boss_move_left(x, y);
                if (nState == 0)//0结束
                {
                    return 0;
                }
                if (nState == 1)//1走了一步
                {
                    return 1;
                }
                if (nState == 2)//2遇到墙或其他boss，重新循环一次，直到可以走动为止
                {
                    break;
                }
            case 4:
                nState = __boss_move_right(x, y);
                if (nState == 0)//0结束
                {
                    return 0;
                }
                if (nState == 1)//1走了一步
                {
                    return 1;
                }
                if (nState == 2)//2遇到墙或其他boss，重新循环一次，直到可以走动为止
                {
                    break;
                }
            default:break;
        }
    }  
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////
/*                            普通Boss移动方法函数                              */
//////////////////////////////////////////////////////////////////////////////////

STATE __find_road(char szTempMap[][WIDTH], int x, int y)//Boss寻找玩家，找到连接的路径并记录在地图里
{
    int nRand = 0;
    int nSort[4] = { 0 };
    int i = 0;
    int j = 0;
    int nFlag = 0; //用来标记随机数是否一致

    if (szMazeMap[x][y] == '4')
    {
        szTempMap[x][y] = '1';
        return 1;
    }
    szTempMap[x][y] = '1';//1代表走过的路

    i = 0; 
    while (1)//产生4个不同的随机数1--4
    {
        nRand = rand() % 4 + 1;
        nFlag = 1;
        for (j = 0; j < i + 1; j++)
        {
            if (nSort[j] == nRand)
            {
                nFlag = 0;
                break;
            }
        }
        if (nFlag ==  1)
        {
            nSort[i] = nRand;
            i++;
        }
        if (nSort[3] != 0)
        {
            break;
        }
    }
    for (i = 0; i < 4; i++) //用4个随机数来作为移动的方向
    {
        switch (nSort[i])
        {
            case 1:
                if ((szMazeMap[x - 1][y] == '0' || szMazeMap[x - 1][y] == '2' || szMazeMap[x - 1][y] == '4')
                                                                              && szTempMap[x - 1][y] == '0')
                {
                    if (__find_road(szTempMap, x - 1, y))
                    {
                        return 1;
                    }
                    else
                    {
                        szTempMap[x - 1][y] = '2';//2代表退出的路
                    }
                }
                break;
            case 2:
                if ((szMazeMap[x][y - 1] == '0' || szMazeMap[x][y - 1] == '2' || szMazeMap[x][y - 1] == '4')
                                                                              && szTempMap[x][y - 1] == '0')
                {
                    if (__find_road(szTempMap, x, y - 1))
                    {
                        return 1;
                    }
                    else
                    {
                        szTempMap[x][y - 1] = '2';//2代表退出的路
                    }
                }
                break;
            case 3:
                if ((szMazeMap[x + 1][y] == '0' || szMazeMap[x + 1][y] == '2' || szMazeMap[x + 1][y] == '4')
                                                                              && szTempMap[x + 1][y] == '0')
                {
                    if (__find_road(szTempMap, x + 1, y))
                    {
                        return 1;
                    }
                    else
                    {
                        szTempMap[x + 1][y] = '2';//2代表退出的路
                    }
                }
                break;
            case 4:
                if ((szMazeMap[x][y + 1] == '0' || szMazeMap[x][y + 1] == '2' || szMazeMap[x][y + 1] == '4')
                                                                              && szTempMap[x][y + 1] == '0')
                {
                    if (__find_road(szTempMap, x, y + 1))
                    {
                        return 1;
                    }
                    else
                    {
                        szTempMap[x][y + 1] = '2';//2代表退出的路
                    }
                }
                break;
            default:break;
        }
    }
    return 0;
}
STATE _move_boss_normal(int *x, int *y)//向用户随机移动
{
    char szTempMap[HIGH][WIDTH] = { 0 }; 

    __copy_map(szTempMap);
    __find_road(szTempMap, *x, *y);
 
    if (szTempMap[*x - 1][*y] == '1')
    {
        if (__boss_move_up(x, y) == 0)
        {
            return 0;
        }
        return 1;
    }
    if (szTempMap[*x + 1][*y] == '1')
    {
        if (__boss_move_down(x, y) == 0)
        {
            return 0;
        }
        return 1;
    }
    if (szTempMap[*x][*y - 1] == '1')
    {
        if (__boss_move_left(x, y) == 0)
        {
            return 0;
        }
        return 1;
    }
    if (szTempMap[*x][*y + 1] == '1')
    {
        if (__boss_move_right(x, y) == 0)
        {
            return 0;
        }
        return 1;
    }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////
/*                            疯狂Boss移动方法函数                              */
//////////////////////////////////////////////////////////////////////////////////

STATE __find_short_road(char szTempBossMap[][WIDTH], int x, int y)//Boss寻找玩家，找到最短路径并记录在地图里
{
    int nRand = 0;
    int nSort[4] = { 0 };
    int i = 0;
    int j = 0;
    int nFlag = 0;//用来标记随机数是否一致

    if (szMazeMap[x][y] == '4')
    {
        szTempBossMap[x][y] = '1';
        return 1;
    }
    szTempBossMap[x][y] = '1';//1代表走过的路

////////////////////////////////////////////////////////////////////////////
/*      以下为根据坐标判断Boss和玩家的位置，来获得Boss下一步移动的方向    */
////////////////////////////////////////////////////////////////////////////

    if (x - xPlayer == 0)//Boss和玩家在同一条水平线上
    {
        if (y - yPlayer == 0)     //Boss和玩家重合
        {
            return 0;
        }
        else if (y - yPlayer < 0) //Boss在玩家正右边
        {
            nSort[0] = 4;
            nSort[1] = 1;
            nSort[2] = 3;
            nSort[3] = 2;
        }
        else                      //Boss在玩家正左边
        {
            nSort[0] = 2;
            nSort[1] = 1;
            nSort[2] = 3;
            nSort[3] = 4;
        }
    }
    else if (x - xPlayer < 0)     //Boss在玩家上方
    {
        if (y - yPlayer == 0)     //Boss在玩家正上方
        {
            nSort[0] = 3;
            nSort[1] = 2;
            nSort[2] = 4;
            nSort[3] = 1;
        }
        else if (y - yPlayer < 0) //Boss在玩家左上方
        {
            nSort[0] = 3;
            nSort[1] = 4;
            nSort[2] = 1;
            nSort[3] = 2;
        }
        else                      //Boss在玩家右上方
        {
            nSort[0] = 3;
            nSort[1] = 2;
            nSort[2] = 1;
            nSort[3] = 4;
        }
    }
    else                          //Boss在玩家下方
    {
        if (y - yPlayer == 0)     //Boss在玩家正下方
        {
            nSort[0] = 1;
            nSort[1] = 2;
            nSort[2] = 4;
            nSort[3] = 1;
        }
        else if (y - yPlayer < 0) //Boss在玩家左下方
        {
            nSort[0] = 1;
            nSort[1] = 4;
            nSort[2] = 3;
            nSort[3] = 2;
        }
        else                      //Boss在玩家右下方
        {
            nSort[0] = 1;
            nSort[1] = 2;
            nSort[2] = 3;
            nSort[3] = 4;
        }
    }
/////////////////////////////////////////////////////////////////
/*                     获取方向结束                           */
/////////////////////////////////////////////////////////////////

    for (i = 0; i < 4; i++) //用4个数来作为移动的方向 1上， 2左， 3下， 4右
    {
        switch (nSort[i])
        {
        case 1:
            if ((szMazeMap[x - 1][y] == '0' || szMazeMap[x - 1][y] == '2' || szMazeMap[x - 1][y] == '4')
                                                                      && szTempBossMap[x - 1][y] == '0')
            {
                if (__find_short_road(szTempBossMap, x - 1, y))
                {
                    return 1;
                }
                else
                {
                    szTempBossMap[x - 1][y] = '2';//2代表退出的路
                }
            }
            break;
        case 2:
            if ((szMazeMap[x][y - 1] == '0' || szMazeMap[x][y - 1] == '2' || szMazeMap[x][y - 1] == '4')
                                                                      && szTempBossMap[x][y - 1] == '0')
            {
                if (__find_short_road(szTempBossMap, x, y - 1))
                {
                    return 1;
                }
                else
                {
                    szTempBossMap[x][y - 1] = '2';//2代表退出的路
                }
            }
            break;
        case 3:
            if ((szMazeMap[x + 1][y] == '0' || szMazeMap[x + 1][y] == '2' || szMazeMap[x + 1][y] == '4')
                                                                      && szTempBossMap[x + 1][y] == '0')
            {
                if (__find_short_road(szTempBossMap, x + 1, y))
                {
                    return 1;
                }
                else
                {
                    szTempBossMap[x + 1][y] = '2';//2代表退出的路
                }
            }
            break;
        case 4:
            if ((szMazeMap[x][y + 1] == '0' || szMazeMap[x][y + 1] == '2' || szMazeMap[x][y + 1] == '4')
                                                                      && szTempBossMap[x][y + 1] == '0')
            {
                if (__find_short_road(szTempBossMap, x, y + 1))
                {
                    return 1;
                }
                else
                {
                    szTempBossMap[x][y + 1] = '2';//2代表退出的路
                }
            }
            break;
        default:break;
        }
    }
    return 0;
}

 STATE _move_boss_crazy(int *x, int *y, int nState, char szTempBossMap[][WIDTH])//用最短路径向玩家移动，每2.5秒刷新一次路径
{     
    if (nState == 1)
    {
        __copy_map(szTempBossMap);
        __find_short_road(szTempBossMap, *x, *y);
    }

    if (szTempBossMap[*x - 1][*y] == '1')
    {
        szTempBossMap[*x][*y] = '0';
        if (__boss_move_up(x, y) == 0)
        {
            return 0;
        }
        return 1;
    }
    if (szTempBossMap[*x + 1][*y] == '1' )
    {
        szTempBossMap[*x][*y] = '0';
        if (__boss_move_down(x, y) == 0)
        {
            return 0;
        }
        return 1;
    }
    if (szTempBossMap[*x][*y - 1] == '1')
    {
        szTempBossMap[*x][*y] = '0';
        if (__boss_move_left(x, y) == 0)
        {
            return 0;
        }
        return 1;
    }
    if (szTempBossMap[*x][*y + 1] == '1')
    {
        szTempBossMap[*x][*y] = '0';
        if (__boss_move_right(x, y) == 0)
        {
            return 0;
        }
        return 1;
    }
    return 1;
}

 /////////////////////////////////////////////////////////
 /*                     总调用函数                      */
 /////////////////////////////////////////////////////////
void game_start()
{
    /*      Boss-1       */
    int xBossOne = 1;//行
    int yBossOne = 27;//列

    /*      Boss-2       */
    int xBossTwo = 18;//行
    int yBossTwo = 1;//列

    /*      Boss-3       */
    int xBossThree = 18;//行
    int yBossThree = 27;//列
    char szBossThreeMap[HIGH][WIDTH] = { 0 };//记录Boss-3的路径

    /*      Boss-4       */
    int xBossFour = 10;//行
    int yBossFour = 15;//列
    char szBossFourMap[HIGH][WIDTH] = { 0 };//记录Boss-4的路径

    clock_t tStart = 0;//long
    clock_t tCurrent = 0;//计算时间差，用于调整Boss移动速度
    clock_t tStateBeging = 0;
    clock_t tStateCurrent = 0;//状态时间差，用来控制Boss刷新路径的时间间隔
    int i = 0;
    int nState = 0;//记录是否需要重新寻址

    srand((unsigned)time(NULL));
    _init_map();           //初始化地图
    _print_map();          //打印地图
    tStart = clock();      //初始计时
    tStateBeging = clock();//初始计时
    while (1)
    {
        tCurrent = clock();      //记录当前时间
        
        if (_move_player() == 0) //0结束游戏
        {
            return;
        }

        if (tCurrent - tStart >= lLevel)//根据level来调整等级
        {
            tStart = tCurrent;          //将当前时间变为开始时间
            tStateCurrent = clock();    //记录当前时间
            if (tStateCurrent - tStateBeging > 2500)//疯狂的Boss每2.5秒，重新计算一次路径
            {
                tStateBeging = tStateCurrent;       //将当前时间变为开始时间
                nState = 1;
            }
            else
            {
                nState = 0;
            }

            if (lLevel > 200)           //以200毫秒移动一次作为Boss的极限速度
            {
                for (i = 0; i < 5; i++) //每次BOSS移动后都将难度升级
                {
                    lLevel--;
                }
            }
            if (_move_boss_easy(&xBossOne, &yBossOne) == 0)           //难度1，0结束游戏
            {
                return;
            }
            if (lLevel < 900)
            {
                if (_move_boss_normal(&xBossTwo, &yBossTwo) == 0)     //解锁难度2，0结束游戏
                {
                    return;
                }
            }
            if (lLevel < 800)
            {
                if (_move_boss_crazy(&xBossThree, &yBossThree, nState, szBossThreeMap) == 0)  //解锁难度3，0结束游戏
                {
                    return;
                }
            }  
            if (lLevel < 700)
            {
                if (_move_boss_crazy(&xBossFour, &yBossFour, nState, szBossFourMap) == 0)  //解锁难度4，0结束游戏
                {
                    return;
                }
            }
            _print_map();
        }      
    }  
}
///////////////////////////////////////////////////////////
/*                     调用游戏函数                      */
///////////////////////////////////////////////////////////
void play_game()
{
    game_start();
    printf("游戏结束！您本次得分：%d\r\n", nScore);
}
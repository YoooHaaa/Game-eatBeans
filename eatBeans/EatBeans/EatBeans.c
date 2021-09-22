#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>


#define WALLS   "*" // 1  ǽ
#define BEANS   "." // 0  ����
#define ROAD    " " // 2  ���궹�ӵĿ�·
#define BOSS    "O" // 3  ����
#define MINE    "@" // 4  ���

#define HIGH    20//��
#define WIDTH   30//��
#define STATE   int

char szMazeMap[HIGH][WIDTH] = { 0 };//�Թ���ͼ
char szBossMap[HIGH][WIDTH] = { 0 };//�����ͼ
int nScore = 0;    //�ܵ÷�
long lLevel = 1000;//�Ѷȣ�ÿ��boss�ƶ���ʱ����
int xPlayer = 1;   //�������  ��
int yPlayer = 1;   //�������  ��

void _init_map()//��ʼ����ҵ�ͼ
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
void __copy_map(char szTempMap[][WIDTH])//��Boss��ͼ���Ƹ�����
{
    int i = 0;

    for (i = 0; i < HIGH; i++)
    {
        strcpy_s(szTempMap[i], WIDTH * sizeof(char), szBossMap[i]);
    }
}
void _print_map()//��ӡ��ͼ
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
            printf("      ��ʾ������Ŀ����������Ͻǣ�ͨ��w/a/s/d������Ŀ���ƶ�");
        }
        if (i == 7)
        {
            printf("      �Ѷ����ã�2��СBoss��2����Boss��ÿ10�뻽��һ��");
        }
        if (i == 9)
        {
            printf("      ����ǰ�ĵ÷��ǣ�%d", nScore);
        }
        if (i == 11)
        {
            printf("      ����ǰ���Ѷ��ǣ�%d", 10 - lLevel/100);
        }   
        printf("\r\n");
    }
}

//////////////////////////////////////////////////////////////////////////
/*                        ����ƶ����ƺ���                              */
//////////////////////////////////////////////////////////////////////////

STATE __player_move_up()//��������ƶ�
{
    if (szBossMap[xPlayer - 1][yPlayer] == '3')//���ж��Ƿ���Boss
    {
        return 0;
    }
    if (szMazeMap[xPlayer - 1][yPlayer] == '0')
    {
        szMazeMap[xPlayer - 1][yPlayer] = '4';//�ƶ�������λ��
        szMazeMap[xPlayer][yPlayer] = '2';    //֮ǰλ�ñ�Ϊ�ո�
        xPlayer = xPlayer - 1;                 //����任
        nScore++;                              //�ӷ�
    }
    else if (szMazeMap[xPlayer - 1][yPlayer] == '2')
    {
        szMazeMap[xPlayer - 1][yPlayer] = '4';//�ƶ�������λ��
        szMazeMap[xPlayer][yPlayer] = '2';    //֮ǰλ�ñ�Ϊ�ո�
        xPlayer = xPlayer - 1;
    }
    else
    {
        return 1;
    }
    _print_map();
    return 1;
}
STATE __player_move_down()//��������ƶ�
{
    if (szBossMap[xPlayer + 1][yPlayer] == '3')//���ж��Ƿ���Boss
    {
        return 0;
    }
    if (szMazeMap[xPlayer + 1][yPlayer] == '0')
    {
        szMazeMap[xPlayer + 1][yPlayer] = '4'; //�ƶ�������λ��
        szMazeMap[xPlayer][yPlayer] = '2';     //֮ǰλ�ñ�Ϊ�ո�
        xPlayer = xPlayer + 1;                 //����任
        nScore++;                              //�ӷ�
    }
    else if (szMazeMap[xPlayer + 1][yPlayer] == '2')
    {
        szMazeMap[xPlayer + 1][yPlayer] = '4';//�ƶ�������λ��
        szMazeMap[xPlayer][yPlayer] = '2';    //֮ǰλ�ñ�Ϊ�ո�
        xPlayer = xPlayer + 1;
    }
    else
    {
        return 1;
    }
    _print_map();
    return 1;
}
STATE __player_move_left()//��������ƶ�
{
    if (szBossMap[xPlayer][yPlayer - 1] == '3')//���ж��Ƿ���Boss
    {
        return 0;
    }
    if (szMazeMap[xPlayer][yPlayer - 1] == '0')
    {
        szMazeMap[xPlayer][yPlayer - 1] = '4'; //�ƶ�������λ��
        szMazeMap[xPlayer][yPlayer] = '2';     //֮ǰλ�ñ�Ϊ�ո�
        yPlayer = yPlayer - 1;                 //����任
        nScore++;                              //�ӷ�
    }
    else if (szMazeMap[xPlayer][yPlayer - 1] == '2')
    {
        szMazeMap[xPlayer][yPlayer - 1] = '4';//�ƶ�������λ��
        szMazeMap[xPlayer][yPlayer] = '2';    //֮ǰλ�ñ�Ϊ�ո�
        yPlayer = yPlayer - 1;
    }
    else
    {
        return 1;
    }
    _print_map();
    return 1;
}
STATE __player_move_right()//��������ƶ�
{
    if (szBossMap[xPlayer][yPlayer + 1] == '3')//���ж��Ƿ���Boss
    {
        return 0;
    }
    if (szMazeMap[xPlayer][yPlayer + 1] == '0')
    {
        szMazeMap[xPlayer][yPlayer + 1] = '4'; //�ƶ�������λ��
        szMazeMap[xPlayer][yPlayer] = '2';     //֮ǰλ�ñ�Ϊ�ո�
        yPlayer = yPlayer + 1;                 //����任
        nScore++;                              //�ӷ�
    }
    else if (szMazeMap[xPlayer][yPlayer + 1] == '2')
    {
        szMazeMap[xPlayer][yPlayer + 1] = '4';//�ƶ�������λ��
        szMazeMap[xPlayer][yPlayer] = '2';    //֮ǰλ�ñ�Ϊ�ո�
        yPlayer = yPlayer + 1;
    }
    else
    {
        return 1;
    }
    _print_map();
    return 1;
}

STATE _move_player()//����ƶ�����
{
    char cMove = 0;

    if (_kbhit() == 0)
    {
        return 2;//2��ʾû���ƶ�
    }
    cMove = _getch();
    rewind(stdin);

    switch (cMove)
    {
        case 'w':
            if (__player_move_up() == 0)  //0������Ϸ
            {
                return 0;
            }
            break;
        case 's':
            if (__player_move_down() == 0)//0������Ϸ
            {
                return 0;
            }
            break;
        case 'a':
            if (__player_move_left() == 0)//0������Ϸ
            {
                return 0;
            }
            break;
        case 'd':
            if (__player_move_right() == 0)//0������Ϸ
            {
                return 0;
            }
            break;
        default:break;
    }
    return 1;//1��ʾ�����ƶ�
}

///////////////////////////////////////////////////////////////////////////////////////
/*                            Boss���������ƶ����ƺ���                               */
///////////////////////////////////////////////////////////////////////////////////////

STATE __boss_move_up(int *x, int *y)    //Boss�����ƶ�����������Ϊ��ȷ������һ����������������
{
    if (szMazeMap[*x - 1][*y] == '4')   //���ж��Ƿ�Ե����
    {
        return 0;
    }
    if (szBossMap[*x - 1][*y] == '3')   //��������Boss
    {
        return 2;   
    }
    if (szMazeMap[*x - 1][*y] == '0' || szMazeMap[*x - 1][*y] == '2')//�������ӻ��߿ո������һ��
    {
        szBossMap[*x - 1][*y] = '3'; //�ƶ�������λ��
        szBossMap[*x][*y] = '0';     //֮ǰλ�ñ�Ϊ0
        *x = *x - 1;                 //����任
    }
    else             //����ǽ
    {
        return 2;    //2��ʾ����ǽ
    }
    return 1;        //��������
}
STATE __boss_move_down(int *x, int *y)  //Boss�����ƶ�����������Ϊ��ȷ������һ����������������
{
    if (szMazeMap[*x + 1][*y] == '4')   //���ж��Ƿ�Ե����
    {
        return 0;
    }
    if (szBossMap[*x + 1][*y] == '3')   //��������Boss
    {
        return 2;   
    }
    if (szMazeMap[*x + 1][*y] == '0' || szMazeMap[*x + 1][*y] == '2')//�������ӻ��߿ո������һ��
    {
        szBossMap[*x + 1][*y] = '3'; //�ƶ�������λ��
        szBossMap[*x][*y] = '0';     //֮ǰλ�ñ�Ϊ0
        *x = *x + 1;                 //����任
    }
    else           //����ǽ������
    {
        return 2;  //2��ʾ����ǽ
    }
    return 1;      //��������
}
STATE __boss_move_left(int *x, int *y)  //Boss�����ƶ�����������Ϊ��ȷ������һ����������������
{
    if (szMazeMap[*x][*y - 1] == '4')   //���ж��Ƿ�Ե����
    {
        return 0;
    }
    if (szBossMap[*x][*y - 1] == '3')   //��������Boss
    {
        return 2;   
    }
    if (szMazeMap[*x][*y - 1] == '0' || szMazeMap[*x][*y - 1] == '2')//�������ӻ��߿ո������һ��
    {
        szBossMap[*x][*y - 1] = '3'; //�ƶ�������λ��
        szBossMap[*x][*y] = '0';     //֮ǰλ�ñ�Ϊ0
        *y = *y - 1;                 //����任
    }
    else          //����ǽ������
    {
        return 2; //2��ʾ����ǽ
    }
    return 1;     //��������
}
STATE __boss_move_right(int *x, int *y)  //Boss�����ƶ�����������Ϊ��ȷ������һ����������������
{
    if (szMazeMap[*x][*y + 1] == '4')   //���ж��Ƿ�Ե����
    {
        return 0;
    }
    if (szBossMap[*x][*y + 1] == '3')   //��������Boss
    {
        return 2;   //��������Boss
    }
    if (szMazeMap[*x][*y + 1] == '0' || szMazeMap[*x][*y + 1] == '2')//�������ӻ��߿ո������һ��
    {
        szBossMap[*x][*y + 1] = '3'; //�ƶ�������λ��
        szBossMap[*x][*y] = '0';     //֮ǰλ�ñ�Ϊ0
        *y = *y + 1;                 //����任
    }
    else           //����ǽ������
    {
        return 2;  //2��ʾ����ǽ
    }
    return 1;      //��������
}

//////////////////////////////////////////////////////////////////////////////////
/*                            ��Boss�ƶ���������                              */
//////////////////////////////////////////////////////////////////////////////////

STATE _move_boss_easy(int *x, int *y)//����ƶ�
{
    int nMove = 0;  //1�ϣ� 2�£� 3�� 4��
    int nState = 0; //��¼�ƶ��ķ���״̬

    while (1)
    {
        nMove = rand() % 4 + 1;
        switch (nMove)//1�ϣ� 2�£� 3�� 4��
        {
            case 1:
                nState = __boss_move_up(x, y);
                if (nState == 0)//0����
                {
                    return 0;
                }              
                if (nState == 1)//1����һ��
                {
                    return 1;
                }
                if (nState == 2)//2����ǽ������boss������ѭ��һ�Σ�ֱ�������߶�Ϊֹ
                {
                    break;
                }
            case 2:
                nState = __boss_move_down(x, y);
                if (nState == 0)//0����
                {
                    return 0;
                }
                if (nState == 1)//1����һ��
                {
                    return 1;
                }
                if (nState == 2)//2����ǽ������boss������ѭ��һ�Σ�ֱ�������߶�Ϊֹ
                {
                    break;
                }
            case 3:
                nState = __boss_move_left(x, y);
                if (nState == 0)//0����
                {
                    return 0;
                }
                if (nState == 1)//1����һ��
                {
                    return 1;
                }
                if (nState == 2)//2����ǽ������boss������ѭ��һ�Σ�ֱ�������߶�Ϊֹ
                {
                    break;
                }
            case 4:
                nState = __boss_move_right(x, y);
                if (nState == 0)//0����
                {
                    return 0;
                }
                if (nState == 1)//1����һ��
                {
                    return 1;
                }
                if (nState == 2)//2����ǽ������boss������ѭ��һ�Σ�ֱ�������߶�Ϊֹ
                {
                    break;
                }
            default:break;
        }
    }  
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////
/*                            ��ͨBoss�ƶ���������                              */
//////////////////////////////////////////////////////////////////////////////////

STATE __find_road(char szTempMap[][WIDTH], int x, int y)//BossѰ����ң��ҵ����ӵ�·������¼�ڵ�ͼ��
{
    int nRand = 0;
    int nSort[4] = { 0 };
    int i = 0;
    int j = 0;
    int nFlag = 0; //�������������Ƿ�һ��

    if (szMazeMap[x][y] == '4')
    {
        szTempMap[x][y] = '1';
        return 1;
    }
    szTempMap[x][y] = '1';//1�����߹���·

    i = 0; 
    while (1)//����4����ͬ�������1--4
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
    for (i = 0; i < 4; i++) //��4�����������Ϊ�ƶ��ķ���
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
                        szTempMap[x - 1][y] = '2';//2�����˳���·
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
                        szTempMap[x][y - 1] = '2';//2�����˳���·
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
                        szTempMap[x + 1][y] = '2';//2�����˳���·
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
                        szTempMap[x][y + 1] = '2';//2�����˳���·
                    }
                }
                break;
            default:break;
        }
    }
    return 0;
}
STATE _move_boss_normal(int *x, int *y)//���û�����ƶ�
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
/*                            ���Boss�ƶ���������                              */
//////////////////////////////////////////////////////////////////////////////////

STATE __find_short_road(char szTempBossMap[][WIDTH], int x, int y)//BossѰ����ң��ҵ����·������¼�ڵ�ͼ��
{
    int nRand = 0;
    int nSort[4] = { 0 };
    int i = 0;
    int j = 0;
    int nFlag = 0;//�������������Ƿ�һ��

    if (szMazeMap[x][y] == '4')
    {
        szTempBossMap[x][y] = '1';
        return 1;
    }
    szTempBossMap[x][y] = '1';//1�����߹���·

////////////////////////////////////////////////////////////////////////////
/*      ����Ϊ���������ж�Boss����ҵ�λ�ã������Boss��һ���ƶ��ķ���    */
////////////////////////////////////////////////////////////////////////////

    if (x - xPlayer == 0)//Boss�������ͬһ��ˮƽ����
    {
        if (y - yPlayer == 0)     //Boss������غ�
        {
            return 0;
        }
        else if (y - yPlayer < 0) //Boss��������ұ�
        {
            nSort[0] = 4;
            nSort[1] = 1;
            nSort[2] = 3;
            nSort[3] = 2;
        }
        else                      //Boss����������
        {
            nSort[0] = 2;
            nSort[1] = 1;
            nSort[2] = 3;
            nSort[3] = 4;
        }
    }
    else if (x - xPlayer < 0)     //Boss������Ϸ�
    {
        if (y - yPlayer == 0)     //Boss��������Ϸ�
        {
            nSort[0] = 3;
            nSort[1] = 2;
            nSort[2] = 4;
            nSort[3] = 1;
        }
        else if (y - yPlayer < 0) //Boss��������Ϸ�
        {
            nSort[0] = 3;
            nSort[1] = 4;
            nSort[2] = 1;
            nSort[3] = 2;
        }
        else                      //Boss��������Ϸ�
        {
            nSort[0] = 3;
            nSort[1] = 2;
            nSort[2] = 1;
            nSort[3] = 4;
        }
    }
    else                          //Boss������·�
    {
        if (y - yPlayer == 0)     //Boss��������·�
        {
            nSort[0] = 1;
            nSort[1] = 2;
            nSort[2] = 4;
            nSort[3] = 1;
        }
        else if (y - yPlayer < 0) //Boss��������·�
        {
            nSort[0] = 1;
            nSort[1] = 4;
            nSort[2] = 3;
            nSort[3] = 2;
        }
        else                      //Boss��������·�
        {
            nSort[0] = 1;
            nSort[1] = 2;
            nSort[2] = 3;
            nSort[3] = 4;
        }
    }
/////////////////////////////////////////////////////////////////
/*                     ��ȡ�������                           */
/////////////////////////////////////////////////////////////////

    for (i = 0; i < 4; i++) //��4��������Ϊ�ƶ��ķ��� 1�ϣ� 2�� 3�£� 4��
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
                    szTempBossMap[x - 1][y] = '2';//2�����˳���·
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
                    szTempBossMap[x][y - 1] = '2';//2�����˳���·
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
                    szTempBossMap[x + 1][y] = '2';//2�����˳���·
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
                    szTempBossMap[x][y + 1] = '2';//2�����˳���·
                }
            }
            break;
        default:break;
        }
    }
    return 0;
}

 STATE _move_boss_crazy(int *x, int *y, int nState, char szTempBossMap[][WIDTH])//�����·��������ƶ���ÿ2.5��ˢ��һ��·��
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
 /*                     �ܵ��ú���                      */
 /////////////////////////////////////////////////////////
void game_start()
{
    /*      Boss-1       */
    int xBossOne = 1;//��
    int yBossOne = 27;//��

    /*      Boss-2       */
    int xBossTwo = 18;//��
    int yBossTwo = 1;//��

    /*      Boss-3       */
    int xBossThree = 18;//��
    int yBossThree = 27;//��
    char szBossThreeMap[HIGH][WIDTH] = { 0 };//��¼Boss-3��·��

    /*      Boss-4       */
    int xBossFour = 10;//��
    int yBossFour = 15;//��
    char szBossFourMap[HIGH][WIDTH] = { 0 };//��¼Boss-4��·��

    clock_t tStart = 0;//long
    clock_t tCurrent = 0;//����ʱ�����ڵ���Boss�ƶ��ٶ�
    clock_t tStateBeging = 0;
    clock_t tStateCurrent = 0;//״̬ʱ����������Bossˢ��·����ʱ����
    int i = 0;
    int nState = 0;//��¼�Ƿ���Ҫ����Ѱַ

    srand((unsigned)time(NULL));
    _init_map();           //��ʼ����ͼ
    _print_map();          //��ӡ��ͼ
    tStart = clock();      //��ʼ��ʱ
    tStateBeging = clock();//��ʼ��ʱ
    while (1)
    {
        tCurrent = clock();      //��¼��ǰʱ��
        
        if (_move_player() == 0) //0������Ϸ
        {
            return;
        }

        if (tCurrent - tStart >= lLevel)//����level�������ȼ�
        {
            tStart = tCurrent;          //����ǰʱ���Ϊ��ʼʱ��
            tStateCurrent = clock();    //��¼��ǰʱ��
            if (tStateCurrent - tStateBeging > 2500)//����Bossÿ2.5�룬���¼���һ��·��
            {
                tStateBeging = tStateCurrent;       //����ǰʱ���Ϊ��ʼʱ��
                nState = 1;
            }
            else
            {
                nState = 0;
            }

            if (lLevel > 200)           //��200�����ƶ�һ����ΪBoss�ļ����ٶ�
            {
                for (i = 0; i < 5; i++) //ÿ��BOSS�ƶ��󶼽��Ѷ�����
                {
                    lLevel--;
                }
            }
            if (_move_boss_easy(&xBossOne, &yBossOne) == 0)           //�Ѷ�1��0������Ϸ
            {
                return;
            }
            if (lLevel < 900)
            {
                if (_move_boss_normal(&xBossTwo, &yBossTwo) == 0)     //�����Ѷ�2��0������Ϸ
                {
                    return;
                }
            }
            if (lLevel < 800)
            {
                if (_move_boss_crazy(&xBossThree, &yBossThree, nState, szBossThreeMap) == 0)  //�����Ѷ�3��0������Ϸ
                {
                    return;
                }
            }  
            if (lLevel < 700)
            {
                if (_move_boss_crazy(&xBossFour, &yBossFour, nState, szBossFourMap) == 0)  //�����Ѷ�4��0������Ϸ
                {
                    return;
                }
            }
            _print_map();
        }      
    }  
}
///////////////////////////////////////////////////////////
/*                     ������Ϸ����                      */
///////////////////////////////////////////////////////////
void play_game()
{
    game_start();
    printf("��Ϸ�����������ε÷֣�%d\r\n", nScore);
}
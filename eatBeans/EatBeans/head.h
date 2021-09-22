#pragma once

////////////////////////////////////////////////////////////////////////////////////////////
//工程功能：在迷宫地图里有2个小Boss，2个大Boss，每10秒钟解锁一个Boss，Boss被解锁后会移动  //
//          ，玩家需要在不被Boss碰到的情况下，尽可能多的吃掉地图上的豆子以获得积分        //
//作者：    郑耀华                                                                        //
//日期：    2019/4/13                                                                     //
////////////////////////////////////////////////////////////////////////////////////////////

#define HIGH    20//行
#define WIDTH   30//列
#define STATE   int

void _init_map();//初始化玩家地图
void __copy_map(char szTempMap[][WIDTH]);//将Boss地图复制给参数

/* -------玩家移动函数-------*/
STATE __player_move_up();
STATE __player_move_down();
STATE __player_move_left();
STATE __player_move_right();

/* -------玩家调用函数-------*/
STATE _move_player();

/* -------BOSS移动函数-------*/
STATE __boss_move_up(int *x, int *y);
STATE __boss_move_down(int *x, int *y);
STATE __boss_move_left(int *x, int *y);
STATE __boss_move_right(int *x, int *y);

STATE _move_boss_easy(int *x, int *y);//简单难度的Boss控制函数

STATE __find_road(char szTempMap[][WIDTH], int x, int y);//Boss寻找玩家，找到连接的（非最短）路径并记录在地图里
STATE _move_boss_normal(int *x, int *y);//一般难度的Boss控制函数

STATE __find_short_road(char szTempMap[][WIDTH], int x, int y);//Boss寻找玩家，找到最短路径并记录在地图里
STATE _move_boss_crazy(int *x, int *y, int nState, char szBossMap[][WIDTH]);//疯狂难度的Boss控制函数

void game_start();//游戏执行控制函数
void play_game();//调用游戏函数
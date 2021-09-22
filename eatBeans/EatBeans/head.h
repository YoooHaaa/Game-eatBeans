#pragma once

////////////////////////////////////////////////////////////////////////////////////////////
//���̹��ܣ����Թ���ͼ����2��СBoss��2����Boss��ÿ10���ӽ���һ��Boss��Boss����������ƶ�  //
//          �������Ҫ�ڲ���Boss����������£������ܶ�ĳԵ���ͼ�ϵĶ����Ի�û���        //
//���ߣ�    ֣ҫ��                                                                        //
//���ڣ�    2019/4/13                                                                     //
////////////////////////////////////////////////////////////////////////////////////////////

#define HIGH    20//��
#define WIDTH   30//��
#define STATE   int

void _init_map();//��ʼ����ҵ�ͼ
void __copy_map(char szTempMap[][WIDTH]);//��Boss��ͼ���Ƹ�����

/* -------����ƶ�����-------*/
STATE __player_move_up();
STATE __player_move_down();
STATE __player_move_left();
STATE __player_move_right();

/* -------��ҵ��ú���-------*/
STATE _move_player();

/* -------BOSS�ƶ�����-------*/
STATE __boss_move_up(int *x, int *y);
STATE __boss_move_down(int *x, int *y);
STATE __boss_move_left(int *x, int *y);
STATE __boss_move_right(int *x, int *y);

STATE _move_boss_easy(int *x, int *y);//���Ѷȵ�Boss���ƺ���

STATE __find_road(char szTempMap[][WIDTH], int x, int y);//BossѰ����ң��ҵ����ӵģ�����̣�·������¼�ڵ�ͼ��
STATE _move_boss_normal(int *x, int *y);//һ���Ѷȵ�Boss���ƺ���

STATE __find_short_road(char szTempMap[][WIDTH], int x, int y);//BossѰ����ң��ҵ����·������¼�ڵ�ͼ��
STATE _move_boss_crazy(int *x, int *y, int nState, char szBossMap[][WIDTH]);//����Ѷȵ�Boss���ƺ���

void game_start();//��Ϸִ�п��ƺ���
void play_game();//������Ϸ����
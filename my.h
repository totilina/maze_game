#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <easyx.h>
#include <graphics.h>
#include <time.h>

#define SIZE 20
#define ROW 41
#define COL 41
#define MAP_ROW ROW - 1
#define MAP_COL COL - 1

struct Button          //按钮
{
	int x, y;		   // 按钮左上角坐标
	int width, height; // 按钮宽度和高度
	const char *text;  // 按钮文本
};

typedef struct Button Button;

int Main_interface(int set);                   //主界面
void drawButton(Button btn);							  // 绘制按钮(功能键)函数
bool isMouseOnButton(Button btn, int mouseX, int mouseY); // 判断鼠标点击位置是否在按钮区域内的函数


void Initmap(int map[][COL],int dem);  //初始化地图，生成迷宫

int Playgame(int map[][COL]);  //游戏操作

void drawmap(int map[][COL],int my_x,int my_y);   //绘制地图，地图可视化

void copy_(struct Stack stack[], int len, struct Stack *answer);//复制节点

void draw_answer(int map[][COL],int my_x,int my_y);         //显示通关路径

void draw_stack(struct Stack stack[], int len,int map[][COL]);  //显示栈中节点

void Game_description();  //游戏说明

int Du_set(int *set);  //读取设置信息

int Game_settings(int *set);  //游戏设置

void Dem_des(); // 生成迷宫演示的说明函数
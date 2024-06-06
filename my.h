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

struct Button
{
	int x, y;		   // 按钮左上角坐标
	int width, height; // 按钮宽度和高度
	const char *text;  // 按钮文本
};

typedef struct Button Button;

int Main_interface();
void drawButton(Button btn);							  // 绘制按钮(功能键)函数
bool isMouseOnButton(Button btn, int mouseX, int mouseY); // 判断鼠标点击位置是否在按钮区域内的函数


void Initmap(int map[][COL]);

int Playgame(int map[][COL]);

void drawmap(int map[][COL]);   //绘制地图，地图可视化

void Game_description();

void Game_settings();


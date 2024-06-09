#include "my.h"

struct Stack // 储存节点的栈
{
	int x;   //节点横坐标
	int y;   //节点纵坐标
};

void Initmap(int map[][COL], int dem)
{

	int x = 1, y = 1;
	// int old_x = x, old_y = y;
	struct Stack stack[ROW * COL / 2 + 1]; // 创建一个栈，模拟递归
	struct Stack answer[ROW * COL / 2 + 1];

	int len = -1; // 栈顶
	int ke = 4;	  // 一个节点可遍历的相邻节点数
	stack[++len] = {1, 1};

	map[1][1] = 1;
	int biao = 1, answer_len = 0; // biao是是否找到入口的标记，answer_len是通关路径的长度

	while (len != -1)
	{
		ke = 4;
		int a0 = -1, a1 = -1, a2 = -1, a3 = -1;

		if (dem)    //判断是否进入迷宫生成演示
		{
			draw_stack(stack, len, map);
			if(_getch()==27) break;
		}

		while (ke > 0)  //以该节点是否有可遍历的相邻节点作为循环条件
		{
			int loc = rand() % 4;     //生成随机数
			if (loc == a0 || loc == a1 || loc == a2 || loc == a3) //防止遍历方向重复
				continue;
			if (loc == 0) // loc==0,向下遍历
			{
				if (map[x - 2][y] != 1 && x > 1)
				{
					if (map[x - 2][y] == 10)
					{
						map[x - 1][y] = 1;
						map[x - 2][y] = 1;
						x -= 2;
						stack[++len] = {x, y};
						if (biao)
						{
							copy_(stack, len, answer);  //复制通关路径
							answer_len = len + 1;
							biao = 0;
						}
						break;
					}
					map[x - 1][y] = 1;  //打通墙
					map[x - 2][y] = 1;
					x -= 2;
					stack[++len] = {x, y};  //储存节点
					break;
				}
				else if (map[x - 2][y] == 1 || x == 1)//该方向无可遍历的相邻节点
				{
					ke--;    //可遍历相邻节点数减少
					a0 = loc;
					continue;
				}
			}
			else if (loc == 1)  //loc==1，向右遍历
			{
				if (map[x][y + 2] != 1 && y < COL - 2)
				{
					if (map[x][y + 2] == 10)
					{
						map[x][y + 1] = 1;
						map[x][y + 2] = 1;
						y += 2;
						stack[++len] = {x, y};
						if (biao)
						{
							copy_(stack, len, answer);
							answer_len = len + 1;
							biao = 0;
						}
						break;
					}
					map[x][y + 1] = 1;
					map[x][y + 2] = 1;
					y += 2;
					stack[++len] = {x, y};
					break;
				}
				else if (map[x][y + 2] == 1 || y == COL - 2)
				{
					ke--;
					a1 = loc;
					continue;
				}
			}
			else if (loc == 2)  //loc==2,向下遍历
			{

				if (map[x + 2][y] != 1 && x < ROW - 2)
				{
					if (map[x + 2][y] == 10)
					{
						map[x + 1][y] = 1;
						map[x + 2][y] = 1;
						x += 2;
						stack[++len] = {x, y};
						if (biao)
						{
							copy_(stack, len, answer);
							answer_len = len + 1;
							biao = 0;
						}
						break;
					}
					map[x + 1][y] = 1;
					map[x + 2][y] = 1;
					x += 2;
					stack[++len] = {x, y};
					break;
				}
				else if (map[x + 2][y] == 1 || x == ROW - 2)
				{
					ke--;
					a2 = loc;
					continue;
				}
			}
			else if (loc == 3)   //loc==3,向左遍历
			{
				if (map[x][y - 2] != 1 && y > 1)
				{
					if (map[x][y - 2] == 10)
					{
						map[x][y - 1] = 1;
						map[x][y - 2] = 1;
						y -= 2;
						stack[++len] = {x, y};
						if (biao)
						{
							copy_(stack, len, answer);
							answer_len = len + 1;
							biao = 0;
						}
						break;
					}
					map[x][y - 1] = 1;
					map[x][y - 2] = 1;
					y -= 2;
					stack[++len] = {x, y};
					break;
				}
				else if (map[x][y - 2] == 1 || y == 1)
				{
					ke--;
					a3 = loc;
					continue;
				}
			}
		}
		if (ke == 0) // 该节点无可遍历的下一个节点，返回上一个节点
		{
			// 清除栈的数据
			stack[len] = {-1, -1}; 
			len--;
            // 返回上一个节点
			x = stack[len].x;
			y = stack[len].y;
		}
		
	}

	for (int i = 0; i < answer_len - 1; i++)  //将通关路径上的点的值均赋值为2
	{
		map[answer[i].x][answer[i].y] = 2;
		map[(answer[i].x + answer[i + 1].x) / 2][(answer[i].y + answer[i + 1].y) / 2] = 2;
	}
	map[1][1] = 9; // 终点位置，迷宫出口
}

int Playgame(int map[][COL])
{
	int my_x = MAP_COL - 1, my_y = MAP_ROW - 1, ans = 1;
	while (map[my_x][my_y] != 9)
	{
		if (ans == 1)
			drawmap(map, my_x, my_y);
		else
			draw_answer(map, my_x, my_y);
		map[MAP_ROW - 1][MAP_COL - 1] = 1;
		setfillcolor(BLUE);
		fillrectangle(my_y * 20, my_x * 20, (my_y + 1) * 20, (my_x + 1) * 20);
		char dir = _getch(); // w 向上移动一格，s 向下移动一格，a 向左移动一格，d 向右移动一格
		switch (dir)
		{
		case 'w':
		case 'W':
			if (map[my_x - 1][my_y] != 0 && my_x > 1)
			{
				my_x--;
			}
			break;
		case 'd':
		case 'D':
			if (map[my_x][my_y + 1] != 0 && my_y < MAP_COL)
			{
				my_y++;
			}
			break;
		case 's':
		case 'S':
			if (map[my_x + 1][my_y] != 0 && my_x < MAP_ROW)
			{
				my_x++;
			}
			break;
		case 'a':
		case 'A':
			if (map[my_x][my_y - 1] != 0 && my_y > 1)
			{
				my_y--;
			}
			break;
		case 27: // 按Esc键返回1，退回主菜单
			return 1;
			break;
		case 'l'://按L键显示通关路径
		case 'L':
			ans = -ans;
			break;
		default:
			break;
		}
	}
	// MessageBox(GetHWnd(), (LPCSTR) "恭喜你走出迷宫", (LPCSTR) "Title", MB_OK); //弹窗
	return 0;
}

void drawmap(int map[][COL], int my_x, int my_y)
{					  // 绘制地图
	BeginBatchDraw(); // 防频闪
	cleardevice();
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == 0)
			{ // 绘制墙
				setfillcolor(BLACK);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
			if (map[i][j] == 9)
			{ // 绘制终点
				setfillcolor(RED);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
		}
	}
	setfillcolor(BLUE);
	fillrectangle(my_y * 20, my_x * 20, (my_y + 1) * 20, (my_x + 1) * 20);
	EndBatchDraw(); // 防频闪
}

void draw_answer(int map[][COL], int my_x, int my_y)
{
	BeginBatchDraw(); // 防频闪
	cleardevice();

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == 0)
			{ // 绘制墙
				setfillcolor(BLACK);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
			if (map[i][j] == 9)
			{ // 绘制终点
				setfillcolor(RED);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
			if (map[i][j] == 2)
			{
				setfillcolor(GREEN);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
		}
	}
	setfillcolor(BLUE);
	fillrectangle(my_y * 20, my_x * 20, (my_y + 1) * 20, (my_x + 1) * 20);
	EndBatchDraw(); // 防频闪
}

void copy_(struct Stack stack[], int len, struct Stack *answer)
{
	for (int i = 0; i < len + 1; i++)
	{
		answer[i].x = stack[i].x;
		answer[i].y = stack[i].y;
	}
}

void draw_stack(struct Stack stack[], int len, int map[][COL])
{
	BeginBatchDraw(); // 防频闪
	cleardevice();

	for (int i = 0; i < len + 1; i++)
	{
		setfillcolor(GREEN);
		if(i==len) setfillcolor(RED);
		fillrectangle(stack[i].y * 20, stack[i].x * 20, (stack[i].y + 1) * 20, (stack[i].x + 1) * 20);
	}

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == 0)
			{ // 绘制墙
				setfillcolor(BLACK);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
			if (map[i][j] == 9)
			{ // 绘制终点
				setfillcolor(RED);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}

			if (map[i][j] == 10)
			{//绘制角色
				setfillcolor(BLUE);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
		}
	}
	EndBatchDraw(); // 防频闪
}
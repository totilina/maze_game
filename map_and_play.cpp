#include "my.h"

struct Stack
{
	int x;
	int y;
};

void Initmap(int map[][COL])
{

	int x = 1, y = 1;
	// int old_x = x, old_y = y;
	struct Stack stack[ROW * COL]; // 创建一个栈，模拟递归

	int len = -1; // 栈顶
	int ke = 2;	  // 一个节点接下来可遍历的节点数
	stack[++len] = {1, 1};

	while (len != -1)
	{
		ke = 4;
		int a1 = -1, a2 = -1, a3 = -1;
		while (ke > 0)
		{
			int loc = rand() % 4;
			if (loc == a1 || loc == a2 || loc == a3)
				continue;
			if (loc == 0)
			{
				if ((map[x - 2][y] == 0 && x > 2) || map[x - 2][y] == 10)
				{
					if (map[x - 2][y] == 10)
					{
						map[x - 1][y] = 1;
						x -= 2;
						break;
					}
					map[x - 1][y] = 1;
					map[x - 2][y] = 1;
					x -= 2;
					stack[++len] = {x, y};
					ke = 4;
					break;
				}
				else if (map[x - 2][y] == 1 || x == 3)
				{
					ke--;
					if (a1 != -1)
						a1 = loc;
					if (a2 != -1)
						a2 = loc;
					if (a3 != -1)
						a3 = loc;
					continue;
				}
			}
			else if (loc == 1)
			{
				if ((map[x][y + 2] == 0 && y < COL - 2) || map[x][y + 2] == 10)
				{
					if (map[x][y + 2] == 10)
					{
						map[x][y + 1] = 1;
						y += 2;
						break;
					}
					map[x][y + 1] = 1;
					map[x][y + 2] = 1;
					y += 2;
					stack[++len] = {x, y};
					ke = 4;
					break;
				}
				else if (map[x][y + 2] == 1 && y == COL - 2)
				{
					ke--;
					if (a1 != -1)
						a1 = loc;
					if (a2 != -1)
						a2 = loc;
					if (a3 != -1)
						a3 = loc;
					continue;
				}
			}
			else if (loc == 2)
			{

				if ((map[x + 2][y] == 0 && x < ROW - 2) || map[x + 2][y] == 10)
				{
					if (map[x + 2][y] == 10)
					{
						map[x + 1][y] = 1;
						x += 2;
						break;
					}
					map[x + 1][y] = 1;
					map[x + 2][y] = 1;
					x += 2;
					stack[++len] = {x, y};
					ke = 4;
					break;
				}
				else if (map[x + 2][y] == 1 || x == ROW - 2)
				{
					ke--;
					if (a1 != -1)
						a1 = loc;
					if (a2 != -1)
						a2 = loc;
					if (a3 != -1)
						a3 = loc;
					continue;
				}
			}
			else if (loc == 3)
			{
				if (map[x][y - 2] == 10)
				{
					map[x][y - 1] = 1;
					y -= 2;
					break;
				}
				if ((map[x][y - 2] == 0 && y > 1) || map[x][y - 1] == 10)
				{
					map[x][y - 1] = 1;
					map[x][y - 2] = 1;
					y -= 2;
					stack[++len] = {x, y};
					ke = 4;
					break;
				}
				else if (map[x][y - 2] == 1 || y == 1)
				{
					ke--;
					if (a1 != -1)
						a1 = loc;
					if (a2 != -1)
						a2 = loc;
					if (a3 != -1)
						a3 = loc;
					continue;
				}
			}
		}
		if (ke == 0) // 该节点无可遍历的下一个节点，返回上一个节点
		{
			len--;
			x = stack[len].x;
			y = stack[len].y;
		}
	}
}

int Playgame(int map[][COL]) // 控制角色移动的函数，w 向上移动一格，s 向下移动一格，a 向左移动一格，d 向右移动一格
{
	int my_x = MAP_COL - 1, my_y = MAP_ROW - 1;
	while (map[my_x][my_y] != 9)
	{
		drawmap(map);
		map[MAP_ROW - 1][MAP_COL - 1] = 1;
		setfillcolor(BLUE);
		fillrectangle(my_y * 20, my_x * 20, (my_y + 1) * 20, (my_x + 1) * 20);
		char dir = _getch();
		switch (dir)
		{
		case 'w':
		case 'W':
			if ((map[my_x - 1][my_y] == 1 && my_x > 1) || map[my_x - 1][my_y] == 9)
			{
				my_x--;
			}
			break;
		case 'd':
		case 'D':
			if ((map[my_x][my_y + 1] == 1 && my_y < MAP_COL) || map[my_x][my_y + 1] == 9)
			{
				my_y++;
			}
			break;
		case 's':
		case 'S':
			if ((map[my_x + 1][my_y] == 1 && my_x < MAP_ROW) || map[my_x + 1][my_y] == 9)
			{
				my_x++;
			}
			break;
		case 'a':
		case 'A':
			if ((map[my_x][my_y - 1] == 1 && my_y > 1) || map[my_x][my_y - 1] == 9)
			{
				my_y--;
			}
			break;
		case 27: // 按Esc键返回1，退回主菜单
			return 1;
			break;
		default:
			break;
		}
	}
	// MessageBox(GetHWnd(), (LPCSTR)"恭喜你走出迷宫", (LPCSTR)"Title", MB_OK);
	return 0;
}

void drawmap(int map[][COL])
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
	EndBatchDraw(); // 防频闪
}
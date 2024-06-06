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
	struct Stack stack[ROW * COL]; // ����һ��ջ��ģ��ݹ�

	int len = -1; // ջ��
	int ke = 2;	  // һ���ڵ�������ɱ����Ľڵ���
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
		if (ke == 0) // �ýڵ��޿ɱ�������һ���ڵ㣬������һ���ڵ�
		{
			len--;
			x = stack[len].x;
			y = stack[len].y;
		}
	}
}

int Playgame(int map[][COL]) // ���ƽ�ɫ�ƶ��ĺ�����w �����ƶ�һ��s �����ƶ�һ��a �����ƶ�һ��d �����ƶ�һ��
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
		case 27: // ��Esc������1���˻����˵�
			return 1;
			break;
		default:
			break;
		}
	}
	// MessageBox(GetHWnd(), (LPCSTR)"��ϲ���߳��Թ�", (LPCSTR)"Title", MB_OK);
	return 0;
}

void drawmap(int map[][COL])
{					  // ���Ƶ�ͼ
	BeginBatchDraw(); // ��Ƶ��
	cleardevice();
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == 0)
			{ // ����ǽ
				setfillcolor(BLACK);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
			if (map[i][j] == 9)
			{ // �����յ�
				setfillcolor(RED);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
		}
	}
	EndBatchDraw(); // ��Ƶ��
}
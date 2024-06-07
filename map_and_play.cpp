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
	struct Stack answer[ROW * COL];

	int len = -1; // ջ��
	int ke = 4;	  // һ���ڵ�������ɱ����Ľڵ���
	stack[++len] = {1, 1};

	map[1][1] = 1;
	int biao = 1, answer_len = 0;

	while (len != -1)
	{
		ke = 4;
		int a0 = -1, a1 = -1, a2 = -1, a3 = -1;

		int old_loc = -1;

		while (ke > 0)
		{
			int loc = rand() % 4;
			if (loc == a0 || loc == a1 || loc == a2 || loc == a3 || loc == old_loc)
				continue;
			if (loc == 0) // loc==0,���±���
			{
				if (map[x - 2][y] != 1 && x > 1)
				{
					if (map[x - 2][y] == 10)
					{
						map[x - 1][y] = 1;
						map[x-2][y]=1;
						x -= 2;
						stack[++len] = {x, y};
						if (biao)
						{
							copy_(stack, len, answer);
							answer_len = len + 1;
							biao = 0;
						}
						old_loc = loc;
						break;
					}
					map[x - 1][y] = 1;
					map[x - 2][y] = 1;
					x -= 2;
					stack[++len] = {x, y};
					old_loc = loc;
					break;
				}
				else if (map[x - 2][y] == 1 || x == 1)
				{
					ke--;
					a0 = loc;
					continue;
				}
			}
			else if (loc == 1)
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
						old_loc = loc;
						break;
					}
					map[x][y + 1] = 1;
					map[x][y + 2] = 1;
					y += 2;
					stack[++len] = {x, y};
					old_loc = loc;
					break;
				}
				else if (map[x][y + 2] == 1 || y == COL - 2)
				{
					ke--;
					a1 = loc;
					continue;
				}
			}
			else if (loc == 2)
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
						old_loc = loc;
					}
					map[x + 1][y] = 1;
					map[x + 2][y] = 1;
					x += 2;
					stack[++len] = {x, y};
					old_loc = loc;
					break;
				}
				else if (map[x + 2][y] == 1 || x == ROW - 2)
				{
					ke--;
					a2 = loc;
					continue;
				}
			}
			else if (loc == 3)
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
						old_loc = loc;
						break;
					}
					map[x][y - 1] = 1;
					map[x][y - 2] = 1;
					y -= 2;
					stack[++len] = {x, y};
					old_loc = loc;
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
		if (ke == 0) // �ýڵ��޿ɱ�������һ���ڵ㣬������һ���ڵ�
		{
			stack[len] = {-1, -1}; // ���ջ������
			len--;
			x = stack[len].x;
			y = stack[len].y; // ������һ���ڵ�
		}
		draw_stack(stack, len, map);
		_getch();
	}

	for (int i = 0; i < answer_len - 1; i++)
	{
		map[answer[i].x][answer[i].y] = 2;
		map[(answer[i].x + answer[i + 1].x) / 2][(answer[i].y + answer[i + 1].y) / 2] = 2;
	}
	map[1][1] = 9; // �յ�λ�ã��Թ�����
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
		case 27: // ��Esc������1���˻����˵�
			return 1;
			break;
		case 'l':
		case 'L':
			draw_answer(map);
			_getch();
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

void draw_answer(int map[][COL])
{
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

			if (map[i][j] == 2)
			{
				setfillcolor(GREEN);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
		}
	}
	EndBatchDraw(); // ��Ƶ��
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
	BeginBatchDraw(); // ��Ƶ��
	cleardevice();

	for (int i = 0; i < len + 1; i++)
	{
		setfillcolor(GREEN);
		fillrectangle(stack[i].y * 20, stack[i].x * 20, (stack[i].y + 1) * 20, (stack[i].x + 1) * 20);
	}

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

			// if (map[i][j] == 2)
			// {
			// 	setfillcolor(GREEN);
			// 	fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			// }
		}
	}
	EndBatchDraw(); // ��Ƶ��
}
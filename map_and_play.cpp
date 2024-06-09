#include "my.h"

struct Stack // ����ڵ��ջ
{
	int x;   //�ڵ������
	int y;   //�ڵ�������
};

void Initmap(int map[][COL], int dem)
{

	int x = 1, y = 1;
	// int old_x = x, old_y = y;
	struct Stack stack[ROW * COL / 2 + 1]; // ����һ��ջ��ģ��ݹ�
	struct Stack answer[ROW * COL / 2 + 1];

	int len = -1; // ջ��
	int ke = 4;	  // һ���ڵ�ɱ��������ڽڵ���
	stack[++len] = {1, 1};

	map[1][1] = 1;
	int biao = 1, answer_len = 0; // biao���Ƿ��ҵ���ڵı�ǣ�answer_len��ͨ��·���ĳ���

	while (len != -1)
	{
		ke = 4;
		int a0 = -1, a1 = -1, a2 = -1, a3 = -1;

		if (dem)    //�ж��Ƿ�����Թ�������ʾ
		{
			draw_stack(stack, len, map);
			if(_getch()==27) break;
		}

		while (ke > 0)  //�Ըýڵ��Ƿ��пɱ��������ڽڵ���Ϊѭ������
		{
			int loc = rand() % 4;     //���������
			if (loc == a0 || loc == a1 || loc == a2 || loc == a3) //��ֹ���������ظ�
				continue;
			if (loc == 0) // loc==0,���±���
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
							copy_(stack, len, answer);  //����ͨ��·��
							answer_len = len + 1;
							biao = 0;
						}
						break;
					}
					map[x - 1][y] = 1;  //��ͨǽ
					map[x - 2][y] = 1;
					x -= 2;
					stack[++len] = {x, y};  //����ڵ�
					break;
				}
				else if (map[x - 2][y] == 1 || x == 1)//�÷����޿ɱ��������ڽڵ�
				{
					ke--;    //�ɱ������ڽڵ�������
					a0 = loc;
					continue;
				}
			}
			else if (loc == 1)  //loc==1�����ұ���
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
			else if (loc == 2)  //loc==2,���±���
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
			else if (loc == 3)   //loc==3,�������
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
		if (ke == 0) // �ýڵ��޿ɱ�������һ���ڵ㣬������һ���ڵ�
		{
			// ���ջ������
			stack[len] = {-1, -1}; 
			len--;
            // ������һ���ڵ�
			x = stack[len].x;
			y = stack[len].y;
		}
		
	}

	for (int i = 0; i < answer_len - 1; i++)  //��ͨ��·���ϵĵ��ֵ����ֵΪ2
	{
		map[answer[i].x][answer[i].y] = 2;
		map[(answer[i].x + answer[i + 1].x) / 2][(answer[i].y + answer[i + 1].y) / 2] = 2;
	}
	map[1][1] = 9; // �յ�λ�ã��Թ�����
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
		char dir = _getch(); // w �����ƶ�һ��s �����ƶ�һ��a �����ƶ�һ��d �����ƶ�һ��
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
		case 'l'://��L����ʾͨ��·��
		case 'L':
			ans = -ans;
			break;
		default:
			break;
		}
	}
	// MessageBox(GetHWnd(), (LPCSTR) "��ϲ���߳��Թ�", (LPCSTR) "Title", MB_OK); //����
	return 0;
}

void drawmap(int map[][COL], int my_x, int my_y)
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
	setfillcolor(BLUE);
	fillrectangle(my_y * 20, my_x * 20, (my_y + 1) * 20, (my_x + 1) * 20);
	EndBatchDraw(); // ��Ƶ��
}

void draw_answer(int map[][COL], int my_x, int my_y)
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
	setfillcolor(BLUE);
	fillrectangle(my_y * 20, my_x * 20, (my_y + 1) * 20, (my_x + 1) * 20);
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
		if(i==len) setfillcolor(RED);
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

			if (map[i][j] == 10)
			{//���ƽ�ɫ
				setfillcolor(BLUE);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
		}
	}
	EndBatchDraw(); // ��Ƶ��
}
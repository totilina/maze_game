#include "my.h"

int Main_interface(int set)
{
	//  initgraph(COL * SIZE, ROW * SIZE);
	IMAGE bgImage;
	switch (set)
	{
	case 0:
		// ���ñ���Ϊһ��ͼƬ

		loadimage(&bgImage, _T("background.png"), ROW * SIZE, COL * SIZE); // ����ͼƬ

		putimage(0, 0, &bgImage); // ��ʾͼƬ
		setbkcolor(RGB(255, 248, 220));
		break;
	case 1:
		// ���ñ�����ɫΪ�װ�ɫ
		// setbkcolor(BLUE);
		setbkcolor(RGB(255, 250, 240)); // ƫ��ɫ 255 ,239 ,213 �� ƫ��ɫ  255 ,248 ,220 ,��׼�װ�ɫ 255 ,250 ,240
		cleardevice();
		break;
	case 2:
		setbkcolor(RGB(255, 239, 213)); // ƫ��ɫ 255 ,239 ,213 �� ƫ��ɫ  255 ,248 ,220 ,��׼�װ�ɫ 255 ,250 ,240
		cleardevice();
		break;
	case 3:
		setbkcolor(RGB(255, 248, 220)); // ƫ��ɫ 255 ,239 ,213 �� ƫ��ɫ  255 ,248 ,220 ,��׼�װ�ɫ 255 ,250 ,240
		cleardevice();
		break;
	default:
		break;
	}

	// �����ı���ɫ������ʹ�С
	settextcolor(RGB(255, 69, 0)); // �����ı���ɫ
	settextstyle(60, 0, "΢���ź�");
	setbkmode(TRANSPARENT); // �����ı�����͸��

	// ����
	const char *title = "�޾��Թ�ð��";									 // ��������
	int title_x = (COL * SIZE - textwidth(title)) / 2;					 // ���������
	int title_y = (ROW * SIZE - textheight(title)) / 2 - ROW *5/ 12 * SIZE; // ����������
	outtextxy(title_x, title_y, title);									 // ��ʾ����

	// �����ĸ����ܼ�(��ť)
	settextstyle(40, 0, "΢���ź�"); // ���ܼ������С
	setbkmode(TRANSPARENT);
	Button buttons[5] = {
		{title_x + 3 * SIZE, title_y + 6 * SIZE, 8 * SIZE, 4 * SIZE, "��ʼ��Ϸ"},
		{title_x + 3 * SIZE, title_y + 12 * SIZE, 8 * SIZE, 4 * SIZE, "��Ϸ˵��"},
		{title_x + 3 * SIZE, title_y + 18 * SIZE, 8 * SIZE, 4 * SIZE, "��Ϸ����"},
		{title_x + 3 * SIZE, title_y + 24 * SIZE, 8 * SIZE, 4 * SIZE, "�Թ�������ʾ"},
		{title_x + 3 * SIZE, title_y + 30 * SIZE, 8 * SIZE, 4 * SIZE, "�˳���Ϸ"}};

	// ���ư�ť
	for (int i = 0; i < 5; i++)
	{
		if(i==3) settextstyle(30, 0, "΢���ź�");
		else settextstyle(40, 0, "΢���ź�");
		drawButton(buttons[i]);
	}

	while (true)
	{
		// ��ȡ�������Ϣ
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();	// ��ȡ�������Ϣ
			if (msg.uMsg == WM_LBUTTONDOWN) // WM_LBUTTONDOWN ��һ�� Windows ��Ϣ����ʾ������������
			{
				for (int i = 0; i < 5; i++)
				{
					if (isMouseOnButton(buttons[i], msg.x, msg.y))
					{
						// �����Ӧ
						return i;
					}
				}
			}
		}
	}
}

void drawButton(Button btn)
{
	// ���ƾ��ΰ�ť
	rectangle(btn.x, btn.y, btn.x + btn.width, btn.y + btn.height);
	// �����ı�λ�ã�ʹ�����
	int text_x = btn.x + (btn.width - textwidth(btn.text)) / 2;
	int text_y = btn.y + (btn.height - textheight(btn.text)) / 2;
	outtextxy(text_x, text_y, btn.text);
}

bool isMouseOnButton(Button btn, int mouseX, int mouseY) // �ж������λ���Ƿ��ڰ�ť������
{
	return mouseX >= btn.x && mouseX <= btn.x + btn.width && mouseY >= btn.y && mouseY <= btn.y + btn.height;
}

void Game_description()
{
	cleardevice();
	settextcolor(BLACK);
	settextstyle(40, 0, "����");
	// settextstyle(40, 0, "����");
	const char *text1 = "��ӭ���������Թ�ð����Ϸ�������ʼ��Ϸ�����������һ���Թ����߳����ں���������һ���Թ����Թ������޾�������ÿ���Թ����ǲ�ͬ�ģ������һֱͨ���Թ������������Ҳ�����˳���\nע����Esc���������˵�\n    ��L�����Բ鿴�Թ��𰸣��ٴΰ�L�������˳���ģʽ\n���������������������Ϸ���淨�ɡ�";
	RECT r = {50, 50, 680, 700};
	drawtext(_T(text1), &r, DT_WORDBREAK);
	settextstyle(20, 0, "����");
	outtextxy(ROW * SIZE - 15 * SIZE, COL * SIZE - 10 * SIZE, "(�������������λ�ü���...)");
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				break;
			}
		}
	}
	// _getch();
	cleardevice();

	setfillcolor(RED);
	fillrectangle(10, 10, 30, 30);
	RECT red = {30, 10, 680, 700};
	settextstyle(20, 0, "����");
	// settextstyle(20, 0, "����");
	const char *text2 = "���ǳ���";
	drawtext(_T(text2), &red, DT_WORDBREAK);

	setfillcolor(BLACK);
	fillrectangle(10, 80, 30, 100);
	RECT black = {30, 80, 639, 479};
	const char *text3 = "����ǽ�����޷�����";
	drawtext(_T(text3), &black, DT_WORDBREAK);

	setfillcolor(BLUE);
	fillrectangle(10, 120, 30, 140);
	RECT blue = {30, 120, 639, 479};
	const char *text4 = "����������Ľ�ɫ����������������Ϥ��WASD����W���������ƶ�һ��A���������ƶ�һ��S���������ƶ�һ��D���������ƶ�һ��\nͼ����ɫ��·�Ǵ�·�ߣ���L����ʾ\n������Ľ�ɫ�ִ���ڰ�(����ͼƬ�����ο�)";
	drawtext(_T(text4), &blue, DT_WORDBREAK);

	IMAGE bgImage;
	loadimage(&bgImage, _T("maze.png"), ROW / 2 * SIZE, COL / 2 * SIZE); // ����ͼƬ

	putimage(30, 200, &bgImage); // ��ʾͼƬ

	outtextxy(ROW * SIZE - 20 * SIZE, COL * SIZE - 10 * SIZE, "(�������������λ�÷������˵�...)");
	// _getch();
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				break;
			}
		}
	}
}

int Du_set(int *set)
{
	FILE *fp;
	char filename[] = "settings.txt";
	char buffer[256];

	// ���ļ�
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("Error opening file");
		return -1;
	}

	// ��ȡ�ļ�
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		*set = buffer[0] - '0';
	}

	// �ر��ļ�
	fclose(fp);
	return 0;
}

int Game_settings(int *set)
{
	setbkcolor(RGB(139, 137, 137));
	cleardevice();
	settextstyle(40, 0, "΢���ź�");
	setbkmode(TRANSPARENT);

	outtextxy(100, 100, "�����Թ���������");

	Button buttons[4] = {
		{100 + 3 * SIZE, 100 + 6 * SIZE, 8 * SIZE, 4 * SIZE, "�Թ�ͼƬ����"},
		{100 + 3 * SIZE, 100 + 12 * SIZE, 8 * SIZE, 4 * SIZE, "��һ�װ�ɫ����"},
		{100 + 3 * SIZE, 100 + 18 * SIZE, 8 * SIZE, 4 * SIZE, "��һ�Ȼ�ɫ����"},
		{100 + 3 * SIZE, 100 + 24 * SIZE, 8 * SIZE, 4 * SIZE, "��һ��ɫ����"}};

	// ���ư�ť
	for (int i = 0; i < 4; i++)
	{
		drawButton(buttons[i]);
	}
	while (true)
	{
		// ��ȡ�������Ϣ
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();	// ��ȡ�������Ϣ
			if (msg.uMsg == WM_LBUTTONDOWN) // WM_LBUTTONDOWN ��һ�� Windows ��Ϣ����ʾ������������
			{
				for (int i = 0; i < 4; i++)
				{
					if (isMouseOnButton(buttons[i], msg.x, msg.y))
					{
						// �����Ӧ
						*set = i;
						FILE *fp;
						char filename[] = "settings.txt";

						// ���ļ�����д��
						fp = fopen(filename, "w");
						if (fp == NULL)
						{
							perror("Error opening file");
							return -1;
						}

						char cset[2];
						cset[0] = '0' + *set;
						cset[1] = '\0';
						// д���ļ�
						fprintf(fp, cset);

						// �ر��ļ�
						fclose(fp);
						return *set;
					}
				}
			}
		}
	}
}

void Dem_des(){
	cleardevice();
	settextcolor(BLACK);
	settextstyle(35, 0, "����");
	// settextstyle(40, 0, "����");
	const char *text1 = "���ڼ����DFS�㷨����⣬�������ôһ��ģʽ�������ģʽ�����ɸ��Թ����㷨���ӻ���ϣ�����ģʽ���Ը����ⷽ�������Ȥ����һ��������\n���������Ҽ򵥽���һ�����ģʽ���ս������ģʽ��չ�ֳ�����Թ���ԭʼ������(����ȫ�Ǻںڵ�ǽ)�������㰴�³�Esc��������һ���������㷨�������ִ��һ������ɫ�ķ�����ջ�Ľڵ㣬��������㵽��ɫ�ڵ���;�辭���Ľڵ㣬�ҵ��Թ���ں����нڵ�����������ͨ��·��������ɫ�����ǵ�ǰ����λ�ã��Թ����ɺú�Ҳ���Լ�������Ϸ��������;��Esc��������ֹ���ɣ��ٰ�һ��Esc�����Է������˵�\nע��ֻ�������Ϊ�����ĵ���ǽڵ㣬���ڵ���Ǳ���ͨ��ǽ�������ڵ�����һ��·";
	RECT r = {50, 50, 700, 800};
	drawtext(_T(text1), &r, DT_WORDBREAK);
	settextstyle(20, 0, "����");
	outtextxy(ROW * SIZE - 15 * SIZE, COL * SIZE - 5 * SIZE, "(�������������λ�ü���...)");
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				break;
			}
		}
	}
}
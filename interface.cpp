#include "my.h"





int Main_interface()
{
	//  initgraph(COL * SIZE, ROW * SIZE);

	// 设置背景颜色为米白色
	// setbkcolor(BLUE);
	setbkcolor(RGB(255, 239, 213)); // 偏橙色 255 ,239 ,213 ， 偏黄色  255 ,248 ,220 ,标准米白色 255 ,250 ,240
	cleardevice();

	//设置背景为一张图片
	IMAGE bgImage;
	loadimage(&bgImage, _T("background.png"), ROW * SIZE, COL * SIZE);//加载图片

	putimage(0, 0, &bgImage);                                  //显示图片

	// 设置文本颜色、字体和大小
	settextcolor(BLUE); // 设置文本颜色为黑色
	settextstyle(60, 0, "微软雅黑");
	setbkmode(TRANSPARENT); // 设置文本背景透明

	// 标题
	const char *title = "无尽迷宫冒险";									 // 标题内容
	int title_x = (COL * SIZE - textwidth(title)) / 2;					 // 标题横坐标
	int title_y = (ROW * SIZE - textheight(title)) / 2 - ROW / 3 * SIZE; // 标题纵坐标
	outtextxy(title_x, title_y, title);									 // 显示标题

	// 定义四个功能键(按钮)
	settextstyle(40, 0, "微软雅黑"); // 功能键字体大小
	setbkmode(TRANSPARENT);
	Button buttons[4] = {
		{title_x + 3 * SIZE, title_y + 6 * SIZE, 8 * SIZE, 4 * SIZE, "开始游戏"},
		{title_x + 3 * SIZE, title_y + 12 * SIZE, 8 * SIZE, 4 * SIZE, "游戏说明"},
		{title_x + 3 * SIZE, title_y + 18 * SIZE, 8 * SIZE, 4 * SIZE, "游戏设置(暂不可用)"},
		{title_x + 3 * SIZE, title_y + 24 * SIZE, 8 * SIZE, 4 * SIZE, "退出游戏"}};

	// 绘制按钮
	for (int i = 0; i < 4; i++)
	{
		if(i==2) settextstyle(20, 0, "微软雅黑");
		else settextstyle(40, 0, "微软雅黑");
		
		drawButton(buttons[i]);
	}
	while (true)
	{
		// 获取鼠标点击信息
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();	// 获取鼠标点击信息
			if (msg.uMsg == WM_LBUTTONDOWN) // WM_LBUTTONDOWN 是一个 Windows 消息，表示鼠标左键被按下
			{
				for (int i = 0; i < 4; i++)
				{
					if (isMouseOnButton(buttons[i], msg.x, msg.y))
					{
						// 点击响应
						switch (i)
						{
						case 0:
							return i;
							break;
						case 1:
							return i;
							break;
						case 2:
							return i;
							break;
						case 3:
							return i;
							break;
						}
					}
				}
			}
		}
	}
}

void drawButton(Button btn)
{
	// 绘制矩形按钮
	rectangle(btn.x, btn.y, btn.x + btn.width, btn.y + btn.height);
	// 计算文本位置，使其居中
	int text_x = btn.x + (btn.width - textwidth(btn.text)) / 2;
	int text_y = btn.y + (btn.height - textheight(btn.text)) / 2;
	outtextxy(text_x, text_y, btn.text);
}

bool isMouseOnButton(Button btn, int mouseX, int mouseY) // 判断鼠标点击位置是否在按钮区域内
{
	return mouseX >= btn.x && mouseX <= btn.x + btn.width && mouseY >= btn.y && mouseY <= btn.y + btn.height;
}

void Game_description()
{
	cleardevice();
	settextstyle(40, 0, "楷书");
	// settextstyle(40, 0, "宋体");
	const char *text1 = "欢迎来到无限迷宫冒险游戏，点击开始游戏，会随机生成一个迷宫，走出出口后会继续生成一个迷宫，迷宫无穷无尽，而且每个迷宫都是不同的，你可以一直通关迷宫，如果玩累了也可以退出。\n注：按Esc键返回主菜单\n    按L键可以查看迷宫答案\n下面让我来告诉你这个游戏的玩法吧。";
	RECT r = {50, 50, 680, 700};
	drawtext(_T(text1), &r, DT_WORDBREAK);
	settextstyle(20, 0, "楷书");
	outtextxy(ROW * SIZE - 15 * SIZE, COL * SIZE - 10 * SIZE, "(鼠标左键点击任意位置继续...)");
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN){
				break;
			}
		}
	}
	// _getch();
	cleardevice();

	setfillcolor(RED);
	fillrectangle(10, 10, 30, 30);
	RECT red = {30, 10, 680, 700};
	settextstyle(20, 0, "楷书");
	// settextstyle(20, 0, "宋体");
	const char *text2 = "这是出口";
	drawtext(_T(text2), &red, DT_WORDBREAK);

	setfillcolor(BLACK);
	fillrectangle(10, 80, 30, 100);
	RECT black = {30, 80, 639, 479};
	const char *text3 = "这是墙，你无法穿过";
	drawtext(_T(text3), &black, DT_WORDBREAK);

	setfillcolor(BLUE);
	fillrectangle(10, 120, 30, 140);
	RECT blue = {30, 120, 639, 479};
	const char *text4 = "这是你操作的角色，操作方法还是熟悉的WASD键，W键是向上移动一格，A键是向左移动一格，S键是向下移动一格，D键是向右移动一格\n操作你的角色抵达出口吧(下面图片仅供参考，玩游戏请返回主界面点击开始游戏)";
	drawtext(_T(text4), &blue, DT_WORDBREAK);

	IMAGE bgImage;
	loadimage(&bgImage, _T("maze.png"), ROW / 2 * SIZE, COL / 2 * SIZE); // 加载图片

	putimage(30, 200, &bgImage); // 显示图片

	outtextxy(ROW * SIZE - 20 * SIZE, COL * SIZE - 10 * SIZE, "(鼠标左键点击任意位置返回主菜单...)");
	// _getch();
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN){
				break;
			}
		}
	}
}
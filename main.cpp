#include "my.h"


int main()
{
	srand((unsigned)time(NULL));
	initgraph(COL * SIZE, ROW * SIZE + 2 * SIZE);

	while (true)
	{

		int flag = Main_interface();

		switch (flag)
		{
		case 0:
			while (true)
			{
				int map[ROW][COL] = {0};
				map[1][1] = 9;						// 终点位置，迷宫出口
				map[MAP_ROW - 1][MAP_COL - 1] = 10; // 角色位置，起点
				Initmap(map);
				if (Playgame(map))
					break;
				;
			}
			break;

		case 1:
			Game_description();
			break;
		case 2:
			// Game_settings();
			break;
		case 3:
			return 0;
			break;
		default:
			break;
		}
	}
	closegraph();

	return 0;
}

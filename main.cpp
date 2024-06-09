#include "my.h"

int main()
{
	srand((unsigned)time(NULL));
	initgraph(COL * SIZE, ROW * SIZE);

	int set = 0;
	Du_set(&set); // 读取设置信息

	while (true)
	{
		// 绘制主界面
		int flag = Main_interface(set);

		switch (flag)
		{
		case 0:
			while (true)
			{
				int map[ROW][COL] = {0};
				map[MAP_ROW - 1][MAP_COL - 1] = 10;
				int diao=0;
				Initmap(map,diao);
				if (Playgame(map))
					break;
			}
			break;

		case 1:
			Game_description();
			break;
		case 2:
			Game_settings(&set);
			break;
		case 3:
		    while (true)
			{
				Dem_des();
				int map[ROW][COL] = {0};
				map[MAP_ROW - 1][MAP_COL - 1] = 10;
				int diao=1;
				Initmap(map,diao);
				if (Playgame(map))
					break;
			}
            break;
		case 4:
			return 0;
			break;
		default:
			break;
		}
	}
	closegraph();
	return 0;
}

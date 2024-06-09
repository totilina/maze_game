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
		case 0:                 //开始游戏
			while (true)
			{
				int map[ROW][COL] = {0};
				map[MAP_ROW - 1][MAP_COL - 1] = 10;
				Initmap(map,false);
				if (Playgame(map))
					break;
			}
			break;

		case 1:                 //游戏说明
			Game_description();
			break;
		case 2:                 //游戏设置
			Game_settings(&set);
			break;
		case 3:                 //生成演示
		    while (true)
			{
				Dem_des();
				int map[ROW][COL] = {0};
				map[MAP_ROW - 1][MAP_COL - 1] = 10;
				Initmap(map,true);
				if (Playgame(map))
					break;
			}
            break;
		case 4:                 //退出游戏
			return 0;
			break;
		default:
			break;
		}
	}
	closegraph();          //关闭窗口
	return 0;
}

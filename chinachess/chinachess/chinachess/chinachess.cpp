#include"chinachess.h"

Chess mychess[10][9];
MouseEventState MEState = {-1,-1,-1,-1,BEGIN};
MOUSEMSG Mmsg;

//重置鼠标点击坐标，为了防止一些小bug，你可以删除这个试一下,不管有没有移动都要在if后加上这个
void ResetMEState()
{
	MEState.pBegin.x = -1;
	MEState.pBegin.y = -1;
	MEState.pEnd.x = -1;
	MEState.pEnd.y = -1;
}
//延时
void MyDelay(int sec)
{
	clock_t start = clock();
	clock_t lay = (clock_t)sec * CLOCKS_PER_SEC;
	while ((clock() - start) < lay);
}

//游戏的初始化
void GameInit()
{
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			if (i == 0)
			{
				if (j < 5)
				{
					mychess[i][j].chessName = redChess[j];
					mychess[i][j].color = 'R';

					mychess[i + 9][j].chessName = blackChess[j];
					mychess[i + 9][j].color = 'B';

				}
				else if (j >= 5)
				{
					mychess[i][j].chessName = redChess[8 - j];
					mychess[i][j].color = 'R';

					mychess[i + 9][j].chessName = blackChess[8 - j];
					mychess[i + 9][j].color = 'B';

				}
			}
			if (i == 2 && (j == 1 || j == 7))
			{
				mychess[i][j].chessName = redChess[5];
				mychess[i][j].color = 'R';

				mychess[i + 5][j].chessName = blackChess[5];
				mychess[i + 5][j].color = 'B';

			}
			if (i == 3 && (j % 2 == 0))
			{
				mychess[i][j].chessName = redChess[6];
				mychess[i][j].color = 'R';

				mychess[i + 3][j].chessName = blackChess[6];
				mychess[i + 3][j].color = 'B';

			}
			//统一初始化，
			mychess[i][j].x = ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + j * (INTERVAL_COL);
			mychess[i][j].y = ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + i * (INTERVAL_ROW);
			mychess[i][j].flag_through_river = false;
			mychess[i][j].flag_die = false;
			mychess[i][j].flag_choosing = false;
		}
	}
}
//改变棋子信息
void ChangeChessMessage()
{
	mychess[MEState.pEnd.x][MEState.pEnd.y].chessName = mychess[MEState.pBegin.x][MEState.pBegin.y].chessName;
	mychess[MEState.pEnd.x][MEState.pEnd.y].color = mychess[MEState.pBegin.x][MEState.pBegin.y].color;
	mychess[MEState.pBegin.x][MEState.pBegin.y].chessName = NONE;
	mychess[MEState.pBegin.x][MEState.pBegin.y].color = '\0';
	if (mychess[MEState.pEnd.x][MEState.pEnd.y].color == 'R' && MEState.pEnd.x > 4)
	{
		mychess[MEState.pBegin.x][MEState.pBegin.y].flag_through_river = false;
		mychess[MEState.pEnd.x][MEState.pEnd.y].flag_through_river = true;
	}
	else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color == 'R' && MEState.pEnd.x <= 4)
	{
		mychess[MEState.pBegin.x][MEState.pBegin.y].flag_through_river = false;
		mychess[MEState.pEnd.x][MEState.pEnd.y].flag_through_river = false;
	}
	if (mychess[MEState.pEnd.x][MEState.pEnd.y].color == 'B' && MEState.pEnd.x < 5)
	{
		mychess[MEState.pBegin.x][MEState.pBegin.y].flag_through_river = false;
		mychess[MEState.pEnd.x][MEState.pEnd.y].flag_through_river = true;
	}
	else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color == 'B' && MEState.pEnd.x >= 5)
	{
		mychess[MEState.pBegin.x][MEState.pBegin.y].flag_through_river = false;
		mychess[MEState.pEnd.x][MEState.pEnd.y].flag_through_river = false;
	}
}

//控制台输出棋盘
void ShowGameConsole()
{
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			cout << "(" << i << "," << j << ")" << ":" << "(" << mychess[i][j].x << "," << mychess[i][j].y << ")" << ":";
			cout << chessName[mychess[i][j].chessName] << " " << mychess[i][j].flag_through_river << " " << mychess[i][j].color << " " << mychess[i][j].flag_die << " ";
		}
		cout << endl;
		cout << endl;
	}
}
//棋子功能
bool Che()
{
	//直行判断
	if (MEState.pBegin.x == MEState.pEnd.x && MEState.pBegin.y != MEState.pEnd.y ||
		MEState.pBegin.x != MEState.pEnd.x && MEState.pBegin.y == MEState.pEnd.y)
	{
		//开始先判断中间是否有障碍物
		
		if (MEState.pBegin.y != MEState.pEnd.y)//x相等
		{
			int times = abs(MEState.pEnd.y - MEState.pBegin.y);
			for (int i = 1; i < times; i++)
			{
				if (MEState.pEnd.y - MEState.pBegin.y > 0)//--->
				{
					if (mychess[MEState.pBegin.x][MEState.pBegin.y + i].chessName == NONE)
						continue;
					else
						return false;
				}
				else if (MEState.pEnd.y - MEState.pBegin.y < 0)//<---
				{
					if (mychess[MEState.pBegin.x][MEState.pBegin.y - i].chessName == NONE)
						continue;
					else
						return false;
				}
			}
		}
		else if (MEState.pBegin.x != MEState.pEnd.x) //y相等
		{
			int times = abs(MEState.pEnd.x - MEState.pBegin.x);
			for (int i = 1; i < times; i++)
			{
				if (MEState.pEnd.x - MEState.pBegin.x > 0)//--->
				{
					if (mychess[MEState.pBegin.x + i][MEState.pBegin.y].chessName == NONE)
						continue;
					else
						return false;
				}
				else if (MEState.pEnd.x - MEState.pBegin.x < 0)//<----
				{
					if (mychess[MEState.pBegin.x - i][MEState.pBegin.y].chessName == NONE)
						continue;
					else
						return false;
				}
			}
		}
		//判断完之间的无障碍物i == times，再判断最后一个位置的信息
		if (mychess[MEState.pEnd.x][MEState.pEnd.y].chessName == NONE) //移动位置
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //吃
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else //否则不能吃
		{
			return false;
		}
	}
}

bool Pao()
{
	//直行判断
	if (MEState.pBegin.x == MEState.pEnd.x && MEState.pBegin.y != MEState.pEnd.y ||
		MEState.pBegin.x != MEState.pEnd.x && MEState.pBegin.y == MEState.pEnd.y)
	{
		//开始先判断中间是否有障碍物
		int obstacleNum = 0;
		if (MEState.pBegin.y != MEState.pEnd.y)//x相等
		{
			int times = abs(MEState.pEnd.y - MEState.pBegin.y);
			for (int i = 1; i < times; i++)
			{
				if (MEState.pEnd.y - MEState.pBegin.y > 0)//--->
				{
					if (mychess[MEState.pBegin.x][MEState.pBegin.y + i].chessName == NONE)
						continue;
					else
					{
						obstacleNum++;
					}
				}
				else if (MEState.pEnd.y - MEState.pBegin.y < 0)//<---
				{
					if (mychess[MEState.pBegin.x][MEState.pBegin.y - i].chessName == NONE)
						continue;
					else
					{
						obstacleNum++;
					}
				}
			}
		}
		else if (MEState.pBegin.x != MEState.pEnd.x) //y相等
		{
			int times = abs(MEState.pEnd.x - MEState.pBegin.x);
			for (int i = 1; i < times; i++)
			{
				if (MEState.pEnd.x - MEState.pBegin.x > 0)//--->
				{
					if (mychess[MEState.pBegin.x + i][MEState.pBegin.y].chessName == NONE)
						continue;
					else
					{
						obstacleNum++;
					}
				}
				else if (MEState.pEnd.x - MEState.pBegin.x < 0)//<----
				{
					if (mychess[MEState.pBegin.x - i][MEState.pBegin.y].chessName == NONE)
						continue;
					else
					{
						obstacleNum++;
					}
				}
			}
		}
		cout << "obstacleNum:" << obstacleNum << endl;
		//判断完之间的无障碍物i == times，再判断最后一个位置的信息
		if (obstacleNum == 1)
		{
			if (mychess[MEState.pEnd.x][MEState.pEnd.y].chessName == NONE) //不能吃，不能走
			{
				return false;
			}
			else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //吃
			{
				ChangeChessMessage();
				ShowGameConsole();
				GameDrawBoard();
				DrawChess();
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (obstacleNum >= 2)
			return false;
		else if (obstacleNum == 0)
		{
			if (mychess[MEState.pEnd.x][MEState.pEnd.y].chessName == NONE) //移动位置
			{
				ChangeChessMessage();
				ShowGameConsole();
				GameDrawBoard();
				DrawChess();
				return true;
			}
			else //否则无法移动
			{
				return false;
			}
		}
	}
}

bool Ma()
{
	//先设计好，马走的路线，就可以了
	//坐标上加下减
	//马走的坐标，加障碍坐标示意图
	//     0        1
	//		   0
	// 4                 5
	//     2       3
	// 6                 7
	//         1
	//     2        3
	// 
	// 
	//
	MyPoint maNextState[8] = {  {MEState.pBegin.x - 2,MEState.pBegin.y - 1},//0
								{MEState.pBegin.x - 2,MEState.pBegin.y + 1},//1
								{MEState.pBegin.x + 2, MEState.pBegin.y - 1},
								{MEState.pBegin.x + 2, MEState.pBegin.y + 1},
								{MEState.pBegin.x - 1, MEState.pBegin.y - 2},//4
								{MEState.pBegin.x - 1, MEState.pBegin.y + 2},
								{MEState.pBegin.x + 1, MEState.pBegin.y - 2},//6
								{MEState.pBegin.x + 1, MEState.pBegin.y + 2}, };

	MyPoint maObstacle[4] = {   {MEState.pBegin.x - 1, MEState.pBegin.y},
								{MEState.pBegin.x + 1, MEState.pBegin.y},
								{MEState.pBegin.x, MEState.pBegin.y - 1},
								{MEState.pBegin.x, MEState.pBegin.y + 1} };

	if ((MEState.pEnd.x == maNextState[0].x) && (MEState.pEnd.y == maNextState[0].y) ||
		(MEState.pEnd.x == maNextState[1].x) && (MEState.pEnd.y == maNextState[1].y))
	{
		if (mychess[maObstacle[0].x][maObstacle[0].y].chessName != NONE)
			return false;
		else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //吃or 移动
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else
		{
			return false;
		}
	}
	else if ((MEState.pEnd.x == maNextState[2].x) && (MEState.pEnd.y == maNextState[2].y) ||
		(MEState.pEnd.x == maNextState[3].x) && (MEState.pEnd.y == maNextState[3].y))
	{
		if (mychess[maObstacle[1].x][maObstacle[1].y].chessName != NONE)
			return false;
		else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //吃or 移动
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else
		{
			return false;
		}
	}
	else if ((MEState.pEnd.x == maNextState[4].x) && (MEState.pEnd.y == maNextState[4].y) ||
		(MEState.pEnd.x == maNextState[6].x) && (MEState.pEnd.y == maNextState[6].y))
	{
		if (mychess[maObstacle[2].x][maObstacle[2].y].chessName != NONE)
			return false;
		else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //吃or 移动
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else
		{
			return false;
		}
	}
	else if ((MEState.pEnd.x == maNextState[5].x) && (MEState.pEnd.y == maNextState[5].y) ||
		(MEState.pEnd.x == maNextState[7].x) && (MEState.pEnd.y == maNextState[7].y))
	{
		if (mychess[maObstacle[3].x][maObstacle[3].y].chessName != NONE)
			return false;
		else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //吃or 移动
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

bool Xiang()
{
	//if ((MEState.pEnd.x == MEState.pBegin.x && MEState.pEnd.y != MEState.pBegin.y) || (MEState.pEnd.x != MEState.pBegin.x && MEState.pEnd.y == MEState.pBegin.y))
	//cout << "move" << endl;
	//if (mychess[MEState.pBegin.x][MEState.pBegin.y].color != mychess[MEState.pEnd.x][MEState.pEnd.y].color)//不能吃自己人
	//{
	//	mychess[MEState.pEnd.x][MEState.pEnd.y].chessName = mychess[MEState.pBegin.x][MEState.pBegin.y].chessName;
	//	mychess[MEState.pEnd.x][MEState.pEnd.y].color = mychess[MEState.pBegin.x][MEState.pBegin.y].color;
	//	mychess[MEState.pBegin.x][MEState.pBegin.y].chessName = NONE;
	//	mychess[MEState.pBegin.x][MEState.pBegin.y].color = '\0';
	//
	//	GameDrawBoard();
	//	DrawChess();
	//}
	//else
	//{
	//	ResetMEState();
	//}

	MyPoint xiangNextState[4] = { {MEState.pBegin.x - 2,MEState.pBegin.y - 2},//0
							{MEState.pBegin.x + 2,MEState.pBegin.y - 2},//1
							{MEState.pBegin.x - 2, MEState.pBegin.y + 2},
							{MEState.pBegin.x + 2, MEState.pBegin.y + 2} };

	MyPoint xiangObstacle[4] = { {MEState.pBegin.x - 1, MEState.pBegin.y - 1},
								{MEState.pBegin.x + 1, MEState.pBegin.y - 1},
								{MEState.pBegin.x - 1, MEState.pBegin.y + 1},
								{MEState.pBegin.x + 1, MEState.pBegin.y + 1} };
	if (MEState.pEnd.x < 5 && mychess[MEState.pBegin.x][MEState.pBegin.y].color == 'R')
	{
		if (MEState.pEnd.x == xiangNextState[0].x && MEState.pEnd.y == xiangNextState[0].y && mychess[xiangObstacle[0].x][xiangObstacle[0].y].chessName == NONE && mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else if (MEState.pEnd.x == xiangNextState[1].x && MEState.pEnd.y == xiangNextState[1].y && mychess[xiangObstacle[1].x][xiangObstacle[1].y].chessName == NONE && mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else if (MEState.pEnd.x == xiangNextState[2].x && MEState.pEnd.y == xiangNextState[2].y && mychess[xiangObstacle[2].x][xiangObstacle[2].y].chessName == NONE && mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else if (MEState.pEnd.x == xiangNextState[3].x && MEState.pEnd.y == xiangNextState[3].y && mychess[xiangObstacle[3].x][xiangObstacle[3].y].chessName == NONE && mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
	}
	else if (MEState.pEnd.x > 4 && mychess[MEState.pBegin.x][MEState.pBegin.y].color == 'B')
	{
		if (MEState.pEnd.x == xiangNextState[0].x && MEState.pEnd.y == xiangNextState[0].y && mychess[xiangObstacle[0].x][xiangObstacle[0].y].chessName == NONE && mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else if (MEState.pEnd.x == xiangNextState[1].x && MEState.pEnd.y == xiangNextState[1].y && mychess[xiangObstacle[1].x][xiangObstacle[1].y].chessName == NONE && mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else if (MEState.pEnd.x == xiangNextState[2].x && MEState.pEnd.y == xiangNextState[2].y && mychess[xiangObstacle[2].x][xiangObstacle[2].y].chessName == NONE && mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else if (MEState.pEnd.x == xiangNextState[3].x && MEState.pEnd.y == xiangNextState[3].y && mychess[xiangObstacle[3].x][xiangObstacle[3].y].chessName == NONE && mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
	}
	else
		return false;
}

void Shi()
{
	//每次xy都变化一可以移动，但是不能超出边界
	/*if ((MEState.pEnd.x == MEState.pBegin.x && MEState.pEnd.y != MEState.pBegin.y) || (MEState.pEnd.x != MEState.pBegin.x && MEState.pEnd.y == MEState.pBegin.y))
	cout << "move" << endl;*/
	if (mychess[MEState.pBegin.x][MEState.pBegin.y].color != mychess[MEState.pEnd.x][MEState.pEnd.y].color)//不能吃自己人
	{
		mychess[MEState.pEnd.x][MEState.pEnd.y].chessName = mychess[MEState.pBegin.x][MEState.pBegin.y].chessName;
		mychess[MEState.pEnd.x][MEState.pEnd.y].color = mychess[MEState.pBegin.x][MEState.pBegin.y].color;
		mychess[MEState.pBegin.x][MEState.pBegin.y].chessName = NONE;
		mychess[MEState.pBegin.x][MEState.pBegin.y].color = '\0';

		GameDrawBoard();
		DrawChess();
	}
	else
	{
		ResetMEState();
	}
}

void Jiang()
{
	//每次x或者y都变化一可以移动，但是不能超出边界
	/*if ((MEState.pEnd.x == MEState.pBegin.x && MEState.pEnd.y != MEState.pBegin.y) || (MEState.pEnd.x != MEState.pBegin.x && MEState.pEnd.y == MEState.pBegin.y))
	cout << "move" << endl;*/
	if (mychess[MEState.pBegin.x][MEState.pBegin.y].color != mychess[MEState.pEnd.x][MEState.pEnd.y].color)//不能吃自己人
	{
		mychess[MEState.pEnd.x][MEState.pEnd.y].chessName = mychess[MEState.pBegin.x][MEState.pBegin.y].chessName;
		mychess[MEState.pEnd.x][MEState.pEnd.y].color = mychess[MEState.pBegin.x][MEState.pBegin.y].color;
		mychess[MEState.pBegin.x][MEState.pBegin.y].chessName = NONE;
		mychess[MEState.pBegin.x][MEState.pBegin.y].color = '\0';

		GameDrawBoard();
		DrawChess();
	}
	else
	{
		ResetMEState();
	}
}

bool Bing()
{
	if (!mychess[MEState.pBegin.x][MEState.pBegin.y].flag_through_river)
		//只能x++;
	{
		if (MEState.pBegin.y == MEState.pEnd.y && abs(MEState.pEnd.x - MEState.pBegin.x) == 1)
		{
			if (mychess[MEState.pBegin.x][MEState.pBegin.y].color == 'R')
			{
				if (MEState.pEnd.x - MEState.pBegin.x > 0)//只能是往前走
				{
					if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)//不能吃自己人
					{
						ChangeChessMessage();
						//if (MEState.pEnd.x > 4)//过河了
						//{
						//	mychess[MEState.pBegin.x][MEState.pBegin.y].flag_through_river = false;
						//	mychess[MEState.pEnd.x][MEState.pEnd.y].flag_through_river = true;
						//}
					}
				}
				else
					return false;
			}
			else if (mychess[MEState.pBegin.x][MEState.pBegin.y].color == 'B')
			{
				if (MEState.pEnd.x - MEState.pBegin.x < 0)
				{
					if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)
					{
						ChangeChessMessage();
						/*if (MEState.pEnd.x < 5)
						{
							mychess[MEState.pBegin.x][MEState.pBegin.y].flag_through_river = false;
							mychess[MEState.pEnd.x][MEState.pEnd.y].flag_through_river = true;
						}*/
					}
				}
				else
					return false;
			}
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else
			return false;
	}
	else if (mychess[MEState.pBegin.x][MEState.pBegin.y].flag_through_river) //过河了的情况
	{
		//此时x或者y移动一次即可移动，但是不能往后走
		if (mychess[MEState.pBegin.x][MEState.pBegin.y].color == 'R')
		{
			if ((MEState.pEnd.x - MEState.pBegin.x == 1 && MEState.pEnd.y == MEState.pBegin.y) ||
				(abs(MEState.pEnd.y - MEState.pBegin.y) == 1 && MEState.pEnd.x == MEState.pBegin.x))
			{
				if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)//不能吃自己人
				{
					ChangeChessMessage();
					ShowGameConsole();
					GameDrawBoard();
					DrawChess();
					return true;
				}
			}
			else
				return false;
		}
		else if (mychess[MEState.pBegin.x][MEState.pBegin.y].color == 'B')
		{
			if ((MEState.pBegin.x - MEState.pEnd.x == 1 && MEState.pEnd.y == MEState.pBegin.y) ||
				(abs(MEState.pEnd.y - MEState.pBegin.y) == 1 && MEState.pEnd.x == MEState.pBegin.x))
			{
				if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)//不能吃自己人
				{
					ChangeChessMessage();
					ShowGameConsole();
					GameDrawBoard();
					DrawChess();
					return true;
				}
			}
			else
				return false;
		}

	}
}
//棋子的控制
//void GameControl()
//{
//	if (MouseHit())//鼠标显示在图形界面的消息触发，只要在界面上，就会触发
//	{
//		cout << "delay1" << endl;
//		Mmsg = GetMouseMsg();//获取鼠标消息状态的
//		//cout << "delay2" << endl;
//		if (Mmsg.uMsg == WM_LBUTTONDOWN)//如果有左键按下
//		{
//			//测试
//			cout << "第一次";
//			cout << "Mmsg.x:" << Mmsg.x;
//			cout << "Mmsg.y:" << Mmsg.y;
//			//判断是否有棋子
//			for (int i = 0; i < GAME_ROW; i++)
//			{
//				for (int j = 0; j < GAME_COL; j++)
//				{
//					if (!(mychess[i][j].flag_die))//注意细节
//					{
//						if ((pow((Mmsg.x - mychess[i][j].x), 2) + pow((Mmsg.y - mychess[i][j].y), 2)) > pow(40, 2))
//							continue;
//						else
//						{
//							//点到棋子了
//							myBegin.x = mychess[i][j].x;
//							myBegin.y = mychess[i][j].y;
//							mychess[i][j].flag_choosing = true;
//							cout << "点到了" << endl;
//							MyDelay(1);
//							Mmsg = GetMouseMsg();
//							while(Mmsg.uMsg != WM_LBUTTONDOWN) Mmsg = GetMouseMsg();
//							myEnd.x = Mmsg.x;
//							myEnd.y = Mmsg.y;
//							cout << "第二次";
//							cout << "Mmsg.x:" << Mmsg.x;
//							cout << "Mmsg.y:" << Mmsg.y;
//							//判断是什么棋子
//							if (mychess[i][j].chessName == redChess[0] || mychess[i][j].chessName == blackChess[0])
//							{
//								
//								//车的行为
//							}
//							else if (mychess[i][j].chessName == redChess[1] || mychess[i][j].chessName == blackChess[1])
//							{
//								//马的行为
//							}
//							else if (mychess[i][j].chessName == redChess[2] || mychess[i][j].chessName == blackChess[2])
//							{
//								//象的行为
//							}
//							else if (mychess[i][j].chessName == redChess[3] || mychess[i][j].chessName == blackChess[3])
//							{
//								//仕的行为
//							}
//							else if (mychess[i][j].chessName == redChess[4] || mychess[i][j].chessName == blackChess[4])
//							{
//								//将的行为
//							}
//							else if (mychess[i][j].chessName == redChess[5] || mychess[i][j].chessName == blackChess[5])
//							{
//								//跑的行为
//							}
//							else if (mychess[i][j].chessName == redChess[6] || mychess[i][j].chessName == blackChess[6])
//							{
//								//兵的行为
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}

//选择棋子
void DrawChoose(int x, int y, int color)
{
	if (color == 1)
		setlinecolor(RGB(0, 0, 255));//蓝色
	else if (color == 2)
		setlinecolor(RGB(255, 255,0));//yellow
	setlinestyle(PS_SOLID, 1);//实线,2宽
	line(((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) - CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) - CIRCLE + y * INTERVAL_ROW, ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) - CIRCLE + y * INTERVAL_ROW);
	line(((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) - CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + CIRCLE + y * INTERVAL_ROW, ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + CIRCLE + y * INTERVAL_ROW);
	line(((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) - CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) - CIRCLE + y * INTERVAL_ROW, ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) - CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + CIRCLE + y * INTERVAL_ROW);
	line(((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) - CIRCLE + y * INTERVAL_ROW, ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + CIRCLE + y * INTERVAL_ROW);
}

//鼠标操作
void MouseEvent()
{
	ExMessage Emsg;//定义消息
	if (peekmessage(&Emsg, EM_MOUSE)) //check Left mouse button is pressed
	{
		if (Emsg.message == WM_LBUTTONDOWN)//Left mouse button is pressed
		{
			//test code
			cout << Emsg.x << "," << Emsg.y << endl;
			int row = (Emsg.y - ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0)) / INTERVAL_ROW;//y = row,计算数组的行
			int col = (Emsg.x - ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0)) / INTERVAL_COL;//x = col，计算数组的列
			//cout << "before:" << x << "," << y << endl;
			//偏移点击位置
			if ((Emsg.x - (((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + col * INTERVAL_COL)) > (INTERVAL_COL / 2) && ((Emsg.y - (((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + row * INTERVAL_ROW) < (INTERVAL_ROW / 2))))
			{
				//test code
				col++;
			}
			else if ((Emsg.x - (((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + col * INTERVAL_COL)) < (INTERVAL_COL / 2) && ((Emsg.y - (((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + row * INTERVAL_ROW) > (INTERVAL_ROW / 2))))
				row++;
			else if ((Emsg.x - (((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + col * INTERVAL_COL)) > (INTERVAL_COL / 2) && ((Emsg.y - (((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + row * INTERVAL_ROW) > (INTERVAL_ROW / 2))))
			{
				col++; row++;
			}
			//后面这两行代码是用来获取两个点的信息的
			if (MEState.pointState == BEGIN)
			{
				DrawChoose(col, row, 1);
				MEState.pBegin.x = row;
				MEState.pBegin.y = col;
				cout <<"BEGIN:" << MEState.pBegin.x << "," << MEState.pBegin.y << endl;
				MEState.pointState = END;
			}
			else if (MEState.pointState == END)
			{
				//DrawChoose(x, y, 2);
				//刷新棋盘
				GameDrawBoard();
				DrawChess();
				MEState.pEnd.x = row;
				MEState.pEnd.y = col;
				cout << "END:" << MEState.pEnd.x << "," << MEState.pEnd.y << endl;
				MEState.pointState = BEGIN;

			}

		}
	}
}

//移动棋子 
void ChessMove()//完完全全按ShowGameConsole输出的坐标操作
{
	//什么情况棋子才能移动
	//1. 一定是dian到了棋子
	//2. 一定是不同于自己的坐标
	//3. 一定是符合自己移动的规则
	//4. 没有吃
	if (!(MEState.pBegin.x == MEState.pEnd.x && MEState.pBegin.y == MEState.pEnd.y) 
		&& MEState.pEnd.x != -1
		&& MEState.pBegin.x != -1
		&& MEState.pEnd.x != 10
		&& MEState.pBegin.x != 10
		&& MEState.pEnd.y != -1
		&& MEState.pBegin.y != -1
		&& MEState.pBegin.y != 9
		&& MEState.pEnd.y != 9)//先判断位置，不能是同一个位置,不能是边界
	{
		//再判断判断没有棋子不能移动，不能自己吃自己人
		//&& mychess[MEState.pBegin.x][MEState.pBegin.y].color != mychess[MEState.pEnd.x][MEState.pEnd.y].color
		switch (mychess[MEState.pBegin.x][MEState.pBegin.y].chessName)//把Pieces直接复制进来就可以自动打出全部case
		{
		case 車:
		case 车:
		{
			bool flagChe = Che();
			if (!flagChe)
				cout << "can't move!" << endl;
			break;
		}
		case 馬:
		case 马:
		{
			bool flagMa = Ma();
			if (!flagMa)
				cout << "can't move!" << endl;
			break;
		}
		case 相:
		case 象:
		{
			bool flagXiang = Xiang();
			if (!flagXiang)
				cout << "can't move!" << endl;
			break;
		}
			
		case 士:
		case 仕:
			Shi();
			break;
		case 帅:
		case 将:
			Jiang();
			break;
		case 炮:
		case 砲:
		{
			bool flagPao = Pao();
			if (!flagPao)
				cout << "can't move!" << endl;
			break;
		}
			
		case 兵:
		case 卒:
		{
			bool flagBing = Bing();
			if (!flagBing)
				cout << "can't move!" << endl;
			break;
		}

		default:
			break;
		}
		ResetMEState();
		cout << "当前begin与end坐标信息:" << endl;
		cout << "(MEState.pBegin.x,MEState.pBegin.y):"  << MEState.pBegin.x <<","<< MEState.pBegin.y <<
			" | (MEState.pEnd.x,MEState.pEnd.y):" << MEState.pEnd.x << ", " << MEState.pEnd.x << endl;
		//cout << "移动" << endl;
	}
	else if (MEState.pBegin.x == MEState.pEnd.x && MEState.pBegin.y == MEState.pEnd.y)
	{
		ResetMEState();
		//cout << "相同位置" << endl;
	}
}
//画棋子
void DrawChess()
{
	settextstyle(40, 0, "楷体");
	const char* textName;
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			if (mychess[i][j].chessName != NONE)//注意细节
			{
				if (mychess[i][j].color == 'R')
				{
					settextcolor(RED);
					setlinecolor(RED);
					textName = chessName[mychess[i][j].chessName].c_str();
				}
				else
				{
					settextcolor(BLACK);
					setlinecolor(BLACK);
					textName = chessName[mychess[i][j].chessName].c_str();
				}
				//测试代码
				//cout << (mychess[i][j].chessName).c_str() << " ";
				//解决string转outtextxy符合的字符输出				
				//测试代码
				//int theight = textheight(textName);//文本高度
				//int twidth = textwidth(textName);//文本宽度
				//cout << "--theight:" << theight << endl;
				//cout << "--twidth:" << twidth << endl;
				fillcircle(mychess[i][j].x, mychess[i][j].y, CIRCLE);//画圆
				fillcircle(mychess[i][j].x, mychess[i][j].y, CIRCLE - 5);//画圆
				//-20 是坐标平移
				outtextxy(mychess[i][j].x - 20, mychess[i][j].y - 20, textName);//写棋子
			}

		}
	}
}

//游戏界面制作
void GameDrawBoard()
{
	//绘制背景颜色
	setbkcolor(RGB(252, 215, 162));
	cleardevice();//刷新graph界面
	//设置线的属性
	setlinecolor(BLACK);//黑线
	setlinestyle(PS_SOLID, 2);//实线,2宽

	setfillcolor(RGB(252, 215, 162));//设置填充颜色
	fillrectangle(WAIFRAME_TOP_X, WAIFRAME_TOP_Y, WAIFRAME_BOTTOM_X, WAIFRAME_BOTTOM_Y);
	for (int i = 0; i < GAME_ROW; i++)
	{
		//横着画线，画GAME_ROW条
		//line(x, y1, x, y2);
		line((GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
			(i) * INTERVAL_ROW + (GRAPH_EDGE - CHESS_EDGE_COL) / 2,
			CHESS_EDGE_ROW + (GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
			(i) * INTERVAL_ROW + (GRAPH_EDGE - CHESS_EDGE_COL) / 2);
	}
	for (int i = 0; i < GAME_COL; i++)
	{
		//竖着画线，画GAME_COL条
		//line(x1,y,x2,y);
		//间隔是8 * Δ = 700
		line(i * (INTERVAL_COL) + (GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
			(GRAPH_EDGE - CHESS_EDGE_COL) / 2,
			i * (INTERVAL_COL) + (GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
			CHESS_EDGE_COL + (GRAPH_EDGE - CHESS_EDGE_COL) / 2);
	}
	//显示楚河汉界
	setfillcolor(RGB(252, 215, 162));
	fillrectangle((GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
		4 * INTERVAL_ROW + (GRAPH_EDGE - CHESS_EDGE_COL) / 2,
		CHESS_EDGE_ROW + (GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
		(4 + 1) * INTERVAL_ROW + (GRAPH_EDGE - CHESS_EDGE_COL) / 2);
	//显示汉字
	settextcolor(BLACK);
	settextstyle(50, 0, "楷体");
	char textRiver[] = "楚河             汉界";
	int theight = textheight(textRiver);//文本高度
	int twidth = textwidth(textRiver);//文本宽度
	double twidthinterval = (CHESS_EDGE_ROW - twidth) / 2.0;//居中间隔
	double theightinterval = (INTERVAL_COL - theight) / 2.0;//居中间隔
	//测试代码
	/*cout << theight << endl;
	cout << twidth << endl;
	cout << "-----------------" << endl;
	cout << twidthinterval << endl;
	cout << theightinterval << endl;*/
	outtextxy(((GRAPH_EDGE - CHESS_EDGE_ROW) / 2) + twidthinterval,
		(4 * INTERVAL_ROW + (GRAPH_EDGE - CHESS_EDGE_COL) / 2) + theightinterval,
		textRiver);
	//外边框画在最前面就不会覆盖
	////画横线
	//line(WAIFRAME_TOP_X, WAIFRAME_TOP_Y, WAIFRAME_BOTTOM_X, WAIFRAME_TOP_Y);
	//line(WAIFRAME_TOP_X, WAIFRAME_BOTTOM_Y, WAIFRAME_BOTTOM_X, WAIFRAME_BOTTOM_Y);
	////画竖线
	//line(WAIFRAME_TOP_X, WAIFRAME_TOP_Y, WAIFRAME_TOP_X, WAIFRAME_BOTTOM_Y);
	//line(WAIFRAME_BOTTOM_X, WAIFRAME_TOP_Y, WAIFRAME_BOTTOM_X, WAIFRAME_BOTTOM_Y);
	//画米字
	line(MIZI_TOP_X, MIZI_TOP_Y, MIZI_BOTTOM_X, MIZI_BOTTOM_Y);
	line(MIZI_BOTTOM_X, MIZI_TOP_Y, MIZI_TOP_X, MIZI_BOTTOM_Y);
	//下面的米字，y坐标往下平移
	line(MIZI_TOP_X, MIZI_TOP_Y + CHESS_EDGE_COL - (2 * INTERVAL_ROW), MIZI_BOTTOM_X, MIZI_BOTTOM_Y + CHESS_EDGE_COL - (2 * INTERVAL_ROW));
	line(MIZI_BOTTOM_X, MIZI_TOP_Y + CHESS_EDGE_COL - (2 * INTERVAL_ROW), MIZI_TOP_X, MIZI_BOTTOM_Y + CHESS_EDGE_COL - (2 * INTERVAL_ROW));
	//画棋子
	//DrawChess();
}

//初始界面
void GameGUI()
{

}

int main()
{
	initgraph(GRAPH_EDGE, GRAPH_EDGE, SHOWCONSOLE);
	cout << "my name is luolan" << endl;
	GameInit();
	GameDrawBoard();
	DrawChess();
	ShowGameConsole();
	//双缓冲绘图，防止闪屏
	BeginBatchDraw();
	while (1)
	{

		MouseEvent();
		//GameControl();
		ChessMove();

		FlushBatchDraw();

	}

	EndBatchDraw();
	system("pause");
	return 0;
}



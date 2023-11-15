#include"chinachess.h"

Chess mychess[10][9];
MouseEventState MEState = {-1,-1,-1,-1,BEGIN};
MOUSEMSG Mmsg;

//������������꣬Ϊ�˷�ֹһЩСbug�������ɾ�������һ��,������û���ƶ���Ҫ��if��������
void ResetMEState()
{
	MEState.pBegin.x = -1;
	MEState.pBegin.y = -1;
	MEState.pEnd.x = -1;
	MEState.pEnd.y = -1;
}
//��ʱ
void MyDelay(int sec)
{
	clock_t start = clock();
	clock_t lay = (clock_t)sec * CLOCKS_PER_SEC;
	while ((clock() - start) < lay);
}

//��Ϸ�ĳ�ʼ��
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
			//ͳһ��ʼ����
			mychess[i][j].x = ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + j * (INTERVAL_COL);
			mychess[i][j].y = ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + i * (INTERVAL_ROW);
			mychess[i][j].flag_through_river = false;
			mychess[i][j].flag_die = false;
			mychess[i][j].flag_choosing = false;
		}
	}
}
//�ı�������Ϣ
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

//����̨�������
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
//���ӹ���
bool Che()
{
	//ֱ���ж�
	if (MEState.pBegin.x == MEState.pEnd.x && MEState.pBegin.y != MEState.pEnd.y ||
		MEState.pBegin.x != MEState.pEnd.x && MEState.pBegin.y == MEState.pEnd.y)
	{
		//��ʼ���ж��м��Ƿ����ϰ���
		
		if (MEState.pBegin.y != MEState.pEnd.y)//x���
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
		else if (MEState.pBegin.x != MEState.pEnd.x) //y���
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
		//�ж���֮������ϰ���i == times�����ж����һ��λ�õ���Ϣ
		if (mychess[MEState.pEnd.x][MEState.pEnd.y].chessName == NONE) //�ƶ�λ��
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //��
		{
			ChangeChessMessage();
			ShowGameConsole();
			GameDrawBoard();
			DrawChess();
			return true;
		}
		else //�����ܳ�
		{
			return false;
		}
	}
}

bool Pao()
{
	//ֱ���ж�
	if (MEState.pBegin.x == MEState.pEnd.x && MEState.pBegin.y != MEState.pEnd.y ||
		MEState.pBegin.x != MEState.pEnd.x && MEState.pBegin.y == MEState.pEnd.y)
	{
		//��ʼ���ж��м��Ƿ����ϰ���
		int obstacleNum = 0;
		if (MEState.pBegin.y != MEState.pEnd.y)//x���
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
		else if (MEState.pBegin.x != MEState.pEnd.x) //y���
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
		//�ж���֮������ϰ���i == times�����ж����һ��λ�õ���Ϣ
		if (obstacleNum == 1)
		{
			if (mychess[MEState.pEnd.x][MEState.pEnd.y].chessName == NONE) //���ܳԣ�������
			{
				return false;
			}
			else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //��
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
			if (mychess[MEState.pEnd.x][MEState.pEnd.y].chessName == NONE) //�ƶ�λ��
			{
				ChangeChessMessage();
				ShowGameConsole();
				GameDrawBoard();
				DrawChess();
				return true;
			}
			else //�����޷��ƶ�
			{
				return false;
			}
		}
	}
}

bool Ma()
{
	//����ƺã����ߵ�·�ߣ��Ϳ�����
	//�����ϼ��¼�
	//���ߵ����꣬���ϰ�����ʾ��ͼ
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
		else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //��or �ƶ�
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
		else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //��or �ƶ�
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
		else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //��or �ƶ�
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
		else if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color) //��or �ƶ�
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
	//if (mychess[MEState.pBegin.x][MEState.pBegin.y].color != mychess[MEState.pEnd.x][MEState.pEnd.y].color)//���ܳ��Լ���
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
	//ÿ��xy���仯һ�����ƶ������ǲ��ܳ����߽�
	/*if ((MEState.pEnd.x == MEState.pBegin.x && MEState.pEnd.y != MEState.pBegin.y) || (MEState.pEnd.x != MEState.pBegin.x && MEState.pEnd.y == MEState.pBegin.y))
	cout << "move" << endl;*/
	if (mychess[MEState.pBegin.x][MEState.pBegin.y].color != mychess[MEState.pEnd.x][MEState.pEnd.y].color)//���ܳ��Լ���
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
	//ÿ��x����y���仯һ�����ƶ������ǲ��ܳ����߽�
	/*if ((MEState.pEnd.x == MEState.pBegin.x && MEState.pEnd.y != MEState.pBegin.y) || (MEState.pEnd.x != MEState.pBegin.x && MEState.pEnd.y == MEState.pBegin.y))
	cout << "move" << endl;*/
	if (mychess[MEState.pBegin.x][MEState.pBegin.y].color != mychess[MEState.pEnd.x][MEState.pEnd.y].color)//���ܳ��Լ���
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
		//ֻ��x++;
	{
		if (MEState.pBegin.y == MEState.pEnd.y && abs(MEState.pEnd.x - MEState.pBegin.x) == 1)
		{
			if (mychess[MEState.pBegin.x][MEState.pBegin.y].color == 'R')
			{
				if (MEState.pEnd.x - MEState.pBegin.x > 0)//ֻ������ǰ��
				{
					if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)//���ܳ��Լ���
					{
						ChangeChessMessage();
						//if (MEState.pEnd.x > 4)//������
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
	else if (mychess[MEState.pBegin.x][MEState.pBegin.y].flag_through_river) //�����˵����
	{
		//��ʱx����y�ƶ�һ�μ����ƶ������ǲ���������
		if (mychess[MEState.pBegin.x][MEState.pBegin.y].color == 'R')
		{
			if ((MEState.pEnd.x - MEState.pBegin.x == 1 && MEState.pEnd.y == MEState.pBegin.y) ||
				(abs(MEState.pEnd.y - MEState.pBegin.y) == 1 && MEState.pEnd.x == MEState.pBegin.x))
			{
				if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)//���ܳ��Լ���
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
				if (mychess[MEState.pEnd.x][MEState.pEnd.y].color != mychess[MEState.pBegin.x][MEState.pBegin.y].color)//���ܳ��Լ���
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
//���ӵĿ���
//void GameControl()
//{
//	if (MouseHit())//�����ʾ��ͼ�ν������Ϣ������ֻҪ�ڽ����ϣ��ͻᴥ��
//	{
//		cout << "delay1" << endl;
//		Mmsg = GetMouseMsg();//��ȡ�����Ϣ״̬��
//		//cout << "delay2" << endl;
//		if (Mmsg.uMsg == WM_LBUTTONDOWN)//������������
//		{
//			//����
//			cout << "��һ��";
//			cout << "Mmsg.x:" << Mmsg.x;
//			cout << "Mmsg.y:" << Mmsg.y;
//			//�ж��Ƿ�������
//			for (int i = 0; i < GAME_ROW; i++)
//			{
//				for (int j = 0; j < GAME_COL; j++)
//				{
//					if (!(mychess[i][j].flag_die))//ע��ϸ��
//					{
//						if ((pow((Mmsg.x - mychess[i][j].x), 2) + pow((Mmsg.y - mychess[i][j].y), 2)) > pow(40, 2))
//							continue;
//						else
//						{
//							//�㵽������
//							myBegin.x = mychess[i][j].x;
//							myBegin.y = mychess[i][j].y;
//							mychess[i][j].flag_choosing = true;
//							cout << "�㵽��" << endl;
//							MyDelay(1);
//							Mmsg = GetMouseMsg();
//							while(Mmsg.uMsg != WM_LBUTTONDOWN) Mmsg = GetMouseMsg();
//							myEnd.x = Mmsg.x;
//							myEnd.y = Mmsg.y;
//							cout << "�ڶ���";
//							cout << "Mmsg.x:" << Mmsg.x;
//							cout << "Mmsg.y:" << Mmsg.y;
//							//�ж���ʲô����
//							if (mychess[i][j].chessName == redChess[0] || mychess[i][j].chessName == blackChess[0])
//							{
//								
//								//������Ϊ
//							}
//							else if (mychess[i][j].chessName == redChess[1] || mychess[i][j].chessName == blackChess[1])
//							{
//								//�����Ϊ
//							}
//							else if (mychess[i][j].chessName == redChess[2] || mychess[i][j].chessName == blackChess[2])
//							{
//								//�����Ϊ
//							}
//							else if (mychess[i][j].chessName == redChess[3] || mychess[i][j].chessName == blackChess[3])
//							{
//								//�˵���Ϊ
//							}
//							else if (mychess[i][j].chessName == redChess[4] || mychess[i][j].chessName == blackChess[4])
//							{
//								//������Ϊ
//							}
//							else if (mychess[i][j].chessName == redChess[5] || mychess[i][j].chessName == blackChess[5])
//							{
//								//�ܵ���Ϊ
//							}
//							else if (mychess[i][j].chessName == redChess[6] || mychess[i][j].chessName == blackChess[6])
//							{
//								//������Ϊ
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}

//ѡ������
void DrawChoose(int x, int y, int color)
{
	if (color == 1)
		setlinecolor(RGB(0, 0, 255));//��ɫ
	else if (color == 2)
		setlinecolor(RGB(255, 255,0));//yellow
	setlinestyle(PS_SOLID, 1);//ʵ��,2��
	line(((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) - CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) - CIRCLE + y * INTERVAL_ROW, ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) - CIRCLE + y * INTERVAL_ROW);
	line(((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) - CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + CIRCLE + y * INTERVAL_ROW, ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + CIRCLE + y * INTERVAL_ROW);
	line(((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) - CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) - CIRCLE + y * INTERVAL_ROW, ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) - CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + CIRCLE + y * INTERVAL_ROW);
	line(((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) - CIRCLE + y * INTERVAL_ROW, ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + CIRCLE + x * INTERVAL_COL, ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + CIRCLE + y * INTERVAL_ROW);
}

//������
void MouseEvent()
{
	ExMessage Emsg;//������Ϣ
	if (peekmessage(&Emsg, EM_MOUSE)) //check Left mouse button is pressed
	{
		if (Emsg.message == WM_LBUTTONDOWN)//Left mouse button is pressed
		{
			//test code
			cout << Emsg.x << "," << Emsg.y << endl;
			int row = (Emsg.y - ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0)) / INTERVAL_ROW;//y = row,�����������
			int col = (Emsg.x - ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0)) / INTERVAL_COL;//x = col�������������
			//cout << "before:" << x << "," << y << endl;
			//ƫ�Ƶ��λ��
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
			//���������д�����������ȡ���������Ϣ��
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
				//ˢ������
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

//�ƶ����� 
void ChessMove()//����ȫȫ��ShowGameConsole������������
{
	//ʲô������Ӳ����ƶ�
	//1. һ����dian��������
	//2. һ���ǲ�ͬ���Լ�������
	//3. һ���Ƿ����Լ��ƶ��Ĺ���
	//4. û�г�
	if (!(MEState.pBegin.x == MEState.pEnd.x && MEState.pBegin.y == MEState.pEnd.y) 
		&& MEState.pEnd.x != -1
		&& MEState.pBegin.x != -1
		&& MEState.pEnd.x != 10
		&& MEState.pBegin.x != 10
		&& MEState.pEnd.y != -1
		&& MEState.pBegin.y != -1
		&& MEState.pBegin.y != 9
		&& MEState.pEnd.y != 9)//���ж�λ�ã�������ͬһ��λ��,�����Ǳ߽�
	{
		//���ж��ж�û�����Ӳ����ƶ��������Լ����Լ���
		//&& mychess[MEState.pBegin.x][MEState.pBegin.y].color != mychess[MEState.pEnd.x][MEState.pEnd.y].color
		switch (mychess[MEState.pBegin.x][MEState.pBegin.y].chessName)//��Piecesֱ�Ӹ��ƽ����Ϳ����Զ����ȫ��case
		{
		case ܇:
		case ��:
		{
			bool flagChe = Che();
			if (!flagChe)
				cout << "can't move!" << endl;
			break;
		}
		case �R:
		case ��:
		{
			bool flagMa = Ma();
			if (!flagMa)
				cout << "can't move!" << endl;
			break;
		}
		case ��:
		case ��:
		{
			bool flagXiang = Xiang();
			if (!flagXiang)
				cout << "can't move!" << endl;
			break;
		}
			
		case ʿ:
		case ��:
			Shi();
			break;
		case ˧:
		case ��:
			Jiang();
			break;
		case ��:
		case �h:
		{
			bool flagPao = Pao();
			if (!flagPao)
				cout << "can't move!" << endl;
			break;
		}
			
		case ��:
		case ��:
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
		cout << "��ǰbegin��end������Ϣ:" << endl;
		cout << "(MEState.pBegin.x,MEState.pBegin.y):"  << MEState.pBegin.x <<","<< MEState.pBegin.y <<
			" | (MEState.pEnd.x,MEState.pEnd.y):" << MEState.pEnd.x << ", " << MEState.pEnd.x << endl;
		//cout << "�ƶ�" << endl;
	}
	else if (MEState.pBegin.x == MEState.pEnd.x && MEState.pBegin.y == MEState.pEnd.y)
	{
		ResetMEState();
		//cout << "��ͬλ��" << endl;
	}
}
//������
void DrawChess()
{
	settextstyle(40, 0, "����");
	const char* textName;
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			if (mychess[i][j].chessName != NONE)//ע��ϸ��
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
				//���Դ���
				//cout << (mychess[i][j].chessName).c_str() << " ";
				//���stringתouttextxy���ϵ��ַ����				
				//���Դ���
				//int theight = textheight(textName);//�ı��߶�
				//int twidth = textwidth(textName);//�ı����
				//cout << "--theight:" << theight << endl;
				//cout << "--twidth:" << twidth << endl;
				fillcircle(mychess[i][j].x, mychess[i][j].y, CIRCLE);//��Բ
				fillcircle(mychess[i][j].x, mychess[i][j].y, CIRCLE - 5);//��Բ
				//-20 ������ƽ��
				outtextxy(mychess[i][j].x - 20, mychess[i][j].y - 20, textName);//д����
			}

		}
	}
}

//��Ϸ��������
void GameDrawBoard()
{
	//���Ʊ�����ɫ
	setbkcolor(RGB(252, 215, 162));
	cleardevice();//ˢ��graph����
	//�����ߵ�����
	setlinecolor(BLACK);//����
	setlinestyle(PS_SOLID, 2);//ʵ��,2��

	setfillcolor(RGB(252, 215, 162));//���������ɫ
	fillrectangle(WAIFRAME_TOP_X, WAIFRAME_TOP_Y, WAIFRAME_BOTTOM_X, WAIFRAME_BOTTOM_Y);
	for (int i = 0; i < GAME_ROW; i++)
	{
		//���Ż��ߣ���GAME_ROW��
		//line(x, y1, x, y2);
		line((GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
			(i) * INTERVAL_ROW + (GRAPH_EDGE - CHESS_EDGE_COL) / 2,
			CHESS_EDGE_ROW + (GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
			(i) * INTERVAL_ROW + (GRAPH_EDGE - CHESS_EDGE_COL) / 2);
	}
	for (int i = 0; i < GAME_COL; i++)
	{
		//���Ż��ߣ���GAME_COL��
		//line(x1,y,x2,y);
		//�����8 * �� = 700
		line(i * (INTERVAL_COL) + (GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
			(GRAPH_EDGE - CHESS_EDGE_COL) / 2,
			i * (INTERVAL_COL) + (GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
			CHESS_EDGE_COL + (GRAPH_EDGE - CHESS_EDGE_COL) / 2);
	}
	//��ʾ���Ӻ���
	setfillcolor(RGB(252, 215, 162));
	fillrectangle((GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
		4 * INTERVAL_ROW + (GRAPH_EDGE - CHESS_EDGE_COL) / 2,
		CHESS_EDGE_ROW + (GRAPH_EDGE - CHESS_EDGE_ROW) / 2,
		(4 + 1) * INTERVAL_ROW + (GRAPH_EDGE - CHESS_EDGE_COL) / 2);
	//��ʾ����
	settextcolor(BLACK);
	settextstyle(50, 0, "����");
	char textRiver[] = "����             ����";
	int theight = textheight(textRiver);//�ı��߶�
	int twidth = textwidth(textRiver);//�ı����
	double twidthinterval = (CHESS_EDGE_ROW - twidth) / 2.0;//���м��
	double theightinterval = (INTERVAL_COL - theight) / 2.0;//���м��
	//���Դ���
	/*cout << theight << endl;
	cout << twidth << endl;
	cout << "-----------------" << endl;
	cout << twidthinterval << endl;
	cout << theightinterval << endl;*/
	outtextxy(((GRAPH_EDGE - CHESS_EDGE_ROW) / 2) + twidthinterval,
		(4 * INTERVAL_ROW + (GRAPH_EDGE - CHESS_EDGE_COL) / 2) + theightinterval,
		textRiver);
	//��߿�����ǰ��Ͳ��Ḳ��
	////������
	//line(WAIFRAME_TOP_X, WAIFRAME_TOP_Y, WAIFRAME_BOTTOM_X, WAIFRAME_TOP_Y);
	//line(WAIFRAME_TOP_X, WAIFRAME_BOTTOM_Y, WAIFRAME_BOTTOM_X, WAIFRAME_BOTTOM_Y);
	////������
	//line(WAIFRAME_TOP_X, WAIFRAME_TOP_Y, WAIFRAME_TOP_X, WAIFRAME_BOTTOM_Y);
	//line(WAIFRAME_BOTTOM_X, WAIFRAME_TOP_Y, WAIFRAME_BOTTOM_X, WAIFRAME_BOTTOM_Y);
	//������
	line(MIZI_TOP_X, MIZI_TOP_Y, MIZI_BOTTOM_X, MIZI_BOTTOM_Y);
	line(MIZI_BOTTOM_X, MIZI_TOP_Y, MIZI_TOP_X, MIZI_BOTTOM_Y);
	//��������֣�y��������ƽ��
	line(MIZI_TOP_X, MIZI_TOP_Y + CHESS_EDGE_COL - (2 * INTERVAL_ROW), MIZI_BOTTOM_X, MIZI_BOTTOM_Y + CHESS_EDGE_COL - (2 * INTERVAL_ROW));
	line(MIZI_BOTTOM_X, MIZI_TOP_Y + CHESS_EDGE_COL - (2 * INTERVAL_ROW), MIZI_TOP_X, MIZI_BOTTOM_Y + CHESS_EDGE_COL - (2 * INTERVAL_ROW));
	//������
	//DrawChess();
}

//��ʼ����
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
	//˫�����ͼ����ֹ����
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



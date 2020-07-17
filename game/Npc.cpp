#include "Npc.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <math.h>
#define HeroX 50
#define HeroY 50
#define TILE 100

using namespace std;

Npc::Npc(String F, float X, float Y, float W, float H, std::string *map)
{
	File = F;
	dx = dy = 0;
	File = F;
	w = W; h = H;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(Color(41, 33, 59));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = X; y = Y;
	sprite.setTextureRect(IntRect(32, 48, w, h));
	LocationNpcX = x / 100;
	LocationNpcY = y / 100;
	TargetX = LocationNpcX;
	TargetY = LocationNpcY;

	//кажись для коллизии, разобраться потом!!!!
	for (int i = 0; i < 34; i++)
		for (int j = 0; j < 34; j++)
		{
			if (map[i][j] == '1' || map[i][j] == '2' || map[i][j] == '0' || map[i][j] == '3' || map[i][j] == '4' || map[i][j] == '5') // стена, метим что нельзя пройти
			{
				MapCheck[i][j] = -2;
				MapTemp[i][j] = -2;
			}
			else
				//if (map[i][j] == map[i][j] == 6) // путь есть, метим что мы тут не были
			{
				MapCheck[i][j] = -1;
				MapTemp[i][j] = -1;
			}
		}
}

Npc::~Npc()
{
}


void Npc::IsActive(float time, float speed, std::string* map, bool* update) //Основной метод для "жизни бота"
{
	LocationNpcX = (x / 100);
	LocationNpcY = (y / 100);
	//std::cout << LocationNpcX << " " << LocationNpcY << std::endl;
	//std::cout << x << " " << y << std::endl << std::endl;
	if (*update)
	{
		for (int i = 0; i < 34; i++)
			for (int j = 0; j < 34; j++)
			{
				if (map[i][j] == '1' || map[i][j] == '2' || map[i][j] == '0' || map[i][j] == '3' || map[i][j] == '4' || map[i][j] == '5') // стена, метим что нельзя пройти
				{
					MapCheck[i][j] = -2;
				//	MapTemp[i][j] = -2;
				}
				else
					//if (map[i][j] == map[i][j] == 6) // путь есть, метим что мы тут не были
				{
					MapCheck[i][j] = -1;
				//	MapTemp[i][j] = -1;
				}
			}
		update = false;
	}
	switch (dir) //движение
	{
	case 1: // влево
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(NpcX * int(CurrentFrame), NpcY, NpcX, NpcY));

		dx = -speed;
		dy = 0;
		break;
	case 2: // вправо
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(NpcX * int(CurrentFrame), NpcY * 2, NpcX, NpcY));
		dx = speed;
		dy = 0;
		break;
	case 3://вниз
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(NpcX * int(CurrentFrame), NpcY * 3, NpcX, NpcY));
		dy = -speed;
		dx = 0;
		break;
	case 4: // вверх
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(NpcX * int(CurrentFrame), NpcY * 0, NpcX, NpcY));
		dy = speed;
		dx = 0;
		break;
	}
	CurrentFrame += 0.005 * time;
	x += dx * time;
	y += dy * time;
	x1 = x; y1 = y;
	x2 = x + 50; y2 = y + 50;
	IIMove();
 	Collision(map);
	speed = dx = dy = 0;
	sprite.setPosition(x, y);
}

float Npc::getplayercoordinateX()
{
	return LocationNpcX;
}
float Npc::getplayercoordinateY()
{
	return LocationNpcY;
}

void Npc::WayPointsMove(int *CountPoints, int **Targets) // движение по вэйпоинтам.  пример: npc.WayPointsMove(&waycount, WayPoints);
{
	int TempCounter = *CountPoints;
	
	if (*CountPoints > 0)
	{
		if (LocationNpcX < Targets[TempCounter-1][0])
		{
			dir = 2;
		}
		if (LocationNpcX > Targets[TempCounter -1][0])
		{
			dir = 1;
		}
		if (LocationNpcY < Targets[TempCounter -1][1])
		{
			dir = 4;
		}
		if (LocationNpcY > Targets[TempCounter -1][1])
		{
			dir = 3;
		}
		if (LocationNpcX == Targets[TempCounter -1][0] && LocationNpcY == Targets[TempCounter -1][1])
		{
			dir = 0;
			
			--*CountPoints;
			std::cout << TempCounter << std::endl;
		}
			
		
	}
}




void Npc::IIMove()
{
	//движение бота. Х и У координаты углов бота
	if (!targetY.empty() && !targetX.empty())
	{
		//cout << targetY.top() << " " << targetX.top() << endl;
	//	cout << "ff";
		if (floor(x1 / 100) < (targetX.top()) && floor(x2 / 100) < ((targetX.top())))
		{
			dir = 2;
		}

		if (floor(y1 / 100) < (targetY.top()) && floor(y2 / 100) < ((targetY.top())))
		{
			dir = 4;
		}

		if (floor(x1 / 100) > (targetX.top()) && floor(x2 / 100) > ((targetX.top())))
		{
			dir = 1;
		}

		if (floor(y1 / 100) > (targetY.top()) && floor(y2 / 100) > ((targetY.top())))
		{
			dir = 3;
		}

		if (floor(x1 / 100) == targetX.top() && floor(y1 / 100) == targetY.top() && floor(x2 / 100) == targetX.top() && floor(y2 / 100) == targetY.top())
		{
			dir = 0;
			//cout << targetY.top() << endl;
			targetX.pop();
			targetY.pop();
		//	cout << "complete";
		}
		
	}

}

void Npc::FindWay(int Ypos, int Xpos)
{
	// волновой поиск
	int step1 = 0;
	bool add = true;
	
	MapCheck[LocationNpcY][LocationNpcX] = step1;
	
	while (add == true)
	{
		for (int i = 1; i < 33; i++)
		{
			for (int j = 1; j < 33; j++)
			{
				if (MapCheck[i][j] == step1)
				{
					if (MapCheck[i][j - 1] == -1)
					{
						MapCheck[i][j - 1] = step1 + 1;
					}
					if (MapCheck[i][j + 1] == -1)
					{
						MapCheck[i][j + 1] = step1 + 1;
					}
					if (MapCheck[i - 1][j] == -1)
					{
						MapCheck[i - 1][j] = step1 + 1;
					}
					if (MapCheck[i + 1][j] == -1)
					{
						MapCheck[i + 1][j] = step1 + 1;
					}
					
				}

			}
			
		}
		step1++;
		if (MapCheck[Ypos][Xpos] != -1 || step1 > 34 * 10)
		{
			add = false;
		}
	}


	//Добавление пути в стек
	if (MapCheck[Ypos][Xpos] != -2 && MapCheck[Ypos][Xpos] != -1 )//решение найдено 
	{
		int xx = Xpos, yy = Ypos;
		if (targetX.empty() && targetY.empty())
		{
			targetX.push(xx);
			targetY.push(yy);
			for (int i = 0; i < MapCheck[Ypos][Xpos]; i++)
			{
				if (MapCheck[yy][xx - 1] == MapCheck[Ypos][Xpos] - i)
				{

					targetY.push(yy);
					targetX.push(xx - 1);
					MapCheck[yy][xx - 1] = 0;
					xx--;
				}
				if (MapCheck[yy][xx + 1] == MapCheck[Ypos][Xpos] - i)
				{
					targetY.push(yy);
					targetX.push(xx + 1);
					MapCheck[yy][xx + 1] = 0;
					xx++;
				}
				if (MapCheck[yy - 1][xx] == MapCheck[Ypos][Xpos] - i)
				{
					targetY.push(yy - 1);
					targetX.push(xx);
					MapCheck[yy - 1][xx] = 0;
					yy--;
				}
				if (MapCheck[yy + 1][xx] == MapCheck[Ypos][Xpos] - i)
				{
					targetY.push(yy + 1);
					targetX.push(xx);
					MapCheck[yy + 1][xx] = 0;
					yy++;
				}
			}
		}
	//	map();
	}
	else//решение не найдено
	{
		std::cout << MapCheck[Ypos][Xpos];
		std::cout << "not;";
	}	
	
	
}


void Npc::ClearWay()
{
	while (!targetX.empty() && !targetY.empty())
	{
		dir = 0;
		targetX.pop();
		targetY.pop();
	}
}

void Npc::map()
{
	if (!targetX.empty())
		cout << targetY.top() << " " << targetX.top() << endl;
	else
		cout << "empty";
/*

	for (int i = 0; i < 34; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			if (i == 17 && j == 17)
			{
				std::cout << "FF ";
				continue;
			}
			if (MapCheck[i][j] < 0)
			{
				std::cout << "## ";
			}
			else if (MapCheck[i][j] > 9)
				std::cout << MapCheck[i][j] << " ";
			else
				std::cout << 0 << MapCheck[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
}



void Npc::Collision(std::string map[34])
{
	for (int i = y / TILE; i < (y + HeroY) / TILE; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
		for (int j = x / TILE; j < (x + HeroX) / TILE; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
		{
			if (map[i][j] == '1' || map[i][j] == '2' || map[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
			{
				if (dy > 0)//если мы шли вниз,
				{
					y = i * TILE - HeroY;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
				//	y -= HeroY/20;
				}
				if (dy < 0)
				{
					y = i * TILE + HeroY * 2;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
				//	y += HeroY/20;
				}
				if (dx > 0)
				{
					//	x -= HeroX/20;
					x = j * TILE - HeroX;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
				}
				if (dx < 0)
				{
					//	x += HeroX/20;
					x = j * TILE + HeroX * 2;//аналогично идем влево
				}

			}

		}
}
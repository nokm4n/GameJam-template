#include "Npc.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#define HeroX 50
#define HeroY 50
#define TILE 100


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
	for (int i = 0; i < 34; i++)
		for (int j = 0; j < 34; j++)
		{
			if (map[i][j] == '1' || map[i][j] == '2' || map[i][j] == '0' || map[i][j] == '3' || map[i][j] == '4' || map[i][j] == '5') // стена, метим что нельзя пройти
			{
				MapCheck[i][j] = -2;
			}
			else
			//if (map[i][j] == map[i][j] == 6) // путь есть, метим что мы тут не были
				MapCheck[i][j] = -1;
		}
}

Npc::~Npc()
{
}


void Npc::IsActive(float time, float speed, std::string* map)
{
	LocationNpcX = x / 100;
	LocationNpcY = y / 100;
	switch (dir)
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
	
	x += dx * time;
	y += dy * time;
	Collision(map);
	speed = dx = dy = 0;

	sprite.setPosition(x, y);
}

float Npc::getplayercoordinateX()
{
	return x;
}
float Npc::getplayercoordinateY()
{
	return y;
}

void Npc::WayPointsMove(int *CountPoints, int **Targets)
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

void Npc::IIMove(int Xpos, int Ypos)
{
	if (LocationNpcX <Xpos)
	{
		dir = 2;
	}
	if (LocationNpcX > Xpos)
	{
		dir = 1;
	}
	if (LocationNpcY < Ypos)
	{
		dir = 4;
	}
	if (LocationNpcY > Ypos)
	{
		dir = 3;
	}
	if (LocationNpcX == Xpos && LocationNpcY == Ypos)
	{
		dir = 0;
	}

}

void Npc::FindWay(int Ypos, int Xpos)
{
	int step1 = 0;
	bool add = true;
	MapCheck[LocationNpcY][LocationNpcX] = step1;
	
	while (add == true)
	{
		add = false;
		for (int i = 0; i < 34; i++)
		{
			for (int j = 0; j < 34; j++)
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
		add = true;
		if (MapCheck[Ypos][Xpos] != -1 || step1 > 34 * 10)
		{
			add = false;
		//	std::cout << "FF ";
		}
	}

	for (int i = 0; i < 34; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			if (i == Ypos && j == Xpos)
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
	}
	
	if (MapCheck[Ypos][Xpos] != -2 && MapCheck[Ypos][Xpos] != -1 )//решение найдено
	{
		std::cout << "FF ";
	//	HelpMove(MapCheck[Ypos][Xpos], Ypos, Xpos);
	}
	else//решение не найдено
	{
		std::cout << MapCheck[Ypos][Xpos];
		std::cout << "not;";
	}	
	
	
}

void Npc::HelpMove(int way, int Ypos, int Xpos)
{

	//while(Sway>0)
	//WayPointsMove(&Sway, WayPoints);
	/*for (int i = 0; i < 34; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			if (i == Ypos && j == Xpos)
			{
				std::cout <<  "FF ";
				continue;
			}
			if (MapCheck[i][j] < 0)
			{
				std::cout << 9 << 9 << " ";
			}
			else if (MapCheck[i][j]>9)
			std::cout << MapCheck[i][j] << " ";
			else
				std::cout << 0 << MapCheck[i][j]  << " ";
		}
		std::cout << std::endl;
	}*/
	/*
	for (int i = tempway; i > 0; i--)
	{
		if (MapCheck[LocationNpcY][LocationNpcX - 1] == 0)
		{
			std::cout << "not;";
			
			IIMove(LocationNpcY, LocationNpcX - 1);
			MapCheck[LocationNpcY][LocationNpcX - 1] = -1;
		}
		if (MapCheck[LocationNpcY][LocationNpcX + 1] == 0)
		{
			std::cout << "not;";
			
			IIMove(LocationNpcY, LocationNpcX + 1);
			MapCheck[LocationNpcY][LocationNpcX + 1] = -1;
		}
		if (MapCheck[LocationNpcY - 1][LocationNpcX] == 0)
		{
			std::cout << "not;";
			
			IIMove(LocationNpcY - 1, LocationNpcX);
			MapCheck[LocationNpcY - 1][LocationNpcX] = -1;
		}
		if (MapCheck[LocationNpcY + 1][LocationNpcX] == 0)
		{
			std::cout << "not;";
		
			IIMove(LocationNpcY + 1, LocationNpcX);
			MapCheck[LocationNpcY + 1][LocationNpcX] = -1;
		}
		
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
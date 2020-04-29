#include "Npc.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <math.h>
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
	TargetX = LocationNpcX;
	TargetY = LocationNpcY;


	for (int i = 0; i < 34; i++)
		for (int j = 0; j < 34; j++)
		{
			if (map[i][j] == '1' || map[i][j] == '2' || map[i][j] == '0' || map[i][j] == '3' || map[i][j] == '4' || map[i][j] == '5') // �����, ����� ��� ������ ������
			{
				MapCheck[i][j] = -2;
			}
			else
			//if (map[i][j] == map[i][j] == 6) // ���� ����, ����� ��� �� ��� �� ����
				MapCheck[i][j] = -1;
		}
}

Npc::~Npc()
{
}


void Npc::IsActive(float time, float speed, std::string* map)
{
	LocationNpcX = (x / 100);
	LocationNpcY = (y / 100);
	//std::cout << LocationNpcX << " " << LocationNpcY << std::endl;
	//std::cout << x << " " << y << std::endl << std::endl;
	switch (dir)
	{
	case 1: // �����
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(NpcX * int(CurrentFrame), NpcY, NpcX, NpcY));

		dx = -speed;
		dy = 0;
		break;
	case 2: // ������
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(NpcX * int(CurrentFrame), NpcY * 2, NpcX, NpcY));
		dx = speed;
		dy = 0;
		break;
	case 3://����
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(NpcX * int(CurrentFrame), NpcY * 3, NpcX, NpcY));
		dy = -speed;
		dx = 0;
		break;
	case 4: // �����
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
	IIMove(TargetY, TargetX);
// 	Collision(map);
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




void Npc::IIMove(int Ypos, int Xpos)
{
	//std::cout << Xpos << " "<<Ypos << std::endl;
	//std::cout << x << " " << y << std::endl;
	//std::cout << dir << std::endl;
	TargetX = Xpos;
	TargetY = Ypos;
	if (floor((x+50)/100) <Xpos+1)
	{
		dir = 2;
	}else
	if (floor((y + 50) / 100) < Ypos+1)
	{
		dir = 4;
	}else
	if (floor((x - 51) / 100) > Xpos-1)
	{
		dir = 1;
	}else
	if (floor((y - 51) / 100) > Ypos-1)
	{
		dir = 3;
	}else
	if (floor(x/100) == Xpos && floor(y/100) == Ypos)
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
		//	std::cout << "FF ";
		}
	}

/*	for (int i = 0; i < 34; i++)
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
	}*/
	
	if (MapCheck[Ypos][Xpos] != -2 && MapCheck[Ypos][Xpos] != -1 )//������� �������
	{
		int xx = Xpos, yy = Ypos;
		for (int i = 0; i < MapCheck[Ypos][Xpos]; i++)
		{
			if (MapCheck[yy][xx - 1] == MapCheck[Ypos][Xpos] - i)
			{
				MapCheck[yy][xx - 1] = 0;
				xx--;
			}
			if (MapCheck[yy][xx + 1] == MapCheck[Ypos][Xpos] - i)
			{
				MapCheck[yy][xx + 1] = 0;
				xx++;
			}
			if (MapCheck[yy - 1][xx] == MapCheck[Ypos][Xpos] - i)
			{
				MapCheck[yy - 1][xx] = 0;
				yy--;
			}
			if (MapCheck[yy + 1][xx] == MapCheck[Ypos][Xpos] - i)
			{
				MapCheck[yy + 1][xx] = 0;
				yy++;
			}
		}
	HelpMove(MapCheck[Ypos][Xpos], Ypos, Xpos);
	}
	else//������� �� �������
	{
		std::cout << MapCheck[Ypos][Xpos];
		std::cout << "not;";
	}	
	
	
}

void Npc::HelpMove(int way, int Ypos, int Xpos)
{

	if (MapCheck[LocationNpcY][LocationNpcX - 1] == 0)
	{

		TargetY = LocationNpcY;
		TargetX = LocationNpcX - 1;

		MapCheck[LocationNpcY][LocationNpcX] = -2;
	}
	else
		if (MapCheck[LocationNpcY][LocationNpcX + 1] == 0)
		{
			TargetY = LocationNpcY;
			TargetX = LocationNpcX + 1;

			MapCheck[LocationNpcY][LocationNpcX] = -2;
		}
		else
			if (MapCheck[LocationNpcY - 1][LocationNpcX] == 0)
			{
				TargetX = LocationNpcX;
				TargetY = LocationNpcY - 1;

				MapCheck[LocationNpcY][LocationNpcX] = -2;
			}
			else
				if (MapCheck[LocationNpcY + 1][LocationNpcX] == 0)
				{
					TargetX = LocationNpcX;
					TargetY = LocationNpcY + 1;
					MapCheck[LocationNpcY][LocationNpcX] = -2;
				}

	/*for (int i = 0; i < 34; i++)
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
	}*/
}



void Npc::Collision(std::string map[34])
{
	for (int i = y / TILE; i < (y + HeroY) / TILE; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
		for (int j = x / TILE; j < (x + HeroX) / TILE; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
		{
			if (map[i][j] == '1' || map[i][j] == '2' || map[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
			{
				if (dy > 0)//���� �� ��� ����,
				{
					y = i * TILE - HeroY;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
				//	y -= HeroY/20;
				}
				if (dy < 0)
				{
					y = i * TILE + HeroY * 2;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
				//	y += HeroY/20;
				}
				if (dx > 0)
				{
					//	x -= HeroX/20;
					x = j * TILE - HeroX;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
				}
				if (dx < 0)
				{
					//	x += HeroX/20;
					x = j * TILE + HeroX * 2;//���������� ���� �����
				}

			}

		}
}
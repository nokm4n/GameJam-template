#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"
#define HeroX 50
#define HeroY 50
#define TILE 100

using namespace sf;

void Player::Move(float time, std::string map[25], int height, int width)
{
	
	switch (dir)
	{
	case 1: // �����

		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(HeroX * int(CurrentFrame), HeroY, HeroX, HeroY));

		dx = -speed;
		dy = 0;
		break;
	case 2: // ������
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(HeroX * int(CurrentFrame), HeroY * 2, HeroX, HeroY));
		dx = speed;
		dy = 0;
		break;
	case 3://����
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(HeroX * int(CurrentFrame), HeroY * 3, HeroX, HeroY));
		dy = -speed;
		dx = 0;
		break;
	case 4: // �����
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(HeroX * int(CurrentFrame), HeroY * 0, HeroX, HeroY));
		dy = speed;
		dx = 0;
		break;
	}
	
	x += dx*time;
	y += dy*time;
	Collision(map, height, width);
	speed = dx = dy = 0;

	
	sprite.setPosition(x, y);
}

Player::Player(String F, float X, float Y, float W, float H)
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
	sprite.setTextureRect(IntRect(0, 48, w, h));
}



float Player::getplayercoordinateX()
{
	return x;
}
float Player::getplayercoordinateY()
{
	return y;
}

Player::~Player()
{
}

void Player::Collision(std::string map[34], int Height, int Width)
{
	for (int i = y / TILE; i < (y + HeroY) / TILE; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
		for (int j = x / TILE; j < (x + HeroX) / TILE; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
		{
			if (map[i][j] == '1' || map[i][j] == '2' || map[i][j] == '3' || map[i][j] == '4' || map[i][j] == '5' || map[i][j] == '6' || map[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
			{
				if (dy > 0)//���� �� ��� ����,
				{
					y = i * TILE - HeroY;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
				//	y -= HeroY/20;
				}
				if (dy < 0)
				{
					y = i * TILE + HeroY*2;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
				//	y += HeroY/20;
				}
				if (dx > 0)
				{
				//	x -= HeroX/20;
					x = j * TILE -HeroX;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
				}
				if (dx < 0)
				{
				//	x += HeroX/20;
					x = j * TILE + HeroX*2;//���������� ���� �����
				}
				
			}
			
		}
}

bool Player::PlayerInside(int MapSize, int* Domi, int* Domj, bool* Outside)
{

	for(int i=0; i<MapSize; i++)
		for (int j = 0; j < MapSize; j++)
		{
			if (x > (i * 1200-50) && x<(i * 1200 + 1000) && y>(j * 1200-50) && y < (j * 1200 + 1000))
			{
				*Outside = false;
				*Domi = i;
				*Domj = j;
				return true;
			}
			else
				*Outside = true;
		}
	return false;
	
}


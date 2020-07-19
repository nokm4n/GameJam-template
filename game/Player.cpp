#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"
#define HeroX 50
#define HeroY 50
#define TILE 100

using namespace sf;
using namespace std;


void Player::Move(float time, std::string map[25])
{
	
	switch (dir)
	{
	case 1: // влево

		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(HeroX * int(CurrentFrame), HeroY, HeroX, HeroY));

		dx = -speed;
		dy = 0;
		break;
	case 2: // вправо
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(HeroX * int(CurrentFrame), HeroY * 2, HeroX, HeroY));
		dx = speed;
		dy = 0;
		break;
	case 3://вниз
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(HeroX * int(CurrentFrame), HeroY * 3, HeroX, HeroY));
		dy = -speed;
		dx = 0;
		break;
	case 4: // вверх
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		sprite.setTextureRect(IntRect(HeroX * int(CurrentFrame), HeroY * 0, HeroX, HeroY));
		dy = speed;
		dx = 0;
		break;
	}
	
	x += dx*time;
	y += dy*time;
	Collision(map);
	speed = dx = dy = 0;
	x1 = x/100; y1 = y/100;
	x2 = (x + 50)/100; y2 = (y + 50)/100;
	
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

	for (int i = 0; i < 10; i++)
		inventory[i] = 0;
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

void Player::Collision(std::string map[34])
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
					y = i * TILE + HeroY*2;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
				//	y += HeroY/20;
				}
				if (dx > 0)
				{
				//	x -= HeroX/20;
					x = j * TILE -HeroX;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
				}
				if (dx < 0)
				{
				//	x += HeroX/20;
					x = j * TILE + HeroX*2;//аналогично идем влево
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


void Player::ItemCollect(int itemY, int itemX, int itemID) //Подбирание предмета
{
	if (itemY  <= y && (itemY + 50)  >= y && itemX  <= x && (itemX + 50)  >= x || (itemY <= y && (itemY + 50) >= y && itemX <= x+50 && (itemX + 50) >= x+50))
	{
		inventory[itemID] = true;
		//Инвентарь или что то типо того
	//	std::cout << "item added";
	}
	
}

void Player::ItemInsert(int itemID)
{
	inventory[itemID] = false;
}

void Player::setHp(int hp)
{
	if (hp >= 0 && hp < 100)
	{
		std::cout <<hp << std::endl;
		this->hp = hp;
	}
}

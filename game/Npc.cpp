#include "Npc.h"
#include <SFML/Graphics.hpp>
#include <iostream>


Npc::Npc(String F, float X, float Y, float W, float H)
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
}

Npc::~Npc()
{
}

void Npc::Move(float time, float speed)
{
	LocationNpcX = x / 100;
	LocationNpcY = y / 100;
//	std::cout << LocationNpcX << "/" << LocationNpcY << std::endl;
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

void Npc::IIMove(std::string* Mapp, int TargetX, int TargetY)
{
	
	if (LocationNpcX < TargetX)
	{
		dir= 2;
	}
	if (LocationNpcX > TargetX)
	{
		dir = 1;
	}
	if (LocationNpcY < TargetY)
	{
		dir = 4;
	}
	if (LocationNpcY > TargetY)
	{
		dir = 3;
	}
	if (LocationNpcX == TargetX && LocationNpcY == TargetY)
	{
		dir = 0;
	}
}
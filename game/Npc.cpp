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
}

Npc::~Npc()
{
}

void Npc::Move(float time)
{
	switch (dir)
	{
	case 1:
		dx = -speed;
		dy = 0;
		break;
	case 2:
		dx = speed;
		dy = 0;
		break;
	case 3:
		dy = -speed;
		dx = 0;
		break;
	case 4:
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
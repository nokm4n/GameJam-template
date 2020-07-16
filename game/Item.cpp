#include "Item.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <math.h>

using namespace std;
using namespace sf;

Item::Item(String F, int ItemX, int ItemY, float ModelW, float ModelH, std::string* map)
{
	x = ItemX;
	y = ItemY;

	File = F;
	w = ModelW; h = ModelH;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(Color(41, 33, 59));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(32, 48, w, h));

	sprite.setPosition(x, y);

}

Item::~Item()
{

}

void Item::Active(int PLayerX, int PlayerY)
{
	if (PLayerX/100==x/100 && PlayerY/100==y/100 && (PLayerX+50) / 100 == x / 100 && (PlayerY+50) / 100 == y / 100)
	{
		
	/*	sprite.setPosition(x+100, y);
		x += 100;*/
	}
}
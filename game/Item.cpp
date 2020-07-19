#include "Item.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <math.h>

using namespace std;
using namespace sf;

Item::Item(String F, int ItemX, int ItemY, float ModelW, float ModelH, std::string* map, int itemId)
{
	itemID = itemId;
	x = ItemX;
	y = ItemY;

	File = F;
	w = ModelW; h = ModelH;
	image.loadFromFile("images/" + File);
//	image.createMaskFromColor(Color(41, 33, 59));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));

	sprite.setPosition(x, y);

}

Item::~Item()
{

}

int Item::getX()
{
	//std::cout << x << std::endl;
	return x;
}


int Item::getY()
{
	//std::cout << y << std::endl;
	return y;
}


void Item::Active(int PlayerY, int PlayerX)
{

	{
		if (PlayerX  >= x  && PlayerY  >= y  && (PlayerX)  <= (x+w)  && (PlayerY)  <= (y+h)   || (PlayerX+50 >= x && PlayerY >= y && (PlayerX+50) <= (x + w) && (PlayerY) <= (y + h)) )
		{
		//	std::cout << "item added";
			sprite.setPosition(0, 0);
			//x = 0;
		}
	}
}

void Item::PlaceItem(int Y, int X)
{
	y = Y;
	x = X;
	sprite.setPosition(x, y);
}
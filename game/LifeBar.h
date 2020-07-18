#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <math.h>
using namespace sf;

class LifeBar
{
public:
	Image image;
	Texture t;
	Sprite s;
	int max;
	RectangleShape bar;
	LifeBar(String F);
	void draw(RenderWindow& window);
	void update(int hp);

};
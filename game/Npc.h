#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;

class Npc
{
private:
	float x, y;
public:
	float dx, dy, w, h, speed;
	int dir;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	void Move(float);
	Npc(String, float, float, float, float);
	~Npc();

	float getplayercoordinateX();
	float getplayercoordinateY();
};


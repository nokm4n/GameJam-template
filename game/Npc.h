#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#define NpcX 50 //npc tile size X
#define NpcY 50 //npc tile size Y

using namespace sf;

class Npc
{
private:
	float x, y;
	int LocationNpcX, LocationNpcY;
public:
	float dx, dy, w, h, speed, CurrentFrame=0;
	int dir=0;// 1-left 2-right 3-down 4-up
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	void Move(float time , float speed);
	void IIMove(std::string*, int, int);
	Npc(String File, float PositionX, float PositionY, float ModelW, float ModelH);
	~Npc();

	float getplayercoordinateX();
	float getplayercoordinateY();
};


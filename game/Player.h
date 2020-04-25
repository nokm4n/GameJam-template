#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;

class Player
{
private:
	float x, y;
public:
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	float dx, dy, w, h, speed;

	float CurrentFrame = 0;

	int dir; // 1-left 2-right 3-down 4-up
	void Move(float, std::string[], int, int);
	void Collision(std::string[], int, int);
	float getplayercoordinateX();
	float getplayercoordinateY();
	bool PlayerInside(int MapSize, int* DomX, int* DomY, bool* Outside);
	Player(String File, float PositionX, float PositionY, float ModelW, float ModelH);
	~Player();
};


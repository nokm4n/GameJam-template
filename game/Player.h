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

	int dir;
	void Move(float, std::string[], int, int);
	void Collision(std::string[], int, int);
	float getplayercoordinateX();
	float getplayercoordinateY();
	bool PlayerInside(int, int*, int*, bool*);
	Player(String, float, float, float, float);
	~Player();
};


#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#define MapSize 36

using namespace sf;

class Player
{
private:
	float x, y;
	int x1, x2, y1, y2; //координаты углов игрока
	
	
public:
	bool inventory[10];
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	float dx, dy, w, h, speed;
	float CurrentFrame = 0;
	int dir; // 1-left 2-right 3-down 4-up
	void Move(float, std::string[]);
	void Collision(std::string[]);
	void ItemCollect(int Y, int X, int intemID);
	void ItemInsert(int itemID);
	float getplayercoordinateX();
	float getplayercoordinateY();
	bool PlayerInside(int MapSise, int* DomY, int* DomYX, bool* Outside); // размер карты в блоках(сейчас 3 на 3), у и х координата для дома в котором находимся, переменная внутри/снаружи 
	Player(String File, float PositionX, float PositionY, float ModelW, float ModelH);
	~Player();
};


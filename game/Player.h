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
	void Move(float, std::string[]);
	void Collision(std::string[]);
	float getplayercoordinateX();
	float getplayercoordinateY();
	bool PlayerInside(int MapSize, int* DomY, int* DomYX, bool* Outside); // ������ ����� � ������(������ 3 �� 3), � � � ���������� ��� ���� � ������� ���������, ���������� ������/������� 
	Player(String File, float PositionX, float PositionY, float ModelW, float ModelH);
	~Player();
};


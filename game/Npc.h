#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <stack> 
#define NpcX 50 //npc tile size X
#define NpcY 50 //npc tile size Y

using namespace sf;

class Npc
{
private:
	float x, y;
	float x1, x2, y1, y2; //координаты углов бота
	int LocationNpcX, LocationNpcY;
	std::stack <int> targetY;
	std::stack <int> targetX;
	float dx, dy, w, h, speed, CurrentFrame = 0;
	int dir = 0;// 1-left 2-right 3-down 4-up
	int  MapCheck[36][70];
	int MapTemp[36][70];

	
public:
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	void IsActive(float time , float speed, std::string* map, bool* update); //метод для того что бы нпс "жил"
	void Collision(std::string[]); // тут все понятно и так
	void FindWay(int Ypos, int Xpos); //волновой поиск
	void IIMove(); // простейшее движение
	void map(); // вывод мапы
	void WayPointsMove(int* CountPoints, int **Positions); // проход по вейпоинтам
	void ClearWay(); // Очищение стека
	Npc(String File, float PositionX, float PositionY, float ModelW, float ModelH, std::string* map);
	~Npc();

	float getplayercoordinateX();
	float getplayercoordinateY();
};


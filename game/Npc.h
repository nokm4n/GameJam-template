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
	float x1, x2, y1, y2; //���������� ����� ����
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
	void IsActive(float time , float speed, std::string* map, bool* update); //����� ��� ���� ��� �� ��� "���"
	void Collision(std::string[]); // ��� ��� ������� � ���
	void FindWay(int Ypos, int Xpos); //�������� �����
	void IIMove(); // ���������� ��������
	void map(); // ����� ����
	void WayPointsMove(int* CountPoints, int **Positions); // ������ �� ����������
	void ClearWay(); // �������� �����
	Npc(String File, float PositionX, float PositionY, float ModelW, float ModelH, std::string* map);
	~Npc();

	float getplayercoordinateX();
	float getplayercoordinateY();
};


#include <string>
#include <iostream>
#include <fstream>
#define MapSize 36
//#include  <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
class DrawMap
{
public:
	string tempString[MapSize];// ���� �����
	string randDom[MapSize];// ��� ������� �� ������
	string CopyMap[MapSize];// ����� �����, ��� ���� ��� �� ������� ����� ���� �� ����� � ���
	//sf::String sfString[34];
	DrawMap(string);
	void AddToCopy(); // ����������� ����� �� ����� � ����
	void ChangeDom(int dom, int y, int x); //����� ����, ���������� � � �
	void Drawsprite(RenderWindow & window, Sprite);
	~DrawMap();
};


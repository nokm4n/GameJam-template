#include <string>
#include <iostream>
#include <fstream>
//#include  <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
class DrawMap
{
public:
	string tempString[36];// ���� �����
	string randDom[34];// ��� ������� �� ������
	string CopyMap[36];// ����� �����, ��� ���� ��� �� ������� ����� ���� �� ����� � ���
	//sf::String sfString[34];
	DrawMap(string);
	void AddToCopy(); // ����������� ����� �� ����� � ����
	void ChangeDom(int dom, int y, int x); //����� ����, ���������� � � �
	void Drawsprite(RenderWindow & window, Sprite);
	~DrawMap();
};


#include <string>
#include <iostream>
#include <fstream>
//#include  <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
class DrawMap
{
public:
	string tempString[36];// сама карта
	string randDom[34];// для домиков на замену
	string CopyMap[36];// копия карты, для того что бы помнить какой была до входа в дом
	//sf::String sfString[34];
	DrawMap(string);
	void AddToCopy(); // запоминание карты из темпа в копи
	void ChangeDom(int dom, int y, int x); //номер дома, координаты у и х
	void Drawsprite(RenderWindow & window, Sprite);
	~DrawMap();
};


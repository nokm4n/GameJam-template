#include <string>
#include <iostream>
#include <fstream>
//#include  <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
class DrawMap
{
public:
	string tempString[34];
	string randDom[34];
	//sf::String sfString[34];
	DrawMap(string);
	void ChangeDom(int, int, int);
	void Drawsprite(RenderWindow & window, Sprite);
	~DrawMap();
};


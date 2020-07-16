#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <stack> 

using namespace std;
using namespace sf;

class Item
{
private:
	int x, y, w, h;
	
public:
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Item(String F, int ItemX, int itemY, float ModelW, float ModelH, string* map);
	~Item();
	void Active(int PLayerX, int PlayerY); //взаимодействие с игроком
};


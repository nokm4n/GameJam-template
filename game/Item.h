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
	int itemID;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Item(String F, int ItemX, int itemY, float ModelW, float ModelH, string* map, int itemId);
	~Item();
	void Active(int PlayerY, int PlayerX); //взаимодействие с игроком
	void PlaceItem(int Y, int X);
	int getX();
	int getY();
};


#include  <SFML/Graphics.hpp>
#include "DrawMap.h"
#include <time.h>
#define TILE 100


using namespace std;
using namespace sf;

DrawMap::DrawMap(string map)
{
	int l = 0, k=0;
	std::ifstream file(map);
	while (!file.eof())
	{
		file >> tempString[l];
		l++;

	}
	for (int i = 0; i < 34; i++)
		CopyMap[i] = tempString[i];

	std::ifstream files("d.txt");  /////////////заполнение рандомного дома
	while (!files.eof())
	{
		files >> randDom[k];
		k++;

	}
		//tempString = sfString[k];
	
}
void DrawMap::ChangeDom(int ChangeDom, int startI, int startJ)
{
	srand(time(NULL));
	/////////////////////////////////////////////замена дома на рандомный дом
//	int random = rand() % 2;
//	cout << random;


	if (ChangeDom == 10)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{tempString[i + startI][j + startJ] = CopyMap[i + startI][j + startJ];
				
			}

		}
		
	}
	else
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			tempString[i+startI][j+startJ] = randDom[i][10 * ChangeDom + j];
		}

	}
}


void DrawMap::AddToCopy()
{
	for (int i = 0; i < 34; i++)
	{
		CopyMap[i] = tempString[i];
	}
}


void DrawMap::Drawsprite(RenderWindow & window, Sprite s_map)
{
	
	for (int i = 0; i < 34; i++)
		for (int j = 0; j < 34; j++)
		{
			switch (tempString[i][j])
			{
			case '1':
			{
				s_map.setTextureRect(IntRect(TILE * 5, TILE * 3, TILE, TILE));
				break;
			}
			case '2':
			{
				s_map.setTextureRect(IntRect(TILE * 1, TILE * 0, TILE, TILE));
				break;
			}
			case '3':
			{
				s_map.setTextureRect(IntRect(TILE * 2, TILE * 0, TILE, TILE));
				break;
			}
			case '4':
			{
				s_map.setTextureRect(IntRect(TILE * 3, TILE * 0, TILE, TILE));
				break;
			}
			case '5':
			{
				s_map.setTextureRect(IntRect(TILE * 4, TILE * 0, TILE, TILE));
				break;
			}
			case '6':
			{
				s_map.setTextureRect(IntRect(TILE * 5, TILE * 0, TILE, TILE));
				break;
			}
			case '7':
			{
				s_map.setTextureRect(IntRect(TILE * 6, TILE * 0, TILE, TILE));
				break;
			}
			case '8':
			{
				s_map.setTextureRect(IntRect(TILE * 0, TILE * 0, TILE, TILE));
				break;
			}
			case '0':
			{
				s_map.setTextureRect(IntRect(TILE * 7, TILE * 0, TILE, TILE));
				break;
			}
			default:
			{
				s_map.setTextureRect(IntRect(TILE * 1, TILE * 6, TILE, TILE));
				break;
			}
			}
			s_map.setPosition(j * TILE, i * TILE);

			window.draw(s_map);
		}
}


DrawMap::~DrawMap()
{
}

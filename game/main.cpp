#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <sstream>
#include "Player.h"
#include "Npc.h"
#include "DrawMap.h"
#include "im/imgui.h"
#include "im/imgui-sfml.h"
#define HeroX 50 //hero tile size X
#define HeroY 50 //hero tile size Y
#define ScreenX 1024
#define ScreenY 720
#define TILE 100

const int HEIGHT_MAP = 34;//������ ����� ������
const int WIDTH_MAP = 34;//������ ����� ������ 
using namespace sf;


View view;



void getplayercoordinateforview(float x, float y)
{
	view.setCenter(x, y);
}



int main()
{
	setlocale(LC_ALL, "Russian");
	float CurrentFrame=0;
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	//RenderWindow window(VideoMode(1920, 1080), "Game", Style::Fullscreen);
	RenderWindow window(VideoMode(1024, 720), "Game");
	view.reset(FloatRect(0, 0, 1920, 1080));
	Clock clock;
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	ImGui::SFML::Init(window);			////////////////////////////////////////////////////Im GUi

	Player player("hero.png", 1000, 1000, HeroX, HeroY);
	DrawMap mapp("karta.txt");
	//menu(window);
	
	Npc npc("hero.png", 1100, 1100, HeroX, HeroY, mapp.tempString);

	bool Outside = false;
	bool flagOutside = true;
	int CounterWayPoints = 5; //���������� ����������
	 // ������ ����������
	int** WayPoints = new int* [5];
	for (int i = 0; i < 5; i++)
		WayPoints[i] = new int[2];




	WayPoints[0][0] = 10;
	WayPoints[0][1] = 10;
	WayPoints[1][0] = 15;
	WayPoints[1][1] = 15;
	WayPoints[2][0] = 10;
	WayPoints[2][1] = 10;
	WayPoints[3][0] = 15;
	WayPoints[3][1] = 15;
	WayPoints[4][0] = 10;
	WayPoints[4][1] = 10;


	int DomI=0, DomJ=0; // ���������� ��� ����������� ���� � ������� ���������
	int perem[3] = {0, 0, 0}; ////////////// ����� ���� ������� ����������� �� �������, ��������� ������� ���� �� � � �
	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
		Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/800;
		Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);  			////////////////////////////////////////////////////Im GUi
			if (event.type == Event::Closed)
				window.close();
			
		}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
				//pause(window);
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.dir = 1; player.speed = 0.6;
				player.CurrentFrame += 0.005*time;

			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.dir = 2; player.speed = 0.6;
				player.CurrentFrame += 0.005*time;
				
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.dir = 3; player.speed = 0.6;
				player.CurrentFrame += 0.005*time;
				
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.dir = 4; player.speed = 0.6;
				player.CurrentFrame += 0.005*time;
	
				
			}
			if (flagOutside)
			{
				if (player.PlayerInside(3, &DomI, &DomJ, &Outside))
				{
					mapp.ChangeDom(3, DomJ * 12, DomI * 12);
				}
				if (Outside)
				{
					mapp.ChangeDom(10, DomJ * 12, DomI * 12);
				}
			}



	/*		float dX = pos.x - player.getplayercoordinateX();//������ , ����������� ������, ������� ���������� ������ � ������
			float dY = pos.y - player.getplayercoordinateY();//�� ��, ���������� y
			float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
			player.sprite.setRotation(rotation);//������������ ������ �� ��� �������
			////////////////////////////////////////////////////Im GUi*/
			

			ImGui::SFML::Update(window, clock.restart());

			ImGui::Begin("Sample window"); // ������ ����

			if (ImGui::Button("Inside/Outside on/off"))
			{
				flagOutside = !flagOutside;
			}

			if (ImGui::Button("My Coord")) 
			{
				cout << player.getplayercoordinateX() / 100 << " " << player.getplayercoordinateY() / 100 << endl;
			}
			if (ImGui::Button("Bot Coord"))
			{
				cout << npc.getplayercoordinateX()/100 << " " << npc.getplayercoordinateY() / 100 << endl;
			}

			ImGui::InputInt3("number house", perem); ///// ������ ���������� ����� ����, ������ � ������ ��������
			if (ImGui::Button("Change dom"))
			{
				mapp.ChangeDom(perem[0], perem[1]*12, perem[2]*12); 
				mapp.AddToCopy();
				npc.FindWay(17, 17);
			}

			ImGui::End(); // end window
			////////////////////////////////////////////////////Im GUi
		//	
		//	npc.WayPointsMove(&CounterWayPoints, WayPoints);
	//	npc.FindWay(player.getplayercoordinateX()/100, player.getplayercoordinateY()/100);
		
		getplayercoordinateforview(player.getplayercoordinateX(), player.getplayercoordinateY());
		player.Move(time, mapp.tempString);
		
	//	npc.WayPointsMove(&CounterWayPoints, Targets);
		npc.IsActive(time, 0.2);

		window.setView(view);
		window.clear();

		mapp.Drawsprite(window, s_map); //////////risovka karti

		window.draw(npc.sprite);
		window.draw(player.sprite);
		ImGui::SFML::Render(window);
		window.display();
		
		
	}
	ImGui::SFML::Shutdown();

	return 0;
}
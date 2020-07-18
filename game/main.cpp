#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <sstream>
#include "Player.h"
#include "Npc.h"
#include "LifeBar.h"
#include "Item.h"
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
using namespace std;

View view;



void getplayercoordinateforview(float x, float y)
{
	view.setCenter(x+25, y+25);
}



int main()
{
	setlocale(LC_ALL, "Russian");
	float CurrentFrame=0; // ������� ���� ��������
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
	Item item("item.png", 1100, 1000, HeroX, HeroY, mapp.tempString, 1);
	Item item2("item.png", 1200, 1000, HeroX, HeroY, mapp.tempString, 2);

	LifeBar lifeBarPlayer("life2.png");


	int hp = 0;
	//menu(window);
	bool noise = false;
	int noiseKoord[2];
	float botSpeed = 0.4;
	Npc npc("hero.png", 1000, 1000, HeroX, HeroY, mapp.tempString);
	bool update = true; //���������� ��� ���������� ����� � ����
	bool Outside = false; // ���������� ���������� �������/������
	bool flagOutside = true; // ���������� ��� ���������/���������� ����������� �����/����� �� ����
	int CounterWayPoints = 5; //���������� ����������

	/*int** WayPoints = new int* [5];  // ������ ����������
	for (int i = 0; i < 5; i++)
		WayPoints[i] = new int[2];

	int waycount= 5;


	WayPoints[0][0] = 10;
	WayPoints[0][1] = 10;
	WayPoints[1][0] = 15;
	WayPoints[1][1] = 15;
	WayPoints[2][0] = 10;
	WayPoints[2][1] = 10;
	WayPoints[3][0] = 15;
	WayPoints[3][1] = 15;
	WayPoints[4][0] = 10;
	WayPoints[4][1] = 10;*/

	int Target[2] = { 10, 10 }; // ���� ���� y/x
	int tempTarget[2] = { 10, 10 }; //���� �������������� � ui
	int DomI=0, DomJ=0; // ���������� ��� ����������� ���� � ������� ���������
	int perem[3] = {1, 1, 0}; // ����� ���� ������� ����������� �� �������, ��������� ������� ���� �� � � �
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
		if (Keyboard::isKeyPressed(Keyboard::E)) // ����� �������
		{
		//	view.zoom(0.995);
			player.ItemCollect(item.getY(), item.getX(), item.itemID);
			item.Active(player.getplayercoordinateY(), player.getplayercoordinateX());

			player.ItemCollect(item2.getY(), item2.getX(), item2.itemID);
			item2.Active(player.getplayercoordinateY(), player.getplayercoordinateX());
			
		}
		
		if (Keyboard::isKeyPressed(Keyboard::T)) // �������� �������
		{
			//	view.zoom(0.995);
			if (player.inventory[item.itemID])
			{
				item.PlaceItem(player.getplayercoordinateY(), player.getplayercoordinateX());
				player.ItemInsert(item.itemID);
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::R)) // �������� �������
		{
			if (player.inventory[item2.itemID])
			{
				item2.PlaceItem(player.getplayercoordinateY(), player.getplayercoordinateX());
				player.ItemInsert(item2.itemID);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Add)) // ����������� ������
		{
			view.zoom(0.995);
		}
		if (Keyboard::isKeyPressed(Keyboard::Subtract))// ��������� ������
		{
			view.zoom(1.005);
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


		/*float dX = pos.x - player.getplayercoordinateX();//������ , ����������� ������, ������� ���������� ������ � ������
		float dY = pos.y - player.getplayercoordinateY();//�� ��, ���������� y
		float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
		player.sprite.setRotation(rotation);//������������ ������ �� ��� �������*/
	

		////////////////////////////////////////////////////Im GUi
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
			cout << npc.getplayercoordinateX() << " " << npc.getplayercoordinateY()  << endl;
			
		}
		if (ImGui::Button("Test"))
		{
			npc.map(); //�� �������� �� ����� ��������� ���������� � ������� IIActive
			//npc.HelpMove();
			//npc.FindWay(player.getplayercoordinateY(), player.getplayercoordinateX());
			//npc.FindWay(17, 17);
		}

		ImGui::InputInt3("number house", perem); ///// ������ ���������� ����� ����, ������ � ������ ��������
		if (ImGui::Button("Change dom"))
		{
			update = true;
			mapp.ChangeDom(perem[0], perem[1]*12, perem[2]*12); 
			mapp.AddToCopy();
		}
		ImGui::InputInt2("Bot smart movement coord y/x", tempTarget);
		if (ImGui::Button("Bot start smart"))
		{
			Target[0] = tempTarget[0];
			Target[1] = tempTarget[1];
			npc.FindWay(Target[0], Target[1]);

		}
		if (ImGui::Button("Clear way"))
		{
			npc.ClearWay();

		}
		if (ImGui::SliderInt("Hp", &hp, 0, 100))
		{
			player.setHp(hp);
			lifeBarPlayer.update(hp);
		}
		if (ImGui::Button("Noise"))
		{
			noise = true;
			noiseKoord[0] = floor(player.getplayercoordinateY() / 100);
			noiseKoord[1] = floor(player.getplayercoordinateX() / 100);
			npc.FindWay(noiseKoord[0], noiseKoord[1]);

		}

		ImGui::InputFloat("Speed", &botSpeed);
		ImGui::End(); // end window
		////////////////////////////////////////////////////Im GUi	
		
		 //�������������� � �������

		

		getplayercoordinateforview(player.getplayercoordinateX(), player.getplayercoordinateY());
		player.Move(time, mapp.tempString);
		npc.IsActive(time, botSpeed, mapp.tempString, &update);
		//npc.FindWay(Target[0], Target[1]);
		//npc.WayPointsMove(&waycount, WayPoints);
		
		window.setView(view);
		window.clear();
		mapp.Drawsprite(window, s_map); //////////������� �����
		window.draw(item.sprite);
		window.draw(item2.sprite);
		window.draw(npc.sprite);
		window.draw(player.sprite);
		lifeBarPlayer.draw(window);
		ImGui::SFML::Render(window);
		window.display();
		
	}
	ImGui::SFML::Shutdown();

	return 0;
}
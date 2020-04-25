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

const int HEIGHT_MAP = 34;//размер карты высота
const int WIDTH_MAP = 34;//размер карты ширина 
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
	
	Npc npc("hero.png", 1100, 1100, HeroX, HeroY);

	////////////////////////////////////////////////////Im GUi
	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };
	char windowTitle[255] = "ImGui + SFML = <3";
	window.setTitle(windowTitle);
	////////////////////////////////////////////////////Im GUi

	bool Outside = false;
	int DomI=0, DomJ=0; // Переменные для определения дома в котором находимся
	int perem[3] = {0, 0, 0}; ////////////// Номер дома который вытаскиваем из рандома, стартовая позиция дома по Х и У
	npc.speed = 0.3;
	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
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
			
			if (player.PlayerInside(3, &DomI, &DomJ, &Outside))
			{
				mapp.ChangeDom(3, DomJ*12, DomI*12);
			}
			if(Outside)
			{
				mapp.ChangeDom(10, DomJ * 12, DomI * 12);
			}




	/*		float dX = pos.x - player.getplayercoordinateX();//вектор , колинеарный прямой, которая пересекает спрайт и курсор
			float dY = pos.y - player.getplayercoordinateY();//он же, координата y
			float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
			player.sprite.setRotation(rotation);//поворачиваем спрайт на эти градусы
			////////////////////////////////////////////////////Im GUi*/
			

			ImGui::SFML::Update(window, clock.restart());

			ImGui::Begin("Sample window"); // создаём окно

			if (ImGui::ColorEdit3("Background color", color)) {

				bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
				bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
				bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
			}

			ImGui::InputText("Window title", windowTitle, 255);

			if (ImGui::Button("Update window title")) {
				// этот код выполняется, когда юзер жмёт на кнопку
				// здесь можно было бы написать 
				// if(ImGui::InputText(...))
				window.setTitle(windowTitle);
			}
			ImGui::InputInt3("number house", perem); ///// первая переменная номер дома, вторая и третья квадраты
			if (ImGui::Button("Change dom"))
			{
				mapp.ChangeDom(perem[0], perem[1]*12, perem[2]*12); 
				mapp.AddToCopy();
			}

			ImGui::End(); // end window
			////////////////////////////////////////////////////Im GUi

			


			
		getplayercoordinateforview(player.getplayercoordinateX(), player.getplayercoordinateY());
		player.Move(time, mapp.tempString, HEIGHT_MAP, WIDTH_MAP);
		npc.IIMove(mapp.CopyMap, 10, 5);
		npc.Move(time, 0.2);


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
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "Npc.h"
#include "DrawMap.h"
#include "imgui.h"
#include "imgui-sfml.h"
#define HeroX 50
#define HeroY 50
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
/*
void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/play2.png");
	menuTexture2.loadFromFile("images/exit2.png");
	menuBackground.loadFromFile("images/LoGo.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 60);
	menu2.setPosition(100, 120);
	menuBg.setPosition(0, 0);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 60, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu1.setColor(Color::Blue);
			menuNum = 1;
		}
		else
		{
			menu1.setColor(Color::White);
		}
		if (IntRect(100, 120, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu2.setColor(Color::Blue);
			menuNum = 2;
		}
		else
		{
			menu2.setColor(Color::White);
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
	////////////////////////////////////////////////////
}

void pause(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/play2.png");
	menuTexture2.loadFromFile("images/exit2.png");
	menuBackground.loadFromFile("images/LoGo.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(-833, -520);
	menu2.setPosition(-833, -470);
	menuBg.setPosition(-960, -539);
	view.setCenter(0, 0);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		window.clear();
		window.setView(view);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 60, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu1.setColor(Color::Blue);
			menuNum = 1;
		}
		else
		{
			menu1.setColor(Color::White);
		}
		if (IntRect(100, 120, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu2.setColor(Color::Blue);
			menuNum = 2;
		}
		else
		{
			menu2.setColor(Color::White);
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
	////////////////////////////////////////////////////
}

*/


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
	
	

	////////////////////////////////////////////////////Im GUi
	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };
	char windowTitle[255] = "ImGui + SFML = <3";
	window.setTitle(windowTitle);
	////////////////////////////////////////////////////Im GUi


	int perem[3] = {0, 0, 0}; ////////////// Номер дома который вытаскиваем из рандома, стартовая позиция дома по Х и У

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
				CurrentFrame += 0.005*time;

				if (CurrentFrame > 4)
					CurrentFrame = 0;
				player.sprite.setTextureRect(IntRect(HeroX*int(CurrentFrame), HeroY, HeroX, HeroY));
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.dir = 2; player.speed = 0.6;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4)
					CurrentFrame = 0;
				player.sprite.setTextureRect(IntRect(HeroX*int(CurrentFrame), HeroY*2, HeroX, HeroY));
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.dir = 3; player.speed = 0.6;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4)
					CurrentFrame = 0;
				player.sprite.setTextureRect(IntRect(HeroX*int(CurrentFrame), HeroY*3, HeroX, HeroY));
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.dir = 4; player.speed = 0.6;
				CurrentFrame += 0.005*time;
	
				if (CurrentFrame > 4)
					CurrentFrame = 0;
				player.sprite.setTextureRect(IntRect(HeroX*int(CurrentFrame), HeroY *0, HeroX, HeroY));
			}
			float dX = pos.x - player.getplayercoordinateX();//вектор , колинеарный прямой, которая пересекает спрайт и курсор
			float dY = pos.y - player.getplayercoordinateY();//он же, координата y
			float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
			player.sprite.setRotation(rotation);//поворачиваем спрайт на эти градусы
			////////////////////////////////////////////////////Im GUi
			

			ImGui::SFML::Update(window, clock.restart());

			ImGui::Begin("Sample window"); // создаём окно

			// Инструмент выбора цвета
			if (ImGui::ColorEdit3("Background color", color)) {
				// код вызывается при изменении значения, поэтому всё
				// обновляется автоматически
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
				
			}

			ImGui::End(); // end window
			////////////////////////////////////////////////////Im GUi




			
			getplayercoordinateforview(player.getplayercoordinateX(), player.getplayercoordinateY());
			player.Move(time, mapp.tempString, HEIGHT_MAP, WIDTH_MAP);
			window.setView(view);
			window.clear();

			mapp.Drawsprite(window, s_map); //////////risovka karti
			
		window.draw(player.sprite);
		ImGui::SFML::Render(window);
		window.display();
		
		
	}
	ImGui::SFML::Shutdown();

	return 0;
}
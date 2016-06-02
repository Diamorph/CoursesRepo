#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include <sstream>

using namespace sf;
#include <SFML/Graphics.hpp>
////////////////////////////////////////////////////����� ������////////////////////////
class Player { // ����� ������
public:
	float x, y, w, h, dx, dy, speed = 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir = 0; //����������� (direction) �������� ������
	String File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������

	Player(String F, float X, float Y, float W, float H){  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		File = F;//��� �����+����������
		w = W; h = H;//������ � ������
		image.loadFromFile("images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������
		x = X; y = Y;//���������� ��������� �������
		sprite.setTextureRect(IntRect(0, 110, w, h));  //������ ������� ���� ������������� ��� ������ ������ ���������, � �� ���� �����. IntRect - ���������� �����
	}

	void update(float time) //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
		{
		case 0: dx = speed; dy = 0;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
		case 1: dx = -speed; dy = 0;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
		case 2: dx = 0; dy = speed;   break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
		case 3: dx = 0; dy = -speed;   break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
		}

		x += dx*time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
		y += dy*time;//���������� �� ������

		speed = 0;//�������� ��������, ����� �������� �����������.
		sprite.setPosition(x, y); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
	}
};

int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Chris Jumper");
	float CurrentFrame = 0;//������ ������� ����
	Clock clock;
	Player p("capitan.png", 100, 100, 70.0, 120.0);//������� ������ p ������ player,������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.
	
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		clock.restart(); //������������� �����
		time = time / 800;
		//sf::Event event;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Left)) { 
			p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
			CurrentFrame += 0.005*time;
			//CurrentFrame += 0.005*time;
			if (CurrentFrame > 10) CurrentFrame -= 10;
			p.sprite.setTextureRect(IntRect(110+110*int(CurrentFrame), 0, -110, 110));
		} 
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dir = 0; p.speed = 0.1;//����������� ������, �� ����
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 10) CurrentFrame -= 10; 
			p.sprite.setTextureRect(IntRect(0+110*int(CurrentFrame), 0, 110, 110));
		} 
		if (Keyboard::isKeyPressed(Keyboard::Up)) { 
			p.dir = 3; p.speed = 0.1;//����������� ����, �� ����
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 12) CurrentFrame -= 12;
			p.sprite.setTextureRect(IntRect(0 + 75*int(CurrentFrame), 1980, 75, 140));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			p.dir = 2; p.speed = 0.1;//����������� �����, �� ����
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 12) CurrentFrame -= 12;
			p.sprite.setTextureRect(IntRect(900 - 75 *int(CurrentFrame), 1980, -75, 140));
		} 
		p.update(time);//�������� ������ p ������ Player � ������� ������� sfml, ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������

	
		window.clear();
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}


/*
using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Lesson 3. kychka-pc.ru"); //��������� ��� �������� ������ ����



	Texture herotexture;//������� ������ Texture (��������)
	herotexture.loadFromFile("cyclops.png");//��������� ��������

	Sprite herosprite;//������� ������ Sprite(������)
	herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
	herosprite.setPosition(50, 25);//������ ��������� ���������� ��������� �������

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(herosprite);//������� ������ �� �����
		window.display();
	}

	return 0;
}
*/
/*
class Player {
private: float x, y;
public:
	float w, h, dx, dy, speed;
	int dir, playerScore;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H){
		dir = 0; playerScore = 0;
		dx = 0; dy = 0; speed = 0;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;

		}

		x += dx*time;
		y += dy*time;

		speed = 0;
		sprite.setPosition(x, y);
		interactionWithMap();
	}

	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){
		return y;
	}




	void interactionWithMap()
	{

		for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')
			{
				if (dy>0)
				{
					y = i * 32 - h;
				}
				if (dy<0)
				{
					y = i * 32 + 32;
				}
				if (dx>0)
				{
					x = j * 32 - w;
				}
				if (dx < 0)
				{
					x = j * 32 + 32;
				}
			}

			if (TileMap[i][j] == 's') {
				playerScore++;
				TileMap[i][j] = ' ';
			}
		}
	}

};

int main()
{
	RenderWindow window(VideoMode(640, 480), "Chris Jumper");
	view.reset(FloatRect(0, 0, 640, 480));

	Font font; 
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setColor(Color::Red);
	text.setStyle(Text::Bold);

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);


	Player p("hero.png", 250, 250, 96.0, 96.0);


	float CurrentFrame = 0;
	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.dir = 1; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));

		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dir = 0; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			p.dir = 3; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 307, 96, 96));// 
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			p.dir = 2; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));

		}


		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		p.update(time);

		window.setView(view);
		window.clear();


		
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));


			s_map.setPosition(j * 32, i * 32);

			window.draw(s_map);
		}
		std::ostringstream playerScoreString;    
		playerScoreString << p.playerScore;		
		text.setString("������� ������:" + playerScoreString.str());
		text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);
		window.draw(text);

		window.draw(p.sprite);

		window.display();
	}

	return 0;
}*/
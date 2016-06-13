#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include <sstream>
#include "mission.h"
#include "menu.h"
#include "LifeBar.h"
#include "level.h"
#include <vector>
#include <list>

using namespace sf;

class Entity {
public:
	std::vector<Object> obj;//������ �������� �����
	float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����
	int w, h, health;
	bool life, isMove, onGround, kickL, kickR, kickUp;

	virtual void update(float time) = 0;
	Texture texture;
	Sprite sprite;
	String name;//����� ����� ���� ������, �� �� ����� ������ ������ ����� ��� �����.����� ���� �������� ������ �� ����� � ����� ������� ���� �������� � update � ����������� �� �����
	Entity(Image &image, String Name, float X, float Y, int W, int H){
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		kickL = false; kickR = false; kickUp = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
		FloatRect getRect(){//�-��� ��������� ��������������. ��� �����,������� (���,�����).
			return FloatRect(x, y, w, h);//��� �-��� ����� ��� �������� ������������ 
		}
		int getHealth(){
			return health;
		}
};

class Enemy :public Entity{
public:
	enum { left, right }state;
	float CurrentFrame = 0;
	float CurrentFrame1 = 0;
	Enemy(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
		obj = lev.GetObjects("solid");//��������������.�������� ������ ������� ��� �������������� ����� � ������
		if (name == "EasyEnemy"){
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;//���� ��������.���� ������ ������ ���������
		}
		if (name == "HardEnemy"){
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;//���� ��������.���� ������ ������ ���������
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (int i = 0; i<obj.size(); i++)//���������� �� ��������
		if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			if (obj[i].name == "solid")//���� ��������� �����������
			{
				if (Dy>0)	{ y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0)	{ x = obj[i].rect.left - w; dx = -0.1; sprite.scale(-1, 1); state = left; }
				if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); state = right; }
			}
		}

	}
	void control(float time,float dx){
		if (dx < 0){
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6) CurrentFrame -= 6;
			sprite.setTextureRect(IntRect(920 - 80 * int(CurrentFrame), 0, -80, 110));
		}
		if (dx > 0){
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6) CurrentFrame -= 6;
			sprite.setTextureRect(IntRect(920 - 80 * int(CurrentFrame), 0, -80, 110));
		}
	}

	void control_1(float time, float dx){
		if (dx < 0){
			CurrentFrame1 += 0.005 * time;
			if (CurrentFrame1 > 4) CurrentFrame1 -= 4;
			sprite.setTextureRect(IntRect(880 - 80 * int(CurrentFrame1), 0, -80, 125));
		}
		if (dx > 0){
			CurrentFrame1 += 0.005 * time;
			if (CurrentFrame1 > 4) CurrentFrame1 -= 4;
			sprite.setTextureRect(IntRect(880 - 80 * int(CurrentFrame1), 0, -80, 125));
		}
	}
	void update(float time)
	{
		if (name == "EasyEnemy"){//��� ��������� � ����� ������ ������ ����� �����
			control(time, dx);
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//������ ����������� �������� ������ 3 ���
			checkCollisionWithMap(dx, 0);//������������ ������������ �� �
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
			if (health <= 0){ life = false; }
		}
		if (name == "HardEnemy"){//��� ��������� � ����� ������ ������ ����� �����
			control_1(time, dx);
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//������ ����������� �������� ������ 3 ���
			checkCollisionWithMap(dx, 0);//������������ ������������ �� �
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
			if (health <= 0){ life = false; }
		}
	}
};

class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������
	int playerScore;
	float CurrentFrame = 0;//��� ���������� ����� ���� ������ � ������
	bool isShoot = false;

	Player(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
		playerScore = 0; state = stay; obj = lvl.GetAllObjects();//��������������.�������� ��� ������� ��� �������������� ��������� � ������
		if (name == "Player1"){
			sprite.setTextureRect(IntRect(0, 110, w, h));
		}
	}

	void control(float time){
		if (Keyboard::isKeyPressed){//���� ������ �������
			if (Keyboard::isKeyPressed(Keyboard::Left)) {//� ������ �����
				state = left; speed = 0.1;
				CurrentFrame += 0.005*3*time;
				if (CurrentFrame > 10) CurrentFrame -= 10;
				sprite.setTextureRect(IntRect(110 + 110 * int(CurrentFrame), 0, -110, 110));
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				state = right; speed = 0.1;
				CurrentFrame += 0.005*3*time;
				if (CurrentFrame > 10) CurrentFrame -= 10;
				sprite.setTextureRect(IntRect(0 + 110 * int(CurrentFrame), 0, 110, 110));
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {//���� ������ ������� ����� � �� �� �����, �� ����� �������
				state = jump; dy = -0.7; onGround = false;//�������� ������ ������
				CurrentFrame += 0.005*3*time;
				if (CurrentFrame > 12) CurrentFrame -= 12;
				sprite.setTextureRect(IntRect(0 + 75 * int(CurrentFrame), 1980, 75, 140));
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down;
				CurrentFrame += 0.005*3*time;
				if (CurrentFrame > 12) CurrentFrame -= 12;
				sprite.setTextureRect(IntRect(900 - 75 * int(CurrentFrame), 1980, -75, 140));
			}
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (int i = 0; i<obj.size(); i++)//���������� �� ��������
		if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			if (obj[i].name == "solid")//���� ��������� �����������
			{
				if (Dy>0)	{ y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0)	{ x = obj[i].rect.left - w; }
				if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
	}

	void update(float time)
	{
		control(time);//������� ���������� ����������
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
		case right:dx = speed; break;//��������� ���� ������
		case left:dx = -speed; break;//��������� ���� �����
		case up: break;//����� ��������� �������� ������ (�������� �� ��������)
		case down: dx = 0; break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		case stay: break;//� ����� ����		
		}
		if (kickUp) { dy = -0.65; kickUp = false; }
		if (kickR) {
			dx = 0.3;
		}
		if (kickL) {
			dx = -0.3;
		}
		if (onGround) { kickR = false; kickL = false; }
		x += dx*time;
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		y += dy*time;
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		if (health <= 0){ life = false; }
		if (!isMove){ speed = 0; }
		if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0015*time;//��������� ������������� � �����
	}
};

class Bullet :public Entity{//����� ����
public:
	int direction;//����������� ����

	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H){//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
		obj = lvl.GetObjects("solid");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
		//���� ������������� � ������������
	}


	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;//������� �������� state = left
		case 1: dx = speed; dy = 0;   break;//������� �������� state = right
		case 2: dx = 0; dy = -speed;   break;//������� �������� state = up
		case 3: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������, ���� ������ ��������� �����, ��� ������ ��� �� �����
		case 4: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������, ���� ������ ��������� �����, ��� ������ ��� �� �����
		case 5: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������, ���� ������ ��������� �����, ��� ������ ��� �� �����
		}

		x += dx*time;//���� �������� ���� �� �
		y += dy*time;//�� �

		if (x <= 0) x = 1;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������
		if (y <= 0) y = 1;
		for (int i = 0; i < obj.size(); i++) {//������ �� �������� solid
			if (getRect().intersects(obj[i].rect)) //���� ���� ������ ���������� � �����,
			{	
				life = false;// �� ���� �������

			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����
	}
};

void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/1.png");
	menuTexture2.loadFromFile("images/2.png");
	menuTexture3.loadFromFile("images/3.png");
	aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/menu_fon.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(345, 0);

	//////////////////////////////����///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//���� ������ ������ ������, �� ������� �� ���� 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3)  { window.close(); isMenu = false;}

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}

void changeLevel(Level &lvl, int &numberLevel) {
	if (numberLevel == 1) { lvl.LoadFromFile("map.tmx"); }
	if (numberLevel == 2) { lvl.LoadFromFile("level.tmx"); }
	//if (numberLevel == 3) { lvl.LoadFromFile("map3.tmx"); }
}

bool startGame(RenderWindow &window, int &numberLevel){
	bool showMissionText = true;//���������� ����������, ���������� �� ��������� ������ ������ �� ������
	//RenderWindow window(VideoMode(640, 600), "Chris Jumper");
	//menu(window);//����� ����
	view.reset(FloatRect(0, 0, 640, 600));


	Level lvl;//������� ��������� ������ �������
	changeLevel(lvl, numberLevel);//��� �������� ����� ��� ������� ������
	//lvl.LoadFromFile("map.tmx");//��������� � ���� �����, ������ ������ � ������� ������� �� �� ����������.

	Font font;//����� 
	font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setColor(Color::Black);

	Music music;//������� ������ ������
	music.openFromFile("sounds/01.ogg");//��������� ����
	music.play();//������������� ������
	music.setLoop(true);

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //���������� �����, ������� �������� ��������
	s_quest.setScale(0.6f, 0.6f);//���� ��������� ��������, => ������ ���� ������

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image heroImage;
	heroImage.loadFromFile("images/capitan.png");

	Image BulletImage;//����������� ��� ����
	BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ �����������
	BulletImage.createMaskFromColor(Color(0, 0, 0));//����� ��� ���� �� ������� �����

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/EasyEnemy.png");
	//easyEnemyImage.createMaskFromColor(Color(255, 0, 0));//����� �� �����

	Image hardEnemyImage;
	hardEnemyImage.loadFromFile("images/HardEnemy.png");

	SoundBuffer shootBuffer;//������ ����� ��� �����
	shootBuffer.loadFromFile("sounds/shoot.wav");//��������� � ���� ����
	Sound shoot(shootBuffer);//������� ���� � ��������� � ���� ���� �� ������


	std::list<Entity*>  entities;//������ ������, ���� ���� ������ �������.�������� ������.
	std::list<Entity*>::iterator it;//�������� ����� ��������� �� ��-��� ������
	std::list<Entity*>::iterator it2;//������ ��������.��� �������������� ����� ��������� ������



	LifeBar lifeBarPlayer;//��������� ������ ������� ��������
	Object player = lvl.GetObject("player");//������ ������ �� ����� �����.������ ���������� ������ � ������ ��� ������ ����

	std::vector<Object> e = lvl.GetObjects("EasyEnemy");//��� ������� ����� �� tmx ����� �������� � ���� �������


	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 70, 120);//�������� ���������� �������������� player �� ����� � ���������� ������ ������
	for (int i = 0; i < e.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 80, 110));//� ���������� � ������ ���� ����� ������ � �����
	e = lvl.GetObjects("HardEnemy");
	for (int i = 0; i < e.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
		entities.push_back(new Enemy(hardEnemyImage, "HardEnemy", lvl, e[i].rect.left, e[i].rect.top, 80, 125));//� ���������� � ������ ���� ����� ������ � �����

	Clock clock;
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F)
				{
					entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x + 55, p.y + 55, 16, 16, p.state));
					shoot.play();//������ ���� ����
				}
				if ((event.key.code == Keyboard::Tab)) {//���� ������� ���


					switch (showMissionText) {//�������������, ����������� �� ���������� ���������� showMissionText

					case true: {
								   std::ostringstream playerHealthString;//������ �������� ������
								   playerHealthString << p.health; //������� � ������ �������� 
								   std::ostringstream task;//������ ������ ������
								   task << getTextMission(getCurrentMission(p.x));//���������� ������� getTextMission (��� ���������� ����� ������), ������� ��������� � �������� ��������� ������� getCurrentMission(������������ ����� ������), � ��� ��� �-��� ��������� � �������� ��������� ������� p.getplayercoordinateX() (��� �-��� ���������� ��� ���������� ������)
								   text.setString("��������: " + playerHealthString.str() + "\n" + task.str());//������
								   text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//������� ����� ����� ���������� �����
								   s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//������� ���� ��� �����
								   showMissionText = false;//��� ������ ��������� ������ ��� ��� �� ������ �� ������
								   break;//������� , ����� �� ��������� ������� "false" (������� ����)
					}
					case false: {
									text.setString("");//���� �� ������ ������� ���, �� ���� ���� ����� ������
									showMissionText = true;// � ��� ������ ��������� ����� ������ ������� ��� � �������� ����� �� �����
									break;
					}
					}
				}
				/*if ((event.key.code == Keyboard::Tab)) {//���� ������� ���
				std::ostringstream task;//������ ������ ������
				task << getTextMission(getCurrentMission(p.x));//���������� ������� getTextMission (��� ���������� ����� ������), ������� ��������� � �������� ��������� ������� getCurrentMission(������������ ����� ������), � ��� ��� �-��� ��������� � �������� ��������� ������� p.getplayercoordinateX() (��� �-��� ���������� ��� ���������� ������)
				text.setString(task.str());//������
				text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//������� ����� ����� ���������� �����
				showMissionText = false;
				break;
				}*/
			}

		}
		for (it = entities.begin(); it != entities.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
			b->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (b->life == false)	{ it = entities.erase(it); delete b; }// ���� ���� ������ �����, �� ������� ���
			else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������

		}

		for (it = entities.begin(); it != entities.end(); it++)
		{
			///////////////////////////////////����//////////////////////////////////

			if ((*it)->name == "EasyEnemy"){
				Entity *enemy = *it;

				for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
				{
					Entity *bullet = *it2;
					if (bullet->name == "Bullet")

					if (bullet->life == true)
					{

						if (bullet->getRect().intersects(enemy->getRect()))
						{
							bullet->life = false;
							std::cout << bullet->life << std::endl;
							enemy->life = false;
						}
					}
				}
			}

			if ((*it)->name == "HardEnemy"){
				Entity *enemy = *it;

				for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
				{
					Entity *bullet = *it2;
					if (bullet->name == "Bullet")

					if (bullet->life == true)
					{

						if (bullet->getRect().intersects(enemy->getRect()))
						{
							bullet->life = false;
							std::cout << bullet->life << std::endl;
							enemy->life = false;
						}
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			if ((*it)->getRect().intersects(p.getRect()))
			{
				if ((*it)->name == "EasyEnemy")
				{
					if ((p.dy>0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = 0; }//���� �������� �� �����,�� ���� ����� �������� 0,����������� �� ���� ���� �����,���� ��� �������� 0
					if ((*it)->dx > 0) {
						p.kickR = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 5;
					}
					if ((*it)->dx < 0) {
						p.kickL = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 5;
					}
				}
				if ((*it)->name == "HardEnemy")
				{

					if ((p.dy>0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = (*it)->health - 50; }//���� �������� �� �����,�� ���� ����� �������� 0,����������� �� ���� ���� �����,���� ��� �������� 0
					if ((*it)->dx > 0) {
						p.kickR = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 15;
					}
					if ((*it)->dx < 0) {
						p.kickL = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 15;
					}
				}

				for (it2 = entities.begin(); it2 != entities.end(); it2++){
					if ((*it)->getRect() != (*it2)->getRect())//��� ���� ��� ������ ���� ������ ��������������
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//���� ����������� ��� ������� � ��� �����
					{
						(*it)->dx *= -1;//������ ����������� �������� �����
						(*it)->sprite.scale(-1, 1);//�������� ������ �� �����������
					}
				}
				for (it2 = entities.begin(); it2 != entities.end(); it2++){
					if ((*it)->getRect() != (*it2)->getRect())//��� ���� ��� ������ ���� ������ ��������������
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "HardEnemy") && ((*it2)->name == "HardEnemy"))//���� ����������� ��� ������� � ��� �����
					{
						(*it)->dx *= -1;//������ ����������� �������� �����
						(*it)->sprite.scale(-1, 1);//�������� ������ �� �����������
					}
				}
			}
		}

		lifeBarPlayer.update(p.getHealth());
		p.update(time);// Player update function
		window.setView(view);
		window.clear(Color(77, 83, 140));
		lvl.Draw(window);//������ ����� �����
		for (it = entities.begin(); it != entities.end(); it++){
			window.draw((*it)->sprite); //������ entities ������� (������ ��� ������ �����)
		}
		lifeBarPlayer.draw(window);//������ ������� ��������
		if (!showMissionText) {
			text.setPosition(view.getCenter().x - 225, view.getCenter().y - 130);//������� ����� ����� ���������� �����
			s_quest.setPosition(view.getCenter().x - 230, view.getCenter().y - 130);//������� ���� ��� �����		
			window.draw(s_quest); window.draw(text);
		}//������ ������ ������ (��� ��� ������ ������). � ����� � �����. ��� ��� �������� �� ���������� ����������, ������� ������ ���� ��������� �� ������� ������� ���
		window.draw(p.sprite);
		window.display();
	}
	//return 0;

}

void gameRunning(RenderWindow & window, int & numberLevel){//�-��� ������������� ���� , ���� ��� ����������
	if (startGame(window, numberLevel)) { numberLevel++; gameRunning(window, numberLevel); }//��������� � ������ ������ ������ ����
}

int main()
{	
	RenderWindow window(VideoMode(640, 480), "Chris Jumper");
	menu(window);
	int numberLevel = 1;//������� 1-�� �������
	gameRunning(window, numberLevel);
	return 0;
	/*bool showMissionText = true;//���������� ����������, ���������� �� ��������� ������ ������ �� ������
	RenderWindow window(VideoMode(640, 600), "Chris Jumper");
	//menu(window);//����� ����
	view.reset(FloatRect(0, 0, 640, 600));


	Level lvl;//������� ��������� ������ �������
	lvl.LoadFromFile("map.tmx");//��������� � ���� �����, ������ ������ � ������� ������� �� �� ����������.

	Font font;//����� 
	font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setColor(Color::Black);

	Music music;//������� ������ ������
	music.openFromFile("sounds/01.ogg");//��������� ����
	music.play();//������������� ������
	music.setLoop(true);

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //���������� �����, ������� �������� ��������
	s_quest.setScale(0.6f, 0.6f);//���� ��������� ��������, => ������ ���� ������

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image heroImage;
	heroImage.loadFromFile("images/capitan.png");

	Image BulletImage;//����������� ��� ����
	BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ �����������
	BulletImage.createMaskFromColor(Color(0, 0, 0));//����� ��� ���� �� ������� �����

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/EasyEnemy.png");
	//easyEnemyImage.createMaskFromColor(Color(255, 0, 0));//����� �� �����

	Image hardEnemyImage;
	hardEnemyImage.loadFromFile("images/HardEnemy.png");

	SoundBuffer shootBuffer;//������ ����� ��� �����
	shootBuffer.loadFromFile("sounds/shoot.wav");//��������� � ���� ����
	Sound shoot(shootBuffer);//������� ���� � ��������� � ���� ���� �� ������


	std::list<Entity*>  entities;//������ ������, ���� ���� ������ �������.�������� ������.
	std::list<Entity*>::iterator it;//�������� ����� ��������� �� ��-��� ������
	std::list<Entity*>::iterator it2;//������ ��������.��� �������������� ����� ��������� ������

	

	LifeBar lifeBarPlayer;//��������� ������ ������� ��������
	Object player = lvl.GetObject("player");//������ ������ �� ����� �����.������ ���������� ������ � ������ ��� ������ ����

	std::vector<Object> e = lvl.GetObjects("EasyEnemy");//��� ������� ����� �� tmx ����� �������� � ���� �������


	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 70, 120);//�������� ���������� �������������� player �� ����� � ���������� ������ ������
	for (int i = 0; i < e.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 80, 110));//� ���������� � ������ ���� ����� ������ � �����
	e = lvl.GetObjects("HardEnemy");
	for (int i = 0; i < e.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
		entities.push_back(new Enemy(hardEnemyImage, "HardEnemy", lvl, e[i].rect.left, e[i].rect.top, 80, 125));//� ���������� � ������ ���� ����� ������ � �����

	Clock clock;
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F)
				{
					entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x + 55, p.y + 55, 16, 16, p.state));
					shoot.play();//������ ���� ����
				}
				if ((event.key.code == Keyboard::Tab)) {//���� ������� ���


					switch (showMissionText) {//�������������, ����������� �� ���������� ���������� showMissionText

					case true: {
								   std::ostringstream playerHealthString;//������ �������� ������
								   playerHealthString << p.health; //������� � ������ �������� 
								   std::ostringstream task;//������ ������ ������
								   task << getTextMission(getCurrentMission(p.x));//���������� ������� getTextMission (��� ���������� ����� ������), ������� ��������� � �������� ��������� ������� getCurrentMission(������������ ����� ������), � ��� ��� �-��� ��������� � �������� ��������� ������� p.getplayercoordinateX() (��� �-��� ���������� ��� ���������� ������)
								   text.setString("��������: " + playerHealthString.str() + "\n" + task.str());//������
								   text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//������� ����� ����� ���������� �����
								   s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//������� ���� ��� �����
								   showMissionText = false;//��� ������ ��������� ������ ��� ��� �� ������ �� ������
								   break;//������� , ����� �� ��������� ������� "false" (������� ����)
					}
					case false: {
									text.setString("");//���� �� ������ ������� ���, �� ���� ���� ����� ������
									showMissionText = true;// � ��� ������ ��������� ����� ������ ������� ��� � �������� ����� �� �����
									break;
					}
					}
				}
				/*if ((event.key.code == Keyboard::Tab)) {//���� ������� ���
					std::ostringstream task;//������ ������ ������
					task << getTextMission(getCurrentMission(p.x));//���������� ������� getTextMission (��� ���������� ����� ������), ������� ��������� � �������� ��������� ������� getCurrentMission(������������ ����� ������), � ��� ��� �-��� ��������� � �������� ��������� ������� p.getplayercoordinateX() (��� �-��� ���������� ��� ���������� ������)
					text.setString(task.str());//������
					text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//������� ����� ����� ���������� �����
					showMissionText = false;
					break;
				}*/
		/*	}
				
		}
		for (it = entities.begin(); it != entities.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
			b->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (b->life == false)	{ it = entities.erase(it); delete b;}// ���� ���� ������ �����, �� ������� ���
			else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������

		}

		for (it = entities.begin(); it != entities.end(); it++)
		{
			///////////////////////////////////����//////////////////////////////////

			if ((*it)->name == "EasyEnemy"){
				Entity *enemy = *it;

				for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
				{
					Entity *bullet = *it2;
					if (bullet->name == "Bullet")

					if (bullet->life == true)
					{

						if (bullet->getRect().intersects(enemy->getRect()))
						{
							bullet->life = false;
							std::cout << bullet->life << std::endl;
							enemy->life = false;
						}
					}
				}
			}

			if ((*it)->name == "HardEnemy"){
				Entity *enemy = *it;

				for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
				{
					Entity *bullet = *it2;
					if (bullet->name == "Bullet")

					if (bullet->life == true)
					{

						if (bullet->getRect().intersects(enemy->getRect()))
						{
							bullet->life = false;
							std::cout << bullet->life << std::endl;
							enemy->life = false;
						}
					}
				}
			}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

			if ((*it)->getRect().intersects(p.getRect()))
			{
				if ((*it)->name == "EasyEnemy")
				{
					if ((p.dy>0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = 0; }//���� �������� �� �����,�� ���� ����� �������� 0,����������� �� ���� ���� �����,���� ��� �������� 0
					if ((*it)->dx > 0) {
						p.kickR = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 5;
					}
					if ((*it)->dx < 0) {
						p.kickL = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 5;
					}
				}
				if ((*it)->name == "HardEnemy")
				{
					
					if ((p.dy>0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = (*it)->health - 50; }//���� �������� �� �����,�� ���� ����� �������� 0,����������� �� ���� ���� �����,���� ��� �������� 0
					if ((*it)->dx > 0) {
						p.kickR = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 15;
					}
					if ((*it)->dx < 0) {
						p.kickL = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 15;
					}
				}

				for (it2 = entities.begin(); it2 != entities.end(); it2++){
					if ((*it)->getRect() != (*it2)->getRect())//��� ���� ��� ������ ���� ������ ��������������
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//���� ����������� ��� ������� � ��� �����
					{
						(*it)->dx *= -1;//������ ����������� �������� �����
						(*it)->sprite.scale(-1, 1);//�������� ������ �� �����������
					}
				}
				for (it2 = entities.begin(); it2 != entities.end(); it2++){
					if ((*it)->getRect() != (*it2)->getRect())//��� ���� ��� ������ ���� ������ ��������������
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "HardEnemy") && ((*it2)->name == "HardEnemy"))//���� ����������� ��� ������� � ��� �����
					{
						(*it)->dx *= -1;//������ ����������� �������� �����
						(*it)->sprite.scale(-1, 1);//�������� ������ �� �����������
					}
				}
							}
		}

		lifeBarPlayer.update(p.getHealth());

		p.update(time);// Player update function
		window.setView(view);
		window.clear(Color(77, 83, 140));
		lvl.Draw(window);//������ ����� �����
			for (it = entities.begin(); it != entities.end(); it++){
			window.draw((*it)->sprite); //������ entities ������� (������ ��� ������ �����)
		}
		lifeBarPlayer.draw(window);//������ ������� ��������
		if (!showMissionText) { 
			text.setPosition(view.getCenter().x - 225, view.getCenter().y - 130);//������� ����� ����� ���������� �����
			s_quest.setPosition(view.getCenter().x - 230, view.getCenter().y - 130);//������� ���� ��� �����		
			window.draw(s_quest); window.draw(text); }//������ ������ ������ (��� ��� ������ ������). � ����� � �����. ��� ��� �������� �� ���������� ����������, ������� ������ ���� ��������� �� ������� ������� ���
		window.draw(p.sprite);
		window.display();
	}
	return 0;*/
}


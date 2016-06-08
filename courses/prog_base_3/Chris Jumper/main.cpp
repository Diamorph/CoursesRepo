/*  //��������� ���
#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include "mission.h"
#include <iostream>
#include <sstream>

using namespace sf;
#include <SFML/Graphics.hpp>
////////////////////////////////////////////////////����� ������////////////////////////
class Player { // ����� ������
	private: float x, y;
	public:
	float w, h, dx, dy, speed = 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir, playerScore,health;//����� ����������, �������� ���� ������ //����������� (direction) �������� ������
	bool life, onGround;//���������� �����, ����������
	String File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������

Player(String F, float X, float Y, float W, float H){  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
	dir = 0; speed = 0; playerScore = 0; health = 100; // ���������������� ���������� ����� � ������������
	life = true;//���������������� ���������� ���������� �����
	onGround = false;
	File = F;//��� �����+����������
	w = W; h = H;//������ � ������
	image.loadFromFile("images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
	texture.loadFromImage(image);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������
	x = X; y = Y;//���������� ��������� �������
	sprite.setTextureRect(IntRect(0, 110, w, h));  //������ ������� ���� ������������� ��� ������ ������ ���������, � �� ���� �����. IntRect - ���������� �����
	sprite.setOrigin(w / 2, h / 2);
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
	interactionWithMap();//�������� �������, ���������� �� �������������� � ������
	if (health <= 0){ life = false; speed = 0; }//���� ������ ������ ���� ����� 0, �� ������� � ��������� �������� ������ ����� ������
}

void interactionWithMap()//�-��� �������������� � ������
{

	for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������, �������������� � �������,, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
	for (int j = x / 32; j<(x + w) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
		{
		if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
		{
		if (dy>0)//���� �� ��� ����,
		{
			y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
		}
		if (dy<0)
		{
			y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
		}
		if (dx>0)
		{
			x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
		}
		if (dx < 0)
		{
			x = j * 32 + 32;//���������� ���� �����
		}
	}

	if (TileMap[i][j] == 's') { //���� ������ ����� 's' (������)
		playerScore++;//���� ����� ������, ���������� playerScore=playerScore+1;
		TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
	}
	if (TileMap[i][j] == 'f'){
		health -= 40;// ���� ����� ������, - ��
		TileMap[i][j] = ' ';//������ ������
	}
	if (TileMap[i][j] == 'h'){
		health += 10;// ���� ����� ��������, + ��
		TileMap[i][j] = ' ';//������ ��������
	}

}
}

	float getplayercoordinateX(){	//���� ������� ����� �������� ���������� �
		return x;
	}
	float getplayercoordinateY(){	//���� ������� ����� �������� ���������� Y
		return y;
	}
};

int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Chris Jumper");

	view.reset(sf::FloatRect(0, 0, 640, 480));//������ "����" ������ ��� �������� ������� ���� ������. (����� ����� ������ ��� �����) ��� �� ���� �������������.

	Font font;//�����
	font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setColor(Color::Black);


	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/map.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //���������� �����, ������� �������� ��������
	s_quest.setScale(0.6f, 0.6f);//���� ��������� ��������, => ������ ���� ������

	Player p("capitan.png", 100, 100, 70.0, 120.0);//������� ������ p ������ player,������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.

	bool showMissionText = true;//���������� ����������, ���������� �� ��������� ������ ������ �� ������
	float CurrentFrame = 0;//������ ������� ����
	Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ����
	int gameTime = 0;//�������� ������� �����, ����������������.


	while (window.isOpen())
{

	float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������

	if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//������� ����� � �������� ��� ������, ���� ��� �����, ������������� ��� time ��� �� ����. ��� �� ��������� ������ ����
	clock.restart(); //������������� �����
	time = time / 800;
	//sf::Event event;

	Event event;
	while (window.pollEvent(event))
{
	if (event.type == sf::Event::Closed)
		window.close();

	if (event.type == Event::KeyPressed)//������� ������� �������
	if ((event.key.code == Keyboard::Tab)) {//���� ������� ���


		switch (showMissionText) {//�������������, ����������� �� ���������� ���������� showMissionText

		case true: {
					   std::ostringstream playerHealthString;//������ �������� ������
					   playerHealthString << p.health; //������� � ������ �������� 
					   std::ostringstream task;//������ ������ ������
					   task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//���������� ������� getTextMission (��� ���������� ����� ������), ������� ��������� � �������� ��������� ������� getCurrentMission(������������ ����� ������), � ��� ��� �-��� ��������� � �������� ��������� ������� p.getplayercoordinateX() (��� �-��� ���������� ��� ���������� ������)
					   text.setString("��������: " + playerHealthString.str() + "\n" + task.str());
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
}


///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
if (p.life){
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 10) CurrentFrame -= 10;
		p.sprite.setTextureRect(IntRect(110 + 110 * int(CurrentFrame), 0, -110, 110));
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		p.dir = 0; p.speed = 0.1;//����������� ������, �� ����
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 10) CurrentFrame -= 10;
		p.sprite.setTextureRect(IntRect(0 + 110 * int(CurrentFrame), 0, 110, 110));
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		p.dir = 3; p.speed = 0.1;//����������� ����, �� ����
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 12) CurrentFrame -= 12;
		p.sprite.setTextureRect(IntRect(0 + 75 * int(CurrentFrame), 1980, 75, 140));
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		p.dir = 2; p.speed = 0.1;//����������� �����, �� ����
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 12) CurrentFrame -= 12;
		p.sprite.setTextureRect(IntRect(900 - 75 * int(CurrentFrame), 1980, -75, 140));
	}
	getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
}
	p.update(time);//�������� ������ p ������ Player � ������� ������� sfml, ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������

	window.setView(view);//"��������" ������ � ���� sfml

	window.clear();

	if ((getCurrentMission(p.getplayercoordinateX())) == 0) { //���� ������� ������ 0, �� ������ ����� ��� ���
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
			if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
			if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
			s_map.setPosition(j * 32, i * 32);

			window.draw(s_map);
		}
	}

	if ((getCurrentMission(p.getplayercoordinateX())) >= 1) { //���� ������� ������ 1, �� ������ ����� ��� ���
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 0, 32, 32));//��� ������� ������� ������� ����� ������� ��� ����� ������� �..
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//� ��� ��� �����. ���������-������� ����� �� ������� ����� ��
			if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
			if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
			s_map.setPosition(j * 32, i * 32);

			window.draw(s_map);
		}
	}

	if (!showMissionText) {
		text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//������� ����� ����� ���������� �����
		s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//������� ���� ��� �����			
		window.draw(s_quest); window.draw(text); //������ ������ ������ (��� ��� ������ ������). � ����� � �����. ��� ��� �������� �� ���������� ����������, ������� ������ ���� ��������� �� ������� ������� ���
	}

	window.draw(p.sprite);
	window.display();
	}

	return 0;
}
*/

#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include <sstream>
#include "mission.h"

using namespace sf;

/*////////////////////////////////////////////////////����� ������////////////////////////
class Player {

public:
	float w, h, dx, dy, x, y, speed;
	int dir, playerScore, health;
	bool life, isMove, isSelect, onGround;//�������� ���������� ��������� ���������� �� �����
	enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H){

		dir = 0; speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false; isSelect = false; onGround = false;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 110, w, h));
		sprite.setOrigin(w / 2, h / 2);
	}
	void control(){
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
			//currentFrame += 0.005*time;
			//if (currentFrame > 3) currentFrame -= 3;
			//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 135, 96, 54));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
			//	currentFrame += 0.005*time;
			//	if (currentFrame > 3) currentFrame -= 3;
			//	p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 232, 96, 54));
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
			state = jump; dy = -0.4; onGround = false;//�� ��������� ����� ������,�������� � ��������, ��� �� �� �� �����
			//currentFrame += 0.005*time;
			//if (currentFrame > 3) currentFrame -= 3;
			//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;

			//currentFrame += 0.005*time;
			//if (currentFrame > 3) currentFrame -= 3;
			//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
		}
	}
	void update(float time)
	{
		control();//������� ���������� ����������
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
		case right: dx = speed; break;//��������� ���� ������
		case left: dx = -speed; break;//��������� ���� �����
		case up: break;//����� ��������� �������� ������ (�������� �� ��������)
		case down: break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		case jump: break;//����� ����� ���� ����� ��������
		case stay: break;//� ����� ����		
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		y += dy*time;
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		if (!isMove) speed = 0;
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		if (health <= 0){ life = false; }
		dy = dy + 0.0015*time;//������ ���������� � �����
	}

	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){
		return y;
	}

	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� ��� ������ �����? ��
			{
				if (Dy>0){ y = i * 32 - h;  dy = 0; onGround = true; }//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
				if (Dy<0){ y = i * 32 + 32;  dy = 0; }//������������ � �������� ������ �����(����� � �� �����������)
				if (Dx>0){ x = j * 32 - w; }//� ������ ����� �����
				if (Dx<0){ x = j * 32 + 32; }// � ����� ����� �����
			}
		}
	}
};

class SpriteManager{//��� ����� �� ��������� �����,����� �� �������� �������� �� ��� ���������)
public:
	Image image;
	Texture texture;
	Sprite sprite;
	String name;
	String file;
	int widthOfSprite;
	int heightOfSprite;
	SpriteManager(String File, String Name){
		file = File;
		name = Name;
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};
*/

/*int main()
{
	

	RenderWindow window(VideoMode(640, 480), "Chris Jumper");
	view.reset(FloatRect(0, 0, 640, 480));

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setColor(Color::Black);


	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));
	s_quest.setScale(0.6f, 0.6f);

	SpriteManager playerSprite("capitan.png", "capitan");//��� ����� �� ��������� �����,����� �� �������� ��������)

	Player p("capitan.png", 100, 100, 70.0, 120.0);

	float currentFrame = 0;
	Clock clock;
	float dX = 0;
	float dY = 0;
	int tempX = 0;//��������� ����� �.������� �� ����� ������� ���� ���� ����
	int tempY = 0;//����� Y
	float distance = 0;//��� ���������� �� ������� �� ���� �������
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
		Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
			if (event.key.code == Mouse::Left){//� ������ �����
				if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
				{
					p.sprite.setColor(Color::Green);//������ ������ � �������,��� ����� ������ ������,��� �� ������ ��������� � ����� ������� ���
					p.isSelect = true;
				}
			}


			if (p.isSelect)//���� ������� ������
			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
			if (event.key.code == Mouse::Right){//� ������ ������
				p.isMove = true;//�� �������� ��������
				p.isSelect = false;//������ ��� �� ������
				p.sprite.setColor(Color::White);//���������� ������� ���� �������
				tempX = pos.x;//�������� ���������� ������� ������� �
				tempY = pos.y;//� Y
				float dX = pos.x - p.x;//������ , ����������� ������, ������� ���������� ������ � ������
				float dY = pos.y - p.y;//�� ��, ���������� y
				float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
				std::cout << rotation << "\n";//������� �� ������� � ���������
				p.sprite.setRotation(rotation);//������������ ������ �� ��� �������	
			}
		}


		if (p.isMove){
			distance = sqrt((tempX - p.x)*(tempX - p.x) + (tempY - p.y)*(tempY - p.y));//������� ��������� (���������� �� ����� � �� ����� �). ��������� ������� ����� �������

			if (distance > 2){//���� �������� ������� �������� �� ����� �������� ������� �������

				p.x += 0.1*time*(tempX - p.x) / distance;//���� �� ���� � ������� ������� �������
				p.y += 0.1*time*(tempY - p.y) / distance;//���� �� ������ ��� ��
			}
			else { p.isMove = false; std::cout << "priehali\n"; }//������� ��� ��� ������ �� ���� � ������� ������� ��������� � �������
		}







		///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if (p.life) {
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}


		p.update(time);


		window.setView(view);
		window.clear();


		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
			if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
			if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
			s_map.setPosition(j * 32, i * 32);

			window.draw(s_map);
		}
		window.draw(p.sprite);
		window.display();
	}
	return 0;
*/


class Entity {
public:
	float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����
	int w, h, health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;//����� ����� ���� ������, �� �� ����� ������ ������ ����� ��� �����.����� ���� �������� ������ �� ����� � ����� ������� ���� �������� � update � ����������� �� �����
	Entity(Image &image, float X, float Y, int W, int H, String Name){
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
};


class Enemy :public Entity{
public:
	Enemy(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name){
		if (name == "EasyEnemy"){
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;//���� ��������.���� ������ ������ ���������
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� ��� ������ �����, ��
			{
				if (Dy>0){ y = i * 32 - h; }//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
				if (Dy<0){ y = i * 32 + 32; }//������������ � �������� ������ �����(����� � �� �����������)
				if (Dx>0){ x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }//� ������ ����� �����
				if (Dx<0){ x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }// � ����� ����� �����
			}
		}
	}

	void update(float time)
	{
		if (name == "EasyEnemy"){//��� ��������� � ����� ������ ������ ����� �����

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
	int playerScore;//��� ���������� ����� ���� ������ � ������

	Player(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name){
		playerScore = 0; state = stay;
		if (name == "Player1"){
			sprite.setTextureRect(IntRect(0, 110, w, h));
		}
	}

	void control(){
		if (Keyboard::isKeyPressed){//���� ������ �������
			if (Keyboard::isKeyPressed(Keyboard::Left)) {//� ������ �����
				state = left; speed = 0.1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				state = right; speed = 0.1;
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {//���� ������ ������� ����� � �� �� �����, �� ����� �������
				state = jump; dy = -0.6; onGround = false;//�������� ������ ������
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down;
			}
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� ��� ������ �����? ��
			{
				if (Dy>0){ y = i * 32 - h;  dy = 0; onGround = true; }//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
				if (Dy<0){ y = i * 32 + 32;  dy = 0; }//������������ � �������� ������ �����(����� � �� �����������)
				if (Dx>0){ x = j * 32 - w; }//� ������ ����� �����
				if (Dx<0){ x = j * 32 + 32; }// � ����� ����� �����
			}
			//else { onGround = false; }//���� ������ �.� �� ����� ���������� � �� ������ ����������� ��� ��������� ������� �������� ����
		}
	}

	void update(float time)
	{
		control();//������� ���������� ����������
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
		case right:dx = speed; break;//��������� ���� ������
		case left:dx = -speed; break;//��������� ���� �����
		case up: break;//����� ��������� �������� ������ (�������� �� ��������)
		case down: dx = 0; break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		case stay: break;//� ����� ����		
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		y += dy*time;
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		if (health <= 0){ life = false; }
		if (!isMove){ speed = 0; }
		//if (!onGround) { dy = dy + 0.0015*time; }//������� � ����� ������ ����������� � �����
		if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0015*time;//��������� ������������� � �����
	}
};

/*class Player {
public:
	float w, h, dx, dy, x, y, speed;
	int playerScore, health;
	bool life, isMove, onGround;//�������� ���������� ��������� ���������� �� �����
	enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H){
		speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false; state = stay;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 110, w, h));
		sprite.setOrigin(w / 2, h / 2);
	}


	void control(){
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
			dy = -0.4; onGround = false;//�� ��������� ����� ������,�������� � ��������, ��� �� �� �� �����

		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;
		}
	}
	void update(float time)
	{
		control();//������� ���������� ����������
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
		case right: dx = speed; break;//��������� ���� ������
		case left: dx = -speed; break;//��������� ���� �����
		case up: break;//����� ��������� �������� ������ (�������� �� ��������)
		case down: dx = 0; break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		case stay: break;//� ����� ����		
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		y += dy*time;
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		if (health <= 0){ life = false; }
		if (!isMove){ speed = 0; }
		dy = dy + 0.0015*time;//������ ���������� � �����
		if (life) { setPlayerCoordinateForView(x, y); }
	}

	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� ��� ������ �����? ��
			{
				if (Dy>0){ y = i * 32 - h;  dy = 0; onGround = true; }//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
				if (Dy<0){ y = i * 32 + 32;  dy = 0; }//������������ � �������� ������ �����(����� � �� �����������)
				if (Dx>0){ x = j * 32 - w; }//� ������ ����� �����
				if (Dx<0){ x = j * 32 + 32; }// � ����� ����� �����
			}
		}
	}
};
*/
int main()
{
	RenderWindow window(VideoMode(640, 480), "Chris Jumper");
	view.reset(FloatRect(0, 0, 640, 480));


	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image heroImage;
	heroImage.loadFromFile("images/capitan.png");

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/shamaich.png");
	easyEnemyImage.createMaskFromColor(Color(255, 0, 0));//����� �� �����


	Player p(heroImage, 250, 500, 70.0, 120.0, "Player1");//������ ������ ������
	
	Enemy easyEnemy(easyEnemyImage, 850, 671, 200, 97, "EasyEnemy");//������� ����, ������ ������ �����

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
		}
		p.update(time);// Player update function	
		easyEnemy.update(time);//easyEnemy update function
		window.setView(view);
		window.clear();


		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
			if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
			if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
			s_map.setPosition(j * 32, i * 32);

			window.draw(s_map);
		}
		window.draw(easyEnemy.sprite);
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}


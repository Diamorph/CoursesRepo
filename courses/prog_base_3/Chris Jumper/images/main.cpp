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
	std::vector<Object> obj;//вектор объектов карты
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер для будущих целей
	int w, h, health;
	bool life, isMove, onGround, kickL, kickR, kickUp;

	virtual void update(float time) = 0;
	Texture texture;
	Sprite sprite;
	String name;//враги могут быть разные, мы не будем делать другой класс для врага.всего лишь различим врагов по имени и дадим каждому свое действие в update в зависимости от имени
	Entity(Image &image, String Name, float X, float Y, int W, int H){
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		kickL = false; kickR = false; kickUp = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
		FloatRect getRect(){//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
			return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
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
		obj = lev.GetObjects("solid");//инициализируем.получаем нужные объекты для взаимодействия врага с картой
		if (name == "EasyEnemy"){
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;//даем скорость.этот объект всегда двигается
		}
		if (name == "HardEnemy"){
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;//даем скорость.этот объект всегда двигается
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
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
		if (name == "EasyEnemy"){//для персонажа с таким именем логика будет такой
			control(time, dx);
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
			checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
			if (health <= 0){ life = false; }
		}
		if (name == "HardEnemy"){//для персонажа с таким именем логика будет такой
			control_1(time, dx);
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
			checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
			if (health <= 0){ life = false; }
		}
	}
};

class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay } state;//добавляем тип перечисления - состояние объекта
	int playerScore;
	float CurrentFrame = 0;//эта переменная может быть только у игрока
	bool isShoot = false;

	Player(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
		playerScore = 0; state = stay; obj = lvl.GetAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
		if (name == "Player1"){
			sprite.setTextureRect(IntRect(0, 110, w, h));
		}
	}

	void control(float time){
		if (Keyboard::isKeyPressed){//если нажата клавиша
			if (Keyboard::isKeyPressed(Keyboard::Left)) {//а именно левая
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

			if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {//если нажата клавиша вверх и мы на земле, то можем прыгать
				state = jump; dy = -0.7; onGround = false;//увеличил высоту прыжка
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

	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
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
		control(time);//функция управления персонажем
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right:dx = speed; break;//состояние идти вправо
		case left:dx = -speed; break;//состояние идти влево
		case up: break;//будет состояние поднятия наверх (например по лестнице)
		case down: dx = 0; break;//будет состояние во время спуска персонажа (например по лестнице)
		case stay: break;//и здесь тоже		
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
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy*time;
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0){ life = false; }
		if (!isMove){ speed = 0; }
		if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0015*time;//постоянно притягиваемся к земле
	}
};

class Bullet :public Entity{//класс пули
public:
	int direction;//направление пули

	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H){//всё так же, только взяли в конце состояние игрока (int dir)
		obj = lvl.GetObjects("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
		//выше инициализация в конструкторе
	}


	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;//интовое значение state = left
		case 1: dx = speed; dy = 0;   break;//интовое значение state = right
		case 2: dx = 0; dy = -speed;   break;//интовое значение state = up
		case 3: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		case 4: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		case 5: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		}

		x += dx*time;//само движение пули по х
		y += dy*time;//по у

		if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
		if (y <= 0) y = 1;
		for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
			if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
			{	
				life = false;// то пуля умирает

			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);//задается позицию пуле
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

	//////////////////////////////МЕНЮ///////////////////
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
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
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
	bool showMissionText = true;//логическая переменная, отвечающая за появление текста миссии на экране
	//RenderWindow window(VideoMode(640, 600), "Chris Jumper");
	//menu(window);//вызов меню
	view.reset(FloatRect(0, 0, 640, 600));


	Level lvl;//создали экземпляр класса уровень
	changeLevel(lvl, numberLevel);//для загрузки карты для нужного уровня
	//lvl.LoadFromFile("map.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(Color::Black);

	Music music;//создаем объект музыки
	music.openFromFile("sounds/01.ogg");//загружаем файл
	music.play();//воспроизводим музыку
	music.setLoop(true);

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(0.6f, 0.6f);//чуть уменьшили картинку, => размер стал меньше

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image heroImage;
	heroImage.loadFromFile("images/capitan.png");

	Image BulletImage;//изображение для пули
	BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображения
	BulletImage.createMaskFromColor(Color(0, 0, 0));//маска для пули по черному цвету

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/EasyEnemy.png");
	//easyEnemyImage.createMaskFromColor(Color(255, 0, 0));//маска по цвету

	Image hardEnemyImage;
	hardEnemyImage.loadFromFile("images/HardEnemy.png");

	SoundBuffer shootBuffer;//создаём буфер для звука
	shootBuffer.loadFromFile("sounds/shoot.wav");//загружаем в него звук
	Sound shoot(shootBuffer);//создаем звук и загружаем в него звук из буфера


	std::list<Entity*>  entities;//создаю список, сюда буду кидать объекты.например врагов.
	std::list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка
	std::list<Entity*>::iterator it2;//второй итератор.для взаимодействия между объектами списка



	LifeBar lifeBarPlayer;//экземпляр класса полоски здоровья
	Object player = lvl.GetObject("player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него

	std::vector<Object> e = lvl.GetObjects("EasyEnemy");//все объекты врага на tmx карте хранятся в этом векторе


	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 70, 120);//передаем координаты прямоугольника player из карты в координаты нашего игрока
	for (int i = 0; i < e.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 80, 110));//и закидываем в список всех наших врагов с карты
	e = lvl.GetObjects("HardEnemy");
	for (int i = 0; i < e.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
		entities.push_back(new Enemy(hardEnemyImage, "HardEnemy", lvl, e[i].rect.left, e[i].rect.top, 80, 125));//и закидываем в список всех наших врагов с карты

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
					shoot.play();//играем звук пули
				}
				if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ


					switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText

					case true: {
								   std::ostringstream playerHealthString;//строка здоровья игрока
								   playerHealthString << p.health; //заносим в строку здоровье 
								   std::ostringstream task;//строка текста миссии
								   task << getTextMission(getCurrentMission(p.x));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
								   text.setString("Здоровье: " + playerHealthString.str() + "\n" + task.str());//задаем
								   text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
								   s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока
								   showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране
								   break;//выходим , чтобы не выполнить условие "false" (которое ниже)
					}
					case false: {
									text.setString("");//если не нажата клавиша таб, то весь этот текст пустой
									showMissionText = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
									break;
					}
					}
				}
				/*if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ
				std::ostringstream task;//строка текста миссии
				task << getTextMission(getCurrentMission(p.x));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
				text.setString(task.str());//задаем
				text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
				showMissionText = false;
				break;
				}*/
			}

		}
		for (it = entities.begin(); it != entities.end();)//говорим что проходимся от начала до конца
		{
			Entity *b = *it;//для удобства, чтобы не писать (*it)->
			b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (b->life == false)	{ it = entities.erase(it); delete b; }// если этот объект мертв, то удаляем его
			else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка

		}

		for (it = entities.begin(); it != entities.end(); it++)
		{
			///////////////////////////////////ПУЛЯ//////////////////////////////////

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
					if ((p.dy>0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = 0; }//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
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

					if ((p.dy>0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = (*it)->health - 50; }//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
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
					if ((*it)->getRect() != (*it2)->getRect())//при этом это должны быть разные прямоугольники
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//если столкнулись два объекта и они враги
					{
						(*it)->dx *= -1;//меняем направление движения врага
						(*it)->sprite.scale(-1, 1);//отражаем спрайт по горизонтали
					}
				}
				for (it2 = entities.begin(); it2 != entities.end(); it2++){
					if ((*it)->getRect() != (*it2)->getRect())//при этом это должны быть разные прямоугольники
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "HardEnemy") && ((*it2)->name == "HardEnemy"))//если столкнулись два объекта и они враги
					{
						(*it)->dx *= -1;//меняем направление движения врага
						(*it)->sprite.scale(-1, 1);//отражаем спрайт по горизонтали
					}
				}
			}
		}

		lifeBarPlayer.update(p.getHealth());
		p.update(time);// Player update function
		window.setView(view);
		window.clear(Color(77, 83, 140));
		lvl.Draw(window);//рисуем новую карту
		for (it = entities.begin(); it != entities.end(); it++){
			window.draw((*it)->sprite); //рисуем entities объекты (сейчас это только враги)
		}
		lifeBarPlayer.draw(window);//рисуем полоску здоровья
		if (!showMissionText) {
			text.setPosition(view.getCenter().x - 225, view.getCenter().y - 130);//позиция всего этого текстового блока
			s_quest.setPosition(view.getCenter().x - 230, view.getCenter().y - 130);//позиция фона для блока		
			window.draw(s_quest); window.draw(text);
		}//рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
		window.draw(p.sprite);
		window.display();
	}
	//return 0;

}

void gameRunning(RenderWindow & window, int & numberLevel){//ф-ция перезагружает игру , если это необходимо
	if (startGame(window, numberLevel)) { numberLevel++; gameRunning(window, numberLevel); }//принимает с какого уровня начать игру
}

int main()
{	
	RenderWindow window(VideoMode(640, 480), "Chris Jumper");
	menu(window);
	int numberLevel = 1;//сначала 1-ый уровень
	gameRunning(window, numberLevel);
	return 0;
	/*bool showMissionText = true;//логическая переменная, отвечающая за появление текста миссии на экране
	RenderWindow window(VideoMode(640, 600), "Chris Jumper");
	//menu(window);//вызов меню
	view.reset(FloatRect(0, 0, 640, 600));


	Level lvl;//создали экземпляр класса уровень
	lvl.LoadFromFile("map.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(Color::Black);

	Music music;//создаем объект музыки
	music.openFromFile("sounds/01.ogg");//загружаем файл
	music.play();//воспроизводим музыку
	music.setLoop(true);

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(0.6f, 0.6f);//чуть уменьшили картинку, => размер стал меньше

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image heroImage;
	heroImage.loadFromFile("images/capitan.png");

	Image BulletImage;//изображение для пули
	BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображения
	BulletImage.createMaskFromColor(Color(0, 0, 0));//маска для пули по черному цвету

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/EasyEnemy.png");
	//easyEnemyImage.createMaskFromColor(Color(255, 0, 0));//маска по цвету

	Image hardEnemyImage;
	hardEnemyImage.loadFromFile("images/HardEnemy.png");

	SoundBuffer shootBuffer;//создаём буфер для звука
	shootBuffer.loadFromFile("sounds/shoot.wav");//загружаем в него звук
	Sound shoot(shootBuffer);//создаем звук и загружаем в него звук из буфера


	std::list<Entity*>  entities;//создаю список, сюда буду кидать объекты.например врагов.
	std::list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка
	std::list<Entity*>::iterator it2;//второй итератор.для взаимодействия между объектами списка

	

	LifeBar lifeBarPlayer;//экземпляр класса полоски здоровья
	Object player = lvl.GetObject("player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него

	std::vector<Object> e = lvl.GetObjects("EasyEnemy");//все объекты врага на tmx карте хранятся в этом векторе


	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 70, 120);//передаем координаты прямоугольника player из карты в координаты нашего игрока
	for (int i = 0; i < e.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 80, 110));//и закидываем в список всех наших врагов с карты
	e = lvl.GetObjects("HardEnemy");
	for (int i = 0; i < e.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
		entities.push_back(new Enemy(hardEnemyImage, "HardEnemy", lvl, e[i].rect.left, e[i].rect.top, 80, 125));//и закидываем в список всех наших врагов с карты

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
					shoot.play();//играем звук пули
				}
				if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ


					switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText

					case true: {
								   std::ostringstream playerHealthString;//строка здоровья игрока
								   playerHealthString << p.health; //заносим в строку здоровье 
								   std::ostringstream task;//строка текста миссии
								   task << getTextMission(getCurrentMission(p.x));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
								   text.setString("Здоровье: " + playerHealthString.str() + "\n" + task.str());//задаем
								   text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
								   s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока
								   showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране
								   break;//выходим , чтобы не выполнить условие "false" (которое ниже)
					}
					case false: {
									text.setString("");//если не нажата клавиша таб, то весь этот текст пустой
									showMissionText = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
									break;
					}
					}
				}
				/*if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ
					std::ostringstream task;//строка текста миссии
					task << getTextMission(getCurrentMission(p.x));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
					text.setString(task.str());//задаем
					text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
					showMissionText = false;
					break;
				}*/
		/*	}
				
		}
		for (it = entities.begin(); it != entities.end();)//говорим что проходимся от начала до конца
		{
			Entity *b = *it;//для удобства, чтобы не писать (*it)->
			b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (b->life == false)	{ it = entities.erase(it); delete b;}// если этот объект мертв, то удаляем его
			else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка

		}

		for (it = entities.begin(); it != entities.end(); it++)
		{
			///////////////////////////////////ПУЛЯ//////////////////////////////////

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
					if ((p.dy>0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = 0; }//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
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
					
					if ((p.dy>0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = (*it)->health - 50; }//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
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
					if ((*it)->getRect() != (*it2)->getRect())//при этом это должны быть разные прямоугольники
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//если столкнулись два объекта и они враги
					{
						(*it)->dx *= -1;//меняем направление движения врага
						(*it)->sprite.scale(-1, 1);//отражаем спрайт по горизонтали
					}
				}
				for (it2 = entities.begin(); it2 != entities.end(); it2++){
					if ((*it)->getRect() != (*it2)->getRect())//при этом это должны быть разные прямоугольники
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "HardEnemy") && ((*it2)->name == "HardEnemy"))//если столкнулись два объекта и они враги
					{
						(*it)->dx *= -1;//меняем направление движения врага
						(*it)->sprite.scale(-1, 1);//отражаем спрайт по горизонтали
					}
				}
							}
		}

		lifeBarPlayer.update(p.getHealth());

		p.update(time);// Player update function
		window.setView(view);
		window.clear(Color(77, 83, 140));
		lvl.Draw(window);//рисуем новую карту
			for (it = entities.begin(); it != entities.end(); it++){
			window.draw((*it)->sprite); //рисуем entities объекты (сейчас это только враги)
		}
		lifeBarPlayer.draw(window);//рисуем полоску здоровья
		if (!showMissionText) { 
			text.setPosition(view.getCenter().x - 225, view.getCenter().y - 130);//позиция всего этого текстового блока
			s_quest.setPosition(view.getCenter().x - 230, view.getCenter().y - 130);//позиция фона для блока		
			window.draw(s_quest); window.draw(text); }//рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
		window.draw(p.sprite);
		window.display();
	}
	return 0;*/
}


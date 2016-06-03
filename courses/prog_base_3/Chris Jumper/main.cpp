#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include <sstream>

using namespace sf;
#include <SFML/Graphics.hpp>
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player { // класс Игрока
private: float x, y;
public:
	float w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir = 0, playerScore = 0;//новая переменная, хранящая очки игрока //направление (direction) движения игрока
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт

	Player(String F, float X, float Y, float W, float H){  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(0, 110, w, h));  //Задаем спрайту один прямоугольник для вывода одного персонажа, а не кучи сразу. IntRect - приведение типов
	}

	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case 1: dx = -speed; dy = 0;   break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case 2: dx = 0; dy = speed;   break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case 3: dx = 0; dy = -speed;   break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		}

		x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
		y += dy*time;//аналогично по игреку

		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой
	}

	void interactionWithMap()//ф-ция взаимодействия с картой
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
		for (int j = x / 32; j<(x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
		{
			if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
			{
				if (dy>0)//если мы шли вниз,
				{
					y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
				}
				if (dy<0)
				{
					y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
				}
				if (dx>0)
				{
					x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
				}
				if (dx < 0)
				{
					x = j * 32 + 32;//аналогично идем влево
				}
			}

			if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
				playerScore++;//если взяли камень, переменная playerScore=playerScore+1;
				TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
			}
		}
	}

	float getplayercoordinateX(){	//этим методом будем забирать координату Х	
		return x;
	}
	float getplayercoordinateY(){	//этим методом будем забирать координату Y 	
		return y;
	}
};

int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Chris Jumper");

	view.reset(sf::FloatRect(0, 0, 640, 480));//размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим) Что то типа инициализации.

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(Text::Bold);//жирный текст.


	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;
	Player p("capitan.png", 100, 100, 70.0, 120.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time / 800;
		//sf::Event event;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float coordinatePlayerX, coordinatePlayerY = 0;
		coordinatePlayerX = p.getplayercoordinateX();
		coordinatePlayerY = p.getplayercoordinateY();

		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.dir = 1; p.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 10) CurrentFrame -= 10;
			p.sprite.setTextureRect(IntRect(110 + 110 * int(CurrentFrame), 0, -110, 110));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dir = 0; p.speed = 0.1;//направление вправо, см выше
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 10) CurrentFrame -= 10;
			p.sprite.setTextureRect(IntRect(0 + 110 * int(CurrentFrame), 0, 110, 110));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			p.dir = 3; p.speed = 0.1;//направление вниз, см выше
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 12) CurrentFrame -= 12;
			p.sprite.setTextureRect(IntRect(0 + 75 * int(CurrentFrame), 1980, 75, 140));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			p.dir = 2; p.speed = 0.1;//направление вверх, см выше
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 12) CurrentFrame -= 12;
			p.sprite.setTextureRect(IntRect(900 - 75 * int(CurrentFrame), 1980, -75, 140));
		}
		getplayercoordinateforview(coordinatePlayerX, coordinatePlayerY);
		p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		
		
		
		viewmap(time);//функция скроллинга карты, передаем ей время sfml
		window.setView(view);//"оживляем" камеру в окне sfml

		window.clear();
		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


			s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

			window.draw(s_map);//рисуем квадратики на экран
		}

		std::ostringstream playerScoreString;    // объявили переменную
		playerScoreString << p.playerScore;		//занесли в нее число очков, то есть формируем строку
		text.setString("Собрано камней:" + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
		window.draw(text);//рисую этот текст


		window.draw(p.sprite);
		window.display();
	}

	return 0;
}



/*#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include <sstream>

using namespace sf;
#include <SFML/Graphics.hpp>
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player { // класс Игрока
private: float x, y;//объявили переменные, в конструкторе Player ниже дадим им значения
public:
	float w, h, dx, dy, speed; // dx dy speed будут = 0 в конструкторе класса ниже
	int dir = 0; //направление (direction) движения игрока
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт

	Player(String F, float X, float Y, float W, float H){  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(0, 110, w, h));  //Задаем спрайту один прямоугольник для вывода одного персонажа, а не кучи сразу. IntRect - приведение типов
	}

	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case 1: dx = -speed; dy = 0;   break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case 2: dx = 0; dy = speed;   break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case 3: dx = 0; dy = -speed;   break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		}

		x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
		y += dy*time;//аналогично по игреку

		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
	}
		float getplayercoordinateX(){	//этим методом будем забирать координату Х	
			return x;
		}
		float getplayercoordinateY(){	//этим методом будем забирать координату Y 	
			return y;
	}
};

int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Chris Jumper");
	view.reset(sf::FloatRect(0, 0, 640, 480));//размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим) Что то типа инициализации.
	
	
	
	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом


	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;
	Player p("capitan.png", 100, 100, 70.0, 120.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time / 800;
		//sf::Event event;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Left)) { 
			p.dir = 1; p.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			CurrentFrame += 0.005*time;
			//CurrentFrame += 0.005*time;
			if (CurrentFrame > 10) CurrentFrame -= 10;
			p.sprite.setTextureRect(IntRect(110+110*int(CurrentFrame), 0, -110, 110));
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());//передаем координаты игрока в функцию управления камерой
		} 
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dir = 0; p.speed = 0.1;//направление вправо, см выше
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 10) CurrentFrame -= 10; 
			p.sprite.setTextureRect(IntRect(0+110*int(CurrentFrame), 0, 110, 110));
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());//передаем координаты игрока в функцию управления камерой
		} 
		if (Keyboard::isKeyPressed(Keyboard::Up)) { 
			p.dir = 3; p.speed = 0.1;//направление вниз, см выше
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 12) CurrentFrame -= 12;
			p.sprite.setTextureRect(IntRect(0 + 75*int(CurrentFrame), 1980, 75, 140));
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());//передаем координаты игрока в функцию управления камерой
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			p.dir = 2; p.speed = 0.1;//направление вверх, см выше
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 12) CurrentFrame -= 12;
			p.sprite.setTextureRect(IntRect(900 - 75 *int(CurrentFrame), 1980, -75, 140));
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());//передаем координаты игрока в функцию управления камерой
		} 
		p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться

		viewmap(time);//функция скроллинга карты, передаем ей время sfml
		window.setView(view);//"оживляем" камеру в окне sfml

		window.clear();
		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


			s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

			window.draw(s_map);//рисуем квадратики на экран
		}


		window.draw(p.sprite);
		window.display();
	}

	return 0;
}


/*
using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Lesson 3. kychka-pc.ru"); //увеличили для удобства размер окна



	Texture herotexture;//создаем объект Texture (текстура)
	herotexture.loadFromFile("cyclops.png");//загружаем картинку

	Sprite herosprite;//создаем объект Sprite(спрайт)
	herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
	herosprite.setPosition(50, 25);//задаем начальные координаты появления спрайта

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(herosprite);//выводим спрайт на экран
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
		text.setString("Собрано камней:" + playerScoreString.str());
		text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);
		window.draw(text);

		window.draw(p.sprite);

		window.display();
	}

	return 0;
}*/
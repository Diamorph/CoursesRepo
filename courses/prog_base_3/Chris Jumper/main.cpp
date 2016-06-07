#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include "mission.h"
#include <iostream>
#include <sstream>

using namespace sf;
#include <SFML/Graphics.hpp>
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player { // класс Игрока
private: float x, y;
public:
	float w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir, playerScore,health;//новая переменная, хранящая очки игрока //направление (direction) движения игрока
	bool life;//переменная жизнь, логическая
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт

	Player(String F, float X, float Y, float W, float H){  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		dir = 0; speed = 0; playerScore = 0; health = 100; // инициализировали переменную жизни в конструкторе
		life = true;//инициализировали логическую переменную жизни
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
		if (health <= 0){ life = false; speed = 0; }//если жизней меньше либо равно 0, то умираем и исключаем движение игрока после смерти
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
			if (TileMap[i][j] == 'f'){
				health -= 40;// если взяли цветок, - хп
				TileMap[i][j] = ' ';//убрали цветок
			}
			if (TileMap[i][j] == 'h'){
				health += 10;// если взяли сердечко, + хп
				TileMap[i][j] = ' ';//убрали сердечко
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
	text.setColor(Color::Black);


	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(0.6f, 0.6f);//чуть уменьшили картинку, => размер стал меньше

	Player p("capitan.png", 100, 100, 70.0, 120.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.

	bool showMissionText = true;//логическая переменная, отвечающая за появление текста миссии на экране
	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.
	int createObjectForMapTimer = 0;//timer for random
	randomMapGenerate();

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//игровое время в секундах идёт вперед, пока жив игрок, перезагружать как time его не надо. оно не обновляет логику игры
		clock.restart(); //перезагружает время
		time = time / 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)//событие нажатия клавиши
			if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ


				switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText

				case true: {
							   std::ostringstream playerHealthString;//строка здоровья игрока
							   playerHealthString << p.health; //заносим в строку здоровье 
							   std::ostringstream task;//строка текста миссии
							   task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
							   text.setString("Здоровье: " + playerHealthString.str() + "\n" + task.str());
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
		}


		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (p.life){
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
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}

		/*sf::Vector2i localPosition = Mouse::getPosition(window);//заносим в вектор координаты мыши относительно окна (х,у)
		if (localPosition.x < 3) { view.move(-0.2*time, 0); }//если пришли курсором в левый край экрана,то двигаем камеру влево
		if (localPosition.x > window.getSize().x - 3) { view.move(0.2*time, 0); }//правый край-вправо
		if (localPosition.y > window.getSize().y - 3) { view.move(0, 0.2*time); }//нижний край - вниз
		if (localPosition.y < 3) { view.move(0, -0.2*time); }//верхний край - вверх*/
		
		createObjectForMapTimer += time;//наращиваем таймер
		if (createObjectForMapTimer>3000){
			randomMapGenerate();//генерация случ камней
			createObjectForMapTimer = 0;//обнуляем таймер
		}

		p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться

		window.setView(view);//"оживляем" камеру в окне sfml

		window.clear();
		
		if ((getCurrentMission(p.getplayercoordinateX())) == 0) { //Если текущая миссия 0, то рисуем карту вот так
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

		if ((getCurrentMission(p.getplayercoordinateX())) >= 1) { //Если текущая миссия 1, то рисуем карту вот так
			for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 0, 32, 32));//для примера поменял местами вывод спрайта для этого символа и..
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//и для вот этого. логически-игровой смысл их остался таким же
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);

				window.draw(s_map);
			}
		}

		if (!showMissionText) {
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока			
			window.draw(s_quest); window.draw(text); //рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
		}
		
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}

/*  Резервный код
#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include "mission.h"
#include <iostream>
#include <sstream>

using namespace sf;
#include <SFML/Graphics.hpp>
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player { // класс Игрока
private: float x, y;
public:
float w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
int dir, playerScore,health;//новая переменная, хранящая очки игрока //направление (direction) движения игрока
bool life;//переменная жизнь, логическая
String File; //файл с расширением
Image image;//сфмл изображение
Texture texture;//сфмл текстура
Sprite sprite;//сфмл спрайт

Player(String F, float X, float Y, float W, float H){  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
dir = 0; speed = 0; playerScore = 0; health = 100; // инициализировали переменную жизни в конструкторе
life = true;//инициализировали логическую переменную жизни
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
if (health <= 0){ life = false; speed = 0; }//если жизней меньше либо равно 0, то умираем и исключаем движение игрока после смерти
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
if (TileMap[i][j] == 'f'){
health -= 40;// если взяли цветок, - хп
TileMap[i][j] = ' ';//убрали цветок
}
if (TileMap[i][j] == 'h'){
health += 10;// если взяли сердечко, + хп
TileMap[i][j] = ' ';//убрали сердечко
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
text.setColor(Color::Black);


Image map_image;//объект изображения для карты
map_image.loadFromFile("images/map.png");//загружаем файл для карты
Texture map;//текстура карты
map.loadFromImage(map_image);//заряжаем текстуру картинкой
Sprite s_map;//создаём спрайт для карты
s_map.setTexture(map);//заливаем текстуру спрайтом

Image quest_image;
quest_image.loadFromFile("images/missionbg.jpg");
quest_image.createMaskFromColor(Color(0, 0, 0));
Texture quest_texture;
quest_texture.loadFromImage(quest_image);
Sprite s_quest;
s_quest.setTexture(quest_texture);
s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
s_quest.setScale(0.6f, 0.6f);//чуть уменьшили картинку, => размер стал меньше

Player p("capitan.png", 100, 100, 70.0, 120.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.

bool showMissionText = true;//логическая переменная, отвечающая за появление текста миссии на экране
float CurrentFrame = 0;//хранит текущий кадр
Clock clock;
Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры
int gameTime = 0;//объявили игровое время, инициализировали.


while (window.isOpen())
{

float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах

if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//игровое время в секундах идёт вперед, пока жив игрок, перезагружать как time его не надо. оно не обновляет логику игры
clock.restart(); //перезагружает время
time = time / 800;
//sf::Event event;

Event event;
while (window.pollEvent(event))
{
	if (event.type == sf::Event::Closed)
		window.close();

	if (event.type == Event::KeyPressed)//событие нажатия клавиши
	if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ


		switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText

		case true: {
					   std::ostringstream playerHealthString;//строка здоровья игрока
					   playerHealthString << p.health; //заносим в строку здоровье 
					   std::ostringstream task;//строка текста миссии
					   task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
					   text.setString("Здоровье: " + playerHealthString.str() + "\n" + task.str());
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
}


///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
if (p.life){
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
	getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
}
p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться

window.setView(view);//"оживляем" камеру в окне sfml

window.clear();

if ((getCurrentMission(p.getplayercoordinateX())) == 0) { //Если текущая миссия 0, то рисуем карту вот так
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

if ((getCurrentMission(p.getplayercoordinateX())) >= 1) { //Если текущая миссия 1, то рисуем карту вот так
	for (int i = 0; i < HEIGHT_MAP; i++)
	for (int j = 0; j < WIDTH_MAP; j++)
	{
		if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 0, 32, 32));//для примера поменял местами вывод спрайта для этого символа и..
		if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
		if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//и для вот этого. логически-игровой смысл их остался таким же
		if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
		if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
		s_map.setPosition(j * 32, i * 32);

		window.draw(s_map);
	}
}

if (!showMissionText) {
	text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
	s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока			
	window.draw(s_quest); window.draw(text); //рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
}

window.draw(p.sprite);
window.display();
	}

	return 0;
}
*/
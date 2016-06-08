/*  //Резервный код
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
	bool life, onGround;//переменная жизнь, логическая
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт

Player(String F, float X, float Y, float W, float H){  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
	dir = 0; speed = 0; playerScore = 0; health = 100; // инициализировали переменную жизни в конструкторе
	life = true;//инициализировали логическую переменную жизни
	onGround = false;
	File = F;//имя файла+расширение
	w = W; h = H;//высота и ширина
	image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
	texture.loadFromImage(image);//закидываем наше изображение в текстуру
	sprite.setTexture(texture);//заливаем спрайт текстурой
	x = X; y = Y;//координата появления спрайта
	sprite.setTextureRect(IntRect(0, 110, w, h));  //Задаем спрайту один прямоугольник для вывода одного персонажа, а не кучи сразу. IntRect - приведение типов
	sprite.setOrigin(w / 2, h / 2);
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

#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include <sstream>
#include "mission.h"

using namespace sf;

/*////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player {

public:
	float w, h, dx, dy, x, y, speed;
	int dir, playerScore, health;
	bool life, isMove, isSelect, onGround;//добавили переменные состояния нахождения на земле
	enum { left, right, up, down, jump, stay } state;//добавляем тип перечисления - состояние объекта
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
			state = jump; dy = -0.4; onGround = false;//то состояние равно прыжок,прыгнули и сообщили, что мы не на земле
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
		control();//функция управления персонажем
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right: dx = speed; break;//состояние идти вправо
		case left: dx = -speed; break;//состояние идти влево
		case up: break;//будет состояние поднятия наверх (например по лестнице)
		case down: break;//будет состояние во время спуска персонажа (например по лестнице)
		case jump: break;//здесь может быть вызов анимации
		case stay: break;//и здесь тоже		
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy*time;
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		if (!isMove) speed = 0;
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0){ life = false; }
		dy = dy + 0.0015*time;//делаем притяжение к земле
	}

	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){
		return y;
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент наш тайлик земли? то
			{
				if (Dy>0){ y = i * 32 - h;  dy = 0; onGround = true; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
				if (Dy<0){ y = i * 32 + 32;  dy = 0; }//столкновение с верхними краями карты(может и не пригодиться)
				if (Dx>0){ x = j * 32 - w; }//с правым краем карты
				if (Dx<0){ x = j * 32 + 32; }// с левым краем карты
			}
		}
	}
};

class SpriteManager{//это задел на следующие уроки,прошу не обращать внимания на эти изменения)
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

	SpriteManager playerSprite("capitan.png", "capitan");//это задел на следующие уроки,прошу не обращать внимания)

	Player p("capitan.png", 100, 100, 70.0, 120.0);

	float currentFrame = 0;
	Clock clock;
	float dX = 0;
	float dY = 0;
	int tempX = 0;//временная коорд Х.Снимаем ее после нажатия прав клав мыши
	int tempY = 0;//коорд Y
	float distance = 0;//это расстояние от объекта до тыка курсора
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
			if (event.key.code == Mouse::Left){//а именно левая
				if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
				{
					p.sprite.setColor(Color::Green);//красим спрайт в зеленый,тем самым говоря игроку,что он выбрал персонажа и может сделать ход
					p.isSelect = true;
				}
			}


			if (p.isSelect)//если выбрали объект
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
			if (event.key.code == Mouse::Right){//а именно правая
				p.isMove = true;//то начинаем движение
				p.isSelect = false;//объект уже не выбран
				p.sprite.setColor(Color::White);//возвращаем обычный цвет спрайту
				tempX = pos.x;//забираем координату нажатия курсора Х
				tempY = pos.y;//и Y
				float dX = pos.x - p.x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
				float dY = pos.y - p.y;//он же, координата y
				float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
				std::cout << rotation << "\n";//смотрим на градусы в консольке
				p.sprite.setRotation(rotation);//поворачиваем спрайт на эти градусы	
			}
		}


		if (p.isMove){
			distance = sqrt((tempX - p.x)*(tempX - p.x) + (tempY - p.y)*(tempY - p.y));//считаем дистанцию (расстояние от точки А до точки Б). используя формулу длины вектора

			if (distance > 2){//этим условием убираем дергание во время конечной позиции спрайта

				p.x += 0.1*time*(tempX - p.x) / distance;//идем по иксу с помощью вектора нормали
				p.y += 0.1*time*(tempY - p.y) / distance;//идем по игреку так же
			}
			else { p.isMove = false; std::cout << "priehali\n"; }//говорим что уже никуда не идем и выводим веселое сообщение в консоль
		}







		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
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
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер для будущих целей
	int w, h, health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;//враги могут быть разные, мы не будем делать другой класс для врага.всего лишь различим врагов по имени и дадим каждому свое действие в update в зависимости от имени
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
			dx = 0.1;//даем скорость.этот объект всегда двигается
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
			{
				if (Dy>0){ y = i * 32 - h; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
				if (Dy<0){ y = i * 32 + 32; }//столкновение с верхними краями карты(может и не пригодиться)
				if (Dx>0){ x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }//с правым краем карты
				if (Dx<0){ x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }// с левым краем карты
			}
		}
	}

	void update(float time)
	{
		if (name == "EasyEnemy"){//для персонажа с таким именем логика будет такой

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
	int playerScore;//эта переменная может быть только у игрока

	Player(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name){
		playerScore = 0; state = stay;
		if (name == "Player1"){
			sprite.setTextureRect(IntRect(0, 110, w, h));
		}
	}

	void control(){
		if (Keyboard::isKeyPressed){//если нажата клавиша
			if (Keyboard::isKeyPressed(Keyboard::Left)) {//а именно левая
				state = left; speed = 0.1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				state = right; speed = 0.1;
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {//если нажата клавиша вверх и мы на земле, то можем прыгать
				state = jump; dy = -0.6; onGround = false;//увеличил высоту прыжка
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down;
			}
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент наш тайлик земли? то
			{
				if (Dy>0){ y = i * 32 - h;  dy = 0; onGround = true; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
				if (Dy<0){ y = i * 32 + 32;  dy = 0; }//столкновение с верхними краями карты(может и не пригодиться)
				if (Dx>0){ x = j * 32 - w; }//с правым краем карты
				if (Dx<0){ x = j * 32 + 32; }// с левым краем карты
			}
			//else { onGround = false; }//надо убрать т.к мы можем находиться и на другой поверхности или платформе которую разрушит враг
		}
	}

	void update(float time)
	{
		control();//функция управления персонажем
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right:dx = speed; break;//состояние идти вправо
		case left:dx = -speed; break;//состояние идти влево
		case up: break;//будет состояние поднятия наверх (например по лестнице)
		case down: dx = 0; break;//будет состояние во время спуска персонажа (например по лестнице)
		case stay: break;//и здесь тоже		
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy*time;
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0){ life = false; }
		if (!isMove){ speed = 0; }
		//if (!onGround) { dy = dy + 0.0015*time; }//убираем и будем всегда притягивать к земле
		if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0015*time;//постоянно притягиваемся к земле
	}
};

/*class Player {
public:
	float w, h, dx, dy, x, y, speed;
	int playerScore, health;
	bool life, isMove, onGround;//добавили переменные состояния нахождения на земле
	enum { left, right, up, down, jump, stay } state;//добавляем тип перечисления - состояние объекта
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
			dy = -0.4; onGround = false;//то состояние равно прыжок,прыгнули и сообщили, что мы не на земле

		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;
		}
	}
	void update(float time)
	{
		control();//функция управления персонажем
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right: dx = speed; break;//состояние идти вправо
		case left: dx = -speed; break;//состояние идти влево
		case up: break;//будет состояние поднятия наверх (например по лестнице)
		case down: dx = 0; break;//будет состояние во время спуска персонажа (например по лестнице)
		case stay: break;//и здесь тоже		
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy*time;
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0){ life = false; }
		if (!isMove){ speed = 0; }
		dy = dy + 0.0015*time;//делаем притяжение к земле
		if (life) { setPlayerCoordinateForView(x, y); }
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент наш тайлик земли? то
			{
				if (Dy>0){ y = i * 32 - h;  dy = 0; onGround = true; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
				if (Dy<0){ y = i * 32 + 32;  dy = 0; }//столкновение с верхними краями карты(может и не пригодиться)
				if (Dx>0){ x = j * 32 - w; }//с правым краем карты
				if (Dx<0){ x = j * 32 + 32; }// с левым краем карты
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
	easyEnemyImage.createMaskFromColor(Color(255, 0, 0));//маска по цвету


	Player p(heroImage, 250, 500, 70.0, 120.0, "Player1");//объект класса игрока
	
	Enemy easyEnemy(easyEnemyImage, 850, 671, 200, 97, "EasyEnemy");//простой враг, объект класса врага

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


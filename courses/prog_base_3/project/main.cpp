#include <SFML/Graphics.hpp>

using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Chris Jumper");



	Texture herotexture;
	herotexture.loadFromFile("images/hero.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 192, 96, 96));//получили нужный нам пр€моугольник с котом
	herosprite.setPosition(250, 250); //выводим спрайт в позицию x y 



	while (window.isOpen())
	{


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		/*if (Keyboard::isKeyPressed(Keyboard::Left)) { herosprite.move(-0.1, 0); } //перва€ координата ’ отрицательна =>идЄм влево
		if (Keyboard::isKeyPressed(Keyboard::Right)) { herosprite.move(0.1, 0); } //перва€ координата ’ положительна =>идЄм вправо
		if (Keyboard::isKeyPressed(Keyboard::Up)) { herosprite.move(0, -0.1); } //втора€ координата (”) отрицательна =>идЄм вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
		if (Keyboard::isKeyPressed(Keyboard::Down)) { herosprite.move(0, 0.1); } //втора€ координата (”) положительна =>идЄм вниз (если не пон€тно почему именно вниз - смотрим предыдущие уроки)*/
		if (Keyboard::isKeyPressed(Keyboard::Left)) { herosprite.move(-0.1, 0); herosprite.setTextureRect(IntRect(0, 96, 96, 96)); } //координата Y, на которой герой изображен идущим влево равна 96
		if (Keyboard::isKeyPressed(Keyboard::Right)) { herosprite.move(0.1, 0); herosprite.setTextureRect(IntRect(0, 192, 96, 96)); } //координата Y, на которой герой изображен идущем вправо равна 96+96=192
		if (Keyboard::isKeyPressed(Keyboard::Up)) { herosprite.move(0, -0.1); herosprite.setTextureRect(IntRect(0, 288, 96, 96)); } //координата Y на которой герой изображен идущим вверх равна 288
		if (Keyboard::isKeyPressed(Keyboard::Down)) { herosprite.move(0, 0.1); herosprite.setTextureRect(IntRect(0, 0, 96, 96)); } //координата 0, это верхн€€ часть изображени€ с героем, от нее и отталкиваемс€ ровными квадратиками по 96. 
		window.clear();
		window.draw(herosprite);
		window.display();
	}

	return 0;
}

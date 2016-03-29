#include <SFML/Graphics.hpp>

using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Chris Jumper");



	Texture herotexture;
	herotexture.loadFromFile("images/hero.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 192, 96, 96));//�������� ������ ��� ������������� � �����
	herosprite.setPosition(250, 250); //������� ������ � ������� x y 



	while (window.isOpen())
	{


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		/*if (Keyboard::isKeyPressed(Keyboard::Left)) { herosprite.move(-0.1, 0); } //������ ���������� � ������������ =>��� �����
		if (Keyboard::isKeyPressed(Keyboard::Right)) { herosprite.move(0.1, 0); } //������ ���������� � ������������ =>��� ������
		if (Keyboard::isKeyPressed(Keyboard::Up)) { herosprite.move(0, -0.1); } //������ ���������� (�) ������������ =>��� ����� (���������� �� ���������� ������ ������ ������ �����, � �� ����)
		if (Keyboard::isKeyPressed(Keyboard::Down)) { herosprite.move(0, 0.1); } //������ ���������� (�) ������������ =>��� ���� (���� �� ������� ������ ������ ���� - ������� ���������� �����)*/
		if (Keyboard::isKeyPressed(Keyboard::Left)) { herosprite.move(-0.1, 0); herosprite.setTextureRect(IntRect(0, 96, 96, 96)); } //���������� Y, �� ������� ����� ��������� ������ ����� ����� 96
		if (Keyboard::isKeyPressed(Keyboard::Right)) { herosprite.move(0.1, 0); herosprite.setTextureRect(IntRect(0, 192, 96, 96)); } //���������� Y, �� ������� ����� ��������� ������ ������ ����� 96+96=192
		if (Keyboard::isKeyPressed(Keyboard::Up)) { herosprite.move(0, -0.1); herosprite.setTextureRect(IntRect(0, 288, 96, 96)); } //���������� Y �� ������� ����� ��������� ������ ����� ����� 288
		if (Keyboard::isKeyPressed(Keyboard::Down)) { herosprite.move(0, 0.1); herosprite.setTextureRect(IntRect(0, 0, 96, 96)); } //���������� 0, ��� ������� ����� ����������� � ������, �� ��� � ������������� ������� ������������ �� 96. 
		window.clear();
		window.draw(herosprite);
		window.display();
	}

	return 0;
}

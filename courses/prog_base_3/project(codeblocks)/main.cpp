#include <SFML/Graphics.hpp>

using namespace sf;
/*
class Animation
{
public:
    std::vector<IncRect> frames, frames_flip;
    float currentFrame, speed;
    bool flip, isPlaying;
    Sprite sprite;




};*/



int main()
{
    RenderWindow window( VideoMode(200,200), "Test!");
    CircleShape MyCircle(100.f);
    MyCircle.setFillColor(Color::Green);

    Texture t;
    t.loadFromFile("fang.png");
    float currentFrame = 0;

    Sprite s;
    s.setTexture(t);
    s.setTextureRect( IntRect(0,244,40,55));
    s.setPosition(50,100);

    Clock clock;

    while(window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            window.close();
        }

        if( Keyboard::isKeyPressed(Keyboard::Left)){
            s.move(-0.1*time,0);
            currentFrame += 0.005*time;
            if (currentFrame > 6) currentFrame -=6;

            s.setTextureRect(IntRect(40*int(currentFrame)+40,244,-40,50));
        }

         if( Keyboard::isKeyPressed(Keyboard::Right)){
            s.move(0.1*time,0);
            currentFrame += 0.005*time;
            if (currentFrame > 6) currentFrame -=6;

            s.setTextureRect(IntRect(40*int(currentFrame),244,40,50));
        }
        if( Keyboard::isKeyPressed(Keyboard::Up)){
            s.move(0,-0.1);
        }
        if( Keyboard::isKeyPressed(Keyboard::Down)){
            s.move(0,0.1);
        }

        window.clear(Color::White);
        window.draw(s);
        window.display();
    }
    return 0;
    /*
    sf::RenderWindow win(sf::VideoMode(200, 200), "SFML Test");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }
        }

        win.clear();
        win.draw(shape);
        win.display();
    }

    return 0;*/
}

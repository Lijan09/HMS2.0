#include <iostream>
#include <sfml/Graphics.hpp>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1366, 768), "HMS", Style::Resize);
    window.setFramerateLimit(60);

    Texture texture;
    if (!texture.loadFromFile("src/asset/Textures/mainpage.png"))
    {
        cout << "Error loading background image\n";
        return -1;
    }

    RectangleShape background(Vector2f(window.getSize().x,window.getSize().y));

    background.setTexture(&texture);

    Font taskbarFont;
    if (!taskbarFont.loadFromFile("src/asset/Font/Inika/Inika-Bold.ttf")) {
        cout << "Cannot load Fonts!" << endl;
        return -1;
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::MouseButtonPressed:

                if (event.mouseButton.button == Mouse::Left)
                {

                    if (event.mouseButton.x >= window.getSize().x - 50 && event.mouseButton.x < window.getSize().x && event.mouseButton.y >= 0 && event.mouseButton.y < 50)
                    {
                        window.close();
                    }
                }
                break;

            default:
                break;
            }
        }

        //set positions

        //draw everything
        window.clear(Color::White);
        window.draw(background);

        window.display();
    }
}
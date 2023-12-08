#include <iostream>
#include <sfml/Graphics.hpp>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1366, 768), "HMS", Style::Resize);
    window.setFramerateLimit(60);

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("src/asset/Textures/mainpage.png"))
    {
        cout << "Error loading background image\n";
        return -1;
    }

    Texture logoTexture;
    if (!logoTexture.loadFromFile("src/asset/Textures/logo.png"))
    {
        cout << "Error loading background image\n";
        return -1;
    }

    Font font;
    if (!font.loadFromFile("src/asset/Font/futura/Futura Extra Black font.ttf")) {
        cout << "Cannot load Fonts!" << endl;
        return -1;
    } 

    Color red(235, 92, 91);
    Color hoverRed(244,81,81);

    Color green(85,185,156);
    Color hoverGreen(125,198,179);

    Color black(61,61,61);
    Color hoverBreen(71,71,71);

    RectangleShape logo(Vector2f(180, 190));
    logo.setPosition(587,288);
    logo.setTexture(&logoTexture);

    RectangleShape adminBox(Vector2f(305, 75));
    adminBox.setPosition(153, 282);
    adminBox.setFillColor(red);

    RectangleShape doctorBox(Vector2f(305, 75));
    doctorBox.setPosition(153, 435); 
    doctorBox.setFillColor(red);

    RectangleShape patientBox(Vector2f(305, 75));
    patientBox.setPosition(530, 589); 
    patientBox.setFillColor(red);

    RectangleShape nurseBox(Vector2f(305, 75));
    nurseBox.setPosition(897, 435); 
    nurseBox.setFillColor(red);

    RectangleShape receptionBox(Vector2f(305, 75));
    receptionBox.setPosition(897, 282); 
    receptionBox.setFillColor(red);

    RectangleShape background(Vector2f(window.getSize().x,window.getSize().y));
    background.setTexture(&backgroundTexture);

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
                    // close button
                    if (event.mouseButton.x >= window.getSize().x - 48 && event.mouseButton.x < window.getSize().x && event.mouseButton.y >= 0 && event.mouseButton.y < 48)
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

        window.draw(logo);
        window.draw(adminBox);
        window.draw(doctorBox);
        window.draw(patientBox);
        window.draw(nurseBox);
        window.draw(receptionBox);

        window.display();
    }
}
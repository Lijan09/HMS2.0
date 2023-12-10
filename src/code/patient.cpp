#include <iostream>
#include <sfml/Graphics.hpp>
#include "globals.h"
#include "functions.h"

using namespace sf;
using namespace std;

inline void runPatient(int *scene, RenderWindow *window)
{

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("src/asset/Textures/mainpage.png"))
    {
        cout << "Error loading background image\n";
        *scene = -1;
        return;
    }

    Texture logoTexture;
    if (!logoTexture.loadFromFile("src/asset/Textures/logo.png"))
    {
        cout << "Error loading background image\n";
        *scene = -1;
        return;
    }

    Font font;
    if (!font.loadFromFile("src/asset/Font/futura/Futura Extra Black font.ttf"))
    {
        cout << "Cannot load Fonts!" << endl;
        *scene = -1;
        return;
    }

    Color red(235, 92, 91);
    Color hoverRed(244, 81, 81);

    Color green(85, 185, 156);
    Color hoverGreen(125, 198, 179);

    Color black(61, 61, 61);
    Color hoverBreen(71, 71, 71);

    Color white(223, 240, 236);
    Color hoverWhite(200, 214, 211);

    RectangleShape logo(Vector2f(180, 190));
    logo.setPosition(587, 288);
    logo.setTexture(&logoTexture);

    RectangleShape background(Vector2f(window->getSize().x, window->getSize().y));
    background.setTexture(&backgroundTexture);

    RectangleShape logoutBox(Vector2f(305, 75));
    logoutBox.setPosition(530, 540);
    logoutBox.setFillColor(red);

    RectangleShape medsBoxBlack(Vector2f(50, 78));
    medsBoxBlack.setPosition(66, 377);
    medsBoxBlack.setFillColor(black);

    RectangleShape medsBoxWhite(Vector2f(1050, 78));
    medsBoxWhite.setPosition(116, 377);
    medsBoxWhite.setFillColor(white);

    string userString = "Hello " + globalName;

    Text userText("", font, 60);
    userText.setString(userString);
    userText.setPosition(400, 140);
    userText.setFillColor(black);

    Text commandText("Your prescribed medicines:", font, 60);
    commandText.setPosition(66, 280);
    commandText.setFillColor(black);

    Text medsText("", font, 44);
    medsText.setString(globalMeds);
    medsText.setPosition(135, 385);
    medsText.setFillColor(black); 

    Text logoutText("LogOut", font, 44);
    logoutText.setPosition(600, 550);
    logoutText.setFillColor(black);

    while (window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                *scene = -1;
                window->close();
                break;

            case Event::MouseButtonPressed:

                if (event.mouseButton.button == Mouse::Left)
                {
                    // close button
                    if (event.mouseButton.x >= window->getSize().x - 48 && event.mouseButton.x < window->getSize().x && event.mouseButton.y >= 0 && event.mouseButton.y < 48)
                    {
                        *scene = -1;
                        window->close();
                    }
                }

                if (logoutBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    *scene = 0;
                    return;
                }
                break;

            default:
                break;
            }
        }

        logoutBox.setFillColor(red);
        if (logoutBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            logoutBox.setFillColor(hoverRed);
        }

        // draw everything
        window->clear(Color::White);
        window->draw(background);

        window->draw(medsBoxBlack);
        window->draw(medsBoxWhite);
        window->draw(logoutBox);

        window->draw(userText);
        window->draw(commandText);
        window->draw(medsText);
        window->draw(logoutText);

        window->display();
    }
}
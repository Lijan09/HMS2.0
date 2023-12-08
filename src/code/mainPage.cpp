#include <iostream>
#include <sfml/Graphics.hpp>

using namespace sf;
using namespace std;

inline void runMain(int *scene, RenderWindow *window)
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

    RectangleShape logo(Vector2f(180, 190));
    logo.setPosition(587, 288);
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

    RectangleShape background(Vector2f(window->getSize().x, window->getSize().y));
    background.setTexture(&backgroundTexture);

    Text adminText("ADMIN", font, 44);
    adminText.setPosition(221, 293);
    adminText.setFillColor(black);

    Text doctorText("DOCTOR", font, 44);
    doctorText.setPosition(213, 444);
    doctorText.setFillColor(black);

    Text patientText("PATIENT", font, 44);
    patientText.setPosition(587, 600);
    patientText.setFillColor(black);

    Text nurseText("NURSE", font, 44);
    nurseText.setPosition(972, 444);
    nurseText.setFillColor(black);

    Text receptionText("RECEPTION", font, 44);
    receptionText.setPosition(920, 293);
    receptionText.setFillColor(black);

    Text userText("CHOOSE   USER!", font, 60);
    userText.setPosition(432, 140);
    userText.setFillColor(black);

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

                if(adminBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    *scene = 1;
                    return;
                }
 
                if(doctorBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    *scene = 2;
                    return;
                }
 
                if(patientBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    *scene = 3;
                    return;
                }
 
                if(nurseBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    *scene = 4;
                    return;
                }
 
                if(receptionBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    *scene = 5;
                    return;
                }

                break;

            default:
                break;
            }
        }

        adminBox.setFillColor(red);
        if (adminBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            adminBox.setFillColor(hoverRed);
        }

        doctorBox.setFillColor(red);
        if (doctorBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            doctorBox.setFillColor(hoverRed);
        }

        patientBox.setFillColor(red);
        if (patientBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            patientBox.setFillColor(hoverRed);
        }

        nurseBox.setFillColor(red);
        if (nurseBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            nurseBox.setFillColor(hoverRed);
        }

        receptionBox.setFillColor(red);
        if (receptionBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            receptionBox.setFillColor(hoverRed);
        }

        // draw everything
        window->clear(Color::White);
        window->draw(background);

        window->draw(logo);
        window->draw(adminBox);
        window->draw(doctorBox);
        window->draw(patientBox);
        window->draw(nurseBox);
        window->draw(receptionBox);

        window->draw(adminText);
        window->draw(doctorText);
        window->draw(patientText);
        window->draw(nurseText);
        window->draw(receptionText);
        window->draw(userText);

        window->display();
    }
}
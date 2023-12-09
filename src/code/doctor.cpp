#include <iostream>
#include <sfml/Graphics.hpp>
#include "globals.h"
#include "functions.h"

using namespace sf;
using namespace std;

inline void runDoctor(int *scene, RenderWindow *window)
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

    RectangleShape salaryBox(Vector2f(305, 75));
    salaryBox.setPosition(303, 548);
    salaryBox.setFillColor(red);

    RectangleShape logoutBox(Vector2f(305, 75));
    logoutBox.setPosition(759, 548);
    logoutBox.setFillColor(red);

    RectangleShape prescribeBox(Vector2f(305, 75));
    prescribeBox.setPosition(925, 375);
    prescribeBox.setFillColor(red);

    RectangleShape idBoxBlack(Vector2f(33, 62));
    idBoxBlack.setPosition(435, 332);
    idBoxBlack.setFillColor(black);

    RectangleShape idBoxWhite(Vector2f(382, 62));
    idBoxWhite.setPosition(468, 332);
    idBoxWhite.setFillColor(white);

    RectangleShape medsBoxBlack(Vector2f(33, 62));
    medsBoxBlack.setPosition(435, 432);
    medsBoxBlack.setFillColor(black);

    RectangleShape medsBoxWhite(Vector2f(382, 62));
    medsBoxWhite.setPosition(468, 432);
    medsBoxWhite.setFillColor(white);

    string userString = "Welcome Back, Dr. " + globalName;

    Text userText("", font, 60);
    userText.setString(userString);
    userText.setPosition(300, 140);
    userText.setFillColor(black);

    Text commandText("Choose Patient", font, 44);
    commandText.setPosition(478, 235);
    commandText.setFillColor(black);

    Text patientIdText("Patient ID:", font, 44);
    patientIdText.setPosition(161, 334);
    patientIdText.setFillColor(black);

    Text medsText("Medicines:", font, 44);
    medsText.setPosition(161, 434);
    medsText.setFillColor(black);

    Text prescribeText("Prescribe", font, 44);
    prescribeText.setPosition(968, 385);
    prescribeText.setFillColor(black);

    Text salaryText("Draw Salary", font, 44);
    salaryText.setPosition(308, 553);
    salaryText.setFillColor(black);

    Text logoutText("LogOut", font, 44);
    logoutText.setPosition(828, 555);
    logoutText.setFillColor(black);

    Text p_idInput("", font, 44);
    p_idInput.setPosition(473, 337);
    p_idInput.setFillColor(black);

    Text medsInput("", font, 44);
    medsInput.setPosition(473, 437);
    medsInput.setFillColor(black);

    string p_id;
    string meds;

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

            case Event::TextEntered:
            
                if (event.text.unicode == 8) // Check for the backspace character explicitly
                {
                    if (p_id.size() > 0 && idBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        p_id.erase(p_id.end() - 1); // Remove the last character from the input string
                        p_idInput.setString(p_id);  // Update the input text object with the new input string
                    }

                    if (meds.size() > 0 && medsBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        meds.erase(meds.end() - 1); // Remove the last character from the input string
                        medsInput.setString(meds);  // Update the input text object with the new input string
                    }
                }

                if (event.text.unicode >= 32 && event.text.unicode < 127) // Check for printable ASCII characters
                {
                    if (medsBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        meds += static_cast<char>(event.text.unicode);
                        medsInput.setString(meds); // Update the input text object with the new input string
                    }
                }

                if (event.text.unicode >= 48 && event.text.unicode < 58) // Check for printable ASCII characters
                {
                    if (idBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        p_id += static_cast<char>(event.text.unicode);
                        p_idInput.setString(p_id); // Update the input text object with the new input string
                    }
                }
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

                if (prescribeBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    makePatient();
                    updatePatient(p_id,"","",meds);
                    meds = "";
                    p_id = "";
                    p_idInput.setString(p_id);
                    medsInput.setString(meds);
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

        prescribeBox.setFillColor(red);
        if (prescribeBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            prescribeBox.setFillColor(hoverRed);
        }

        salaryBox.setFillColor(red);
        if (salaryBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            salaryBox.setFillColor(hoverRed);
        }

        idBoxWhite.setFillColor(white);
        if (idBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            idBoxWhite.setFillColor(hoverWhite);
        }

        medsBoxWhite.setFillColor(white);
        if (medsBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            medsBoxWhite.setFillColor(hoverWhite);
        }

        // draw everything
        window->clear(Color::White);
        window->draw(background);

        window->draw(idBoxBlack);
        window->draw(idBoxWhite);
        window->draw(prescribeBox);
        window->draw(medsBoxBlack);
        window->draw(medsBoxWhite);
        window->draw(salaryBox);
        window->draw(logoutBox);

        window->draw(userText);
        window->draw(commandText);
        window->draw(patientIdText);
        window->draw(p_idInput);
        window->draw(medsText);
        window->draw(medsInput);
        window->draw(prescribeText);
        window->draw(salaryText);
        window->draw(logoutText);

        window->display();
    }
}
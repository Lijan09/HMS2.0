#include <iostream>
#include <sfml/Graphics.hpp>
#include "functions.h"
#include "globals.h"

using namespace sf;
using namespace std;

inline void runReception(int *scene, RenderWindow *window)
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

    RectangleShape background(Vector2f(window->getSize().x, window->getSize().y));
    background.setTexture(&backgroundTexture);

    string userString = "Welcome "+ globalName;

    Text userText("", font, 60);
    userText.setString(userString);
    userText.setPosition(400, 130);
    userText.setFillColor(black);

    Text commandText("Patient Details", font, 44);
    commandText.setPosition(255, 229);
    commandText.setFillColor(black);

    Text addText("Add Data", font, 44);
    addText.setPosition(914, 292);
    addText.setFillColor(black);

    Text deleteText("Delete Data", font, 44);
    deleteText.setPosition(886, 403);
    deleteText.setFillColor(black);

    Text updateText("Update Data", font, 44);
    updateText.setPosition(875, 514);
    updateText.setFillColor(black);

    Text viewText("View Lists", font, 44);
    viewText.setPosition(908, 620);
    viewText.setFillColor(black);

    Text logoutText("LogOut", font, 44);
    logoutText.setPosition(190, 623);
    logoutText.setFillColor(black);

    RectangleShape addBox(Vector2f(305, 75));
    addBox.setPosition(871, 284);
    addBox.setFillColor(red);

    RectangleShape deleteBox(Vector2f(305, 75));
    deleteBox.setPosition(871, 395);
    deleteBox.setFillColor(red);

    RectangleShape updateBox(Vector2f(305, 75));
    updateBox.setPosition(871, 505);
    updateBox.setFillColor(red);

    RectangleShape viewBox(Vector2f(305, 75));
    viewBox.setPosition(871, 615);
    viewBox.setFillColor(red);

    RectangleShape logoutBox(Vector2f(305, 75));
    logoutBox.setPosition(120, 615);
    logoutBox.setFillColor(red);

    RectangleShape idBoxBlack(Vector2f(30, 56));
    idBoxBlack.setPosition(409, 328);
    idBoxBlack.setFillColor(black);

    RectangleShape idBoxWhite(Vector2f(348, 56));
    idBoxWhite.setPosition(439, 328);
    idBoxWhite.setFillColor(white);

    RectangleShape userBoxBlack(Vector2f(30, 56));
    userBoxBlack.setPosition(409, 406);
    userBoxBlack.setFillColor(black);

    RectangleShape userBoxWhite(Vector2f(348, 56));
    userBoxWhite.setPosition(439, 406);
    userBoxWhite.setFillColor(white);

    RectangleShape pwdBoxBlack(Vector2f(30, 56));
    pwdBoxBlack.setPosition(409, 484);
    pwdBoxBlack.setFillColor(black);

    RectangleShape pwdBoxWhite(Vector2f(348, 56));
    pwdBoxWhite.setPosition(439, 484);
    pwdBoxWhite.setFillColor(white);

    // inputs

    Text usernameInput("", font, 44);
    usernameInput.setPosition(444, 412);
    usernameInput.setFillColor(black);

    Text usernameText("UserName:", font, 44);
    usernameText.setPosition(135, 405);
    usernameText.setFillColor(black);

    Text pwdInput("", font, 44);
    pwdInput.setPosition(444, 490);
    pwdInput.setFillColor(black);

    Text pwdText("Password:", font, 44);
    pwdText.setPosition(135, 488);
    pwdText.setFillColor(black);

    Text idInput("", font, 44);
    idInput.setPosition(444, 333);
    idInput.setFillColor(black);

    Text idText("Patient ID:", font, 44);
    idText.setPosition(135, 327);
    idText.setFillColor(black);

    string username = "";
    string pwd = "";
    string idString = "";

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

            case Event::KeyPressed:

                if (event.key.code == Keyboard::Escape)
                {
                    *scene = 0;
                    return;
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

                if (logoutBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    *scene = 0;
                    return;
                }

                if (viewBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    *scene = 12;
                    return;
                }

                if (deleteBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    makePatient();
                    deletePatient(idString);
                    username = "";
                    pwd = "";
                    idString = "";
                    usernameInput.setString(username);
                    pwdInput.setString(pwd);
                    idInput.setString(idString);
                }

                if (addBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    makePatient();
                    insertPatient(idString, username, pwd);
                    username = "";
                    pwd = "";
                    idString = "";
                    usernameInput.setString(username);
                    pwdInput.setString(pwd);
                    idInput.setString(idString);
                }

                if (updateBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    makePatient();
                    updatePatient(idString, username, pwd, "");
                    username = "";
                    pwd = "";
                    idString = "";
                    usernameInput.setString(username);
                    pwdInput.setString(pwd);
                    idInput.setString(idString);
                }

                break;

            case Event::TextEntered:

                if (event.text.unicode == 8) // Check for the backspace character explicitly
                {
                    if (username.size() > 0 && userBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        username.erase(username.end() - 1); // Remove the last character from the input string
                        usernameInput.setString(username);  // Update the input text object with the new input string
                    }

                    if (pwd.size() > 0 && pwdBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        pwd.erase(pwd.end() - 1);                    // Remove the last character from the input string
                        pwdInput.setString(string(pwd.size(), '*')); // Update the input text object with a string of asterisks
                    }

                    if (idString.size() > 0 && idBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        idString.erase(idString.end() - 1); // Remove the last character from the input string
                        idInput.setString(idString);
                    }
                }

                if (event.text.unicode >= 48 && event.text.unicode < 58) // Check for printable ASCII characters
                {
                    if (idBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        idString += static_cast<char>(event.text.unicode);
                        idInput.setString(idString); // Update the input text object with the new input string
                    }
                }

                if (event.text.unicode >= 32 && event.text.unicode < 127) // Check for printable ASCII characters
                {
                    if (userBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        username += static_cast<char>(event.text.unicode);
                        usernameInput.setString(username); // Update the input text object with the new input string
                    }

                    if (pwdBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        pwd += static_cast<char>(event.text.unicode);
                        pwdInput.setString(string(pwd.size(), '*')); // Update the input text object with a string of asterisks
                    }
                }
                break;

            default:
                break;
            }
        }

        addBox.setFillColor(red);
        if (addBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            addBox.setFillColor(hoverRed);
        }

        deleteBox.setFillColor(red);
        if (deleteBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            deleteBox.setFillColor(hoverRed);
        }

        updateBox.setFillColor(red);
        if (updateBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            updateBox.setFillColor(hoverRed);
        }

        logoutBox.setFillColor(red);
        if (logoutBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            logoutBox.setFillColor(hoverRed);
        }

        viewBox.setFillColor(red);
        if (viewBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            viewBox.setFillColor(hoverRed);
        }

        userBoxWhite.setFillColor(white);
        if (userBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            userBoxWhite.setFillColor(hoverWhite);
        }

        pwdBoxWhite.setFillColor(white);
        if (pwdBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            pwdBoxWhite.setFillColor(hoverWhite);
        }

        idBoxWhite.setFillColor(white);
        if (idBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            idBoxWhite.setFillColor(hoverWhite);
        }

        // draw everything
        window->clear(Color::White);
        window->draw(background);

        window->draw(updateBox);
        window->draw(deleteBox);
        window->draw(addBox);
        window->draw(viewBox);
        window->draw(logoutBox);
        window->draw(userBoxBlack);
        window->draw(userBoxWhite);
        window->draw(pwdBoxBlack);
        window->draw(pwdBoxWhite);
        window->draw(idBoxBlack);
        window->draw(idBoxWhite);

        window->draw(userText);
        window->draw(commandText);
        window->draw(addText);
        window->draw(deleteText);
        window->draw(updateText);
        window->draw(viewText);
        window->draw(logoutText);

        window->draw(usernameInput);
        window->draw(usernameText);
        window->draw(idText);
        window->draw(idInput);
        window->draw(pwdInput);
        window->draw(pwdText);

        window->display();
    }
}
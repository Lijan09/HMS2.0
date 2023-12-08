#include <iostream>
#include <sfml/Graphics.hpp>

using namespace sf;
using namespace std;

inline void receptionLogin(int *scene, RenderWindow *window)
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

    RectangleShape userBoxBlack(Vector2f(33, 62));
    userBoxBlack.setPosition(399, 308);
    userBoxBlack.setFillColor(black);

    RectangleShape pwdBoxBlack(Vector2f(33, 62));
    pwdBoxBlack.setPosition(399, 393);
    pwdBoxBlack.setFillColor(black);

    RectangleShape userBoxWhite(Vector2f(382, 62));
    userBoxWhite.setPosition(432, 308);
    userBoxWhite.setFillColor(white);

    RectangleShape pwdBoxWhite(Vector2f(382, 62));
    pwdBoxWhite.setPosition(432, 393);
    pwdBoxWhite.setFillColor(white);

    RectangleShape loginBox(Vector2f(305, 75));
    loginBox.setPosition(303, 548);
    loginBox.setFillColor(red);

    RectangleShape backBox(Vector2f(305, 75));
    backBox.setPosition(759, 548);
    backBox.setFillColor(red);

    Text userText("PLEASE ENTER YOUR CREDENTIALS", font, 60);
    userText.setPosition(140, 140);
    userText.setFillColor(black);

    Text usernameInput("",font,44);
    usernameInput.setPosition(437, 317);
    usernameInput.setFillColor(black);

    Text pwdInput("",font,44);
    pwdInput.setPosition(437, 407);
    pwdInput.setFillColor(black);

    Text usernameText("UserName:", font, 44);
    usernameText.setPosition(120, 312);
    usernameText.setFillColor(black);

    Text pwdText("Password:", font, 44);
    pwdText.setPosition(120, 402);
    pwdText.setFillColor(black);

    Text login("Login", font, 44);
    login.setPosition(392, 558);
    login.setFillColor(black);

    Text back("Back", font, 44);
    back.setPosition(857, 558);
    back.setFillColor(black);

    string username = "";
    string pwd = "";

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

                if (event.key.code == Keyboard::Return)
                {
                    *scene = 6;
                    return;
                }
                if (event.key.code == Keyboard::Escape)
                {
                    *scene = 0;
                    return;
                }
                break;

            case Event::TextEntered:

                if (event.text.unicode == 8) // Check for the backspace character explicitly
                {
                    if (username.size() > 0 && userBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        username.erase(username.end() - 1); // Remove the last character from the input string
                        usernameInput.setString(username);   // Update the input text object with the new input string
                    }

                    if (pwd.size() > 0 && pwdBoxWhite.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                    {
                        pwd.erase(pwd.end() - 1);                   // Remove the last character from the input string
                        pwdInput.setString(string(pwd.size(), '*')); // Update the input text object with a string of asterisks
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

                if (backBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    *scene = 0;
                    return;
                }

                if (loginBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    *scene = 6;
                    return;
                }

                break;

            default:
                break;
            }
        }

        backBox.setFillColor(red);
        if (backBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            backBox.setFillColor(hoverRed);
        }

        loginBox.setFillColor(red);
        if (loginBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            loginBox.setFillColor(hoverRed);
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

        // draw everything
        window->clear(Color::White);
        window->draw(background);

        window->draw(pwdBoxBlack);
        window->draw(pwdBoxWhite);
        window->draw(userBoxBlack);
        window->draw(userBoxWhite);
        window->draw(loginBox);
        window->draw(backBox);

        window->draw(userText);
        window->draw(login);
        window->draw(usernameText);
        window->draw(pwdText);
        window->draw(back);
        window->draw(usernameInput);
        window->draw(pwdInput);

        window->display();
    }
}
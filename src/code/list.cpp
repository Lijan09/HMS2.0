#include <iostream>
#include <sfml/Graphics.hpp>
#include "sqlite3.h"
#include "functions.h"
#include "globals.h"

using namespace sf;
using namespace std;

inline void runLists(int *scene, RenderWindow *window)
{

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("src/asset/Textures/listpage.png"))
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

    RectangleShape nextBox(Vector2f(305, 75));
    nextBox.setPosition(990, 634);
    nextBox.setFillColor(red);

    RectangleShape previousBox(Vector2f(305, 75));
    previousBox.setPosition(92, 634);
    previousBox.setFillColor(red);

    Text prevText("Previous", font, 44);
    prevText.setPosition(125, 643);
    prevText.setFillColor(black);

    Text nextText("Next", font, 44);
    nextText.setPosition(1086, 643);
    nextText.setFillColor(black);

    Text idText("", font, 44);
    idText.setFillColor(black);

    Text nameText("", font, 44);
    nameText.setFillColor(black);

    Text posText("", font, 44);
    posText.setFillColor(black);

    // start

    int i = 0, page = 1, dataindex = 0;
    totalData = 0;

    sqlite3_open("hospital.db", &db);

    query = "SELECT * FROM hospital";
    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "Error3: " << sqlite3_errmsg(db) << endl;
    }

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        totalData = totalData + 1;
    }

    Data data[totalData];
    string str, str2, str3;

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW && dataindex < totalData)
    {
        const unsigned char *change = sqlite3_column_text(stmt, 0);
        str = reinterpret_cast<const char *>(change);
        data[i].id = str;

        const unsigned char *change1 = sqlite3_column_text(stmt, 1);
        str2 = reinterpret_cast<const char *>(change1);
        data[i].name = str2;

        const unsigned char *change2 = sqlite3_column_text(stmt, 3);
        str3 = reinterpret_cast<const char *>(change2);
        data[i].pos = str3;
        i++;
        dataindex++;
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    sqlite3_close(db);

    // end

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

                if (previousBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    cout << "Prev" << endl;
                    page--;
                    if (page < 1)
                    {
                        *scene = 6;
                        return;
                    }
                }

                if (nextBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
                {
                    if (page <= 2)
                    {
                        page++;
                    }
                }

                break;

            default:
                break;
            }
        }

        previousBox.setFillColor(red);
        if (previousBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            previousBox.setFillColor(hoverRed);
        }

        nextBox.setFillColor(red);
        if (nextBox.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
        {
            nextBox.setFillColor(hoverRed);
        }

        // draw everything

        int id_y = 269;

        window->clear(Color::White);
        window->draw(background);

        if (page == 1)
        {
            for (int k = 0; k < 5; k++)
            {
                if (k < totalData)
                {
                    idText.setPosition(200, id_y);
                    idText.setString(data[k].id);

                    nameText.setPosition(590, id_y);
                    nameText.setString(data[k].name);

                    posText.setPosition(1014, id_y);
                    posText.setString(data[k].pos);

                    window->draw(idText);
                    window->draw(nameText);
                    window->draw(posText);
                    id_y += 70;
                }
            }
        }

        if (page == 2 && totalData > 4)
        {
            for (int j = 5; j < 10; j++)
            {
                if (j < totalData)
                {
                    idText.setPosition(200, id_y);
                    idText.setString(data[j].id);

                    nameText.setPosition(590, id_y);
                    nameText.setString(data[j].name);

                    posText.setPosition(1014, id_y);
                    posText.setString(data[j].pos);

                    window->draw(idText);
                    window->draw(nameText);
                    window->draw(posText);
                    id_y += 70;
                }
            }
        }

        window->draw(nextBox);
        window->draw(previousBox);

        window->display();
    }
}
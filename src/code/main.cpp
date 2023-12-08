#include <iostream>
#include <sfml/Graphics.hpp>
#include "mainPage.cpp"
#include "loginPage.cpp"

using namespace sf;
using namespace std;

int main()
{
    int *scene = new int(0);

    RenderWindow window(VideoMode(1366, 768), "HMS", Style::Resize);
    window.setFramerateLimit(60);

    while (*scene != -1)
    {
        switch (*scene)
        {
        case 0: // Login page
            runMain(scene, &window);
            window.clear();
            break;

        case 1: //adminLogin
            runLogin(scene, &window);
            break;

        case 2: //doctorLogin
            cout << "works!";
            break;

        case 3: //patientLogin
            cout << "works!";
            break;

        case 4: //nurseLogin
            cout << "works!";
            break;

        case 5: //receptionLogin
            cout << "works!";
            break;

        }
    }
}

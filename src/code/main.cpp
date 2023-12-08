#include <iostream>
#include <sfml/Graphics.hpp>
#include "mainPage.cpp"

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
        }
    }
}

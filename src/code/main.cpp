#include <iostream>
#include <sfml/Graphics.hpp>
#include "mainPage.cpp"
#include "login/adminLogin.cpp"
#include "login/patientLogin.cpp"
#include "login/doctorLogin.cpp"
#include "login/nurseLogin.cpp"
#include "login/receptionLogin.cpp"
#include "admin.cpp"
#include "globals.h"
#include "functions.h"

using namespace sf;
using namespace std;

string globalName;

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

        case 1: // adminLogin
            adminLogin(scene, &window);
            break;

        case 2: // doctorLogin
            doctorLogin(scene, &window);
            break;

        case 3: // patientLogin
            patientLogin(scene, &window);
            break;

        case 4: // nurseLogin
            nurseLogin(scene, &window);
            break;

        case 5: // receptionLogin
            receptionLogin(scene, &window);
            break;
        case 6: // adminPage
            runAdmin(scene, &window);
            break;
        }
    }
}

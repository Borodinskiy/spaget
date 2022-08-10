#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "windowListener.hpp"
#include "uiBase.hpp"

int main()
{
#ifdef _DEBUG
    printf("This is a debug version. Recommended to use release (without _debug in filename)\n\n");
#endif
    printf("Entering to workdir. . .\n");
    system("pwd");

    sf::RenderWindow window;
    sf::Image icon;
    WindowListener wlistener(window);
    
    icon.loadFromFile("data/icon.png");
    window.create(sf::VideoMode(1280U, 720U), "Spaget");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);
//    window.setFramerateLimit(60);

    std::vector<UI> uis;
    uis.reserve(9);

    for (unsigned int i = 0; i < 9; i++)
    {
        uis.push_back(UI(wlistener.getEventsList(), { 0.f, 0.f }, {128.f, 64.f }));
        uis[i].setScale(1.f);
        uis[i].setupAlignmentByView(window.getView());
        uis[i].setAlignmentPoint(i);
    }

    sf::Font font;
    sf::Text log("", font);
    font.loadFromFile("data/misans.ttf");

    do
    {
        wlistener.handleEvents();

        if (wlistener.getEventsList().win_resized)
        {
            for (unsigned int i = 0; i < 9; i++)
            {
                uis[i].setupAlignmentByView(window.getView());
            }
        }

        if (wlistener.getEventsList().key_up)
        {
            switch (wlistener.getEventsList().key_up_code)
            {
            case sf::Keyboard::Escape:
                window.close();
                break;
            };
        }

        window.clear();

        for (auto ui : uis)
            window.draw(ui);

        log.setString("mouse x,y - " + std::to_string(wlistener.getEventsList().mouse_position_raw.x) + ", " + std::to_string(wlistener.getEventsList().mouse_position_raw.y));
        window.draw(log);

        window.display();   
    }
    while (window.isOpen());
    

    printf("This is a final wrotten message before return zero\n\n");
    return 0;
}
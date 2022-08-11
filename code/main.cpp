#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "windowListener.hpp"
#include "button.hpp"

#define DEFAULT_VIEW_SIZE sf::Vector2f(1280.f, 720.f)

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
    window.create(sf::VideoMode(DEFAULT_VIEW_SIZE.x, DEFAULT_VIEW_SIZE.y), "Spaget");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);
//    window.setFramerateLimit(60);

    UIEvents uievents;
    UIEvent storage;

    std::vector<UI*> uis;
    uis.reserve(9);

    for (unsigned int i = 0; i < 9; i++)
    {
        uis.push_back(new UIButton(wlistener.getEventsList(), uievents, { 0.f, 0.f }, {128.f, 64.f }));
        uis[i]->setScale({ window.getView().getSize().x / DEFAULT_VIEW_SIZE.x, window.getView().getSize().y / DEFAULT_VIEW_SIZE.y });
        uis[i]->setupAlignmentByView(window.getView());
        switch (i)
        {
        case 3:
            uis[i]->setPosition({ 0.f, -68.f });
            uis[i]->setAlignmentPoint(CENTER);
            break;
        case 5:
            uis[i]->setPosition({ 0.f, 68.f });
            uis[i]->setAlignmentPoint(CENTER);
            break;
        default:
            uis[i]->setAlignmentPoint(i);
            break;
        }
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
                uis[i]->setScale({window.getView().getSize().x / DEFAULT_VIEW_SIZE.x, window.getView().getSize().y / DEFAULT_VIEW_SIZE.y});
                uis[i]->setupAlignmentByView(window.getView());
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

        while (uievents.pollEvent(storage))
        {
            switch (storage.id)
            {
            case stringHash("close"):
                window.close();
                break;
            };
        };

        window.clear();

        for (auto& ui : uis)
        {
            ui->update();
            window.draw(*ui);
        }

        log.setString("fps - " + std::to_string((int)(1.f / wlistener.getEventsList().frametime))  +"\nmouse x,y - " + std::to_string(wlistener.getEventsList().mouse_position_raw.x) + ", " + std::to_string(wlistener.getEventsList().mouse_position_raw.y));
        window.draw(log);

        window.display();   
    }
    while (window.isOpen());
    

    printf("This is a final wrotten message before return zero\n\n");
    return 0;
}
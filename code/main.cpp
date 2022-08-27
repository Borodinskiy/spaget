#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

    ui::BUTTON_SOUND = new sf::SoundBuffer();
    ui::BUTTON_SOUND->loadFromFile("data/sound/click.ogg");

    sf::RenderWindow window;
    sf::Image icon;
    WindowListener wlistener(window);
    
    icon.loadFromFile("data/icon.png");
    window.create(sf::VideoMode(DEFAULT_VIEW_SIZE.x, DEFAULT_VIEW_SIZE.y), "Spaget", sf::Style::Close);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);
//    window.setFramerateLimit(60);

    ui::EventsHandler uievents;
    ui::Event storage;

    ui::WidgetExecutable::setDefaultWindowEventsLink(&wlistener.getEventsList());
    ui::WidgetExecutable::setDefaultEventHandlerLink(&uievents);

    sf::Font font;
    ui::Button button({"label", font, 30U});

    button.setupAlignmentByView(window.getView());
    button.setAlignmentPoint(ALIGN::CENTER);
    button.setSize({ 256.f, 64.f });

    sf::Text log("", font);
    font.loadFromFile("data/misans.ttf");

    do
    {
        wlistener.handleEvents();

        if (wlistener.getEventsList().win_resized)
        {
            button.setupAlignmentByView(window.getView());
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

        button.update();
        window.draw(button);

//        log.setString("fps - " + std::to_string((int)(1.f / wlistener.getEventsList().frametime))  +"\nmouse x,y - " + std::to_string(wlistener.getEventsList().mouse_position_raw.x) + ", " + std::to_string(wlistener.getEventsList().mouse_position_raw.y));
//        window.draw(log);

        window.display();   
    }
    while (window.isOpen());
    
    delete ui::BUTTON_SOUND;

    printf("This is a final wrotten message before return zero\n\n");
    return EXIT_SUCCESS;
}
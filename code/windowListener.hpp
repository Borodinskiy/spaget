#pragma once
#include "SFML/Graphics.hpp"

struct WindowEvents
{
    float frametime{};
    bool  win_resized{};

    bool mouse_moved     {};
    bool mouse_pressed   {};
    bool mouse_down      {};
    bool mouse_up        {};
    bool mouse_scrolled  {};
    int  mouse_down_buttonindex {};
    int  mouse_up_buttonindex   {};
    int  mouse_scroll_delta     {};
    //Raw position from window form
    sf::Vector2i mouse_position_raw       {};
    sf::Vector2i mouse_down_position_raw  {};
    sf::Vector2i mouse_up_position_raw    {};
    sf::Vector2i mouse_scroll_position_raw{};
    //Corrected for current window's view
    sf::Vector2f mouse_position       {};
    sf::Vector2f mouse_down_position  {};
    sf::Vector2f mouse_up_position    {};
    sf::Vector2f mouse_scroll_position{};
    bool key_pressed     {};
    bool key_down        {};
    bool key_up          {};
    bool key_control     {};
    bool key_shift       {};
    bool key_alt         {};
                     
    int  key_down_code   {};
    int  key_up_code     {};
                     
    bool text_entered    {};
                  
    sf::Uint32  text_code{};
};

class WindowListener
{
public:
    WindowListener(sf::RenderWindow& window);

    WindowEvents& getEventsList();

    void handleEvents();

    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow& window;
    sf::Event handler;
    sf::Clock clock;

    WindowEvents events;
};
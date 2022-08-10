#include "windowListener.hpp"

WindowListener::WindowListener(sf::RenderWindow& window)
    : window{window}
{}

WindowEvents& WindowListener::getEventsList() { return events; }

void WindowListener::handleEvents()
{
    events.frametime = clock.restart().asSeconds();
    events.win_resized = false;

    events.mouse_moved = false;

    events.mouse_up = false;
    events.mouse_down = false;

    events.key_up = false;
    events.key_down = false;

    events.text_entered = false;

    while(window.pollEvent(handler))
    {
        switch (handler.type)
            {
            case sf::Event::Closed: window.close(); break;
            case sf::Event::Resized: 
                events.win_resized = true;
                window.setView(sf::View
                (
                    sf::Vector2f((float)window.getSize().x, (float)window.getSize().y) / 2.f,
                    { (float)window.getSize().x, (float)window.getSize().y }
                )); 
                break;
            case sf::Event::MouseMoved:
            {
                events.mouse_moved = true;
                events.mouse_position_raw = { handler.mouseMove.x, handler.mouseMove.y };
                events.mouse_position     = window.mapPixelToCoords({ handler.mouseMove.x, handler.mouseMove.y });
            } break;
            case sf::Event::MouseButtonPressed:
            {
                events.mouse_pressed = true;
                events.mouse_down = true;

                events.mouse_down_position_raw = { handler.mouseButton.x, handler.mouseButton.y };
                events.mouse_down_position     = window.mapPixelToCoords({ handler.mouseButton.x, handler.mouseButton.y });
                events.mouse_down_buttonindex = handler.mouseButton.button;
            } break;
            case sf::Event::MouseButtonReleased:
            {
                events.mouse_pressed = false;
                events.mouse_up = true;

                events.mouse_up_position_raw = { handler.mouseButton.x, handler.mouseButton.y };
                events.mouse_up_position     = window.mapPixelToCoords({ handler.mouseButton.x, handler.mouseButton.y });
                events.mouse_up_buttonindex = handler.mouseButton.button;
            } break;
            case sf::Event::MouseWheelScrolled:
            {
                events.mouse_scrolled = true;

                events.mouse_scroll_delta = handler.mouseWheelScroll.delta;
                events.mouse_scroll_position_raw = { handler.mouseWheelScroll.x,handler.mouseWheelScroll.x };
                events.mouse_scroll_position     = window.mapPixelToCoords({ handler.mouseWheelScroll.x, handler.mouseWheelScroll.y });
            } break;
            case sf::Event::KeyPressed:
            {
                events.key_pressed = true;
                events.key_down = true;

                events.key_down_code = handler.key.code;
                events.key_control   = handler.key.control;
                events.key_shift     = handler.key.shift;
                events.key_alt       = handler.key.alt;
            } break;
            case sf::Event::KeyReleased:
            {
                events.key_pressed = false;
                events.key_up = true;

                events.key_up_code = handler.key.code;
                events.key_control   = handler.key.control;
                events.key_shift     = handler.key.shift;
                events.key_alt       = handler.key.alt;

            } break;
            case sf::Event::TextEntered:
            {
                events.text_entered = true;
                events.text_code = handler.text.unicode;
            } break;
            }
    }
}

sf::RenderWindow& WindowListener::getWindow() { return window; }

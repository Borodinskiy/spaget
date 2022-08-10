#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "windowListener.hpp"
#include "coordinate.hpp"

constexpr unsigned int stringHash(const char *string)
{
    unsigned int i = 0, hash = 0;
    for (; string[i] != '\0'; i++)
        hash += (unsigned int)string[i];

    return hash + i;
}

struct UIEvent
{
    unsigned int id;
};


class UIEvents
{
public:
    UIEvents();
    ~UIEvents();

    bool receiveEvent(UIEvent event);
    //If have unreaded events, returns true and handling event info to "storage" variable
    bool pollEvent(UIEvent& storage);

private:
    std::list<UIEvent> events;
};

class UI: public TransForm, public sf::Drawable
{
public:
    UI(WindowEvents& window_events, UIEvents& ui_events, sf::Vector2f position, sf::Vector2f size);
    ~UI();

    
    virtual void updateElements();

protected:
    void refresh(unsigned int type = 0);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    WindowEvents& w_events;
    UIEvents&    ui_events;

    sf::RectangleShape m_fone;

};
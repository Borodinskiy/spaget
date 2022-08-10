#pragma once
#include <SFML/Graphics.hpp>
#include "windowListener.hpp"
#include "coordinate.hpp"


class UI: public TransForm, public sf::Drawable
{
public:
    UI(WindowEvents& window_events, sf::Vector2f position, sf::Vector2f size);
    ~UI();

    
    virtual void updateElements();

protected:

    void refresh(unsigned int type = 0);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    WindowEvents& w_events;

    sf::RectangleShape m_fone;

};
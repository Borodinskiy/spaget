#pragma once
#include "uiBase.hpp"

class UIButton : public UI
{
public:
    UIButton(WindowEvents &window_events, UIEvents &ui_events, sf::Vector2f position, sf::Vector2f size);
    ~UIButton();

    void update();

    void updateElements();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::VertexArray b_fone;
    sf::Text        b_text;
};
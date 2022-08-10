#include "button.hpp"

UIButton::UIButton(WindowEvents &window_events, UIEvents &ui_events, sf::Vector2f position, sf::Vector2f size)
    : UI(window_events, ui_events, position, size)
{
    b_fone.resize(4);
    b_fone.setPrimitiveType(sf::Quads);
    for (unsigned int i = 0; i < 4; i++)
        b_fone[i].color = {50 * i, 50 * i, 50 * i};
}

UIButton::~UIButton()
{
}

void UIButton::updateElements()
{
    b_fone[0].position = getPosition();
    b_fone[1].position = getPosition() + sf::Vector2f(w, 0.f);
    b_fone[2].position = getPosition() + getSize();
    b_fone[3].position = getPosition() + sf::Vector2f(0.f, h);
}

void UIButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(b_fone);
}

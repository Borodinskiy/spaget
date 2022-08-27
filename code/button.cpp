#include "button.hpp"

sf::SoundBuffer *UINAMESPACE::BUTTON_SOUND{};

using namespace UINAMESPACE;

const int PREFERED_MOUSE_BUTTON{sf::Mouse::Left};

const float OUTLINE_THICKNESS{4.f};

const sf::Color DEFAULT_FILL{120, 20, 30};
const sf::Color DEFAULT_OUTLINE{DEFAULT_FILL};
const sf::Color DEFAULT_TEXT{sf::Color::White};

const sf::Color HIGHLIGHT_FILL{60,  10, 15 };
const sf::Color HIGHLIGHT_OUTLINE{255, 20, 30};
const sf::Color HIGHLIGHT_TEXT{HIGHLIGHT_OUTLINE};

const sf::Color PRESSED_FILL{HIGHLIGHT_FILL};
const sf::Color PRESSED_OUTLINE{HIGHLIGHT_FILL};
const sf::Color PRESSED_TEXT{sf::Color::Black};

Button::Button(sf::Text label)
    : b_text{label}
    , b_fone{}
    , b_sound{*BUTTON_SOUND}
{
    onHoverChange();
}
void Button::onRefreshBounds()
{
    b_fone.setOutlineThickness(OUTLINE_THICKNESS * getScale().left);

    sf::Vector2f outline_thickness{OUTLINE_THICKNESS, OUTLINE_THICKNESS};
    b_fone.setPosition(getPosition() + outline_thickness);
    b_fone.setSize(getSize() - outline_thickness * 2.f);

    b_text.setPosition(getPosition() + getSize() / 2.f - sf::Vector2f(b_text.getGlobalBounds().width / 2.f, b_text.getCharacterSize() / 1.5f ));
}
void Button::onUpdate()
{}
void Button::onHoverChange()
{
    if (m_hovered)
    {
        b_fone.setFillColor(HIGHLIGHT_FILL);
        b_fone.setOutlineColor(HIGHLIGHT_OUTLINE);
        b_text.setFillColor(HIGHLIGHT_TEXT);
    }
    else
    {
        b_fone.setFillColor(DEFAULT_FILL);
        b_fone.setOutlineColor(DEFAULT_OUTLINE);
        b_text.setFillColor(DEFAULT_TEXT);
    }
}
void Button::onPressedChange(int button_index)
{
    if (m_pressed && button_index == PREFERED_MOUSE_BUTTON)
    {
        b_fone.setFillColor(PRESSED_FILL);
        b_fone.setOutlineColor(PRESSED_OUTLINE);
        b_text.setFillColor(PRESSED_TEXT);
    }
    else
    {
        b_fone.setFillColor(HIGHLIGHT_FILL);
        b_fone.setOutlineColor(HIGHLIGHT_OUTLINE);
        b_text.setFillColor(HIGHLIGHT_TEXT);
    }
}
void Button::onClick(int clicked_button)
{
    if (clicked_button == PREFERED_MOUSE_BUTTON)
    {
        b_sound.play();
        e_handler.addEvent("s");
    }
}
void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(b_fone);
    target.draw(b_text);
}

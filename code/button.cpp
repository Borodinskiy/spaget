#include "button.hpp"

sf::SoundBuffer *UINAMESPACE::BUTTON_SOUND{};

using namespace UINAMESPACE;

//in seconds
//const int TIME_FOR_ANIMATION = 5.f;
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

Button::
    Button(sf::Text label, Event event, WindowEvents &events, EventsHandler &handler
        , sf::FloatRect bounds, int align_point, sf::FloatRect align_rect)
    : WidgetExecutable(event, events, handler, bounds, align_point, align_rect)
    , b_text{label}
    , b_fone_color{sf::Color::Black, DEFAULT_FILL, 10.f}
    , b_outline_color{sf::Color::Black, DEFAULT_OUTLINE, 10.f}
    , b_text_color{sf::Color::Black, DEFAULT_TEXT, 10.f}
    , b_text_char_size{b_text.getCharacterSize()}
{
    refreshBounds(REFRESH_TYPE::ALL);
}

sf::Text& Button::getText()
{
    return b_text;   
}

void Button::onRefreshBounds()
{
    b_fone.setOutlineThickness(OUTLINE_THICKNESS * getScale().left);

    sf::Vector2f outline_thickness{OUTLINE_THICKNESS, OUTLINE_THICKNESS};
    b_fone.setPosition(getPosition() + outline_thickness);
    b_fone.setSize(getSize() - outline_thickness * 2.f);

    b_text.setScale({getScale().width, getScale().height});
    b_text.setPosition(roundVector(getPosition() + getSize() / 2.f - sf::Vector2f(b_text.getGlobalBounds().width / 2.f, b_text.getCharacterSize() / 1.5f * f_y )));
}
void Button::onUpdate()
{
    b_fone_color.update(m_events.frametime);
    b_fone.setFillColor(b_fone_color.getColor());
    b_outline_color.update(m_events.frametime);
    b_fone.setOutlineColor(b_outline_color.getColor());
    b_text_color.update(m_events.frametime);
    b_text.setFillColor(b_text_color.getColor());
}
void Button::onHoverChange()
{
    if (m_hovered)
    {
        b_fone_color.setTarget(HIGHLIGHT_FILL);
        b_outline_color.setTarget(HIGHLIGHT_OUTLINE);
        b_text_color.setTarget(HIGHLIGHT_TEXT);
    }
    else
    {
        b_fone_color.setTarget(DEFAULT_FILL);
        b_outline_color.setTarget(DEFAULT_OUTLINE);
        b_text_color.setTarget(DEFAULT_TEXT);
    }
}
void Button::onPressedChange(int button_index)
{
    if (m_pressed && button_index == PREFERED_MOUSE_BUTTON)
    {
        b_fone_color.setTarget(PRESSED_FILL);
        b_outline_color.setTarget(PRESSED_OUTLINE);
        b_text_color.setTarget(PRESSED_TEXT);
    }
    else
    {
        b_fone_color.setTarget(HIGHLIGHT_FILL);
        b_outline_color.setTarget(HIGHLIGHT_OUTLINE);
        b_text_color.setTarget(HIGHLIGHT_TEXT);
    }
}
void Button::onClick(int clicked_button)
{
    if (clicked_button == PREFERED_MOUSE_BUTTON)
    {
        b_sound.play();
        sendEvent();
    }
}
void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(b_fone);
    target.draw(b_text);
}

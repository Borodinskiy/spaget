#pragma once
#include "uiBase.hpp"
#include <SFML/Audio/Sound.hpp>
#include "utils.hpp"

namespace UINAMESPACE
{
    using namespace UINAMESPACE;

    extern sf::SoundBuffer* BUTTON_SOUND;

    class Button : public WidgetExecutable
    {
    public:
        Button(sf::Text label, Event event, WindowEvents &events, EventsHandler &handler
        , sf::FloatRect bounds = {}, int align_point = ALIGN::LEFT_TOP, sf::FloatRect align_rect = {});

        
        sf::Text& getText();

    private:
        void onRefreshBounds();

        void onUpdate();
        void onHoverChange();
        void onPressedChange(int button_index);
        void onClick(int clicked_button);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        float b_text_char_size;
        sf::RectangleShape b_fone;
        LerpingColor       b_fone_color;
        LerpingColor       b_outline_color;
        sf::Text           b_text;
        LerpingColor       b_text_color;
        sf::Sound          b_sound;
    };
};
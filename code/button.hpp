#pragma once
#include "uiBase.hpp"
#include "SFML/Audio/Sound.hpp"

namespace UINAMESPACE
{
    using namespace UINAMESPACE;

    extern sf::SoundBuffer* BUTTON_SOUND;

    class Button : public WidgetExecutable
    {
    public:
        Button(sf::Text label);


    private:
        void onRefreshBounds();

        void onUpdate();
        void onHoverChange();
        void onPressedChange(int button_index);
        void onClick(int clicked_button);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::RectangleShape b_fone;
        sf::Text           b_text;
        sf::Sound          b_sound;
    };
};
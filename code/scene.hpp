#pragma once
#include "uiBase.hpp"
#include "button.hpp"

#define GAMENAMESPACE game
#ifdef _DEBUG
#define DEFAULT_VIEW_SIZE sf::Vector2f(1280.f, 720.f)
#else
#define DEFAULT_VIEW_SIZE sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)
#endif

namespace GAMENAMESPACE
{
    class Scene : public sf::Drawable
    {
    public:
        Scene(sf::RenderWindow &window);

        virtual void update() = 0;

        sf::RenderWindow getWindow();

    protected:
        virtual void onWindowResize() {}
        
    protected:
        sf::RenderWindow &m_window;
        WindowListener    m_listener;

    };

    class MainMenu : public Scene
    {
    public:
        MainMenu(sf::RenderWindow &window);

        void update();

        void startScreen();
        void settingsScreen();
        void exitSplash();

    private:
        void onWindowResize();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Font m_font;
        ui::EventsHandler m_uihandler;
        ui::Container m_uicontainer;

        sf::FloatRect m_align_rect;
        sf::Text m_text;
    };

};
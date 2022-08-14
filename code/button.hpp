#pragma once
#include "uiBase.hpp"

class UISprite : public sf::Drawable
{
public:
    UISprite(sf::Texture& texture, sf::Vector2u tilesize);
    ~UISprite();

    void initialize();
    void setSize(sf::Vector2f s);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Image m_image;
    sf::Texture& m_tex;
    sf::VertexArray m_fone;

    sf::Vector2u m_tilesize;
    std::list<sf::IntRect> m_tilerects;
};

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
#include "button.hpp"

UISprite::UISprite(sf::Texture &texture, sf::Vector2u tilesize)
    : m_tex{texture}
    , m_tilesize{tilesize}
{
    m_image = m_tex.copyToImage();
    m_fone.resize(9 * 4);
    m_fone.setPrimitiveType(sf::Quads);
}

UISprite::~UISprite()
{}

void UISprite::initialize()
{
    m_tilerects.clear();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            sf::Vector2i used_size{};

            for (unsigned int y = 0; y < 64U; y++)
                for (unsigned int x = 0; x < 64U; x++)
                {
                    if (m_image.getPixel(x, y).a != 0)
                    {
                        if (used_size.x < (int)x)
                            used_size.x = (int)x;
                        if (used_size.y < (int)y)
                            used_size.y = (int)y;
                    }
                }
            m_tilerects.push_back({ m_tilesize.x * j, m_tilesize.y * i, used_size.x, used_size.y });
            auto t = *(--m_tilerects.end());
            m_fone[i * j    ].texCoords = { t.left, t.top };
            m_fone[i * j + 1].texCoords = { t.left + t.width, t.top };
            m_fone[i * j + 2].texCoords = { t.left + t.width, t.top + t.height };
            m_fone[i * j + 3].texCoords = { t.left, t.top + t.height };
        }
}

void UISprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_fone, states);
}

UIButton::UIButton(WindowEvents &window_events, UIEvents &ui_events, sf::Vector2f position, sf::Vector2f size)
    : UI(window_events, ui_events, position, size)
{
    b_fone.resize(4);
    b_fone.setPrimitiveType(sf::Quads);
    for (unsigned int i = 0; i < 4; i++)
        b_fone[i].color = { 128, 90, 34 };
}

UIButton::~UIButton()
{
}

void UIButton::update()
{
    if (getBounds().contains(win_events.mouse_position))
        for (unsigned int i = 0; i < 4; i++)
            b_fone[i].color = { 100, 100, 100 };
    else
        for (unsigned int i = 0; i < 4; i++)
            b_fone[i].color = { 128, 90, 34 };
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

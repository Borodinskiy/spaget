#include "utils.hpp"

template <typename T>
sf::Vector2<T> roundVec(sf::Vector2<T> vector)
{
    return sf::Vector2<T>(round(vector.x), round(vector.y));
}
sf::Vector2f roundVector(sf::Vector2f vector)
{
    return sf::Vector2f(round(vector.x), round(vector.y));
}

LerpingColor::LerpingColor(sf::Vector3f color, sf::Vector3f target, float speed)
    : m_color{color}
    , m_color_target{target}
    , m_speed{speed}
{}
LerpingColor::LerpingColor(sf::Color color, sf::Color target, float speed)
    : LerpingColor
        ( sf::Vector3f((float)color.r, (float)color.g, (float)color.b)
        , sf::Vector3f((float)target.r, (float)target.g, (float)target.a), speed)
{}

void LerpingColor::update(float frametime)
{
    m_color.x += (m_color_target.x - m_color.x) * m_speed * frametime;
    m_color.y += (m_color_target.y - m_color.y) * m_speed * frametime;
    m_color.z += (m_color_target.z - m_color.z) * m_speed * frametime;
//    m_color.x = (m_color_target.x - m_color.x) * m_speed * frametime;
}
void LerpingColor::setTarget(sf::Vector3f target)
{
    m_color_target = target;
}
void LerpingColor::setTarget(sf::Color target)
{
    m_color_target = sf::Vector3f((float)target.r, (float)target.g, (float)target.b);
}
sf::Vector3f LerpingColor::getColorVector()
{
    return m_color;
}
sf::Color LerpingColor::getColor()
{
    return sf::Color((sf::Uint8)m_color.x, (sf::Uint8)m_color.y, (sf::Uint8)m_color.z);
}

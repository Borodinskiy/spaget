#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

//remove float point from vector by rounding.
//supported types: double, float
template <typename T>
sf::Vector2<T> roundVec(sf::Vector2<T> vector); //TODO Fix unkown link error and replace roundVector

sf::Vector2f roundVector(sf::Vector2f vector);

class LerpingColor
{
public:
    LerpingColor(sf::Vector3f color, sf::Vector3f target, float speed);
    LerpingColor(sf::Color color, sf::Color target, float speed);

    void update(float frametime);

    void setTarget(sf::Vector3f target);
    void setTarget(sf::Color target);

    sf::Vector3f getColorVector();
    sf::Color getColor();


private:
    sf::Vector3f m_color;
    sf::Vector3f m_color_target;    
    float m_speed;

};
#include "coordinate.hpp"
TransForm::TransForm(float l_x, float l_y, float l_w, float l_h)
    : a_x{0.f}, a_y{0.f}, a_w{1280.f}, a_h{720.f}
    , l_x{l_x}, l_y{l_y}, l_w{l_w}, l_h{l_h}
    , x{a_x + l_x}, y{a_y + l_y}, w{l_w}, h{l_h}
    , f_x{1.f}, f_y{1.f}, f_w{1.f}, f_h{1.f}
    , a_point{LEFT_TOP}
{
}

TransForm::~TransForm()
{
}

void TransForm::setupAlignmentByView(sf::View view)
{
    a_w = view.getSize().x;
    a_h = view.getSize().y;
    a_x = view.getCenter().x - a_w / 2.f;
    a_y = view.getCenter().y - a_h / 2.f;
}

void TransForm::setAlignmentPosition(sf::Vector2f position)
{
    a_x = position.x;
    a_y = position.y;
}

void TransForm::setAlignmentSize(sf::Vector2f size)
{
    a_w = size.x;
    a_h = size.y;
}

void TransForm::setAlignmentPoint(unsigned int point)
{
    a_point = point;
}

void TransForm::setPosition(sf::Vector2f position, bool withAlignment)
{
    l_x = position.x;
    l_y = position.y;

    if (withAlignment)
    {
        switch (a_point)
        {
        default:       x = l_x + a_x;                         y = l_y + a_y;                         break;
        case LEFT:     x = l_x + a_x;                         y = l_y + a_y + a_h / 2.f - l_h / 2.f; break;
        case LEFT_BOT: x = l_x + a_x;                         y = l_y + a_y + a_h - l_h;             break;
        case TOP:      x = l_x + a_x + a_w / 2.f - l_w / 2.f; y = l_y + a_y;                         break;
        case CENTER:   x = l_x + a_x + a_w / 2.f - l_w / 2.f; y = l_y + a_y + a_h / 2.f - l_h / 2.f; break;
        case BOT:      x = l_x + a_x + a_w / 2.f - l_w / 2.f; y = l_y + a_y + a_h - l_h;             break;
        case RIGHT_TOP:x = l_x + a_x + a_w - l_w;             y = l_y + a_y;                         break;
        case RIGHT:    x = l_x + a_x + a_w - l_w;             y = l_y + a_y + a_h / 2.f - l_h / 2.f; break;
        case RIGHT_BOT:x = l_x + a_x + a_w - l_w;             y = l_y + a_y + a_h - l_h;             break;
        };
    }
    else
    {
        x = l_x;
        y = l_y;
    }

    x *= f_x;
    y *= f_x;
}

void TransForm::setSize(sf::Vector2f size, bool withScaleFactor)
{
    l_w = size.x;
    l_h = size.y;
    if (withScaleFactor)
    {
        w = l_w * f_w;
        h = l_h * f_h;
    }
    else
    {
        w = l_w;
        h = l_h;
    }
}

void TransForm::setScale(sf::Vector2f scale)
{
//  f_x = scale.x;
//  f_y = scale.y;
    f_w = scale.x;
    f_h = scale.y;
}

sf::Vector2f TransForm::getAlignmentPosition()
{
    return { a_x, a_y };
}
sf::Vector2f TransForm::getAlignmentSize()
{
    return { a_w, a_h};
}
unsigned int TransForm::getAlignmentPoint()
{
    return a_point;
}

sf::Vector2f TransForm::getPosition() 
{ 
    return { x, y };
}
sf::Vector2f TransForm::getLocalPosition()
{
	return { l_x, l_y };
}

sf::Vector2f TransForm::getSize()
{
    return { w, h };
}

sf::FloatRect TransForm::getScale()
{
	return { f_x, f_y, f_w, f_h};
}

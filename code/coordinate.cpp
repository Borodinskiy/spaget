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
    refresh(POSITON);
}

void TransForm::setAlignmentBounds(sf::FloatRect bounds)
{
    a_x = bounds.left;
    a_y = bounds.top;
    a_w = bounds.width;
    a_h = bounds.height;
    refresh(POSITON);
}

void TransForm::setAlignmentPosition(sf::Vector2f position)
{
    a_x = position.x;
    a_y = position.y;
    refresh(POSITON);
}

void TransForm::setAlignmentSize(sf::Vector2f size)
{
    a_w = size.x;
    a_h = size.y;
    refresh(POSITON);
}

void TransForm::setAlignmentPoint(unsigned int point)
{
    a_point = point;
    refresh(POSITON);
}

void TransForm::setBounds(sf::FloatRect bounds)
{
    l_x = bounds.left;
    l_y = bounds.top;
    l_w = bounds.width;
    l_h = bounds.height;

    refresh(ALL);
}

void TransForm::setPosition(sf::Vector2f position)
{
    l_x = position.x;
    l_y = position.y;

    x = l_x * f_x;
    y = l_y * f_y;

    switch (a_point)
    {
    default:       x += a_x;                       y += a_y;                       break;
    case LEFT:     x += a_x;                       y += a_y + a_h / 2.f - h / 2.f; break;
    case LEFT_BOT: x += a_x;                       y += a_y + a_h - h;             break;
    case TOP:      x += a_x + a_w / 2.f - w / 2.f; y += a_y;                       break;
    case CENTER:   x += a_x + a_w / 2.f - w / 2.f; y += a_y + a_h / 2.f - h / 2.f; break;
    case BOT:      x += a_x + a_w / 2.f - w / 2.f; y += a_y + a_h - h;             break;
    case RIGHT_TOP:x += a_x + a_w - w;             y += a_y;                       break;
    case RIGHT:    x += a_x + a_w - w;             y += a_y + a_h / 2.f - h / 2.f; break;
    case RIGHT_BOT:x += a_x + a_w - w;             y += a_y + a_h - h;             break;
    };
}

void TransForm::setSize(sf::Vector2f size)
{
    l_w = size.x;
    l_h = size.y;

    w = l_w * f_w;
    h = l_h * f_h;

    refresh(POSITON);
}

void TransForm::setScale(sf::Vector2f scale)
{
    f_x = scale.x;
    f_y = scale.y;
    f_w = scale.x;
    f_h = scale.y;

    refresh();
}
void TransForm::setScale(float scale)
{
    setScale({scale, scale});
}

sf::FloatRect TransForm::getAlignmentBounds()
{
    return { a_x, a_y, a_w, a_h };
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

sf::FloatRect TransForm::getBounds()
{
    return { x, y, w, h };
}

sf::FloatRect TransForm::getLocalBounds()
{
    return { l_x, l_y, l_w, l_h };
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

sf::Vector2f TransForm::getLocalSize()
{
    return { l_w, l_h };
}

sf::FloatRect TransForm::getScale()
{
	return { f_x, f_y, f_w, f_h};
}

void TransForm::refresh(unsigned int type)
{
    switch (type)
    {
    case POSITON:
        setPosition(getLocalPosition());
        break;
    case SIZE:
    default:
        setSize(getLocalSize());
        break;
    };
}

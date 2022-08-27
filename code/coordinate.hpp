#pragma once
#include <SFML/Graphics/View.hpp>


namespace ALIGN
{
    enum
    {
        LEFT_TOP = 0,
        LEFT,
        LEFT_BOT,
        TOP,
        CENTER,
        BOT,
        RIGHT_TOP,
        RIGHT,
        RIGHT_BOT
    };
}

namespace REFRESH_TYPE
{
    enum
    {
        ALL = 0,
        POSITION,
        SIZE
    };
}

//Transformable form (aka Mr. Bons//(aka Bounds))
class TransForm
{
public:
    TransForm(float x = 0, float y = 0, float width = 0, float height = 0);
    ~TransForm();

    void setupAlignmentByView(sf::View view);

    void setAlignmentBounds(sf::FloatRect bounds);

    void setAlignmentPosition(sf::Vector2f position);

    void setAlignmentSize(sf::Vector2f size);

    void setAlignmentPoint(unsigned int point);

    void setBounds(sf::FloatRect bounds);

    void setPosition(sf::Vector2f position);

    void setSize(sf::Vector2f size);

    void setScale(sf::Vector2f scale);
    void setScale(float size);

    sf::FloatRect getAlignmentBounds();

    sf::Vector2f getAlignmentPosition();

    sf::Vector2f getAlignmentSize();

    unsigned int getAlignmentPoint();

    sf::FloatRect getBounds();
    
    sf::FloatRect getLocalBounds();

    sf::Vector2f getPosition();
    
    sf::Vector2f getLocalPosition();   
    
    sf::Vector2f getSize();

    sf::Vector2f getLocalSize();
    
    sf::FloatRect getScale();

protected:
    //Calls every time, when changing bounds. Use in child classes
    virtual void onRefreshBounds() = 0;
    //Calls every time, when changing bounds. Used by main class
    void refreshBounds(int refresh_type = REFRESH_TYPE::ALL);

protected:

    //alignment's rect bounds
    float a_x, a_y, a_w, a_h;
    //object local bounds
    float l_x, l_y, l_w, l_h;
    //object scale factor (example use: ui scale)
    float f_x, f_y, f_w, f_h;
    //object absolute bounds (position and size, rendered on screen (aka "a_x + l_x"//(aka sum))
    float x, y, w, h;
	//alignment's coordinate start (allowed vars written in enum "ALIGNMENT")
    unsigned int a_point;
};
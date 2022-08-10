#pragma once
#include <SFML/Graphics.hpp>

enum ALIGNMENT
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

//Transformable form (aka Mr. Bons//(aka Bounds))
class TransForm
{
public:
    TransForm(float l_x = 0, float l_y = 0, float l_w = 0, float l_h = 0);
    ~TransForm();

    void setupAlignmentByView(sf::View view);

    void setAlignmentPosition(sf::Vector2f position);

    void setAlignmentSize(sf::Vector2f size);

    void setAlignmentPoint(unsigned int point);

    void setPosition(sf::Vector2f position);

    void setSize(sf::Vector2f size);

    void setScale(float scale);

    sf::Vector2f getAlignmentPosition();

    sf::Vector2f getAlignmentSize();

    unsigned int getAlignmentPoint();

    sf::Vector2f getPosition();
    
    sf::Vector2f getLocalPosition();   
    
    sf::Vector2f getSize();

    sf::Vector2f getLocalSize();
    
    sf::FloatRect getScale();

protected:
    //Calls every time, when other transform's elements need to change (example: correct position, when size changes)
    virtual void refresh(unsigned int type = 0);

protected:
    enum REFRESH_TYPE
    {
        ALL = 0,
        POSITON,
        SIZE

    };

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
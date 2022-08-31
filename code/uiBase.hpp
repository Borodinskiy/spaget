#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "windowListener.hpp"
#include "coordinate.hpp"

#define UINAMESPACE ui

constexpr unsigned int stringHash(const char *string)
{
    unsigned int i = 0, hash = 0;
    for (; string[i] != '\0'; i++)
        hash += (unsigned int)string[i];

    return hash + i;
};

namespace UINAMESPACE
{
    class Animator
    {

    };

    struct Event
    {
        Event(const char *str);
        Event(unsigned int id = 0);

        unsigned int id;
    };
    typedef std::list<Event> EventsList;

    class EventsHandler
    {
    public:
        EventsHandler();
        ~EventsHandler();
        //Add new event to list. Can be handled by pollEvent method
        bool addEvent(Event event);
        //If have unreaded events, returns true and writing event info to "storage" variable
        bool pollEvent(Event& storage);
        //Return link to list of events
        EventsList& getEventsList();

    private:
        EventsList m_events;
    };
    //main class for any ui element
    class Widget : public TransForm, public sf::Drawable
    {
        public:
            Widget(sf::FloatRect bounds = {}, unsigned int align_point = ALIGN::LEFT_TOP, sf::FloatRect align_rect = {});

            virtual void update() = 0;

    };
    //Widget, but with event functions (from window and ui)
    class WidgetExecutable : public Widget
    {
    public:
        WidgetExecutable(Event event, WindowEvents& events, EventsHandler& handler
        , sf::FloatRect bounds = {}, unsigned int align_point = ALIGN::LEFT_TOP, sf::FloatRect align_rect = {});
        
        void update();
        void sendEvent();
        void disable();
        void enable();
        Event& getEvent();
    private:
        virtual void onUpdate() {}
        virtual void onHoverChange() {}
        virtual void onPressedChange(int button_index) {}
        virtual void onClick(int button_index) {}
        
        virtual void onDisable() {}
        virtual void onEnable() {}
    protected:        
        WindowEvents& m_events;
        EventsHandler& m_handler;
        Event m_event;
        bool m_enabled;
        // bounds contains a mouse?
        bool m_hovered;
        // bounds contains a mouse, and she is pressed?
        bool m_pressed;
    };
    typedef std::list<Widget*> WidgetsList;
    //storage for ui elements
    class Container : public TransForm, public sf::Drawable
    {
    public:
        Container(sf::FloatRect bounds = {}, unsigned int aling_point = ALIGN::LEFT_TOP, sf::FloatRect align_rect = {});
        ~Container();
        
        void update();
        
        void clear();
        void addWidget(Widget* widget);
        WidgetsList& getWidgetsList();
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        WidgetsList m_elements;
        sf::FloatRect m_alignment;
    };
};
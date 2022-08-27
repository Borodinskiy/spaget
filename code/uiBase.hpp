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
            Widget();

            virtual void update() = 0;

    };
    //Widget, but with event functions (from window and ui)
    class WidgetExecutable : public Widget
    {
        public:
            WidgetExecutable(WindowEvents& window_events = *default_window_events, EventsHandler& events_handler = *default_events_handler);
            void update();

            static void setDefaultWindowEventsLink(WindowEvents* window_events);
            static void setDefaultEventHandlerLink(EventsHandler* events_handler);

        private:
            virtual void onUpdate() {}
            virtual void onHoverChange() {}
            virtual void onPressedChange(int button_index) {}
            virtual void onClick(int button_index) {}

        protected:
            static WindowEvents* default_window_events;
            static EventsHandler* default_events_handler;
        
            WindowEvents& w_events;
            EventsHandler& e_handler;

            // bounds contains a mouse?
            bool m_hovered;
            // bounds contains a mouse, and she is pressed?
            bool m_pressed;
    };
    typedef std::list<Widget> WidgetsList;

    //storage for ui elements
    class Container
    {
        public:
            Container();
            ~Container();

        private:
    };
};
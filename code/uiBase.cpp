#include "uiBase.hpp"

using namespace UINAMESPACE;

WindowEvents* WidgetExecutable::default_window_events;
EventsHandler* WidgetExecutable::default_events_handler;

Event::Event(const char *str)
	: id{stringHash(str)}
{}
Event::Event(unsigned int id)
	: id{id}
{}

EventsHandler::EventsHandler()
{}
EventsHandler::~EventsHandler()
{}
bool EventsHandler::addEvent(Event event)
{
	m_events.push_back(event);
	return true;
}
bool EventsHandler::pollEvent(Event& storage)
{
	if (m_events.size() > 0)
	{
		storage = *(m_events.begin());
		m_events.pop_front();
		return true;
	}
	return false;
}
EventsList& EventsHandler::getEventsList()
{
	return m_events;
}

Widget::Widget()
	: TransForm()
{}

WidgetExecutable::WidgetExecutable(WindowEvents& window_events, EventsHandler& events_handler)
	: Widget()
	, w_events{window_events}
	, e_handler{events_handler}
	, m_hovered{}
	, m_pressed{}
{}
void WidgetExecutable::setDefaultWindowEventsLink(WindowEvents* window_events)
{
	default_window_events = window_events;
}
void WidgetExecutable::setDefaultEventHandlerLink(EventsHandler* events_handler)
{
	default_events_handler = events_handler;
}
void WidgetExecutable::update()
{
	if (m_hovered != getBounds().contains(w_events.mouse_position)) 
	{
		m_hovered = !m_hovered;
		if (m_pressed && !m_hovered)
			m_pressed = false;
		onHoverChange();
	}
	if (m_hovered && m_pressed != (m_hovered && w_events.mouse_pressed))
	{
		m_pressed = !m_pressed;
		onPressedChange(w_events.mouse_down_buttonindex);
	}
	if (m_hovered && w_events.mouse_up)
	{
		onClick(w_events.mouse_up_buttonindex);
	}
	onUpdate();
}
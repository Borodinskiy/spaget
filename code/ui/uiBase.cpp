#include "uiBase.hpp"

using namespace UINAMESPACE;

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

Widget::
	Widget(sf::FloatRect bounds, unsigned int align_point, sf::FloatRect align_rect)
	: TransForm(bounds, align_point, align_rect)
{}

WidgetExecutable::
	WidgetExecutable(Event event, WindowEvents &events, EventsHandler &handler
		, sf::FloatRect bounds, unsigned int align_point, sf::FloatRect align_rect)
	: Widget(bounds, align_point, align_rect)
	, m_events{events}
	, m_event{event}
	, m_handler{handler}
	, m_hovered{}
	, m_pressed{}
{
	onHoverChange();
}
void WidgetExecutable::update()
{
	if (m_hovered != getBounds().contains(m_events.mouse_position)) 
	{
		m_hovered = !m_hovered;
		if (m_pressed && !m_hovered)
			m_pressed = false;
		onHoverChange();
	}
	if (m_hovered && m_pressed != (m_hovered && m_events.mouse_pressed))
	{
		m_pressed = !m_pressed;
		onPressedChange(m_events.mouse_down_buttonindex);
	}
	if (m_hovered && m_events.mouse_up)
	{
		onClick(m_events.mouse_up_buttonindex);
	}
	onUpdate();
}
void WidgetExecutable::sendEvent()
{
	m_handler.addEvent(getEvent());
}
Event& WidgetExecutable::getEvent()
{
	return m_event;
}
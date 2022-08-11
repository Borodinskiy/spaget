#include "uiBase.hpp"

UIEvents::UIEvents()
{}
UIEvents::~UIEvents()
{}

bool UIEvents::receiveEvent(UIEvent event)
{
	events.push_back(event);
	return true;
}

bool UIEvents::pollEvent(UIEvent& storage)
{
	if (events.size() > 0)
	{
		storage = *(events.begin());
		events.pop_front();
		return true;
	}
	return false;
}

UI::UI(WindowEvents& window_events, UIEvents& ui_events,  sf::Vector2f position, sf::Vector2f size)
	: TransForm(position.x, position.y, size.x, size.y)
	, win_events{window_events}
	, ui_events{ui_events}
{
	refresh();
}

UI::~UI()
{}

void UI::refresh(unsigned int type)
{
	TransForm::refresh(type);

	updateElements();
}

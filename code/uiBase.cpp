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
	, w_events{window_events}
	, ui_events{ui_events}
{
	refresh();

	m_fone.setFillColor({120, 120, 120});
}

UI::~UI()
{}

void UI::updateElements()
{
	m_fone.setPosition(getPosition());
	m_fone.setSize(getSize());
}

void UI::refresh(unsigned int type)
{
	TransForm::refresh(type);

	updateElements();
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_fone, states);
}

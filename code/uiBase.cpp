#include "uiBase.hpp"

UI::UI(WindowEvents& window_events, sf::Vector2f position, sf::Vector2f size)
	: TransForm(position.x, position.y, size.x, size.y)
	, w_events{window_events}
{
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

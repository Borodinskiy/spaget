#include "container.hpp"

using namespace UINAMESPACE;

Container::Container(sf::FloatRect bounds, unsigned int aling_point, sf::FloatRect align_rect)
	: TransForm{bounds, aling_point, align_rect}
{}
Container::~Container()
{
	clear();
}
void Container::clear()
{
	for (auto element : m_elements)
		delete element;
	m_elements.clear();
}
void Container::update()
{
	for (auto element : m_elements)
		element->update();
}
void Container::addWidget(Widget* widget)
{
	m_elements.push_back(widget);
}
void Container::addWidget(Button widget)
{
    addWidget(new Button(widget));
}
WidgetsList& Container::getWidgetsList()
{
	return m_elements;
}
void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto element : m_elements)
		target.draw(*element, states);
}
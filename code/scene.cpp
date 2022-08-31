#include "scene.hpp"

using namespace GAMENAMESPACE;

Scene::Scene(sf::RenderWindow &window)
    : m_window{window}
    , m_listener{window}
{}

MainMenu::MainMenu(sf::RenderWindow &window)
    : Scene(window)
    , m_uihandler{}
    , m_uicontainer{}
    , m_text{"Current ui scale: 0, 0", m_font, 30U}
    , m_align_rect{{0.f, 0.f}, (sf::Vector2f)window.getSize()}
{
    m_font.loadFromFile("data/misans.ttf");
    startScreen();
}
void MainMenu::update()
{
    m_listener.handleEvents();
    m_uicontainer.update();

    ui::Event event;
    while (m_uihandler.pollEvent(event))
    {
        switch (event.id)
        {
        case stringHash("game.exit"):
            m_window.close();
            break;
        }
    }
    if (m_listener.getEventsList().win_resized)
        onWindowResize();
}
void MainMenu::startScreen()
{
    m_uicontainer.clear();
    m_uicontainer.addWidget(new ui::Button({"Exit", m_font, 34U}
        , "game.exit", m_listener.getEventsList(), m_uihandler
            , {0.f, 0.f, 256.f, 64.f}, ALIGN::CENTER, m_align_rect));
}
void MainMenu::onWindowResize()
{
    m_align_rect = { {0.f, 0.f}, (sf::Vector2f)m_window.getSize() };

    m_text.setString("Current scale: " + std::to_string(round((float)m_window.getSize().x / DEFAULT_VIEW_SIZE.x * 100.f) / 100.f) + ", " + std::to_string((float)m_window.getSize().y / DEFAULT_VIEW_SIZE.y));

    for (auto element : m_uicontainer.getWidgetsList())
    {
        element->setAlignmentBounds(m_align_rect);
        element->setScale({(float)m_window.getSize().x / DEFAULT_VIEW_SIZE.x, (float)m_window.getSize().y / DEFAULT_VIEW_SIZE.y});
    }
}
void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.clear();
    target.draw(m_uicontainer);

    target.draw(m_text);
}

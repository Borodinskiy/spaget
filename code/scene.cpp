#include "scene.hpp"

using namespace GAMENAMESPACE;

Scene::Scene(sf::RenderWindow &window)
    : m_window{window}
    , m_listener{window}
{}

MainMenu::MainMenu(sf::RenderWindow &window)
    : Scene(window)
    , m_uiscale{1.f, 1.f}
    , m_uihandler{}
    , m_uicontainer{}
    , m_text{"", m_font, 30U}
    , m_align_rect{{0.f, 0.f}, (sf::Vector2f)window.getSize()}
    , m_view_changing{}
{
    level.load("sonic");
    m_font.loadFromFile("data/misans.ttf");
    m_view = m_window.getView();
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
        case stringHash("ui.scale.up"):
            m_uiscale += {0.2f, 0.2f};
            onWindowResize();
            break;
        case stringHash("ui.scale.down"):
            m_uiscale -= {0.2f, 0.2f};
            onWindowResize();
            break;
        }
    }
    if (m_listener.getEventsList().mouse_pressed)
    {
        if (!m_view_changing)
        {
            m_mouse_position = (sf::Vector2f)m_listener.getEventsList().mouse_position_raw;
            m_view_center = m_view.getCenter();
            m_view_changing = true;
        }
        m_view.setCenter(m_view_center + sf::Vector2f
        (
            m_mouse_position.x - (float)m_listener.getEventsList().mouse_position_raw.x,
            m_mouse_position.y - (float)m_listener.getEventsList().mouse_position_raw.y
        ));
    }
    else
        m_view_changing = false;
    if (m_listener.getEventsList().win_resized)
    {
        m_uiscale = {(float)m_window.getSize().x / DEFAULT_VIEW_SIZE.x, (float)m_window.getSize().y / DEFAULT_VIEW_SIZE.y};
        onWindowResize();
    }
}
void MainMenu::startScreen()
{
    m_uicontainer.clear();

    WindowEvents& evs = m_listener.getEventsList();

    m_uicontainer.addWidget({{"Start", m_font}
        , "game.saves", evs, m_uihandler
            , {0.f, -70.f, 256.f, 64.f}, ALIGN::CENTER, m_align_rect});

    m_uicontainer.addWidget({{"Settings", m_font}
        , "game.settings", evs, m_uihandler
            , {0.f, 0.f, 256.f, 64.f}, ALIGN::CENTER, m_align_rect});

    m_uicontainer.addWidget({{"Exit", m_font}
        , "game.exit", evs, m_uihandler
            , {0.f, 70.f, 256.f, 64.f}, ALIGN::CENTER, m_align_rect});

    m_uicontainer.addWidget({{"-", m_font}
        , "ui.scale.down", evs, m_uihandler
            , {0.f, 0.f, 64.f, 64.f}, ALIGN::LEFT_TOP, m_align_rect});

    m_uicontainer.addWidget({{"+", m_font}
        , "ui.scale.up", evs, m_uihandler
            , {0.f, 0.f, 64.f, 64.f}, ALIGN::RIGHT_TOP, m_align_rect});


}
void MainMenu::onWindowResize()
{
    m_view.setSize((sf::Vector2f)m_window.getSize());
    m_align_rect = { {0.f, 0.f}, (sf::Vector2f)m_window.getSize() };

    m_text.setString("Current scale: " + std::to_string(m_uiscale.x) + ", " + std::to_string(m_uiscale.y));

    for (auto element : m_uicontainer.getWidgetsList())
    {
        element->setAlignmentBounds(m_align_rect);
        element->setScale(m_uiscale);
    }
}
void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.clear({120, 120, 120});
    target.setView(m_view);
    target.draw(level);
    target.setView(target.getDefaultView());
    target.draw(m_uicontainer);

    target.draw(m_text);
}

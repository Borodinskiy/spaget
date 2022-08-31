#include "scene.hpp"

int main()
{
#ifdef _DEBUG
    printf("This is a debug version. Recommended to use release (without _debug in filename)\n\n");
#endif
    sf::RenderWindow window;
    sf::Image icon;

    icon.loadFromFile("data/icon.png");
    window.create(sf::VideoMode(DEFAULT_VIEW_SIZE.x, DEFAULT_VIEW_SIZE.y), "Spaget", sf::Style::Default);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);
//    window.setFramerateLimit(60);

    game::Scene* scene = new game::MainMenu(window);
    
    do
    {
        scene->update();
        window.draw(*scene);
        window.display();
    }
    while (window.isOpen());

    delete scene;

#ifdef _DEBUG
    printf("This is a final wrotten message before return zero\n\n");
#endif
    return EXIT_SUCCESS;
}
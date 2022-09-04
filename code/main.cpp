#include "scene.hpp"

int main()
{
#ifdef _DEBUG
    printf("This is a debug version. Recommended to use release (without _debug in filename)\n\n");
#endif

    sf::RenderWindow window;
    sf::Image icon;
    if (!icon.loadFromFile("data/icon.png"))
    {
        return EXIT_FAILURE;
    }

    sf::VideoMode videomode;
    sf::Uint32 style;
    sf::String title;
#ifdef _DEBUG
    videomode = {(unsigned int)DEFAULT_VIEW_SIZE.x, (unsigned int)DEFAULT_VIEW_SIZE.y};
    style = sf::Style::Default;
    title = "Spaget debug";
#else
    videomode = videomode.getDesktopMode();
    style = sf::Style::Fullscreen;
    title = "Spaget";
#endif
    window.create(videomode, title, style);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    game::Scene* scene = new game::MainMenu(window);
    
    do
    {
        scene->update();
        window.draw(*scene);
        window.display();
    }
    while (window.isOpen());

    delete scene;
    return EXIT_SUCCESS;
}
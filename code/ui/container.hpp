#include "uiBase.hpp"
#include "button.hpp"

namespace UINAMESPACE
{
    using namespace UINAMESPACE;
    class Container : public TransForm, public sf::Drawable
    {
    public:
        Container(sf::FloatRect bounds = {}, unsigned int aling_point = ALIGN::LEFT_TOP, sf::FloatRect align_rect = {});
        ~Container();

        void update();

        void clear();

        void addWidget(Widget* widget);
        void addWidget(Button widget);

        WidgetsList &getWidgetsList();

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        WidgetsList m_elements;
        sf::FloatRect m_alignment;
    };
}
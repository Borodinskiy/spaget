#include "level.hpp"

using namespace GAMENAMESPACE;
using namespace pugi;

const char* levelfolder = "data/level/";
const char* mainxmlname = "/main.tmx";

Tilesets::Tilesets()
{}
std::list<Tileset> &Tilesets::getList()
{
    return m_list;
}
bool Tilesets::add(xml_node& tileset, const char* levelname)
{
    Tileset res
    {
        tileset.attribute("firstgid").as_uint(),
        tileset.attribute("tilewidth").as_float(),
        tileset.attribute("tileheight").as_float(),
        tileset.attribute("tilecount").as_uint(),
        tileset.attribute("columns").as_uint(),
    };
    std::string 
        file = levelfolder;
    file += levelname;
    file += '/';
    file += tileset.child("image").attribute("source").as_string();
    if (!res.texture.loadFromFile(file))
    {
        printf
        (
            "\\-Failed to add tileset \"%s\" from level \"%s\"\n",
            tileset.attribute("name").as_string(),
            levelname
        );
        return false;
    }
    m_list.push_back(res);

    return true;
}
Tileset& Tilesets::get(unsigned int index)
{
    int i{};
    for (auto it = m_list.begin(); it != m_list.end(); it++, i++)
    {
        if (i == index)
            return *it;
    }
    return *m_list.begin();
}
Tile Tilesets::getTile(unsigned int index)
{
    int textureindex{};
    for (auto it = m_list.begin(); it != m_list.end(); it++, textureindex++)
    {
        if (!(it->firstgid <= index && index < (it->firstgid + it->tilecount)))
            continue;
        index -= it->firstgid;
        unsigned int 
            t_x{index % it->columns},
            t_y{(unsigned int)(index / it->columns)};

        Tile tile
        {
            &it->texture,
            textureindex,
            sf::FloatRect
            (
                (float)t_x * it->tilewidth,
                (float)t_y * it->tileheight,
                it->tilewidth,
                it->tileheight
            )
        };
        return tile;
    }
    return 
    {
        &m_list.begin()->texture,
        0U,
        sf::FloatRect
        (
            0.f, 0.f,
            (float)m_list.begin()->tilewidth,
            (float)m_list.begin()->tileheight
        )
    };
}
void vectorRect(std::vector<sf::Vertex>& vector, size_t s_index, sf::FloatRect bounds, sf::FloatRect texrect)
{
    vector[s_index    ] = {{bounds.left, bounds.top},                                {texrect.left, texrect.top}};
    vector[s_index + 1] = {{bounds.left + bounds.width, bounds.top},                 {texrect.left + texrect.width, texrect.top}};
    vector[s_index + 2] = {{bounds.left, bounds.top + bounds.height},                {texrect.left, texrect.top + texrect.height}};
    vector[s_index + 3] = {{bounds.left + bounds.width, bounds.top},                 {texrect.left + texrect.width, texrect.top}};
    vector[s_index + 4] = {{bounds.left + bounds.width, bounds.top + bounds.height}, {texrect.left + texrect.width, texrect.top + texrect.height}};
    vector[s_index + 5] = {{bounds.left, bounds.top + bounds.height},                {texrect.left, texrect.top + texrect.height}};

}
Chunk::Chunk(sf::FloatRect tiled_bounds, std::string data, Tilesets &tilesets)
    : m_tilesets{tilesets}
{
    while (data.find('\n') != -1)
        data.replace(data.find('\n'), 1, "");

    /// @param t_x x position
    /// @param t_y y position
    /// @param s_i string char index
    float t_x{}, t_y{}, s_i{};
    for (t_y = 0; t_y < tiled_bounds.height && s_i < data.size(); t_y++)
    {
        std::string buff{};
        for (t_x = 0; t_x < tiled_bounds.width && s_i < data.size(); s_i++)
        {
            if (data[s_i] != ',')
                buff += data[s_i];
            else
            {
                if (buff == "0")
                {
                    buff = {};
                    t_x++;
                    continue;
                }
                Tile tile = m_tilesets.getTile(std::atoi(buff.c_str()));

                while (m_vertexes.size() <= tile.textureindex)
                    m_vertexes.push_back({});
                auto vector = m_vertexes.begin();
                for (int i = 0; vector != m_vertexes.end() && i < tile.textureindex; i++, vector++);
                vector->resize(vector->size() + 6);
                
                Tileset& tileset = m_tilesets.get(tile.textureindex);

                vectorRect
                (
                    *vector, vector->size() - 6,
                    {
                        (tiled_bounds.left + t_x) * tileset.tilewidth, (tiled_bounds.top + t_y) * tileset.tileheight,
                        tileset.tilewidth, tileset.tileheight
                    },
                    tile.rect
                );

                buff = {};
                t_x++;
            }
        }
    }
}
void Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    auto tileset  = m_tilesets.getList().begin();
    auto vertexes = m_vertexes.begin();
    sf::VertexArray arr;
    for (; vertexes != m_vertexes.end(); vertexes++, tileset++)
        target.draw
        (
            &*(vertexes->begin()),
            vertexes->size(),
            sf::Triangles,
            &tileset->texture
        );
}
Level::Level()
{}
bool Level::load(const char* levelname)
{
    std::string filepath = levelfolder;
    filepath += levelname;
    filepath += mainxmlname;
    
    xml_document file;
    xml_parse_result loadresult = file.load_file(filepath.c_str());
    if (loadresult.status != xml_parse_status::status_ok)
    {
        printf("XML Level \"%s\" load error: %s\n", levelname, loadresult.description());
        return false;
    }
    
    xml_node root = file.first_child();
    if (!root.attribute("infinite").as_bool())
    {
        printf("XML Level \"%s\" cannot be loaded, because it's not infinite\n", levelname);
        return false;
    }

    for (auto tileset = root.child("tileset")
            ; tileset != nullptr
            ; tileset = tileset.next_sibling("tileset"))
        m_tilesets.add(tileset, levelname); 

    for (auto layer = root.child("layer")
            ; layer != nullptr
            ; layer = layer.next_sibling("layer"))
        for (auto chunk = layer.child("data").child("chunk")
                ; chunk != nullptr
                ; chunk = chunk.next_sibling("chunk"))
        {
            float 
                x = chunk.attribute("x").as_float(),
                y = chunk.attribute("y").as_float(),
                w = chunk.attribute("width").as_float(),
                h = chunk.attribute("height").as_float();
            m_chunks.push_back({{x, y, w, h}, chunk.text().as_string(), m_tilesets});
        }

    return true;
}
void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto chunk : m_chunks)
        target.draw(chunk, states);
}
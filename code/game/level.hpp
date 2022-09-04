#pragma once
#include <SFML/Graphics.hpp>
#include "xml/pugixml.hpp"
#include <list>
#define GAMENAMESPACE game

namespace GAMENAMESPACE
{
    /// @brief Texture Tile from map. Contains position and size on TEXTURE
    struct Tile
    {
        sf::Texture* texture; // Pointer to tileset's, where tile located
        int textureindex;     // Index of texture (from class Tilesets)
        sf::FloatRect rect;   // Tile position and size on texture (use in vertexes)
    };
    /// @brief Tileset from xml map. Contains texture and tileinformation
    ///
    struct Tileset
    {
        unsigned int firstgid;              // First tile index
        float        tilewidth, tileheight; // Tile size
        unsigned int tilecount;             // Count of tiles
        unsigned int columns;               // Tileset's texture's width divided on tile's width
        sf::Texture texture;
    };

    class Tilesets
    {
    public:
        Tilesets();
        /// @brief Get List of all tilesets in map
        /// @return Tilesets list
        std::list<Tileset>& getList();
        /// @brief Add tileset from example_map.tmx
        /// @param tileset 
        /// @param levelname name of level (default located in )
        /// @return true, if tileset loaded, else - false
        bool add(pugi::xml_node& tileset, const char* levelname);
        /// @brief Return tileset by index.
        /// @param index number of tileset. Starts from 0 
        /// @return Tileset by index. If index higher, than count of tilesets,
        /// return first tileset
        Tileset& get(unsigned int index = 0);
        /// @brief Allow to get tile from csv map
        /// @param index tile number (can be viewed in .tmx map)
        /// @return Tile, which contains pointer to texture,
        /// her's index and tile's IntRect (location on texture).
        /// If index higher, than count of tiles, returns first tile
        Tile getTile(unsigned int index = 0);

    private:        

        std::list<Tileset> m_list;
    };
    class Chunk : public sf::Drawable
    {
    public:
        /// @brief Create chunk
        /// @param tiled_bounds x, y - position (in tiles); w, h - size (in tiles)
        /// @param data csv coded tile position from xml's chunk
        /// @param tilesets list of tilesets (for rendering)
        Chunk(sf::FloatRect tiled_bounds, std::string data, Tilesets& tilesets);
        
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        Tilesets& m_tilesets;
        std::list<std::vector<sf::Vertex>> m_vertexes;
    };
    typedef std::list<Chunk> Chunks;

    class Level : public sf::Drawable
    {
    public:
        Level();

        bool load(const char* name);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        Tilesets m_tilesets;
        Chunks m_chunks;

    };
};
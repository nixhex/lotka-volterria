#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <string_view>
#include <optional>

class AssetManager
{
public:
    // TEXTURE METHODS //
    const sf::Texture& requireTexture(std::string_view key, std::string_view path)
    {
        // this function tries to obtain a texture from the asset manager, and if it can't be found,
        // it must be grabbed from a file at path -- caching (get or use)
        if(auto it = textures_.find(key); it != textures_.end()) 
            return it->second; // ->second = value
        sf::Texture t;

        if(!t.loadFromFile(std::string(path))) // tries to load from file AND confirms it in one statement
            throw std::runtime_error("Texture load error: " + std::string(path)); // texture not found probably
        return textures_.emplace(key, std::move(t)).first->second;
    }

    const sf::Texture& requireTextMem(std::string_view key, const void* data, std::size_t size)
    {
        // this function tries to obtain a texture from the asset manager, and if it can't be found,
        // it must be grabbed from memory (like a sprite map) -- caching (get or use)
        if(auto it = textures_.find(key); it != textures_.end()) 
            return it->second; // ->second = value
        sf::Texture t;

        if(!t.loadFromMemory(data, size)) 
            throw std::runtime_error("Texture mem error: " + std::string(key));
        return textures_.emplace(key, std::move(t)).first->second;
    }

    const sf::Texture& getTexture(std::string_view key) const {
        // less strict than previous functions, just search by key
        return textures_.at(std::string(key));
    }

    bool hasTexture(std::string_view key)
    {
        // is the texture in the asset manager?
        return textures_.find(std::string(key)) != textures_.end();
    }

    // FONTS //

    // AUDIO //

    // HELPERS //

    sf::Sprite makeSprite(std::string_view textureKey, sf::IntRect rect) const {
        sf::Sprite s(getTexture(textureKey));
        s.setTextureRect(rect);
        return s;
    }

private:
    std::unordered_map<std::string_view, sf::Texture> textures_;
    std::unordered_map<std::string_view, sf::Font> fonts_;
};
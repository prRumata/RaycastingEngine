#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class Map
{
private:
	std::vector<std::vector<unsigned char>> m_map;


public:
	Map();
	sf::Color getColor(size_t x, size_t y) const;
	const std::vector<std::vector<unsigned char>> & getMap() const;
};

#pragma once

#include <SFML/System.hpp>
#include <cmath>

#include "Constants.hpp"
#include "Map.hpp"

class Player
{
private:
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	sf::Vector2f m_plane;
	Map& m_map;
public:
	Player(Map& map);

	void move(sf::Vector2f moving);
	void rotate(float rotation);

	sf::Vector2f getPosition() const;
	sf::Vector2f getDirection() const;
	sf::Vector2f getPlane() const;
};

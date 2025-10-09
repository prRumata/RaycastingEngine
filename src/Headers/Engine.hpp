#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Input.hpp"
#include "Render.hpp"


class Engine
{
private:
	sf::RenderWindow m_window;

	sf::Clock m_delta_clock;
	sf::Time m_delta_time;

	Map m_map;
	Player m_player;
	Input m_input;
	Render m_render;

	//void loadTextures();
public:
	Engine();
	void start();
};

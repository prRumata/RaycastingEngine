#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Ray.hpp"

class Render
{
private:
	Player& m_player;
	sf::RenderWindow& m_window;
	Map& m_map;
	sf::VertexBuffer m_buffer;
	// sf::Vertex * m_pixels;

	// sf::VertexArray m_lines;

	sf::Text m_fps_text;
	sf::Font m_font;
	sf::Clock m_fps_clock;
	sf::Clock m_fps_update_clock;
	float m_fps;

	Ray m_rays[SCREEN_WIDTH];

	void updateRays();
	void renderUI();
public:
	Render(Player& player, sf::RenderWindow& window, Map& map);
	~Render();
	void render();
};

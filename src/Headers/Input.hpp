#pragma once

#include <unordered_map>
#include <string>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Constants.hpp"

class Input
{
private:
	sf::RenderWindow& m_window;
	sf::Time m_delta_time;
	Player& m_player;

	std::unordered_map<std::string, bool> m_key_is_pressed;

	void keysCheck();
	void move_player();
	void rotate_player();
public:
	Input(Player& player, sf::RenderWindow& window);
	void input(sf::Time delta);
};

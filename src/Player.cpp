#include "Headers/Player.hpp"

Player::Player(Map& map) :
	m_position(sf::Vector2f(SIZE_X * 0.49f, SIZE_Y * 0.49f)),
	m_direction(sf::Vector2f(0.0f, -1.0f)),
	m_plane(sf::Vector2f(0.66f, 0.0f)),
	m_map(map)
{
}

void Player::move(sf::Vector2f moving)
{
	// Знак передвижения
	sf::Vector2<signed char> sign
	{
		moving.x >= 0.0f ? (signed char)1 : (signed char)-1,
		moving.y >= 0.0f ? (signed char)1 : (signed char)-1
	};
	
	// Передвижение по вертикали
	m_position.x += moving.x * PLAYER_MOVING_SPEED + PLAYER_SIZE * sign.x;

	// Проверка на выход за пределы карты
	if (m_map.getMap()[(size_t)m_position.x][(size_t)m_position.y])
	{
		m_position.x = moving.x >= 0.0f ?
			(size_t)m_position.x - 0.0f :
			(size_t)m_position.x + 1.0f;
	}

	m_position.x -= PLAYER_SIZE * sign.x;

	// Передвижение по горизонтали
	m_position.y += moving.y * PLAYER_MOVING_SPEED + PLAYER_SIZE * sign.y;

	// Проверка на выход за пределы карты
	if (m_map.getMap()[(size_t)m_position.x][(size_t)m_position.y])
	{
		m_position.y = moving.y >= 0.0f ?
			(size_t)m_position.y - 0.0f :
			(size_t)m_position.y + 1.0f;
	}

	m_position.y -= PLAYER_SIZE * sign.y;
}

void Player::rotate(float rotation)
{
	rotation *= PLAYER_ROTATION_SPEED;

	float old_direction_x = m_direction.x;
	m_direction.x = m_direction.x * cos(rotation) - m_direction.y * sin(rotation);
	m_direction.y = old_direction_x * sin(rotation) + m_direction.y * cos(rotation);

	float old_plane_x = m_plane.x;
	m_plane.x = m_plane.x * cos(rotation) - m_plane.y * sin(rotation);
	m_plane.y = old_plane_x * sin(rotation) + m_plane.y * cos(rotation);
}

sf::Vector2f Player::getPosition() const
{
	return m_position;
}

sf::Vector2f Player::getDirection() const
{
	return m_direction;
}

sf::Vector2f Player::getPlane() const
{
	return m_plane;
}

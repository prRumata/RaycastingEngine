#include "Headers/Engine.hpp"


Engine::Engine() :
    m_window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Raycasting"),
    m_input(m_player, m_window),
    m_render(m_player, m_window, m_map),
    m_player(m_map)
{
    // m_window.setFramerateLimit(60);
}

void Engine::start()
{
    while (m_window.isOpen())
    {
        m_input.input(m_delta_time);
        m_render.render();

        m_delta_time = m_delta_clock.restart();
    }
}

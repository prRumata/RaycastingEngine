#include "Headers/Input.hpp"

void Input::keysCheck()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        // Закрыть
        case sf::Event::Closed:
            m_window.close();
            break;

        // Проверка на нажатия клавиш
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                m_key_is_pressed["W"] = true;
                break;

            case sf::Keyboard::A:
                m_key_is_pressed["A"] = true;
                break;

            case sf::Keyboard::S:
                m_key_is_pressed["S"] = true;
                break;

            case sf::Keyboard::D:
                m_key_is_pressed["D"] = true;
                break;

            case sf::Keyboard::Q:
                m_key_is_pressed["Q"] = true;
                break;

            case sf::Keyboard::E:
                m_key_is_pressed["E"] = true;
                break;
            
            default:
                break;
            }
            break;

        // Проверка на отпускание клавиш
        case sf::Event::KeyReleased:

            switch (event.key.code)
            {
            case sf::Keyboard::W:
                m_key_is_pressed["W"] = false;
                break;

            case sf::Keyboard::A:
                m_key_is_pressed["A"] = false;
                break;

            case sf::Keyboard::S:
                m_key_is_pressed["S"] = false;
                break;

            case sf::Keyboard::D:
                m_key_is_pressed["D"] = false;
                break;

            case sf::Keyboard::Q:
                m_key_is_pressed["Q"] = false;
                break;

            case sf::Keyboard::E:
                m_key_is_pressed["E"] = false;
                break;
            
            default:
                break;
            }
            
        default:
            break;
        }
    }
}

void Input::move_player()
{
    // Вектор изменения местоположения игрока относительно текущего
    sf::Vector2f velocity;

    if (m_key_is_pressed["W"])
    {
        velocity.x += m_player.getDirection().x;
        velocity.y += m_player.getDirection().y;
    }
    if (m_key_is_pressed["A"])
    {
        velocity.x += m_player.getDirection().y;
        velocity.y -= m_player.getDirection().x;
    }
    if (m_key_is_pressed["S"])
    {
        velocity.x -= m_player.getDirection().x;
        velocity.y -= m_player.getDirection().y;
    }
    if (m_key_is_pressed["D"])
    {
        velocity.x -= m_player.getDirection().y;
        velocity.y += m_player.getDirection().x;
    }
    if (velocity.x == 0 && velocity.y == 0)
    {
        return;
    }

    // Приведение к единичному вектору
    velocity = velocity / (float)sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    m_player.move(velocity * float(m_delta_time.asSeconds()));
}

void Input::rotate_player()
{
    if ((m_key_is_pressed["E"] - m_key_is_pressed["Q"]))
    {
        m_player.rotate((float)(m_key_is_pressed["E"] - m_key_is_pressed["Q"]) *
                        (float)m_delta_time.asSeconds());
    }
}

Input::Input(Player& player, sf::RenderWindow& window) :
    m_player(player),
    m_window(window),
    m_key_is_pressed
    {
        { "W", false },
        { "A", false },
        { "S", false },
        { "D", false },
        { "Q", false },
        { "E", false }
    }
{
}

void Input::input(sf::Time delta)
{
    m_delta_time = delta;
    keysCheck();
    move_player();
    rotate_player();
}

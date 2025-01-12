#include "Headers/Render.hpp"


void Render::updateRays()
{
    for (unsigned int i = 0; i < SCREEN_WIDTH; i++)
    {
        // рассчитывание положение и направление луча

        // координата x в пространстве камеры
        float camera_x = 2.0f * i / float(SCREEN_WIDTH) - 1.0f;
        // направление луча
        sf::Vector2f ray_direction
        (m_player.getDirection().x + m_player.getPlane().x * camera_x,
            m_player.getDirection().y + m_player.getPlane().y * camera_x);



        // в какой клетке сейчас находится игрок
        sf::Vector2i cell((int)m_player.getPosition().x, (int)m_player.getPosition().y);

        // длина луча из текущей позиции до следующей стороны клетки
        sf::Vector2f side_distance;

        // длина луча с одной стороны клетки до следующей стороны клетки
        sf::Vector2f delta_distance(
            (ray_direction.x == 0.0f) ? 1e30f : std::abs(1.0f / ray_direction.x),
            (ray_direction.y == 0.0f) ? 1e30f : std::abs(1.0f / ray_direction.y));
        float perp_wall_dist;

        // в каком направлении делать шаг по оси x или y (+1 или -1)
        sf::Vector2<char> step;

        bool hit = false; // было ли касание со стеной
        char side = 0; // x-сторона - 0, y-сторона - 1



        // вычисление step и начального side_distance
        if (ray_direction.x < 0.0f)
        {
            step.x = -1;
            side_distance.x = (m_player.getPosition().x - cell.x) * delta_distance.x;
        }
        else
        {
            step.x = 1;
            side_distance.x = (cell.x + 1.0f - m_player.getPosition().x) * delta_distance.x;
        }
        if (ray_direction.y < 0.0f)
        {
            step.y = -1;
            side_distance.y = (m_player.getPosition().y - cell.y) * delta_distance.y;
        }
        else
        {
            step.y = 1;
            side_distance.y = (cell.y + 1.0f - m_player.getPosition().y) * delta_distance.y;
        }



        // выполнение алгоритма DDA
        while (!hit)
        {
            // перейти к следующей клетке либо в x-направлении, либо в y-направлении
            if (side_distance.x < side_distance.y)
            {
                side_distance.x += delta_distance.x;
                cell.x += step.x;
                side = 0;
            }
            else
            {
                side_distance.y += delta_distance.y;
                cell.y += step.y;
                side = 1;
            }

            // Проверка на касание со стеной
            if (m_map.getMap()[cell.x][cell.y] != 0)
            {
                hit = true;
            }
        }



        if (side == 0)
        {
            perp_wall_dist = (side_distance.x - delta_distance.x);
        }
        else
        {
            perp_wall_dist = (side_distance.y - delta_distance.y);
        }

        m_rays[i].setLength(perp_wall_dist);
    }
}

Render::Render(Player& player, sf::RenderWindow& window, Map& map) :
    m_player(player),
    m_window(window),
    m_map(map),
    m_rays(),
    m_lines(sf::Lines, SCREEN_WIDTH * 2),
    m_buffer(sf::Lines),
    // m_pixels(new sf::Vertex[SCREEN_HEIGHT * SCREEN_WIDTH]),
    m_fps(0.0f)
    
{
    m_buffer.create(size_t(SCREEN_WIDTH));

    // for (size_t x = 0; x < SCREEN_WIDTH; ++x)
    // {
    //     for (size_t y = 0; y < SCREEN_HEIGHT; ++y)
    //     {
    //         m_pixels[x * SCREEN_HEIGHT + y].position = sf::Vector2f((float)x, (float)y);
    //     }
    // }
    m_font.setSmooth(false);
    m_font.loadFromFile("res/font.otf");
    m_fps_text = sf::Text(std::to_string(m_fps), m_font, 18);
    m_fps_text.setPosition(10, 10);
}

Render::~Render()
{
    // delete[] m_pixels;
}

void Render::render()
{
    updateRays();
    
    m_window.clear(sf::Color(0x282828FF));

    /*####################*/
    /*#      Pixels      #*/
    /*####################*/

    // for (size_t x = 0; x < SCREEN_WIDTH; ++x)
    // {
    //     float wall_coord_top = (SCREEN_HEIGHT / 2.0f) -
    //         SCREEN_WIDTH / m_rays[x].getLength() / 4.0f / 0.66f;

    //     float wall_coord_low = (SCREEN_HEIGHT / 2.0f) +
    //         SCREEN_WIDTH / m_rays[x].getLength() / 4.0f / 0.66f;

    //     sf::Color wall_color =
    //     {
    //         sf::Uint8(0xa8 / (m_rays[x].getLength() / 15.0f + 1.0f)),
    //         sf::Uint8(0x99 / (m_rays[x].getLength() / 15.0f + 1.0f)),
    //         sf::Uint8(0x84 / (m_rays[x].getLength() / 15.0f + 1.0f)),
    //         sf::Uint8(0xFF / (m_rays[x].getLength() / 15.0f + 1.0f))
    //     };

    //     for (size_t y = 0; y < SCREEN_HEIGHT; ++y)
    //     {
    //        if (wall_coord_top <= y && wall_coord_low >= y)
    //        {
    //            m_pixels[x * SCREEN_HEIGHT + y].color = wall_color;
    //        }
    //        else
    //        {
    //            m_pixels[x * SCREEN_HEIGHT + y].color = sf::Color(0x282828FF);
    //        }
    //     }
    // }
    // m_buffer.update(m_pixels);

    // m_window.draw(m_buffer);

    /*###################*/
    /*#      Lines      #*/
    /*###################*/

    for (size_t x = 0; x < SCREEN_WIDTH; ++x)
    {
        sf::Color wall_color =
        {
            sf::Uint8(0xa8 / (m_rays[x].getLength() / 15.0f + 1.0f)),
            sf::Uint8(0x99 / (m_rays[x].getLength() / 15.0f + 1.0f)),
            sf::Uint8(0x84 / (m_rays[x].getLength() / 15.0f + 1.0f)),
            sf::Uint8(0xFF / (m_rays[x].getLength() / 15.0f + 1.0f))
        };

        m_lines[x * 2].position = sf::Vector2f(x, (SCREEN_HEIGHT / 2.0f) -
            SCREEN_WIDTH / m_rays[x].getLength() / 4.0f / 0.66f);
        m_lines[x * 2 + 1].position = sf::Vector2f(x, (SCREEN_HEIGHT / 2.0f) +
            SCREEN_WIDTH / m_rays[x].getLength() / 4.0f / 0.66f);
        m_lines[x * 2].color = wall_color;
        m_lines[x * 2 + 1].color = wall_color;
    }
    m_window.draw(m_lines);

    renderUI();
    m_window.display();
}

void Render::renderUI()
{
    if (m_fps_update_clock.getElapsedTime().asSeconds() > 0.5f) {
        m_fps = 1.0f / m_fps_clock.restart().asSeconds();
        m_fps_text.setString(std::to_string((int)(m_fps)));
        m_fps_update_clock.restart();
    }
    m_window.draw(m_fps_text);
    m_fps_clock.restart();
}
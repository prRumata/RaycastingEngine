#include "Headers/Ray.hpp"

Ray::Ray() :
    m_length(0.0f),
    m_wall(0)
{
}

void Ray::setLength(float length)
{
    m_length = length;
}

void Ray::setWall(unsigned char wall)
{
    m_wall = wall;
}

float Ray::getLength() const
{
    return m_length;
}

unsigned char Ray::getWall() const
{
    return m_wall;
}

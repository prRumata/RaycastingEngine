#pragma once
class Ray
{
private:
	float m_length;
	unsigned char m_wall;
public:
	Ray();

	void setLength(float length);
	void setWall(unsigned char wall);

	float getLength() const;
	unsigned char getWall() const;
};


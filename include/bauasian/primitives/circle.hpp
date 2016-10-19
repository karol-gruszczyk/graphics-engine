#ifndef BAUASIAN_CIRCLE_HPP
#define BAUASIAN_CIRCLE_HPP

#include "abstract/entity_2d.hpp"


namespace bauasian
{
	class Circle;
}

class bauasian::Circle
		: public Entity2D
{
public:
	Circle(const float& radius, const unsigned short& num_sides = 32);

	const float& getRadius() const;

private:
	float m_radius;

};


#endif /* BAUASIAN_CIRCLE_HPP */

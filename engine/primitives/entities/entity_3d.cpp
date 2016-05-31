#include "entity_3d.h"

using engine::Entity3D;


Entity3D::Entity3D(glm::vec3 position, glm::vec3 rotation /* = { 0.f, 0.f, 0.f } */,glm::vec3 scale /* = { 1.f, 1.f, 1.f } */, 
	glm::vec3 pivot /* = { 0.f, 0.f, 0.f } */)
	: m_position(position), m_rotation(rotation), m_scale(scale), m_pivot(pivot)
{}

Entity3D::~Entity3D()
{}

void Entity3D::setPosition(glm::vec3 position)
{
	m_position = position;
}

glm::vec3 Entity3D::getPosition()
{
	return m_position;
}

void Entity3D::translate(glm::vec3 position)
{
	setPosition(m_position + position);
}

void Entity3D::setRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
}

glm::vec3 Entity3D::getRotation()
{
	return m_rotation;
}

void Entity3D::rotate(glm::vec3 rotation)
{
	setRotation(m_rotation + rotation);
}

void Entity3D::setScale(glm::vec3 scale)
{
	m_scale = scale;
}

glm::vec3 Entity3D::getScale()
{
	return m_scale;
}

void Entity3D::setPivot(glm::vec3 pivot)
{
	m_pivot = pivot;
}

glm::vec3 Entity3D::getPivot()
{
	return m_pivot;
}

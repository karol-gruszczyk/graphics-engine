#include "entity_3d.h"

using engine::Entity3D;


Entity3D::~Entity3D()
{}

void Entity3D::setPosition(glm::vec3 position)
{
	m_position = position;
	updateTranslationMatrix();
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
	updateRotationMatrix();
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
	updateScaleMatrix();
}

glm::vec3 Entity3D::getScale()
{
	return m_scale;
}

void Entity3D::setPivot(glm::vec3 pivot)
{
	m_pivot = pivot;
	updatePivotMatrix();
}

glm::vec3 Entity3D::getPivot()
{
	return m_pivot;
}

void Entity3D::updateTranslationMatrix()
{
	// TODO
}

void Entity3D::updateRotationMatrix()
{
	// TODO
}

void Entity3D::updateScaleMatrix()
{
	// TODO
}

void Entity3D::updatePivotMatrix()
{
	// TODO
}

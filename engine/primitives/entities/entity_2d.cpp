#include "entity_2d.h"
#include <glm/gtc/matrix_transform.hpp>

using engine::Entity2D;


void Entity2D::setRotation(GLfloat angle)
{
	m_rotation = angle;
	m_rotation_rad = glm::radians(m_rotation);
	updateRotationMatrix();
}

GLfloat Entity2D::getRotation()
{
	return m_rotation;
}

void Entity2D::rotate(GLfloat angle)
{
	setRotation(m_rotation + angle);
}

void Entity2D::setRotationRad(GLfloat angle)
{
	m_rotation_rad = angle;
	m_rotation = glm::degrees(m_rotation_rad);
	updateRotationMatrix();
}

GLfloat Entity2D::getRotationRad()
{
	return m_rotation_rad;
}

void Entity2D::rotateRad(GLfloat angle)
{
	setRotationRad(m_rotation_rad + angle);
}

void Entity2D::setPosition(glm::vec2 position)
{
	m_position = position;
	updateTranslationMatrix();
}

glm::vec2 Entity2D::getPosition()
{
	return m_position;
}

void Entity2D::translate(glm::vec2 position)
{
	setPosition(m_position + position);
}

void Entity2D::setScale(GLfloat scale)
{
	m_scale = scale;
	updateScaleMatrix();
}

GLfloat Entity2D::getScale()
{
	return m_scale;
}

void Entity2D::setPivot(glm::vec2 pivot)
{
	m_pivot = pivot;
	updateTranslationMatrix();
}

glm::vec2 Entity2D::getPivot()
{
	return m_pivot;
}

void Entity2D::updateTranslationMatrix()
{
	m_translation_matrix = glm::translate(glm::mat4(), glm::vec3(m_position, 0.f));
	updateRotationMatrix();
}

void Entity2D::updateRotationMatrix()
{
	m_rotation_matrix = glm::rotate(m_translation_matrix, m_rotation_rad, glm::vec3(0.f, 0.f, 1.f));
	updateScaleMatrix();
}

void Entity2D::updateScaleMatrix()
{
	m_scale_matrix = glm::scale(m_rotation_matrix, glm::vec3(m_scale, m_scale, m_scale));
	updatePivotMatrix();
}

void Entity2D::updatePivotMatrix()
{
	m_pivot_matrix = glm::translate(m_scale_matrix, glm::vec3(-m_pivot, 0.f));
}

#include "entity_2d.h"
#include <glm/gtc/matrix_transform.hpp>

using engine::Entity2D;


Entity2D::Entity2D(glm::vec2 position, GLfloat rotation /* = 0.f */, GLfloat scale /* = 1.f */, glm::vec2 pivot /* = { 0.f, 0.f } */)
{
	setPivot(pivot);
	setRotation(rotation);
	setPosition(position);
	setScale(scale);
}

void Entity2D::rotate(GLfloat angle)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(m_pivot, 0.f));
	m_model_matrix = glm::rotate(m_model_matrix, angle, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(-m_pivot, 0.f));
	m_rotation += angle;
}

void Entity2D::setRotation(GLfloat angle)
{
	rotate(angle - m_rotation);
}

GLfloat Entity2D::getRotation()
{
	return m_rotation;
}

void Entity2D::translate(glm::vec2 position)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(position, 0.f));
	m_position += position;
}

void Entity2D::setPosition(glm::vec2 position)
{
	translate(position - m_position);
}

glm::vec2 Entity2D::getPosition()
{
	return m_position;
}

void Entity2D::setScale(GLfloat scale)
{
	//m_model_matrix = glm::mat4();
	//setPivot(m_pivot);
	//m_model_matrix = glm::scale(m_model_matrix, glm::vec3(scale, scale, 1.f));
	//setRotation(m_rotation);
	//setPosition(m_position);
	m_scale = scale;
}

GLfloat Entity2D::getScale()
{
	return m_scale;
}

void Entity2D::setPivot(glm::vec2 pivot)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(m_pivot - pivot, 0.f));
	m_pivot = pivot;
}

glm::vec2 Entity2D::getPivot()
{
	return m_pivot;
}

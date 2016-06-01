#include "entity_3d.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

using engine::Entity3D;


Entity3D::Entity3D(glm::vec3 position, glm::vec3 rotation /* = { 0.f, 0.f, 0.f } */,glm::vec3 scale /* = { 1.f, 1.f, 1.f } */, 
	glm::vec3 pivot /* = { 0.f, 0.f, 0.f } */)
{
	setPosition(position);
	setRotation(rotation);
	setScale(scale);
	setPivot(pivot);
}

Entity3D::~Entity3D()
{}

void Entity3D::translate(glm::vec3 position)
{
	m_model_matrix = glm::translate(m_model_matrix, position);
	m_position += position;
}

void Entity3D::setPosition(glm::vec3 position)
{
	translate(position - m_position);
}

glm::vec3 Entity3D::getPosition()
{
	return m_position;
}

void Entity3D::rotate(glm::vec3 rotation)
{
	m_model_matrix = glm::translate(m_model_matrix, m_pivot);
	m_model_matrix = glm::rotate(m_model_matrix, rotation.x, { 1.f, 0.f, 0.f });
	m_model_matrix = glm::rotate(m_model_matrix, rotation.y, { 0.f, 1.f, 0.f });
	m_model_matrix = glm::rotate(m_model_matrix, rotation.z, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::translate(m_model_matrix, -m_pivot);
	m_rotation += rotation;
}

void Entity3D::setRotation(glm::vec3 rotation)
{
	rotate(rotation - m_rotation);
}

glm::vec3 Entity3D::getRotation()
{
	return m_rotation;
}

void Entity3D::setScale(glm::vec3 scale)
{
	m_model_matrix = glm::translate(glm::mat4(), m_position);
	m_model_matrix = glm::scale(m_model_matrix, scale);
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation.x, { 1.f, 0.f, 0.f });
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation.y, { 0.f, 1.f, 0.f });
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation.z, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::translate(m_model_matrix, -m_pivot);
	m_scale = scale;
}

glm::vec3 Entity3D::getScale()
{
	return m_scale;
}

void Entity3D::setPivot(glm::vec3 pivot)
{
	m_model_matrix = glm::translate(m_model_matrix, m_pivot - pivot);
	m_pivot = pivot;
}

glm::vec3 Entity3D::getPivot()
{
	return m_pivot;
}

glm::mat3 Entity3D::getNormalMatrix()
{
	return glm::inverseTranspose(glm::mat3(m_model_matrix));
}

#include "entity_2d.hpp"
#include <glm/gtc/matrix_transform.hpp>


using bauasian::Texture;
using bauasian::Entity2D;


void Entity2D::translate(const glm::vec2& position)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(position, 0.f));
	m_position += position;
}

void Entity2D::setPosition(const glm::vec2& position)
{
	translate(position - m_position);
}

const glm::vec2& Entity2D::getPosition() const
{
	return m_position;
}

void Entity2D::rotate(const GLfloat& rotation)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(m_pivot, 0.f));
	m_model_matrix = glm::rotate(m_model_matrix, rotation, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(-m_pivot, 0.f));
	m_rotation += rotation;
}

void Entity2D::setRotation(const GLfloat& rotation)
{
	rotate(rotation - m_rotation);
}

GLfloat Entity2D::getRotation() const
{
	return m_rotation;
}

void Entity2D::setScale(const glm::vec2& scale)
{
	m_model_matrix = glm::translate(glm::mat4(), glm::vec3(m_position, 0.f));
	m_model_matrix = glm::scale(m_model_matrix, glm::vec3(scale.x, scale.y, 1.f));
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(-m_pivot, 0.f));
	m_scale = scale;
}

const glm::vec2& Entity2D::getScale() const
{
	return m_scale;
}

void Entity2D::setPivot(const glm::vec2& pivot)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(m_pivot - pivot, 0.f));
	m_pivot = pivot;
}

const glm::vec2& Entity2D::getPivot() const
{
	return m_pivot;
}

void Entity2D::setMaterial(bauasian::BasicMaterial* material)
{
	m_material = material;
}

void Entity2D::render() const
{
	if (m_material)
	{
		m_material->bind();
		Entity::render();
		m_material->unbind();
	}
	else
		Entity::render();
}

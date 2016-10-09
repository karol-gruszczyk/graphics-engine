#ifndef BAUASIAN_SCENE_2D_HPP
#define BAUASIAN_SCENE_2D_HPP

#include "bauasian/primitives/abstract/entity_2d.hpp"


namespace bauasian
{
	class Scene2D;
}

class bauasian::Scene2D
{
public:
	~Scene2D();

	void addEntity(Entity2D* entity);
	void render(const ShaderProgram* shader, const GLint& model_matrix_location) const;

private:
	std::list<Entity2D*> m_entities;

};

#endif /* BAUASIAN_SCENE_2D_HPP */

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "basic_material.hpp"


namespace engine
{
	class Material;
}

class engine::Material : public engine::BasicMaterial
{
public:
	Material();
	Material(const glm::vec3 &diffuse_color, float shininess = 0);
	Material(Texture *diffuse_texture, float shininess = 0);
	Material(ShaderProgram *shader);

	void setShininess(const float &shininess);

	void bind() const override;

protected:
	float m_shininess = 0.f;
};

#endif /* MATERIAL_HPP_ */

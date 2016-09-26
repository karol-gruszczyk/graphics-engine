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
	Material(ShaderProgram* shader);

	void setShininess(const float& shininess);

	void bind() const override;

protected:
	float m_shininess;
};

#endif /* MATERIAL_HPP_ */

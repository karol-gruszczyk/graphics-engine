#ifndef GRAPHICS_ENGINE_MATERIAL_HPP
#define GRAPHICS_ENGINE_MATERIAL_HPP

#include "basic_material.hpp"


namespace engine
{
	class Material;
}

class engine::Material : public engine::BasicMaterial
{
public:
	Material();
	Material(const glm::vec3& diffuse_color, float shininess = 0);
	Material(Texture* diffuse_texture, float shininess = 0);
	Material(ShaderProgram* shader);

	void setAmbient(const glm::vec3& color);
	void setAmbient(Texture* texture);
	void setSpecular(const glm::vec3& color);
	void setSpecular(Texture* texture);
	void setShininess(const float& shininess);

	void bind() const override;

protected:
	glm::vec3 m_ambient_color;
	Texture* m_ambient_texture = nullptr;
	glm::vec3 m_specular_color;
	Texture* m_specular_texture = nullptr;
	float m_shininess = 0.f;
};

#endif /* GRAPHICS_ENGINE_MATERIAL_HPP */

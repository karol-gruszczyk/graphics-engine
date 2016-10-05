#ifndef BAUASIAN_MATERIAL_HPP
#define BAUASIAN_MATERIAL_HPP

#include "basic_material.hpp"


namespace bauasian
{
	class Material;
}

class bauasian::Material : public bauasian::BasicMaterial
{
public:
	Material();
	Material(const glm::vec3& diffuse_color, float shininess = 0.f);
	Material(Texture* diffuse_texture, float shininess = 0.f);
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

#endif /* BAUASIAN_MATERIAL_HPP */

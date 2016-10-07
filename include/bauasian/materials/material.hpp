#ifndef BAUASIAN_MATERIAL_HPP
#define BAUASIAN_MATERIAL_HPP

#define AMBIENT_TEXTURE 0
#define DIFFUSE_TEXTURE 1
#define SPECULAR_TEXTURE 2

#include "basic_material.hpp"
#include "bauasian/shaders/buffers/material_buffer.hpp"

#include <memory>


namespace bauasian
{
	class Material;
}

class bauasian::Material
{
public:
	void setName(const std::string& name);
	const std::string& getName();
	void setAmbient(const glm::vec3& color);
	void setAmbient(Texture* texture);
	void setDiffuse(const glm::vec3& color);
	void setDiffuse(Texture* texture);
	void setSpecular(const glm::vec3& color);
	void setSpecular(Texture* texture);
	void setShininess(const float& shininess);

	void bind() const;

protected:
	MaterialBuffer::GlslMaterial m_material;
	Texture* m_ambient_texture = nullptr;
	Texture* m_diffuse_texture = nullptr;
	Texture* m_specular_texture = nullptr;
	std::string m_name;

};

#endif /* BAUASIAN_MATERIAL_HPP */

#ifndef BAUASIAN_MATERIAL_HPP
#define BAUASIAN_MATERIAL_HPP

#define AMBIENT_TEXTURE 0
#define DIFFUSE_TEXTURE 1
#define SPECULAR_TEXTURE 2

#include "basic_material.hpp"
#include "bauasian/shaders/uniform_buffer.hpp"

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

	static UniformBuffer* getUniformBuffer();

protected:
	struct alignas(16) UniformMaterial
	{
		glm::vec4 ambient_color = glm::vec4(1.f);
		glm::vec4 diffuse_color = glm::vec4(1.f);
		glm::vec4 specular_color = glm::vec4(1.f);

		GLint use_ambient_texture = 0;
		GLint use_diffuse_texture = 0;
		GLint use_specular_texture = 0;
		GLint use_normal_texture = 0;

		float shininess = 0.f;
	} m_material;
	Texture* m_ambient_texture = nullptr;
	Texture* m_diffuse_texture = nullptr;
	Texture* m_specular_texture = nullptr;
	std::string m_name;

};

#endif /* BAUASIAN_MATERIAL_HPP */

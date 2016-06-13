#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include <glm/glm.hpp>
#include "texture.hpp"
#include "../shaders/shader_program.hpp"


namespace engine
{
	class Material;
}

class engine::Material
{
public:
	Material(ShaderProgram* shader);
	~Material();

	void setAmbient(const glm::vec3& color);
	void setAmbient(Texture* texture);
	void setDiffuse(const glm::vec3& color);
	void setDiffuse(Texture* texture);
	void setSpecular(const glm::vec3& color);
	void setSpecular(Texture* texture);
	void setShininess(const float& shininess);

	void bind() const;
	void unbind() const;
private:
	ShaderProgram* m_shader;

	glm::vec3 m_ambient_color;
	glm::vec3 m_diffuse_color;
	glm::vec3 m_specular_color;
	Texture* m_ambient_texture;
	Texture* m_diffuse_texture;
	Texture* m_specular_texture;
	float m_shininess;
};

#endif /* MATERIAL_HPP_ */

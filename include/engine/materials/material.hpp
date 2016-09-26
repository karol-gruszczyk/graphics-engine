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

	void setDiffuse(const glm::vec3& color);
	void setDiffuse(Texture* texture);
	void setShininess(const float& shininess);

	void bind() const;
	void unbind() const;
private:
	ShaderProgram* m_shader;

	glm::vec3 m_diffuse_color = { 1.f, 1.f, 1.f };
	Texture* m_diffuse_texture;
	float m_shininess;
};

#endif /* MATERIAL_HPP_ */

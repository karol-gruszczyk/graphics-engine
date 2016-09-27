#ifndef GRAPHICS_ENGINE_BASICMATERIAL_HPP
#define GRAPHICS_ENGINE_BASICMATERIAL_HPP

#include <glm/glm.hpp>

#include "texture.hpp"
#include "../shaders/shader_program.hpp"


namespace engine
{
	class BasicMaterial;
}

class engine::BasicMaterial
{
public:
	BasicMaterial();
	BasicMaterial(const glm::vec3 &diffuse_color);
	BasicMaterial(Texture *diffuse_texture);
	BasicMaterial(ShaderProgram *shader);

	void setName(const std::string& name);
	const std::string& getName();
	void setDiffuse(const glm::vec3 &color);
	void setDiffuse(Texture *texture);

	virtual void bind() const;
	virtual void unbind() const;

	static void setDefaultShader(ShaderProgram *shader);

protected:
	ShaderProgram *m_shader;

	std::string m_name;
	glm::vec3 m_diffuse_color = { 1.f, 1.f, 1.f };
	Texture *m_diffuse_texture = nullptr;

private:
	static ShaderProgram *s_shader;
};

#endif  // GRAPHICS_ENGINE_BASICMATERIAL_HPP

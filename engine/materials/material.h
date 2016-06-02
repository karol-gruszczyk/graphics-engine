#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/glm.hpp>
#include "texture.h"
#include "../shaders/shader_program.h"


namespace engine
{
	class Material;
}

class engine::Material
{
public:
	Material(ShaderProgram* shader);
	~Material();

	void setAmbient(glm::vec3 color);
	void setAmbient(Texture* texture);
	void setDiffuse(glm::vec3 color);
	void setDiffuse(Texture* texture);
	void setSpecular(glm::vec3 color);
	void setSpecular(Texture* texture);
	void setShininess(float shininess);

	void bind();
	void unbind();
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

#endif /* MATERIAL_H_ */

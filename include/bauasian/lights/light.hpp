#ifndef BAUASIAN_LIGHT_HPP
#define BAUASIAN_LIGHT_HPP

#include <glm/glm.hpp>


namespace bauasian
{
	class Light;
}

class alignas(16) bauasian::Light
{
public:
	const glm::vec3 getAmbientColor() const;
	void setAmbientColor(const glm::vec3& color);
	const glm::vec3 getDiffuseColor() const;
	void setDiffuseColor(const glm::vec3& color);
	const glm::vec3 getSpecularColor() const;
	void setSpecularColor(const glm::vec3& color);
	void setColor(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

protected:
	glm::vec4 m_ambient_color = glm::vec4(1.f);
	glm::vec4 m_diffuse_color = glm::vec4(1.f);
	glm::vec4 m_specular_color = glm::vec4(1.f);

};

#endif /* BAUASIAN_LIGHT_HPP */

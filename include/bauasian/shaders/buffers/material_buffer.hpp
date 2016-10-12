#ifndef BAUASIAN_MATERIAL_BUFFER_HPP
#define BAUASIAN_MATERIAL_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class MaterialBuffer;
}

class bauasian::MaterialBuffer : public UniformBuffer
{
public:
	struct alignas(16) GlslMaterial
	{
		glm::vec4 ambient_color = glm::vec4(1.f);
		glm::vec4 diffuse_color = glm::vec4(1.f);
		glm::vec4 specular_color = glm::vec4(1.f);

		GLint use_ambient_texture = 0;
		GLint use_diffuse_texture = 0;
		GLint use_specular_texture = 0;
		GLint use_normal_texture = 0;
		GLint use_opacity_texture = 0;

		float shininess = 0.f;
	};

	static MaterialBuffer& getInstance();

private:
	MaterialBuffer();

};


#endif /* BAUASIAN_MATERIAL_BUFFER_HPP */

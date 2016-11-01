#ifndef BAUASIAN_BASIC_MATERIAL_BUFFER_HPP
#define BAUASIAN_BASIC_MATERIAL_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class BasicMaterialBuffer;
}

class bauasian::BasicMaterialBuffer : public UniformBuffer
{
public:
	struct alignas(16) GlslBasicMaterial
	{
		glm::vec3 diffuse_color = glm::vec3(1.f);
		GLint use_diffuse_texture = 0;
	};

	static BasicMaterialBuffer& getInstance();

private:
	BasicMaterialBuffer();

};


#endif /* BAUASIAN_BASIC_MATERIAL_BUFFER_HPP */

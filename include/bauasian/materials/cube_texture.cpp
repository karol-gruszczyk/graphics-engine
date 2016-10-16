#include "cube_texture.hpp"


using bauasian::CubeTexture;

CubeTexture::CubeTexture(const std::vector<glm::uvec2>& sizes, const std::vector<unsigned char*> pixel_ptrs,
                         const GLint& internal_format,
                         const GLenum& format, std::string image_name)
		: TextureInterface(GL_TEXTURE_CUBE_MAP, internal_format, format)
{
	assert(sizes.size() == pixel_ptrs.size() && pixel_ptrs.size() == 6);

	for (unsigned i = 0; i < 6; i++)
	{
		glTextureImage2DEXT(m_texture_id, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format,
		                    sizes[i].x, sizes[i].y, 0, format, GL_UNSIGNED_BYTE, pixel_ptrs[i]);
	}
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

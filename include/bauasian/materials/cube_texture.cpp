#include <cassert>
#include "cube_texture.hpp"


using bauasian::CubeTexture;

CubeTexture::CubeTexture(const std::vector<unsigned>& widths, const std::vector<unsigned>& heights,
                         const std::vector<unsigned char*> pixel_ptrs, const GLint& internal_format,
                         const GLenum& format, std::string image_name)
{
	assert((widths.size() == heights.size()) == (pixel_ptrs.size() == 6));

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
	for (unsigned i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format, widths[i], heights[i],
		             0, format,GL_UNSIGNED_BYTE, pixel_ptrs[i]);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

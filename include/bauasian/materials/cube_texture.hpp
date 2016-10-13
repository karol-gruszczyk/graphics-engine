#ifndef BAUASIAN_CUBE_TEXTURE_HPP
#define BAUASIAN_CUBE_TEXTURE_HPP

#include "texture_interface.hpp"

#include <string>
#include <vector>

#include <glm/glm.hpp>


namespace bauasian
{
	class CubeTexture;
}

class bauasian::CubeTexture final : public TextureInterface
{
public:
	CubeTexture(const std::vector<glm::uvec2>& sizes, const std::vector<unsigned char*> pixel_ptrs,
	            const GLint& internal_format, const GLenum& format,
	            std::string image_name = "");

};

#endif /* BAUASIAN_CUBE_TEXTURE_HPP */

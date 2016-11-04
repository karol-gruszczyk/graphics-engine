#ifndef BAUASIAN_CUBE_TEXTURE_HPP
#define BAUASIAN_CUBE_TEXTURE_HPP

#include "mixins/texture_mixin.hpp"

#include <string>
#include <vector>

#include <glm/glm.hpp>


namespace bauasian
{
	class CubeTexture;
}

class bauasian::CubeTexture final : public TextureMixin
{
public:
	CubeTexture(const std::vector<glm::uvec2>& sizes, const std::vector<unsigned char*> pixel_ptrs,
				GLint internal_format, GLenum format, std::string image_name = "");

};

#endif /* BAUASIAN_CUBE_TEXTURE_HPP */

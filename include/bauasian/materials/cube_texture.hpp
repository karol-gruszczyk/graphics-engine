#ifndef BAUASIAN_CUBE_TEXTURE_HPP
#define BAUASIAN_CUBE_TEXTURE_HPP

#include "texture_interface.hpp"

#include <string>
#include <vector>


namespace bauasian
{
	class CubeTexture;
}

class bauasian::CubeTexture final : public TextureInterface
{
public:
	CubeTexture(const std::vector<unsigned>& widths, const std::vector<unsigned>& heights,
	            const std::vector<unsigned char*> pixel_ptrs, const GLint& internal_format, const GLenum& format,
	            std::string image_name = "");

private:


};


#endif /* BAUASIAN_CUBE_TEXTURE_HPP */

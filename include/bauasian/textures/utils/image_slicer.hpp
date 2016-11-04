#ifndef BAUASIAN_IMAGE_SLICER_HPP
#define BAUASIAN_IMAGE_SLICER_HPP

#include <vector>
#include <list>

#include <glm/glm.hpp>


namespace bauasian
{
	class ImageSlicer;
}

class bauasian::ImageSlicer
{
public:
	ImageSlicer(const glm::uvec2& image_size, const unsigned char* image_pixels, unsigned bytes_per_pixel);
	~ImageSlicer();

	std::tuple<std::vector<glm::uvec2>, std::vector<unsigned char*>> getCubeTextureFaces();
	unsigned char* getSubImage(const glm::uvec2& sub_image_size, const glm::uvec2& sub_image_position);

private:
	glm::uvec2 m_image_size;
	const unsigned char* m_image_pixels;
	unsigned m_bytes_per_pixel;
	std::list<unsigned char*> m_ptrs;

};


#endif /* BAUASIAN_IMAGE_SLICER_HPP */
